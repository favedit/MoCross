#include "MoErTechnique.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>����Ч�������������ϡ�</T>
//============================================================
TEffectConstDescriptors::TEffectConstDescriptors(){
   _count = _capacity;
}

//============================================================
// <T>ע��һ��������Ϣ��</T>
//
// @param shaderCd ��Ⱦ����
// @param code ����
// @param pName ����
//============================================================
void TEffectConstDescriptors::Register(ERenderShader shaderCd, TInt code, TCharC* pName){
   SEffectConstDescriptor& descriptor = _memory[code];
   descriptor.shaderCd = shaderCd;
   descriptor.code = code;
   descriptor.namePtr = pName;
   descriptor.bindId = -1;
}

MO_NAMESPACE_END
