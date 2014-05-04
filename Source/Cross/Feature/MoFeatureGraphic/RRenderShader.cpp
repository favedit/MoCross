#include "MoFgBase.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>�����ַ���Ϊö�����ݡ�</T>
//
// @param pValue �ַ���
// @param shaderCd Ĭ������
// @return ö������
//============================================================
ERenderShader RRenderShader::Parse(TCharC* pValue, ERenderShader shaderCd){
   if(pValue != NULL){
      TFsCode code = pValue;
      code.ToLower();
      if(code.Equals("unknown")){
         return ERenderShader_Unknown;
      }else if(code.Equals("vertex")){
         return ERenderShader_Vertex;
      }else if(code.Equals("fragment")){
         return ERenderShader_Fragment;
      }else{
         MO_STATIC_FATAL("Parse shader failure. (value=%s)", pValue);
      }
   }
   return shaderCd;
}

//============================================================
// <T>��ʽ��ö������Ϊ�ַ�����</T>
//
// @param shaderCd ö������
// @return �ַ���
//============================================================
TCharC* RRenderShader::Format(ERenderShader shaderCd){
   switch(shaderCd){
      case ERenderShader_Vertex:
         return "Vertex";
      case ERenderShader_Fragment:
         return "Fragment";
      default:
         break;
   }
   return "Unknown";
}

MO_NAMESPACE_END
