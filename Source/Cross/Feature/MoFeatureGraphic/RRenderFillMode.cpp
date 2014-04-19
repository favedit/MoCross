#include "MoFgBase.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>�����ַ���Ϊö�����ݡ�</T>
//
// @param pValue �ַ���
// @param fillModeCd Ĭ������
// @return ö������
//============================================================
ERenderFillMode RRenderFillMode::Parse(TCharC* pValue, ERenderFillMode fillModeCd){
   if(pValue != NULL){
      TFsCode code = pValue;
      code.ToLower();
      if(code.Equals("point")){
         return ERenderFillMode_Point;
      }else if(code.Equals("line")){
         return ERenderFillMode_Line;
      }else if(code.Equals("fill")){
         return ERenderFillMode_Fill;
         MO_STATIC_FATAL("Parse fill mode failure. (value=%s)", pValue);
      }
   }
   return fillModeCd;
}

//============================================================
// <T>��ʽ��ö������Ϊ�ַ�����</T>
//
// @param fillModeCd ö������
// @return �ַ���
//============================================================
TCharC* RRenderFillMode::Format(ERenderFillMode fillModeCd){
   switch (fillModeCd){
      case ERenderFillMode_Point:
         return "Point";
      case ERenderFillMode_Line:
         return "Line";
      case ERenderFillMode_Fill:
         return "Fill";
      default:
         break;
   }
   return "Unknown";
}

MO_NAMESPACE_END
