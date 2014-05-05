#include "MoPoe2Technique.h"

MO_NAMESPACE_BEGIN

#define MO_3D_BONE_MAXCNT 20

//============================================================
// <T>������롣</T>
//============================================================
static TCharC* SourceVertexShader =
      "uniform mat4 vc_mvp_matrix; \n"
      "uniform mat4 vc_bone_matrixs[20]; \n"
      "attribute vec4 va_position; \n"
      "attribute vec4 va_color; \n"
      "attribute vec2 va_coord; \n"
      "attribute vec4 va_bone_index; \n"
      "attribute vec4 va_bone_weight; \n"
      "varying vec4 v_color; \n"
      "varying vec2 v_coord; \n"
      "void main(){ \n"
      "   vec4 position = vec4(0, 0, 0, 0); \n"
      "   position += va_position * vc_bone_matrixs[int(va_bone_index.x)] * va_bone_weight.x; \n"
      "   position += va_position * vc_bone_matrixs[int(va_bone_index.y)] * va_bone_weight.y; \n"
      "   position += va_position * vc_bone_matrixs[int(va_bone_index.z)] * va_bone_weight.z; \n"
      "   position += va_position * vc_bone_matrixs[int(va_bone_index.w)] * va_bone_weight.w; \n"
      "   gl_Position = position * vc_mvp_matrix; \n"
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
      "   vec4 color = texture2D(fs_color, v_coord); \n"
      "   if(color.a < 0.1){ discard; } \n"
      "   gl_FragColor = color * v_color; \n"
      "} \n";

//============================================================
// <T>������ʾ��Ⱦ������</T>
//============================================================
FPoe23dSkeleton4Effect::FPoe23dSkeleton4Effect(){
   _pBoneStream = MO_CREATE(FByteStream);
   // �������
   //for(TInt n = 0; n < EEffectVertexAttribute_Count; n++){
   //   _effectAttributes[n] = -1;
   //}
   //for(TInt n = 0; n < EEffectSampler_Count; n++){
   //   _effectSamplers[n] = -1;
   //}
}

//============================================================
// <T>������ʾ��Ⱦ������</T>
//============================================================
FPoe23dSkeleton4Effect::~FPoe23dSkeleton4Effect(){
   MO_DELETE(_pBoneStream);
}

//============================================================
// <T>���ô���</T>
//============================================================
TResult FPoe23dSkeleton4Effect::Setup(){
 //  FScreenDevice* pScreenDevice = RDeviceManager::Instance().Find<FScreenDevice>();
 //  FRenderDevice* pRenderDevice = RDeviceManager::Instance().Find<FRenderDevice>();
 //  //............................................................
 //  // ����MVP����
 //  SIntSize2& screenSize = pScreenDevice->Size();
 //  Resize(screenSize.width, screenSize.height);
 //  //............................................................
 //  // ��������
 //  FPoe2RenderProgram* pProgram = (FPoe2RenderProgram*)pRenderDevice->CreateProgrom();
 //  pProgram->Setup();
 //  pProgram->VertexShader()->Compile(SourceVertexShader);
 //  pProgram->FragmentShader()->Compile(SourceFragmentShader);
 //  pProgram->Build();
 //  // �󶨳���λ��
 ////  GLuint progromId = pProgram->ProgramId();
	////_effectConsts[EEffectVertexConst_MvpMat4] = glGetUniformLocation(progromId, "vc_mvp_matrix");
 ////  _effectConsts[EEffectVertexConst_BoneMatrixs] = glGetUniformLocation(progromId, "vc_bone_matrixs");
 ////  // ������λ��
 ////  _effectAttributes[EEffectVertexAttribute_Position] = glGetAttribLocation(progromId, "va_position");
 ////  _effectAttributes[EEffectVertexAttribute_Color] = glGetAttribLocation(progromId, "va_color");
 ////  _effectAttributes[EEffectVertexAttribute_Coord] = glGetAttribLocation(progromId, "va_coord");
 ////  _effectAttributes[EEffectVertexAttribute_BoneIndex] = glGetAttribLocation(progromId, "va_bone_index");
 ////  _effectAttributes[EEffectVertexAttribute_BoneWeight] = glGetAttribLocation(progromId, "va_bone_weight");
 ////  // ������λ��
 ////  _effectSamplers[EEffectSampler_Color] = glGetUniformLocation(progromId, "fs_color");
 //  // �����������
 //  _program = pProgram;
   return ESuccess;
}

//============================================================
// <T>�����С��</T>
//
// @return ������
//============================================================
TResult FPoe23dSkeleton4Effect::Resize(TInt width, TInt height){
   // ����MVP����
   _mvpMatrix.tx = -1.0f;
   _mvpMatrix.ty = 1.0f;
   //_mvpMatrix.rx = MO_PI_FLOAT;
   _mvpMatrix.sx = 2.0f / (TFloat)width;
   _mvpMatrix.sy = 2.0f / (TFloat)height;
   _mvpMatrix.UpdateForce();
   return ESuccess;
}

//============================================================
// <T>���ƴ���</T>
//
// @param pRenderable ��Ⱦ����
// @return ������
//============================================================
TResult FPoe23dSkeleton4Effect::Draw(FRenderRegion* pRegion, FRenderable* pRenderable){
   // ����豸
   //FRenderDevice* pRenderDevice = RDeviceManager::Instance().RenderDevice();
   //FTemplate3dRenderable* pTemplateRenderable = (FTemplate3dRenderable*)pRenderable;
   //SFloatMatrix3d& renderableMatrix = pTemplateRenderable->Matrix();
   //FAnimation3d* pAnimation = pTemplateRenderable->Template()->Animation();
   //TTimeTick currentTick = pAnimation->CurrentTick();
   //FRs3dGeometry* pGeometryResource =  pTemplateRenderable->GeometryResource();
   //FRs3dVertexBuffer* pVertexBuffer = pGeometryResource->VertexBuffer();
   //// ����ģ�;���
   //SFloatMatrix3d modelMatrix;
   //FRs3dTrack* pTrack = pTemplateRenderable->GeometryResource()->Track();
   //if(!pTrack->Frames()->IsEmpty()){
   //   SRs3dFrameInfo info;
   //   pTrack->CalculateFrameInfo(info, currentTick);
   //   info.Update();
   //   modelMatrix.Assign(pTrack->MatrixInvert());
   //   modelMatrix.Append(info.matrix);
   //}
   //// ����MVP����
   //SFloatMatrix3d matrixMvp;
   //matrixMvp.Assign(modelMatrix);
   //matrixMvp.Append(renderableMatrix);
   //matrixMvp.Append(_vpMatrix);
   //// ���ù���
   //FBone3dCollection* pBones = pTemplateRenderable->Bones();
   //TInt boneCount = pBones->Count();
   //_pBoneStream->Reset();
   //for(TInt n = 0; n < boneCount; n++){
   //   FBone3d* pBone = pBones->Get(n);
   //   SFloatMatrix3d& boneMatrix = pBone->Matrix();
   //   boneMatrix.SerializeData4x4(_pBoneStream, ETrue);
   //}
   //............................................................
   // ���ó���
   //pRenderDevice->BindConstMatrix4x4(ERenderShader_Vertex, _effectConsts[EEffectVertexConst_MvpMat4], matrixMvp);
   //pRenderDevice->BindConstData(ERenderShader_Vertex, _effectConsts[EEffectVertexConst_BoneMatrixs], ERenderShaderParameterFormat_Matrix, _pBoneStream->MemoryC(), _pBoneStream->Position());
   //............................................................
   // �趨������
   //FRs3dVertexStream* pPositionStream = pVertexBuffer->FindStream(ERenderVertexBuffer_Position);
   //pRenderDevice->BindVertexBuffer(_effectAttributes[EEffectVertexAttribute_Position], pPositionStream->VertexBuffer(), 0, ERenderVertexFormat_Float4);
   //FRs3dVertexStream* pColorStream = pVertexBuffer->FindStream(ERenderVertexBuffer_Color);
   //pRenderDevice->BindVertexBuffer(_effectAttributes[EEffectVertexAttribute_Color], pColorStream->VertexBuffer(), 0, ERenderVertexFormat_ByteNormal4);
   //FRs3dVertexStream* pCoordStream = pVertexBuffer->FindStream(ERenderVertexBuffer_Coord);
   //pRenderDevice->BindVertexBuffer(_effectAttributes[EEffectVertexAttribute_Coord], pCoordStream->VertexBuffer(), 0, ERenderVertexFormat_Float2);
   //FRs3dVertexStream* pBoneIndexStream = pVertexBuffer->FindStream(ERenderVertexBuffer_BoneIndex);
   //pRenderDevice->BindVertexBuffer(_effectAttributes[EEffectVertexAttribute_BoneIndex], pBoneIndexStream->VertexBuffer(), 0, ERenderVertexFormat_Byte4);
   //FRs3dVertexStream* pBoneWeightStream = pVertexBuffer->FindStream(ERenderVertexBuffer_BoneWeight);
   //pRenderDevice->BindVertexBuffer(_effectAttributes[EEffectVertexAttribute_BoneWeight], pBoneWeightStream->VertexBuffer(), 0, ERenderVertexFormat_ByteNormal4);
   ////............................................................
   //// ��������
   //FMaterial3d* pMaterial = (FMaterial3d*)pTemplateRenderable->Material();
   //FMaterialTexture3d* pTexture = pMaterial->MaterialTextures()->Get(0);
   //FBitmap* pBitmap = pTexture->Bitmap();
   //pRenderDevice->BindTexture(_effectSamplers[EEffectSampler_Diffuse], pBitmap->RenderTexture());
   ////............................................................
   //// ����������������������
   //FRs3dIndexBuffer* pRsIndexBuffer = pGeometryResource->IndexBuffer();
   //FRenderIndexBuffer* pIndexBuffer = pRsIndexBuffer->IndexBuffer();
   //pRenderDevice->DrawTriangles(pIndexBuffer, 0, 3 * pRsIndexBuffer->Count());
   //glDisableVertexAttribArray(_effectAttributes[EEffectVertexAttribute_Position]);
   //glDisableVertexAttribArray(_effectAttributes[EEffectVertexAttribute_Color]);
   //glDisableVertexAttribArray(_effectAttributes[EEffectVertexAttribute_Coord]);
   //glDisableVertexAttribArray(_effectAttributes[EEffectVertexAttribute_BoneIndex]);
   //glDisableVertexAttribArray(_effectAttributes[EEffectVertexAttribute_BoneWeight]);
   return ESuccess;
}

//============================================================
// <T>������Ⱦ�鴦��</T>
//
// @param pRenderables ��Ⱦ���󼯺�
// @param offset λ��
// @param count ����
// @return ������
//============================================================
TResult FPoe23dSkeleton4Effect::DrawGroup(FRenderRegion* pRegion, TInt offset, TInt count){
   //MO_CHECK(pRegion, return ENull);
   //// ����任����
   //FCamera3d* pCamera = (FCamera3d*)pRegion->Camera();
   //_vpMatrix.Assign(pCamera->Matrix());
   //FProjection3d* pProjection = (FProjection3d*)pRegion->Projection();
   //_vpMatrix.Append(pProjection->Matrix());
   //// �����豸״̬
   //FRenderDevice* pRenderDevice = RDeviceManager::Instance().RenderDevice();
   //pRenderDevice->SetDepthMode(ETrue, ERenderDepthMode_Less);
   //// pRenderDevice->SetCullingMode(EFalse);
   //pRenderDevice->SetBlendFactors(ETrue, ERenderBlendMode_SourceAlpha, ERenderBlendMode_OneMinusSourceAlpha);
   //pRenderDevice->SetProgram(_program);
   ////............................................................
   //// ������Ⱦ���ͽ��з���
   //FRenderableCollection* pRenderables = pRegion->Renderables();
   //TInt offsetEnd = offset + count;
   //for(TInt n = offset; n < offsetEnd; n++){
   //   FRenderable* pRenderable = pRenderables->Get(n);
   //   Draw(pRegion, pRenderable);
   //}
   ////............................................................
   //// �رճ���
   //pRenderDevice->SetProgram(NULL);
   return ESuccess;
}

MO_NAMESPACE_END
