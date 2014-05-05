#include "MoErCore.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>����Ч��ȡ�����������ϡ�</T>
//============================================================
TEffectSamplerDescriptors::TEffectSamplerDescriptors(){
   _count = _capacity;
}

//============================================================
// <T>ע��һ��������Ϣ��</T>
//
// @param code ����
// @param pName ����
// @param samplerCd ȡ������
//============================================================
void TEffectSamplerDescriptors::Register(TInt code, TCharC* pName, ERenderSampler samplerCd){
   SEffectSamplerDescriptor descriptor;
   descriptor.code = code;
   descriptor.namePtr = pName;
   descriptor.samplerCd = samplerCd;
   Push(descriptor);
}

//============================================================
// <T>ע��һ��������Ϣ��</T>
//
// @param pLinker ������Ϣ
//============================================================
TResult TEffectSamplerDescriptors::Link(FRenderShaderSampler* pSampler){
   MO_CHECK(pSampler, return ENull);
   TCharC* pLinker = pSampler->Linker();
   // ��������
   ERenderSampler samplerCd = RRenderSampler::Parse(pLinker);
   ERenderSampler packCd = RRenderSampler::ParsePack(samplerCd);
   // ���ò���
   SEffectSamplerDescriptor& descriptor = _memory[packCd];
   descriptor.samplerPtr = pSampler;
   descriptor.code = samplerCd;
   descriptor.namePtr = pLinker;
   descriptor.samplerCd = samplerCd;
   descriptor.bindId = pSampler->Slot();
   return ESuccess;
}

//============================================================
SEffectSamplerDescriptor* TEffectSamplerDescriptors::FindByBindId(TInt bindId){
   for(TInt n = 0; n < MO_EG_EFFECT_SAMPLER_MAXCNT; n++){
      SEffectSamplerDescriptor& descriptor = _memory[n];
      if(descriptor.bindId == bindId){
         return &descriptor;
      }
   }
   return NULL;
}

MO_NAMESPACE_END
