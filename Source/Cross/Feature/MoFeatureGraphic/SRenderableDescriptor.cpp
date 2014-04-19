#include "MoFgBase.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>������Ⱦ��־��</T>
//============================================================
SRenderableDescriptor::SRenderableDescriptor(){
   setuped = EFalse;
   Reset();
}

//============================================================
// <T>���ô���</T>
//
// @return ������
//============================================================
void SRenderableDescriptor::Assign(SRenderableDescriptor* pFlags){
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
   MO_LIB_MEMORY_COPY(pFlags->vertexBuffers, sizeof(pFlags->vertexBuffers), vertexBuffers, sizeof(vertexBuffers));
   // ����ȡ������Ϣ
   MO_LIB_MEMORY_COPY(pFlags->samplers, sizeof(pFlags->samplers), samplers, sizeof(samplers));
}

//============================================================
// <T>��������</T>
//============================================================
void SRenderableDescriptor::Build(){
   // ֧�ֶ�����ɫ����
   if(vertexBuffers[ERenderVertexBuffer_Color]){
      supportVertexColor = ETrue;
   }
   // ֧���������꼼��
   if(vertexBuffers[ERenderVertexBuffer_Coord]){
      supportVertexCoord = ETrue;
   }
   // ֧�ַ��߼���
   if(vertexBuffers[ERenderVertexBuffer_Normal]){
      supportVertexNormal = ETrue;
   }
   // ֧��ȫ���߼���
   if(vertexBuffers[ERenderVertexBuffer_Normal] && vertexBuffers[ERenderVertexBuffer_Binormal] && vertexBuffers[ERenderVertexBuffer_Tangent]){
      supportVertexNormalFull = ETrue;
   }
   // ֧�ֹ�ͷ����
   if(vertexBuffers[ERenderVertexBuffer_BoneIndex] && vertexBuffers[ERenderVertexBuffer_BoneWeight]){
      supportVertexBone = ETrue;
   }
   //............................................................
   // ֧�ֻ����⼼��
   supportAmbient = ETrue;
   // ֧�������似��
   if(supportVertexCoord && samplers[ERenderSampler_Diffuse]){
      supportDiffuse = ETrue;
   }
   // ֧�ַ��߼���
   if(supportVertexNormal){
      supportNormal = ETrue;
   }
   // ֧�ְ�͹����
   if(supportVertexCoord && supportVertexNormalFull && samplers[ERenderSampler_Normal]){
      supportBump = ETrue;
   }
   // ֧�ָ߹���ɫ����
   if(supportVertexCoord && supportVertexNormal & samplers[ERenderSampler_SpecularColor]){
      supportSpecularColor = ETrue;
   }
   // ֧�ָ߹⼶����
   if(supportVertexCoord && supportVertexNormal & samplers[ERenderSampler_SpecularLevel]){
      supportSpecularLevel = ETrue;
   }
   // ֧�ֻ����⼼��
   if(supportVertexNormal & samplers[ERenderSampler_Environment]){
      supportEnvironment = ETrue;
   }
   // ֧���ܹ⼼��
   if(supportVertexCoord && samplers[ERenderSampler_Light]){
      supportLight = ETrue;
   }
   // ֧�ַ��似��
   if(supportVertexCoord && samplers[ERenderSampler_Reflect]){
      supportReflect = ETrue;
   }
   // ֧�����似��
   if(supportVertexCoord && samplers[ERenderSampler_Refract]){
      supportRefract = ETrue;
   }
   // ֧�ַ��⼼��
   if(supportVertexCoord && samplers[ERenderSampler_Emissive]){
      supportEmissive = ETrue;
   }
   // ֧�ָ߶ȼ���
   if(supportVertexCoord && samplers[ERenderSampler_Height]){
      supportHeight = ETrue;
   }
   // �����ɹ�
   setuped = ETrue;
}

//============================================================
// <T>���ô���</T>
//============================================================
void SRenderableDescriptor::Reset(){
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
   // ���ò���֧��
   supportAlpha = EFalse;
   supportBump = EFalse;
   supportAmbient = EFalse;
   supportDiffuse = EFalse;
   supportNormal = EFalse;
   supportSpecularColor = EFalse;
   supportSpecularLevel = EFalse;
   supportReflect = EFalse;
   supportEnvironment = EFalse;
   supportLight = EFalse;
   supportReflect = EFalse;
   supportRefract = EFalse;
   supportEmissive = EFalse;
   supportHeight = EFalse;
   //supportDiffuseCamera = EFalse;
   //supportBumpCamera = EFalse;
   //supportSpecularCamera = EFalse;
   //supportSpecularCameraLevel = EFalse;
   // ���ö������
   vertexCount = 0;
   // ���ù�ͷ����
   boneCount = 0;
   // ���ö��㻺����Ϣ
   RBools::Fill(vertexBuffers, ERenderVertexBuffer_Count, EFalse);
   // ����ȡ������Ϣ
   RBools::Fill(samplers, ERenderSampler_Count, EFalse);
}

MO_NAMESPACE_END
