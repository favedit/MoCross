#include "MoFgTechnique.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>������Ⱦ������Ϣ��</T>
//============================================================
SEffectDescriptor::SEffectDescriptor(){
   MO_CLEAR(namePtr);
   // ����״̬
   fillModeCd = ERenderFillMode_Fill;
   optionCullMode = ETrue;
   cullModeCd = ERenderCullMode_Front;
   optionDepthTest = ETrue;
   depthModeCd = ERenderDepthMode_Less;
   optionDepthWrite = ETrue;
   optionBlendMode = EFalse;
   blendSourceMode = ERenderBlendMode_SourceAlpha;
   blendTargetMode = ERenderBlendMode_OneMinusSourceAlpha;
   optionAlphaTest = EFalse;
   // ����ģʽ
   supportInstance = EFalse;
   supportVertexColor = EFalse;
   supportVertexCoord = EFalse;
   supportVertexNormal = EFalse;
   supportVertexNormalFull = EFalse;
   supportSkeleton = EFalse;
   // ����ģʽ
   supportAlpha = EFalse;
   supportBump = EFalse;
   supportAmbient = EFalse;
   supportDiffuse = EFalse;
   supportDiffuseView = EFalse;
   supportSpecularColor = EFalse;
   supportSpecularLevel = EFalse;
   supportSpecularView = EFalse;
   supportEnvironment = EFalse;
   supportLight = EFalse;
   supportReflect = EFalse;
   supportRefract = EFalse;
   supportEmissive = EFalse;
   supportHeight = EFalse;
}

//============================================================
// <T>����������Ϣ��</T>
//============================================================
TResult SEffectDescriptor::LoadConfig(FXmlNode* pConfig){
   TXmlNodeIteratorC iterator = pConfig->NodeIteratorC();
   while(iterator.Next()){
      FXmlNode* pNode = *iterator;
      // ��ȡ״̬
      if(pNode->IsName("State")){
         TFsName name = pNode->Get("name");
         if(name.Equals("fill_mode")){
            // ������ģʽ
            TCharC* pValue = pNode->Get("value");
            fillModeCd = RRenderFillMode::Parse(pValue);
         }else if(name.Equals("cull_mode")){
            // ����޳�ģʽ
            TCharC* pValue = pNode->Get("value");
            cullModeCd = RRenderCullMode::Parse(pValue);
            optionCullMode = (cullModeCd != ERenderCullMode_None);
         }else if(name.Equals("depth_mode")){
            // �����Ȳ���
            TCharC* pValue = pNode->Get("value");
            depthModeCd = RRenderDepthMode::Parse(pValue);
            optionDepthTest = (depthModeCd != ERenderDepthMode_None);
         }else if(name.Equals("depth_write")){
            // ������д��
            optionDepthWrite = pNode->GetAsBool("value", optionDepthWrite);
         }else if(name.Equals("blend_mode")){
            // ����ں�ģʽ
            optionBlendMode = pNode->GetAsBool("value", optionBlendMode);
            if(optionBlendMode){
               TCharC* pSource = pNode->Get("source");
               blendSourceMode = RRenderBlendMode::Parse(pSource);
               TCharC* pTarget = pNode->Get("target");
               blendTargetMode = RRenderBlendMode::Parse(pTarget);
            }
         }else if(name.Equals("alpha_test")){
            // ���͸������
            optionAlphaTest = pNode->GetAsBool("value", optionAlphaTest);
         }
      }
   }
   return ESuccess;
}

MO_NAMESPACE_END
