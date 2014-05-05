#include "MoFgRender.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FRenderShaderSampler, FRenderObject);

//============================================================
// <T>������Ⱦ��ȡ����</T>
//============================================================
FRenderShaderSampler::FRenderShaderSampler(){
   _code = -1;
   _statusUsed = EFalse;
   _slot = -1;
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
   _source = pConfig->Get("source", NULL);
   return ESuccess;
}

MO_NAMESPACE_END
