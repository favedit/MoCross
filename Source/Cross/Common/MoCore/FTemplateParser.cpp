#include "MoCrTemplate.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FTemplateParser, FConfigParser);

//============================================================
// <T>����ģ���ǩ��</T>
//============================================================
FTemplateParser::FTemplateParser(){
   _optionTextNode = ETrue;
   _pFactory->Register(MO_CONFIG_ELEMENT_NODE, FTemplateTag::Class());
   _pFactory->Register(MO_CONFIG_ELEMENT_TEXT, FTemplateTagText::Class());
   _pFactory->Register("write", FTemplateTagWrite::Class());
   _pFactory->Register("include", FTemplateTagInclude::Class());
   _pFactory->Register("true", FTemplateTagTrue::Class());
   _pFactory->Register("false", FTemplateTagFalse::Class());
   _pFactory->Register("counter", FTemplateTagCounter::Class());
}

//============================================================
// <T>����ģ���ǩ��</T>
//============================================================
FTemplateParser::~FTemplateParser(){
}

//============================================================
// <T>������Դ����ģ�塣</T>
//
// @return ģ��
//============================================================
FTemplateSource* FTemplateParser::Load(TCharC* pSource){
   // ��������
   FTemplateTag* pRootTag = FTemplateTag::InstanceCreate();
   Parse(pRootTag, pSource);
   // ����ģ��
   FTemplateSource* pTemplateSource = FTemplateSource::InstanceCreate();
   pTemplateSource->SetRootTag(pRootTag);
   return pTemplateSource;
}

MO_NAMESPACE_END
