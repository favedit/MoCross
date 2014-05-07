#include "MoFgBase.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>�����ַ���Ϊö�����ݡ�</T>
//
// @param pValue �ַ���
// @param bufferCd Ĭ������
// @return ö������
//============================================================
ERenderShaderBuffer RRenderShaderBuffer::Parse(TCharC* pValue, ERenderShaderBuffer bufferCd){
   if(pValue != NULL){
      TFsCode code = pValue;
      code.ToLower();
      if(code.Equals("globalstatic")){
         return ERenderShaderBuffer_GlobalStatic;
      }else if(code.Equals("globaldynamic")){
         return ERenderShaderBuffer_GlobalDynamic;
      }else if(code.Equals("techniquestatic")){
         return ERenderShaderBuffer_TechniqueStatic;
      }else if(code.Equals("techniquedynamic")){
         return ERenderShaderBuffer_TechniqueDynamic;
      }else if(code.Equals("effectstatic")){
         return ERenderShaderBuffer_EffectStatic;
      }else if(code.Equals("effectdynamic")){
         return ERenderShaderBuffer_EffectDynamic;
      }else if(code.Equals("renderabledynamic")){
         return ERenderShaderBuffer_RenderableDynamic;
      }else if(code.Equals("renderablematerial")){
         return ERenderShaderBuffer_RenderableMaterial;
      }else{
         MO_STATIC_FATAL("Parse shader buffer type failure. (value=%s)", pValue);
      }
   }
   return bufferCd;
}

//============================================================
// <T>��������Ϊ���黺�塣</T>
//
// @param bufferCd ��������
// @return ö������
//============================================================
ERenderShaderBuffer RRenderShaderBuffer::ParseGroup(ERenderShaderBuffer bufferCd){
   switch(bufferCd){
      case ERenderShaderBuffer_Global:
      case ERenderShaderBuffer_GlobalStatic:
      case ERenderShaderBuffer_GlobalDynamic:
         return ERenderShaderBuffer_Global;
      case ERenderShaderBuffer_Technique:
      case ERenderShaderBuffer_TechniqueStatic:
      case ERenderShaderBuffer_TechniqueDynamic:
         return ERenderShaderBuffer_Technique;
      case ERenderShaderBuffer_Effect:
      case ERenderShaderBuffer_EffectStatic:
      case ERenderShaderBuffer_EffectDynamic:
         return ERenderShaderBuffer_Effect;
      case ERenderShaderBuffer_Renderable:
      case ERenderShaderBuffer_RenderableDynamic:
      case ERenderShaderBuffer_RenderableMaterial:
         return ERenderShaderBuffer_Renderable;
      default:
         MO_STATIC_FATAL("Parse shader buffer group failure. (buffer=%d)", bufferCd);
   }
   return ERenderShaderBuffer_Unknown;
}

//============================================================
// <T>��������Ϊ���λ�á�</T>
//
// @param bufferCd ��������
// @return ���λ��
//============================================================
TInt RRenderShaderBuffer::ParseSlot(ERenderShaderBuffer bufferCd){
   switch(bufferCd){
      case ERenderShaderBuffer_GlobalStatic:
         return 0;
      case ERenderShaderBuffer_GlobalDynamic:
         return 1;
      case ERenderShaderBuffer_TechniqueStatic:
         return 2;
      case ERenderShaderBuffer_TechniqueDynamic:
         return 3;
      case ERenderShaderBuffer_EffectStatic:
         return 4;
      case ERenderShaderBuffer_EffectDynamic:
         return 5;
      case ERenderShaderBuffer_RenderableDynamic:
         return 6;
      case ERenderShaderBuffer_RenderableMaterial:
         return 7;
      default:
         MO_STATIC_FATAL("Parse shader buffer group failure. (buffer=%d)", bufferCd);
   }
   return ERenderShaderBuffer_Unknown;
}

//============================================================
// <T>��ʽ��ö������Ϊ�ַ�����</T>
//
// @param bufferCd ö������
// @return �ַ���
//============================================================
TCharC* RRenderShaderBuffer::Format(ERenderShaderBuffer bufferCd){
   switch(bufferCd){
      case ERenderShaderBuffer_GlobalStatic:
         return "GlobalStatic";
      case ERenderShaderBuffer_GlobalDynamic:
         return "GlobalDynamic";
      case ERenderShaderBuffer_TechniqueStatic:
         return "TechniqueStatic";
      case ERenderShaderBuffer_TechniqueDynamic:
         return "TechniqueDynamic";
      case ERenderShaderBuffer_EffectStatic:
         return "EffectStatic";
      case ERenderShaderBuffer_EffectDynamic:
         return "EffectDynamic";
      case ERenderShaderBuffer_RenderableDynamic:
         return "RenderableDynamic";
      case ERenderShaderBuffer_RenderableMaterial:
         return "RenderableMaterial";
   }
   return "Unknown";
}

MO_NAMESPACE_END
