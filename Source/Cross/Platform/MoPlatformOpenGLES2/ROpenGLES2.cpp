#include "MoEoRender.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>ת���ϳɷ�ʽ��</T>
//
// @param blendCd �ϳɷ�ʽ
// @return ������
//============================================================
GLenum ROpenGLES2::ConvertBlendFactors(ERenderBlendMode blendCd){
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
GLenum ROpenGLES2::ConvertIndexStride(ERenderIndexStride strideCd){
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
