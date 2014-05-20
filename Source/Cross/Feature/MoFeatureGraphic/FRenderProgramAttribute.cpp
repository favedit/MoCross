#include "MoFgRender.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FRenderProgramAttribute, FInstance);

//============================================================
// <T>������Ⱦ�����ԡ�</T>
//============================================================
FRenderProgramAttribute::FRenderProgramAttribute(){
   _code = -1;
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
   //_code = RRenderAttribute::Parse(_linker);
   return ESuccess;
}

MO_NAMESPACE_END
