#include "MoEoTechnique.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>������롣</T>
//============================================================
static TCharC* SourceVertexShader =
      "uniform mat4 vc_mvp_matrix; \n"
      "attribute vec4 va_position; \n"
      "attribute vec4 va_color; \n"
      "attribute vec2 va_coord; \n"
      "varying vec4 v_color; \n"
      "varying vec2 v_coord; \n"
      "void main(){ \n"
      "   gl_Position = va_position * vc_mvp_matrix; \n"
      "   v_color = va_color; \n"
      "   v_coord = va_coord; \n"
      "} \n";

//============================================================
// <T>���ش��롣</T>
//============================================================
static TCharC* SourceFragmentShader =
#ifdef _MO_ANDROID
      "precision mediump float; \n"
#endif // _MO_ANDROID
      "varying vec4 v_color; \n"
      "varying vec2 v_coord; \n"
      "uniform sampler2D fs_color; \n"
      "void main(){ \n"
      "   gl_FragColor = v_color * texture2D(fs_color, v_coord); \n"
      "} \n";

//============================================================
// <T>������ʾ��Ⱦ������</T>
//============================================================
FEo2dTextureEffect::FEo2dTextureEffect(){
   _limitCount = 16384;
   _count = 0;
   MO_CLEAR(_pVertexPositionBuffer);
   _pPositionData = MO_CREATE(FDataStream);
   MO_CLEAR(_pVertexColorBuffer);
   _pColorData = MO_CREATE(FDataStream);
   MO_CLEAR(_pVertexCoordBuffer);
   _pCoordData = MO_CREATE(FDataStream);
   MO_CLEAR(_pIndexBuffer);
   // �������
   for(TInt n = 0; n < EEffectVertexAttribute_Count; n++){
      _effectAttributes[n] = -1;
   }
   for(TInt n = 0; n < EEffectSampler_Count; n++){
      _effectSamplers[n] = -1;
   }
}

//============================================================
// <T>������ʾ��Ⱦ������</T>
//============================================================
FEo2dTextureEffect::~FEo2dTextureEffect(){
   MO_DELETE(_pVertexPositionBuffer);
   MO_DELETE(_pPositionData);
   MO_DELETE(_pVertexColorBuffer);
   MO_DELETE(_pColorData);
   MO_DELETE(_pVertexCoordBuffer);
   MO_DELETE(_pCoordData);
   MO_DELETE(_pIndexBuffer);
}

//============================================================
// <T>���ô���</T>
//============================================================
TResult FEo2dTextureEffect::Setup(){
   FScreenDevice* pScreenDevice = RDeviceManager::Instance().Find<FScreenDevice>();
   FRenderDevice* pRenderDevice = RDeviceManager::Instance().Find<FRenderDevice>();
   //............................................................
   // ����MVP����
   SIntSize2& screenSize = pScreenDevice->Size();
   _mvpMatrix.tx = -1;
   _mvpMatrix.ty = 1;
   _mvpMatrix.rx = MO_PI_FLOAT;
   _mvpMatrix.sx = 2.0f / (TFloat)screenSize.width;
   _mvpMatrix.sy = 2.0f / (TFloat)screenSize.height;
   _mvpMatrix.UpdateForce();
   //............................................................
   // ��������
   FEoRenderProgram* pProgram = (FEoRenderProgram*)pRenderDevice->CreateProgrom();
   pProgram->Setup();
   pProgram->VertexShader()->Compile(SourceVertexShader);
   pProgram->FragmentShader()->Compile(SourceFragmentShader);
   pProgram->Build();
   // �󶨳���λ��
   GLuint progromId = pProgram->ProgramId();
	//_effectConsts[EEffectVertexConst_MvpMat4] = glGetUniformLocation(progromId, "vc_mvp_matrix");
   // ������λ��
   glBindAttribLocation(progromId, EEffectVertexAttribute_Position, "va_position");
   glBindAttribLocation(progromId, EEffectVertexAttribute_Color, "va_color");
   glBindAttribLocation(progromId, EEffectVertexAttribute_Coord, "va_coord");
   // ������λ��
   _effectSamplers[EEffectSampler_Diffuse] = glGetUniformLocation(progromId, "fs_color");
   // �����������
   _program = pProgram;
   //............................................................
   // ����������
   TInt vertexCount = 4 * _limitCount;
   for(TInt n = 0; n < _limitCount; n++){
      // д���1����
      _pPositionData->WriteFloat4(0.0f, 0.0f, 0.0f, 1.0f);
      _pColorData->WriteByte4(255, 255, 255, 255);
      _pCoordData->WriteFloat2(0.0f, 0.0f);
      // д���2����
      _pPositionData->WriteFloat4(1.0f, 0.0f, 0.0f, 1.0f);
      _pColorData->WriteByte4(255, 255, 255, 255);
      _pCoordData->WriteFloat2(1.0f, 0.0f);
      // д���3����
      _pPositionData->WriteFloat4(1.0f, 1.0f, 0.0f, 1.0f);
      _pColorData->WriteByte4(255, 255, 255, 255);
      _pCoordData->WriteFloat2(1.0f, 1.0f);
      // д���4����
      _pPositionData->WriteFloat4(0.0f, 1.0f, 0.0f, 1.0f);
      _pColorData->WriteByte4(255, 255, 255, 255);
      _pCoordData->WriteFloat2(0.0f, 1.0f);
   }
   // �ϴ�����λ��
   _pVertexPositionBuffer = (FEoRenderVertexBuffer*)pRenderDevice->CreateVertexBuffer();
   _pVertexPositionBuffer->SetCount(vertexCount);
   _pVertexPositionBuffer->SetStride(4 * 4);
   _pVertexPositionBuffer->Setup();
   _pVertexPositionBuffer->Upload(_pPositionData->Memory(), _pPositionData->Length());
   // �ϴ�������ɫ
   _pVertexColorBuffer = (FEoRenderVertexBuffer*)pRenderDevice->CreateVertexBuffer();
   _pVertexColorBuffer->SetCount(vertexCount);
   _pVertexColorBuffer->SetStride(1 * 4);
   _pVertexColorBuffer->Setup();
   _pVertexColorBuffer->Upload(_pColorData->Memory(), _pColorData->Length());
   // �ϴ�������������
   _pVertexCoordBuffer = (FEoRenderVertexBuffer*)pRenderDevice->CreateVertexBuffer();
   _pVertexCoordBuffer->SetCount(vertexCount);
   _pVertexCoordBuffer->SetStride(4 * 2);
   _pVertexCoordBuffer->Setup();
   _pVertexCoordBuffer->Upload(_pCoordData->Memory(), _pCoordData->Length());
   //............................................................
   // ����������
   TInt vertexIndex = 0;
   _pIndexBuffer = (FEoRenderIndexBuffer*)pRenderDevice->CreateIndexBuffer();
   _pIndexBuffer->SetCount(6 * _limitCount);
   _pIndexBuffer->Setup();
   FByteStream* pIndexData = MO_CREATE(FByteStream);
   for(TInt n = 0; n < _limitCount; n++){
      // ��һ��������
      pIndexData->WriteUint16(vertexIndex + 0);
      pIndexData->WriteUint16(vertexIndex + 2);
      pIndexData->WriteUint16(vertexIndex + 1);
      // �ڶ���������
      pIndexData->WriteUint16(vertexIndex + 0);
      pIndexData->WriteUint16(vertexIndex + 3);
      pIndexData->WriteUint16(vertexIndex + 2);
      // �����������
      vertexIndex += 4;
   }
   _pIndexBuffer->Upload(pIndexData->Memory(), pIndexData->Length());
   MO_DELETE(pIndexData);
   return ESuccess;
}

//============================================================
// <T>���¿�ʼ����</T>
//============================================================
TResult FEo2dTextureEffect::UpdateBegin(){
   _count = 0;
   _pPositionData->Reset();
   _pColorData->Reset();
   _pCoordData->Reset();
   return ESuccess;
}

//============================================================
// <T>д�����Ⱦ����</T>
//
// @param pRenderable ����Ⱦ����
//============================================================
TResult FEo2dTextureEffect::WriteRenderable(FRenderable* pRenderable){
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
      // �������
      _pCoordData->WriteFloat2(coord.x1, coord.y1);
      _pCoordData->WriteFloat2(coord.x2, coord.y1);
      _pCoordData->WriteFloat2(coord.x2, coord.y2);
      _pCoordData->WriteFloat2(coord.x1, coord.y2);
   }
   // ����������
   _count += count;
   return ESuccess;
}

//============================================================
// <T>���½�������</T>
//============================================================
TResult FEo2dTextureEffect::UpdateEnd(){
   // �ϴ���������
   _pVertexPositionBuffer->Upload(_pPositionData->MemoryC(), _pPositionData->Position());
   _pVertexColorBuffer->Upload(_pColorData->MemoryC(), _pColorData->Position());
   _pVertexCoordBuffer->Upload(_pCoordData->MemoryC(), _pCoordData->Position());
   return ESuccess;
}

//============================================================
// <T>�����С��</T>
//
// @return ������
//============================================================
TResult FEo2dTextureEffect::Resize(TInt width, TInt height){
   // ����MVP����
   _mvpMatrix.tx = -1;
   _mvpMatrix.ty = 1;
   _mvpMatrix.rx = MO_PI_FLOAT;
   _mvpMatrix.sx = 2.0f / (TFloat)width;
   _mvpMatrix.sy = 2.0f / (TFloat)height;
   _mvpMatrix.UpdateForce();
   return ESuccess;
}

//============================================================
// <T>���ƴ���</T>
//============================================================
TResult FEo2dTextureEffect::Draw(){
   //// �����豸״̬
   //FRenderDevice* pRenderDevice = RDeviceManager::Instance().RenderDevice();
   //pRenderDevice->SetDepthMode(_pMaterial->OptionDepth());
   //pRenderDevice->SetBlendFactors(_pMaterial->OptionAlpha(), _pMaterial->BlendSourceMode(), _pMaterial->BlendTargetMode());
   ////............................................................
   //// �趨����
   //pRenderDevice->SetProgram(_program);
   //// ���ó���
   //pRenderDevice->BindConstMatrix3d(ERenderShader_Vertex, _effectConsts[EEffectVertexConst_MvpMatrix], _mvpMatrix);
   //// �趨������
   //pRenderDevice->BindVertexBuffer(EEffectVertexAttribute_Position, _pVertexPositionBuffer, 0, ERenderVertexFormat_Float4);
   //pRenderDevice->BindVertexBuffer(EEffectVertexAttribute_Color, _pVertexColorBuffer, 0, ERenderVertexFormat_ByteNormal4);
   //pRenderDevice->BindVertexBuffer(EEffectVertexAttribute_Coord, _pVertexCoordBuffer, 0, ERenderVertexFormat_Float2);
   ////............................................................
   //// ��������
   //if(_pMaterial->HasTexture()){
   //   FTextureCollection* pTextures = _pMaterial->Textures();
   //   TInt count = pTextures->Count();
   //   for(TInt n = 0; n < count; n++){
   //      // �������
   //      ITexture* pTexture = pTextures->Get(n);
   //      FRenderTexture* pRenderTexture = pTexture->RenderTexture();
   //      // ������
   //      ERenderSampler slotCd = pRenderTexture->SlotCd();
   //      if(slotCd == ERenderSampler_Diffuse){
   //         pRenderDevice->BindTexture(_effectSamplers[EEffectSampler_Color], pRenderTexture);
   //      }
   //   }
   //}
   ////............................................................
   //// ����������������������
   //pRenderDevice->DrawTriangles(_pIndexBuffer, 0, 6 * _count);
   return ESuccess;
}

MO_NAMESPACE_END
