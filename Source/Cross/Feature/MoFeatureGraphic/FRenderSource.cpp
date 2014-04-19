#include "MoFgRender.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>������Ⱦ��Դ��</T>
//============================================================
FRenderSource::FRenderSource(){
}

//============================================================
// <T>������Ⱦ��Դ��</T>
//============================================================
FRenderSource::~FRenderSource(){
}

//============================================================
// <T>׷��ע����Ϣ��</T>
//
// @param pFormat ��ʽ
// @param ... ����
// @return ������
//============================================================
TResult FRenderSource::AppendCommet(TChar8C* pFormat, ...){
   // ������
   MO_CHECK(pFormat, return ENull);
   // ׷������
   va_list params;
   va_start(params, pFormat);
   AppendFormatParameters(pFormat, params);
   va_end(params);
   return ESuccess;
}

//============================================================
// <T>׷�Ӵ�����Ϣ��</T>
//
// @param pFormat ��ʽ
// @param ... ����
// @return ������
//============================================================
TResult FRenderSource::AppendSource(TChar8C* pFormat, ...){
   // ������
   MO_CHECK(pFormat, return ENull);
   // ׷������
   va_list params;
   va_start(params, pFormat);
   AppendFormatParameters(pFormat, params);
   va_end(params);
   return ESuccess;
}

//============================================================
// <T>������Ⱦ��Դ��</T>
//
// @return �ַ���
//============================================================
TCharC* FRenderSource::Build(){
   return MemoryC();
}

MO_NAMESPACE_END
