#include "MoE3Material.h"
#include "MoE3Model.h"
#include "MoE3Template.h"
#include "MoE3Instance.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FTemplate3dRenderable, FModel3dRenderable);

//============================================================
// <T>����ʵ��3D�����塣</T>
//============================================================
FTemplate3dRenderable::FTemplate3dRenderable(){
   _material = FMaterial3d::InstanceCreate();
   MO_CLEAR(_pTemplate);
   MO_CLEAR(_pModel);
   MO_CLEAR(_pGeometry);
   MO_CLEAR(_pAnimation);
   _pBones = MO_CREATE(FBone3dCollection);
}

//============================================================
// <T>����ʵ��3D�����塣</T>
//============================================================
FTemplate3dRenderable::~FTemplate3dRenderable(){
   MO_DELETE(_pBones);
}

//============================================================
// <T>����ģ�;���</T>
//
// @param matrix ģ�;���
// @return ������
//============================================================
TResult FTemplate3dRenderable::CalculateModelMatrix(SFloatMatrix3d& matrix){
   //_locker.Enter();
   // �������
   FRs3dGeometry* pGeometryResource = _pGeometry->Resource();
   FRs3dTrack* pTrack = pGeometryResource->Track();
   if(pTrack->HasFrame()){
      // ���ʱ��
      FAnimation3d* pAnimation = _pTemplate->Animation();
      TTimeTick currentTick = pAnimation->CurrentTick();
      // ����֡��Ϣ
      SRs3dFrameInfo info;
      pTrack->CalculateFrameInfo(info, currentTick);
      info.Update();
      // ׷�ӱ任
      matrix.Assign(pTrack->MatrixInvert());
      matrix.Append(info.matrix);
   }
   //_locker.Leave();
   return ESuccess;
}

//============================================================
// <T>����ģ�;���</T>
//
// @param pMatrix ���󼯺�
// @param offset λ��
// @param count ����
// @return �������
//============================================================
TInt FTemplate3dRenderable::CalculateBoneMatrix(SFloatMatrix3d* pMatrix, TInt offset, TInt capacity){
   // ����������
   if(_pBones == NULL){
      MO_FATAL("Bone is null.");
      return 0;
   }
   // �����ͷ����
   //_pAnimation->Locker().Enter();
   TInt boneCount = _pBones->Count();
   TInt count = boneCount;
   if(capacity > 0){
      count = MO_LIB_MIN(boneCount, capacity);
   }
   if(pMatrix != NULL){
      // ���ù�������
      for(TInt n = 0; n < count; n++){
         FBone3d* pBone = _pBones->Get(n);
         SFloatMatrix3d& boneMatrix = pBone->Matrix();
         SFloatMatrix3d& matrix = pMatrix[offset + n];
         matrix.Assign(boneMatrix);
      }
   }
   //_pAnimation->Locker().Leave();
   return count;
}

//============================================================
// <T>������Դ��</T>
//
// @param pResource ��Դ����
//============================================================
TResult FTemplate3dRenderable::LoadResource(FRs3dTemplateRenderable* pResource){
   MO_CHECK(pResource, return ENull);
   //............................................................
   // ����ģ��
   TCharC* pModelName = pResource->ModelName();
   _pModel = RInstance3dManager::Instance().ModelConsole()->Load(pModelName);
   MO_FATAL_CHECK(_pModel, return EFailure,
         "Model is not exists. (model=%s)", pModelName);
   //............................................................
   // ��������
   TInt geometryIndex = pResource->GeometryIndex();
   _pGeometry = _pModel->Geometrys()->Get(geometryIndex);
   MO_FATAL_CHECK(_pGeometry, return EFailure,
         "Model geometry is not exists. (model=%s, geometry_index=%d)", pModelName, geometryIndex);
   SetGeometry(_pGeometry->Geometry());
   //............................................................
   // ���ز���
   FMaterial3d* pMaterial = _materialReference->Convert<FMaterial3d>();
   GMaterial3dTexturePtrs& materialTextures = pMaterial->MaterialTextures();
   if(!materialTextures.IsEmpty()){
      GMaterial3dTexturePtrs::TIteratorC iterator = materialTextures.IteratorC();
      while(iterator.Next()){
         FMaterial3dTexture* pTexture = *iterator;
         FRs3dMaterialTexture* pTextureResource = pTexture->Resource();
         // �������
         TCharC* pCode = pTextureResource->Code();
         TCharC* pPackCode = pTextureResource->PackCode();
         FRenderTexture* pRenderTexture = pTexture->RenderTexture();
         //pRenderTexture->SetOwner(this);
         // ����ȡ����
         FRenderableSampler* pSampler = FRenderableSampler::InstanceCreate();
         pSampler->SetCode(pCode);
         pSampler->SetPackCode(pPackCode);
         pSampler->SetGraphicsObject(pRenderTexture);
         SamplerPush(pSampler);
      }
   }
   _material->AssignOption(pMaterial);
   //............................................................
   // ��������
   _modelModel.Assign(pResource->Matrix());
   //............................................................
   TFsName typeName;
   typeName.AppendFormat("%s|%d", pModelName, geometryIndex);
   SetTypeName(typeName);
   return ESuccess;
}

//============================================================
// <T>������־��</T>
//
// @������
//============================================================
TResult FTemplate3dRenderable::BuildDescriptor(){
   //// ���ù�ͷ����
   //_descriptor.vertexCount = _pVertexStreams->VertexCount();
   //if(_pBones != NULL){
   //   _descriptor.boneCount = _pBones->Count();
   //}
   //// �������Լ���
   //FRenderVertexStreamCollection* pStreams = _pVertexStreams->Streams();
   //TInt count = pStreams->Count();
   //for(TInt n = 0; n < count; n++){
   //   FRenderVertexStream* pStream = pStreams->Get(n);
   //   //TInt bufferCd = RRenderAttribute::Parse(pStream->Code());
   //   //_descriptor.vertexBuffers[bufferCd] = ETrue;
   //}
   //// ���ò��ʼ���
   //FMaterial3d* pMaterial = _material->Convert<FMaterial3d>();
   //pMaterial->BuildDescriptor(_descriptor);
   return ESuccess;
}

//============================================================
// <T>�������ʡ�</T>
//
// @return ������
//============================================================
TResult FTemplate3dRenderable::UpdateMaterial(FMaterial* pLightMaterial){
   _material->AssignValue(_materialReference);
   if(pLightMaterial != NULL){
      _material->Merge(pLightMaterial);
   }
   return ESuccess;
}

//============================================================
TResult FTemplate3dRenderable::AnsyProcess(){
   //_locker.Enter();
   //// �������
   //FRs3dGeometry* pGeometryResource = _pGeometry->Resource();
   //FRs3dTrack* pTrack = pGeometryResource->Track();
   //if(!pTrack->Frames()->IsEmpty()){
   //   // ���ʱ��
   //   FAnimation3d* pAnimation = _pTemplate->Animation();
   //   TTimeTick currentTick = pAnimation->CurrentTick();
   //   // ����֡��Ϣ
   //   SRs3dFrameInfo info;
   //   pTrack->CalculateFrameInfo(info, currentTick);
   //   info.Update();
   //   // ׷�ӱ任
   //   _frameMatrix.Assign(pTrack->MatrixInvert());
   //   _frameMatrix.Append(info.matrix);
   //}
   ////_matrix.Assign(_frameMatrix);
   ////_matrix.Append(_modelModel);
   //_locker.Leave();
   return ESuccess;
}

MO_NAMESPACE_END
