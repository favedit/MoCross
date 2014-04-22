#include "MoFrContent3dModel.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FRs3dModelConsole, FConsole);

//============================================================
// <T>������Դ3Dģ�͹�������</T>
//============================================================
FRs3dModelConsole::FRs3dModelConsole(){
   _processLimit = 16;
   _trigger = FMonitorTrigger::InstanceCreate();
   _pLooper = MO_CREATE(FRs3dModelLooper);
}

//============================================================
// <T>������Դ3Dģ�͹�������</T>
//============================================================
FRs3dModelConsole::~FRs3dModelConsole(){
}

//============================================================
// <T>������Դ���������Դ����</T>
//
// @param resourceId ��Դ����
// @return ��Դ����
//============================================================
FRs3dModel* FRs3dModelConsole::Load(TCharC* pName){
   FAssetStream* pStream = RAssetManager::Instance().OpenAssetStreamFormat("asset:/model/%s.ser", pName);
   MO_ERROR_CHECK(pStream, return NULL, "Open model stream failure. (resource_id=%s)", pName);
   // ��������
   FRs3dModel* pModel = MO_CREATE(FRs3dModel);
   pModel->Unserialize(pStream);
   // �ͷ���Դ
   RAssetManager::Instance().CloseAssetStream(pStream);
   return pModel;
}

//============================================================
// <T>������Դ���������Դ����</T>
//
// @param resourceId ��Դ����
// @return ��Դ����
//============================================================
FRs3dModel* FRs3dModelConsole::Find(TCharC* pName){
   FRs3dModel* pModel = _models.Find(pName);
   if(pModel == NULL){
      pModel = Load(pName);
      _models.Set(pName, pModel);
   }
   return pModel;
}

//============================================================
// <T>������Դ�������Դ����</T>
//
// @param resourceId ��Դ����
// @return ��Դ����
//============================================================
FRs3dModel* FRs3dModelConsole::Open(TCharC* pName){
   FRs3dModel* pModel = Find(pName);
   if(pModel != NULL){
      pModel->Open();
   }
   return pModel;
}

//============================================================
// <T>����ˢ�´���</T>
//
// @param ��ǰʱ��
// @return ������
//============================================================
TResult FRs3dModelConsole::TriggerRefresh(TTimeTick currentTick){
   _pLooper->Record();
   for(TInt n = 0; n < _processLimit; n++){
      FRs3dModel* pModel = _pLooper->Next();
      if(pModel == NULL){
         break;
      }
      TResult processResultCd = pModel->Process();
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
TResult FRs3dModelConsole::Startup(){
   RMonitorManager::Instance().Register(_trigger);
   return ESuccess;
}

//============================================================
// <T>�رմ���</T>
//
// @return ������
//============================================================
TResult FRs3dModelConsole::Shutdown(){
   RMonitorManager::Instance().Unregister(_trigger);
   return ESuccess;
}

//============================================================
// <T>������ݡ�</T>
//
// @return ������
//============================================================
TResult FRs3dModelConsole::Clear(){
   _models.Clear();
   return ESuccess;
}

MO_NAMESPACE_END
