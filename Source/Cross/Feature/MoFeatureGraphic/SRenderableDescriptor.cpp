#include "MoFgBase.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>������Ⱦ��־��</T>
//============================================================
SRenderableDescriptor::SRenderableDescriptor(){
   Reset();
}

//============================================================
// <T>���ô���</T>
//
// @return ������
//============================================================
TResult SRenderableDescriptor::Assign(SRenderableDescriptor* pFlags){
   MO_ASSERT(pFlags);
   // ��������
   //optionMaterial = pFlags->optionMaterial;
   //optionBinder = pFlags->optionBinder;
   //optionInstanced = pFlags->optionInstanced;
   //optionBoneScale = pFlags->optionBoneScale;
   //optionNormalScale = pFlags->optionNormalScale;
   //optionNormalFull = pFlags->optionNormalFull;
   //optionDepth = pFlags->optionDepth;
   //optionShadowSelf = pFlags->optionShadowSelf;
   //optionLightMap = pFlags->optionLightMap;
   //optionTransmittance = pFlags->optionTransmittance;
   // ���ö��㻺����Ϣ
   //MO_LIB_MEMORY_COPY(pFlags->vertexBuffers, sizeof(pFlags->vertexBuffers), vertexBuffers, sizeof(vertexBuffers));
   // ����ȡ������Ϣ
   //MO_LIB_MEMORY_COPY(pFlags->samplers, sizeof(pFlags->samplers), samplers, sizeof(samplers));
   return ESuccess;
}

//============================================================
// <T>���ô���</T>
//
// @return ������
//============================================================
TResult SRenderableDescriptor::Reset(){
   // ������������
   optionInstanced = EFalse;
   optionBinder = EFalse;
   optionMaterial = EFalse;
   //optionNormal = EFalse;
   //optionNormalFull = EFalse;
   //optionNormalScale = EFalse;
   //optionBoneScale = EFalse;
   //optionDepth = EFalse;
   optionShadow = EFalse;
   optionShadowSelf = EFalse;
   //optionLightMap = EFalse;
   //optionTransmittance = EFalse;
   // ��������֧��
   supportVertexColor = EFalse;
   supportVertexCoord = EFalse;
   supportVertexNormal = EFalse;
   supportVertexNormalFull = EFalse;
   supportVertexBone = EFalse;
   // ���ö������
   vertexCount = 0;
   // ���ù�ͷ����
   boneCount = 0;
   return ESuccess;
}

MO_NAMESPACE_END
