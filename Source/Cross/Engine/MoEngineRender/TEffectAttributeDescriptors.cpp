#include "MoErTechnique.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>����Ч�������������ϡ�</T>
//============================================================
TEffectAttributeDescriptors::TEffectAttributeDescriptors(){
}

//============================================================
// <T>ע��һ��������Ϣ��</T>
//
// @param code ����
// @param pName ����
// @param formatCd ��ʽ
//============================================================
void TEffectAttributeDescriptors::Register(TInt code, TCharC* pName, ERenderVertexFormat formatCd){
   SEffectAttributeDescriptor descriptor;
   descriptor.code = code;
   descriptor.namePtr = pName;
   descriptor.formatCd = formatCd;
   descriptor.bindIndex = _count;
   Push(descriptor);
}

MO_NAMESPACE_END
