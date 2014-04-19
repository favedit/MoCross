#include "MoFrContent3dModel.h"
#include "MoFrContent3dTemplate.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>������Դ3Dģ���������</T>
//============================================================
FRs3dTemplateConsole::FRs3dTemplateConsole(){
   _pTemplates = MO_CREATE(FRs3dTemplateDictionary);
}

//============================================================
// <T>������Դ3Dģ���������</T>
//============================================================
FRs3dTemplateConsole::~FRs3dTemplateConsole(){
   MO_DELETE(_pTemplates);
}

//============================================================
// <T>������Դ���������Դ����</T>
//
// @param resourceId ��Դ����
// @return ��Դ����
//============================================================
FRs3dTemplate* FRs3dTemplateConsole::Load(TCharC* pName){
   FAssetStream* pStream = RAssetManager::Instance().OpenAssetStreamFormat("asset:/template/%s.ser", pName);
   MO_ERROR_CHECK(pStream, return NULL, "Open template stream failure. (resource=%s)", pName);
   // ��������
   FRs3dTemplate* pTemplate = MO_CREATE(FRs3dTemplate);
   pTemplate->Unserialize(pStream);
   // �ͷ���Դ
   RAssetManager::Instance().CloseAssetStream(pStream);
   return pTemplate;
}

//============================================================
// <T>������Դ���������Դ����</T>
//
// @param resourceId ��Դ����
// @return ��Դ����
//============================================================
FRs3dTemplate* FRs3dTemplateConsole::Find(TCharC* pName){
   FRs3dTemplate* pTemplate = _pTemplates->Find(pName);
   if(pTemplate == NULL){
      pTemplate = Load(pName);
      _pTemplates->Set(pName, pTemplate);
   }
   return pTemplate;
}

//============================================================
// <T>������ݡ�</T>
//============================================================
void FRs3dTemplateConsole::Clear(){
}

MO_NAMESPACE_END
