#include "MoFgRender.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FRenderShaderAttribute, FRenderObject);

//============================================================
// <T>������Ⱦ�����ԡ�</T>
//============================================================
FRenderShaderAttribute::FRenderShaderAttribute(){
   _index = -1;
   _slot = -1;
   _formatCd = ERenderShaderAttributeFormat_Unknown;
   _statusUsed = EFalse;
}

//============================================================
// <T>������Ⱦ�����ԡ�</T>
//============================================================
FRenderShaderAttribute::~FRenderShaderAttribute(){
}

//============================================================
// <T>�������á�</T>
//
// @param pConfig ���ýڵ�
// @return ������
//============================================================
TResult FRenderShaderAttribute::LoadConfig(FXmlNode* pConfig){
   MO_CHECK(pConfig, return ENull);
   // ��������
   _name = pConfig->Get("name");
   // ���ù���
   _linker = pConfig->Get("linker");
   // ���ø�ʽ
   TCharC* pFormat = pConfig->Get("format", NULL);
   if(pFormat != NULL){
      _formatCd = RRenderShaderAttributeFormat::Parse(pFormat);
   }
   return ESuccess;
}

MO_NAMESPACE_END
