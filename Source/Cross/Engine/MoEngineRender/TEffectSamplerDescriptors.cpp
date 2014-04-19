#include "MoErTechnique.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>����Ч��ȡ�����������ϡ�</T>
//============================================================
TEffectSamplerDescriptors::TEffectSamplerDescriptors(){
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
