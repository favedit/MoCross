#include "MoFgBase.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>�����ַ���Ϊö�����ݡ�</T>
//
// @param pValue �ַ���
// @param scriptCd Ĭ������
// @return ö������
//============================================================
ERenderScript RRenderScript::Parse(TCharC* pValue, ERenderScript scriptCd){
   if(pValue != NULL){
      TFsCode code = pValue;
      code.ToLower();
      if(code.Equals("unknown")){
         return ERenderScript_Unknown;
      }else if(code.Equals("hlsl")){
         return ERenderScript_Hlsl;
      }else if(code.Equals("glsl")){
         return ERenderScript_Glsl;
      }else{
         MO_STATIC_FATAL("Parse render device failure. (value=%s)", pValue);
      }
   }
   return scriptCd;
}

//============================================================
// <T>��ʽ��ö������Ϊ�ַ�����</T>
//
// @param scriptCd ö������
// @return �ַ���
//============================================================
TCharC* RRenderScript::Format(ERenderScript scriptCd){
   switch(scriptCd){
      case ERenderScript_Hlsl:
         return "Hlsl";
      case ERenderScript_Glsl:
         return "Glsl";
   }
   return "Unknown";
}

MO_NAMESPACE_END
