#include "MoPoCore.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>ת�����ģʽ���͡�</T>
//
// @param fillCd ���ģʽ
// @return ������
//============================================================
GLenum ROpenGL::ConvertFillMode(ERenderFillMode fillCd){
   switch(fillCd){
      case ERenderFillMode_Point:
         return GL_POINT;
      case ERenderFillMode_Line:
         return GL_LINE;
      case ERenderFillMode_Fill:
         return GL_FILL;
   }
   MO_STATIC_FATAL("Convert fill mode failure. (fill=%d)", fillCd);
   return GL_FILL;
}

//============================================================
// <T>ת���޳�ģʽ���͡�</T>
//
// @param cullCd �޳�ģʽ
// @return ������
//============================================================
GLenum ROpenGL::ConvertCullMode(ERenderCullMode cullCd){
   switch(cullCd){
      case ERenderCullMode_Front:
         return GL_FRONT;
      case ERenderCullMode_Back:
         return GL_BACK;
      case ERenderCullMode_Both:
         return GL_FRONT_AND_BACK;
   }
   MO_STATIC_FATAL("Convert cull mode failure. (cull=%d)", cullCd);
   return ERenderCullMode_Front;
}

//============================================================
// <T>ת�����ģʽ���͡�</T>
//
// @param depthCd ���ģʽ
// @return ������
//============================================================
GLenum ROpenGL::ConvertDepthMode(ERenderDepthMode depthCd){
   switch(depthCd){
      case ERenderDepthMode_Equal:
         return GL_EQUAL;
      case ERenderDepthMode_NotEqual:
         return GL_NOTEQUAL;
      case ERenderDepthMode_Less:
         return GL_LESS;
      case ERenderDepthMode_LessEqual:
         return GL_LEQUAL;
      case ERenderDepthMode_Greater:
         return GL_GREATER;
      case ERenderDepthMode_GreaterEqual:
         return GL_GEQUAL;
      case ERenderDepthMode_Always:
         return GL_ALWAYS;
   }
   MO_STATIC_FATAL("Convert depth mode failure. (depth=%d)", depthCd);
   return GL_LESS;
}

//============================================================
// <T>ת���ϳɷ�ʽ��</T>
//
// @param blendCd �ϳɷ�ʽ
// @return ������
//============================================================
GLenum ROpenGL::ConvertBlendFactors(ERenderBlendMode blendCd){
   switch(blendCd){
      case ERenderBlendMode_SourceAlpha:
         return GL_SRC_ALPHA;
      case ERenderBlendMode_OneMinusSourceAlpha:
         return GL_ONE_MINUS_SRC_ALPHA;
      default:
         break;
   }
   MO_STATIC_FATAL("Convert blend factors failure. (blend=%d)", blendCd);
   return 0;
}

//============================================================
// <T>ת������������͡�</T>
//
// @param strideCd �������
// @return ������
//============================================================
GLenum ROpenGL::ConvertIndexStride(ERenderIndexStride strideCd){
   switch(strideCd){
      case ERenderIndexStride_Uint16:
         return GL_UNSIGNED_SHORT;
      case ERenderIndexStride_Uint32:
         return GL_UNSIGNED_INT;
   }
   MO_STATIC_FATAL("Convert index stride failure. (stride=%d)", strideCd);
   return 0;
}

MO_NAMESPACE_END
