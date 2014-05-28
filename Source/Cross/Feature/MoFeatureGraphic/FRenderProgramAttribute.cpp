#include "MoFgRender.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FRenderProgramAttribute, FRenderInstance);

//============================================================
// <T>������Ⱦ�����ԡ�</T>
//============================================================
FRenderProgramAttribute::FRenderProgramAttribute(){
   _index = -1;
   _slot = -1;
   _formatCd = ERenderAttributeFormat_Unknown;
   _statusUsed = EFalse;
}

//============================================================
// <T>������Ⱦ�����ԡ�</T>
//============================================================
FRenderProgramAttribute::~FRenderProgramAttribute(){
}

//============================================================
// <T>�������á�</T>
//
// @param pConfig ���ýڵ�
// @return ������
//============================================================
TResult FRenderProgramAttribute::LoadConfig(FXmlNode* pConfig){
   MO_CHECK(pConfig, return ENull);
   // ��������
   _name = pConfig->Get("name");
   // ���ù���
   _linker = pConfig->Get("linker");
   // ���ø�ʽ
   TCharC* pFormat = pConfig->Get("format", NULL);
   if(pFormat != NULL){
      _formatCd = RRenderAttributeFormat::Parse(pFormat);
   }
   return ESuccess;
}

//============================================================
// <T>����ڲ�������Ϣ��</T>
//
// @param pDump �������
// @return ������
//============================================================
TResult FRenderProgramAttribute::Dump(MString* pDump){
   MO_CHECK(pDump, return ENull);
   pDump->AppendFormat("Buffer: name=%s, linker=%s, slot=%d", (TCharC*)_name, (TCharC*)_linker, _slot);
   return ESuccess;
}

MO_NAMESPACE_END
