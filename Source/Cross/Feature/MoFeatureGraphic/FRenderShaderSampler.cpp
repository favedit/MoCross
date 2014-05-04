#include "MoFgRender.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FRenderShaderSampler, FRenderObject);

//============================================================
// <T>������Ⱦ��ȡ����</T>
//============================================================
FRenderShaderSampler::FRenderShaderSampler(){
}

//============================================================
// <T>������Ⱦ��ȡ����</T>
//============================================================
FRenderShaderSampler::~FRenderShaderSampler(){
}

//============================================================
// <T>�������á�</T>
//
// @param pConfig ���ýڵ�
// @return ������
//============================================================
TResult FRenderShaderSampler::LoadConfig(FXmlNode* pConfig){
   MO_CHECK(pConfig, return ENull);
   // ��������
   _name = pConfig->Get("name");
   // ���ù���
   _linker = pConfig->Get("linker");
   // ���ù���
   _source = pConfig->Get("source");
   return ESuccess;
}

MO_NAMESPACE_END
