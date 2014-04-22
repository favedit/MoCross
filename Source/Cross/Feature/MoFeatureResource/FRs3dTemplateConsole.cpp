#include "MoFrContent3dModel.h"
#include "MoFrContent3dTemplate.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>������Դ3Dģ���������</T>
//============================================================
FRs3dTemplateConsole::FRs3dTemplateConsole(){
   _processLimit = 16;
   _trigger = FMonitorTrigger::InstanceCreate();
   _pLooper = MO_CREATE(FRs3dTemplateLooper);
   _pTemplates = MO_CREATE(FRs3dTemplateDictionary);
}

//============================================================
// <T>������Դ3Dģ���������</T>
//============================================================
FRs3dTemplateConsole::~FRs3dTemplateConsole(){
   MO_DELETE(_pLooper);
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
   // ����ѭ����
   _pLooper->Push(pTemplate);
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
// <T>����ˢ�´���</T>
//
// @param ��ǰʱ��
// @return ������
//============================================================
TResult FRs3dTemplateConsole::TriggerRefresh(TTimeTick currentTick){
   _pLooper->Record();
   for(TInt n = 0; n < _processLimit; n++){
      FRs3dTemplate* pTemplate = _pLooper->Next();
      if(pTemplate == NULL){
         break;
      }
      TResult processResultCd = pTemplate->Process();
      if(processResultCd == ESuccess){
         _pLooper->RemoveCurrent();
      }
   }
   return ESuccess;
}

//============================================================
// <T>��������</T>
//
// @return ������
//============================================================
TResult FRs3dTemplateConsole::Startup(){
   RMonitorManager::Instance().Register(_trigger);
   return ESuccess;
}

//============================================================
// <T>�رմ���</T>
//
// @return ������
//============================================================
TResult FRs3dTemplateConsole::Shutdown(){
   RMonitorManager::Instance().Unregister(_trigger);
   return ESuccess;
}

//============================================================
// <T>������ݡ�</T>
//
// @return ������
//============================================================
TResult FRs3dTemplateConsole::Clear(){
   return ESuccess;
}

MO_NAMESPACE_END
