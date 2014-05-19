#include "MoFgRender.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FRenderSampler, FRenderObject);

//============================================================
// <T>������Ⱦ��ȡ����</T>
//============================================================
FRenderSampler::FRenderSampler(){
   _code = -1;
   _statusUsed = EFalse;
   _slot = -1;
   _samplerCode = ERenderSampler_Unknown;
   _packCode = ERenderSampler_Unknown;
}

//============================================================
// <T>������Ⱦ��ȡ����</T>
//============================================================
FRenderSampler::~FRenderSampler(){
}

//============================================================
// <T>�������á�</T>
//
// @param pConfig ���ýڵ�
// @return ������
//============================================================
TResult FRenderSampler::LoadConfig(FXmlNode* pConfig){
   MO_CHECK(pConfig, return ENull);
   // ��������
   _name = pConfig->Get("name");
   // ���ù���
   _linker = pConfig->Get("linker");
   // ���ù���
   _source = pConfig->Get("source", NULL);
   // ��������
   _samplerCode = RRenderSampler::Parse(_linker);
   _packCode = RRenderSampler::ParsePack(_samplerCode);
   return ESuccess;
}

MO_NAMESPACE_END
