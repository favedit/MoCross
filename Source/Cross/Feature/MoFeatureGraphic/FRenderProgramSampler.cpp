#include "MoFgRender.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FRenderProgramSampler, FRenderInstance);

//============================================================
// <T>������Ⱦ��ȡ����</T>
//============================================================
FRenderProgramSampler::FRenderProgramSampler(){
   _statusUsed = EFalse;
   _slot = -1;
   _index = -1;
}

//============================================================
// <T>������Ⱦ��ȡ����</T>
//============================================================
FRenderProgramSampler::~FRenderProgramSampler(){
}

//============================================================
// <T>�������á�</T>
//
// @param pConfig ���ýڵ�
// @return ������
//============================================================
TResult FRenderProgramSampler::LoadConfig(FXmlNode* pConfig){
   MO_CHECK(pConfig, return ENull);
   // ��������
   _name = pConfig->Get("name");
   // ���ù���
   _linker = pConfig->Get("linker");
   // ���ù���
   _source = pConfig->Get("source", NULL);
   return ESuccess;
}

//============================================================
// <T>����ڲ�������Ϣ��</T>
//
// @param pDump �������
// @return ������
//============================================================
TResult FRenderProgramSampler::Dump(MString* pDump, TBool detail){
   MO_CHECK(pDump, return ENull);
   pDump->AppendFormat("Sampler: name=%s, linker=%s, used=%d, slot=%d, index=%d", (TCharC*)_name, (TCharC*)_linker, _statusUsed, _slot, _index);
   return ESuccess;
}

MO_NAMESPACE_END
