#include "MoFgBase.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>�����ַ���Ϊö�����ݡ�</T>
//
// @param pValue �ַ���
// @param formatCd Ĭ������
// @return ö������
//============================================================
ERenderShaderAttributeFormat RRenderShaderAttributeFormat::Parse(TCharC* pValue, ERenderShaderAttributeFormat formatCd){
   if(pValue != NULL){
      TFsCode code = pValue;
      code.ToLower();
      if(code.Equals("unknown")){
         return ERenderShaderAttributeFormat_Unknown;
      }else if(code.Equals("float1")){
         return ERenderShaderAttributeFormat_Float1;
      }else if(code.Equals("float2")){
         return ERenderShaderAttributeFormat_Float2;
      }else if(code.Equals("float3")){
         return ERenderShaderAttributeFormat_Float3;
      }else if(code.Equals("float4")){
         return ERenderShaderAttributeFormat_Float4;
      }else if(code.Equals("byte4")){
         return ERenderShaderAttributeFormat_Byte4;
      }else if(code.Equals("byte4normal")){
         return ERenderShaderAttributeFormat_Byte4Normal;
      }else{
         MO_STATIC_FATAL("Parse shader attribute format failure. (value=%s)", pValue);
      }
   }
   return formatCd;
}

//============================================================
// <T>��ʽ��ö������Ϊ�ַ�����</T>
//
// @param formatCd ö������
// @return �ַ���
//============================================================
TCharC* RRenderShaderAttributeFormat::Format(ERenderShaderAttributeFormat formatCd){
   switch(formatCd){
      case ERenderShaderAttributeFormat_Float1:
         return "Float1";
      case ERenderShaderAttributeFormat_Float2:
         return "Float2";
      case ERenderShaderAttributeFormat_Float3:
         return "Float3";
      case ERenderShaderAttributeFormat_Float4:
         return "Float4";
      case ERenderShaderAttributeFormat_Byte4:
         return "Byte4";
      case ERenderShaderAttributeFormat_Byte4Normal:
         return "Byte4Normal";
      default:
         break;
   }
   return "Unknown";
}

MO_NAMESPACE_END
