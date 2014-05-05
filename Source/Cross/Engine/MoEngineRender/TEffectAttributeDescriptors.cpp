#include "MoErCore.h"

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

//============================================================
// <T>ע��һ��������Ϣ��</T>
//
// @param pLinker ������Ϣ
//============================================================
TResult TEffectAttributeDescriptors::Link(FRenderShaderAttribute* pAttribute){
   MO_CHECK(pAttribute, return ENull);
   TCharC* pLinker = pAttribute->Linker();
   // ��������
   EEffectAttribute attributeCd = EEffectAttribute_Unknown;
   ERenderShaderAttributeFormat formatCd = ERenderShaderAttributeFormat_Unknown;
   REffectAttribute::Parse(pLinker, attributeCd, formatCd);
   pAttribute->SetFormatCd(formatCd);
   // ���ò���
   SEffectAttributeDescriptor descriptor;
   descriptor.attributePtr = pAttribute;
   descriptor.code = attributeCd;
   descriptor.namePtr = pLinker;
   descriptor.bindId = pAttribute->Slot();
   Push(descriptor);
   return ESuccess;
}

MO_NAMESPACE_END
