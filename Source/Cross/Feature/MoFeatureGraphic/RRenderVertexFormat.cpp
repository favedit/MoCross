#include "MoFgBase.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>�����ַ���Ϊö�����ݡ�</T>
//
// @param pValue �ַ���
// @param formatCd Ĭ������
// @return ö������
//============================================================
ERenderVertexFormat RRenderVertexFormat::Parse(TCharC* pValue, ERenderVertexFormat formatCd){
   if(pValue != NULL){
      TFsCode code = pValue;
      code.ToLower();
      if(code.Equals("float1")){
         return ERenderVertexFormat_Float1;
      }else if(code.Equals("float2")){
         return ERenderVertexFormat_Float2;
      }else if(code.Equals("float3")){
         return ERenderVertexFormat_Float3;
      }else if(code.Equals("float4")){
         return ERenderVertexFormat_Float4;
      }else if(code.Equals("byte4")){
         return ERenderVertexFormat_Byte4;
      }else if(code.Equals("bytenormal4")){
         return ERenderVertexFormat_ByteNormal4;
      }else{
         MO_STATIC_FATAL("Parse vertex format failure. (value=%s)", pValue);
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
TCharC* RRenderVertexFormat::Format(ERenderVertexFormat formatCd){
   switch(formatCd){
      case ERenderVertexFormat_Float1:
         return "Float1";
      case ERenderVertexFormat_Float2:
         return "Float2";
      case ERenderVertexFormat_Float3:
         return "Float3";
      case ERenderVertexFormat_Float4:
         return "Float4";
      case ERenderVertexFormat_Byte4:
         return "Byte4";
      case ERenderVertexFormat_ByteNormal4:
         return "ByteNormal4";
      default:
         break;
   }
   return "Unknown";
}

MO_NAMESPACE_END
