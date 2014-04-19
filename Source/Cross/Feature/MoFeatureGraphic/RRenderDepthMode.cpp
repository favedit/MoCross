#include "MoFgBase.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>�����ַ���Ϊö�����ݡ�</T>
//
// @param pValue �ַ���
// @param depthModeCd Ĭ������
// @return ö������
//============================================================
ERenderDepthMode RRenderDepthMode::Parse(TCharC* pValue, ERenderDepthMode depthModeCd){
   if(pValue != NULL){
      TFsCode code = pValue;
      code.ToLower();
      if(code.Equals("equal")){
         return ERenderDepthMode_Equal;
      }else if(code.Equals("notequal")){
         return ERenderDepthMode_NotEqual;
      }else if(code.Equals("less")){
         return ERenderDepthMode_Less;
      }else if(code.Equals("lessequal")){
         return ERenderDepthMode_LessEqual;
      }else if(code.Equals("greater")){
         return ERenderDepthMode_Greater;
      }else if(code.Equals("greaterequal")){
         return ERenderDepthMode_GreaterEqual;
      }else if(code.Equals("always")){
         return ERenderDepthMode_Always;
      }else{
         MO_STATIC_FATAL("Parse depth mode failure. (value=%s)", pValue);
      }
   }
   return depthModeCd;
}

//============================================================
// <T>��ʽ��ö������Ϊ�ַ�����</T>
//
// @param depthModeCd ö������
// @return �ַ���
//============================================================
TCharC* RRenderDepthMode::Format(ERenderDepthMode depthModeCd){
   switch(depthModeCd){
      case ERenderDepthMode_Equal:
         return "Equal";
      case ERenderDepthMode_NotEqual:
         return "NotEqual";
      case ERenderDepthMode_Less:
         return "Less";
      case ERenderDepthMode_LessEqual:
         return "LessEqual";
      case ERenderDepthMode_Greater:
         return "Greater";
      case ERenderDepthMode_GreaterEqual:
         return "GreaterEqual";
      case ERenderDepthMode_Always:
         return "Always";
      default:
         break;
   }
   return "None";
}

MO_NAMESPACE_END
