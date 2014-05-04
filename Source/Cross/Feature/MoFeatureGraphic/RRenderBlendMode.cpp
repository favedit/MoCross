#include "MoFgBase.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>�����ַ���Ϊö�����ݡ�</T>
//
// @param pValue �ַ���
// @param blendModeCd Ĭ������
// @return ö������
//============================================================
ERenderBlendMode RRenderBlendMode::Parse(TCharC* pValue, ERenderBlendMode blendModeCd){
   if(pValue != NULL){
      TFsCode code = pValue;
      code.ToLower();
      if(code.Equals("none")){
         return ERenderBlendMode_None;
      }else if(code.Equals("sourcealpha")){
         return ERenderBlendMode_SourceAlpha;
      }else if(code.Equals("oneminussourcealpha")){
         return ERenderBlendMode_OneMinusSourceAlpha;
      }else{
         MO_STATIC_FATAL("Parse blend mode failure. (value=%s)", pValue);
      }
   }
   return blendModeCd;
}

//============================================================
// <T>��ʽ��ö������Ϊ�ַ�����</T>
//
// @param blendModeCd ö������
// @return �ַ���
//============================================================
TCharC* RRenderBlendMode::Format(ERenderBlendMode blendModeCd){
   switch(blendModeCd){
      case ERenderBlendMode_None:
         return "None";
      case ERenderBlendMode_SourceAlpha:
         return "SourceAlpha";
      case ERenderBlendMode_OneMinusSourceAlpha:
         return "OneMinusSourceAlpha";
      default:
         break;
   }
   return "Unknown";
}

MO_NAMESPACE_END
