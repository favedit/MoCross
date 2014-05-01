#include "MoEoTechnique.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>������롣</T>
//============================================================
static TCharC* SourceVertexShader =
      "uniform mat4 c_mvp_matrix; \n"
      "attribute vec4 a_position; \n"
      "attribute vec4 a_color; \n"
      "varying vec4 v_color; \n"
      "void main(){ \n"
      "   gl_Position = a_position * c_mvp_matrix; \n"
      "   v_color = a_color; \n"
      "} \n";

//============================================================
// <T>���ش��롣</T>
//============================================================
static TCharC* SourceFragmentShader =
#ifdef _MO_ANDROID
      "precision mediump float; \n"
#endif // _MO_ANDROID
      "varying vec4 v_color; \n"
      "void main(){ \n"
      "   gl_FragColor = v_color; \n"
      "} \n";

//============================================================
// <T>������ʾ��ɫ��Ⱦ����</T>
//============================================================
FEo2dColorEffect::FEo2dColorEffect(){
   _limitCount = 16384;
   _count = 0;
   MO_CLEAR(_pVertexPositionBuffer);
   _pPositionData = MO_CREATE(FDataStream);
   MO_CLEAR(_pVertexColorBuffer);
   _pColorData = MO_CREATE(FDataStream);
   MO_CLEAR(_pIndexBuffer);
}

//============================================================
// <T>������ʾ��ɫ��Ⱦ����</T>
//============================================================
FEo2dColorEffect::~FEo2dColorEffect(){
   MO_DELETE(_pVertexPositionBuffer);
   MO_DELETE(_pPositionData);
   MO_DELETE(_pVertexColorBuffer);
   MO_DELETE(_pColorData);
   MO_DELETE(_pIndexBuffer);
}

//============================================================
// <T>���ô���</T>
//============================================================
TResult FEo2dColorEffect::Setup(){
   FRenderDevice* pRenderDevice = RDeviceManager::Instance().Find<FRenderDevice>();
   // ��������
   FEoRenderProgram* pProgram = (FEoRenderProgram*)pRenderDevice->CreateProgrom();
   pProgram->Setup();
   pProgram->VertexShader()->Compile(SourceVertexShader);
   pProgram->FragmentShader()->Compile(SourceFragmentShader);
   pProgram->Build();
   // �󶨳���λ��
   GLuint progromId = pProgram->ProgramId();
	//_effectConsts[EEffectVertexConst_MvpMat4] = glGetUniformLocation(progromId, "c_mvp_matrix");
   // ������λ��
   glBindAttribLocation(progromId, EEffectVertexAttribute_Position, "a_position");
   glBindAttribLocation(progromId, EEffectVertexAttribute_Color, "a_color");
   // �����������
   _program = pProgram;
   // ����������
   for(TInt n = 0; n < _limitCount; n++){
      // д���1����
      _pPositionData->WriteFloat4(0.0f, 0.0f, 0.0f, 1.0f);
      _pColorData->WriteByte4(255, 255, 255, 255);
      // д���2����
      _pPositionData->WriteFloat4(1.0f, 0.0f, 0.0f, 1.0f);
      _pColorData->WriteByte4(255, 255, 255, 255);
      // д���3����
      _pPositionData->WriteFloat4(1.0f, 1.0f, 0.0f, 1.0f);
      _pColorData->WriteByte4(255, 255, 255, 255);
      // д���4����
      _pPositionData->WriteFloat4(0.0f, 1.0f, 0.0f, 1.0f);
      _pColorData->WriteByte4(255, 255, 255, 255);
   }
   // �ϴ�����λ��
   _pVertexPositionBuffer = (FEoRenderVertexBuffer*)pRenderDevice->CreateVertexBuffer();
   _pVertexPositionBuffer->SetCount(4 * _limitCount);
   _pVertexPositionBuffer->SetStride(4 * 4);
   _pVertexPositionBuffer->Setup();
   _pVertexPositionBuffer->Upload(_pPositionData->Memory(), _pPositionData->Length());
   // �ϴ�������ɫ
   _pVertexColorBuffer = (FEoRenderVertexBuffer*)pRenderDevice->CreateVertexBuffer();
   _pVertexColorBuffer->SetCount(4 * _limitCount);
   _pVertexColorBuffer->SetStride(1 * 4);
   _pVertexColorBuffer->Setup();
   _pVertexColorBuffer->Upload(_pColorData->Memory(), _pColorData->Length());
   // ����������
   _pIndexBuffer = (FEoRenderIndexBuffer*)pRenderDevice->CreateIndexBuffer();
   _pIndexBuffer->SetCount(6 * _limitCount);
   _pIndexBuffer->Setup();
   FByteStream* pIndexData = MO_CREATE(FByteStream);
   for(TInt n = 0; n < _limitCount; n++){
      TInt index = 4 * n;
      // ��һ��������
      pIndexData->WriteUint16(index + 0);
      pIndexData->WriteUint16(index + 2);
      pIndexData->WriteUint16(index + 1);
      // �ڶ���������
      pIndexData->WriteUint16(index + 0);
      pIndexData->WriteUint16(index + 3);
      pIndexData->WriteUint16(index + 2);
   }
   _pIndexBuffer->Upload(pIndexData->Memory(), pIndexData->Length());
   MO_DELETE(pIndexData);
   return ESuccess;
}

//============================================================
// <T>���¿�ʼ����</T>
//============================================================
TResult FEo2dColorEffect::UpdateBegin(){
   _limitCount = 0;
   _count = 0;
   _pPositionData->Reset();
   _pColorData->Reset();
   return ESuccess;
}

//============================================================
// <T>д�����Ⱦ����</T>
//
// @param pRenderable ����Ⱦ����
//============================================================
TResult FEo2dColorEffect::WriteRenderable(FRenderable* pRenderable){
   // �������
   if(_count >= _limitCount){
      return EFailure;
   }
   // ��������
   SRenderable renderable;
   //pRenderable->CalculateRenderable(renderable);
   TInt count = renderable.items.Count();
   for(TInt n = 0; n < count; n++){
      SRenderableItem& item = renderable.items.Get(n);
      // ����λ��
      SFloatPoint3& location = item.location;
      SFloatSize3& size = item.size;
      SFloatVector3& rotation = item.rotation;
      SFloatCoord& coord = item.coord;
      SFloatMatrix3d& matrix = item.matrix;
      // ��������
      SFloatPoint3 p1 = matrix.TransformPoint3(0, 0, 0);
      SFloatPoint3 p2 = matrix.TransformPoint3(size.width, 0, 0);
      SFloatPoint3 p3 = matrix.TransformPoint3(size.width, size.height, 0);
      SFloatPoint3 p4 = matrix.TransformPoint3(0, size.height, 0);
      // ���λ��
      _pPositionData->WriteFloat4(location.x + p1.x, location.y + p1.y, location.z, 1.0f);
      _pPositionData->WriteFloat4(location.x + p2.x, location.y + p2.y, location.z, 1.0f);
      _pPositionData->WriteFloat4(location.x + p3.x, location.y + p3.y, location.z, 1.0f);
      _pPositionData->WriteFloat4(location.x + p4.x, location.y + p4.y, location.z, 1.0f);
      // �����ɫ
      SFloatColor4& groundColor = item.groundColor;
      for(TInt n = 0; n < 4; n++){
         _pColorData->WriteInt8((TByte)(255 * groundColor.red));
         _pColorData->WriteInt8((TByte)(255 * groundColor.green));
         _pColorData->WriteInt8((TByte)(255 * groundColor.blue));
         _pColorData->WriteInt8((TByte)(255 * groundColor.alpha));
      }
   }
   // ����������
   _count += count;
   return ESuccess;
}

//============================================================
// <T>���½�������</T>
//============================================================
TResult FEo2dColorEffect::UpdateEnd(){
   // �ϴ���������
   _pVertexPositionBuffer->Upload(_pPositionData->MemoryC(), _pPositionData->Position());
   _pVertexColorBuffer->Upload(_pColorData->MemoryC(), _pColorData->Position());
   return ESuccess;
}

//============================================================
// <T>�����С��</T>
//
// @return ������
//============================================================
TResult FEo2dColorEffect::Resize(TInt width, TInt height){
   // ����MVP����
   _mvpMatrix.tx = -1;
   _mvpMatrix.ty = 1;
   _mvpMatrix.rx = MO_PI_FLOAT;
   _mvpMatrix.sx = 2.0f / (TFloat)width;
   _mvpMatrix.sy = 2.0f / (TFloat)height;
   _mvpMatrix.Update();
   return ESuccess;
}

//============================================================
// <T>���ƴ���</T>
//============================================================
TResult FEo2dColorEffect::Draw(){
   //// �������
   //FRenderDevice* pRenderDevice = RDeviceManager::Instance().RenderDevice();
   //// �趨����
   //FEoRenderProgram* pProgram = (FEoRenderProgram*)_program;
   //pRenderDevice->SetProgram(_program);
   //// ���ó���
   //pRenderDevice->BindConstMatrix3d(ERenderShader_Vertex, _effectConsts[EEffectVertexConst_MvpMatrix], _mvpMatrix);
   //// �趨������
   //pRenderDevice->BindVertexBuffer(EEffectVertexAttribute_Position, _pVertexPositionBuffer, 0, ERenderVertexFormat_Float4);
   //pRenderDevice->BindVertexBuffer(EEffectVertexAttribute_Color, _pVertexColorBuffer, 0, ERenderVertexFormat_Byte4);
   //// ����������������������
   //pRenderDevice->DrawTriangles(_pIndexBuffer, 0, 6 * _count);
   return ESuccess;
}

MO_NAMESPACE_END
