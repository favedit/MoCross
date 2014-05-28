#include "MoFgRender.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FRenderProgramAttribute, FRenderInstance);

//============================================================
// <T>������Ⱦ�����ԡ�</T>
//============================================================
FRenderProgramAttribute::FRenderProgramAttribute(){
   _statusUsed = EFalse;
   _slot = -1;
   _index = -1;
   _formatCd = ERenderAttributeFormat_Unknown;
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
TResult FRenderProgramAttribute::Dump(MString* pDump, TBool detail){
   MO_CHECK(pDump, return ENull);
   pDump->AppendFormat("Buffer: name=%s, linker=%s, used=%d, slot=%d, index=%d, format=%s",
         (TCharC*)_name, (TCharC*)_linker, _statusUsed, _slot, _index, RRenderAttributeFormat::Format(_formatCd));
   return ESuccess;
}

MO_NAMESPACE_END
