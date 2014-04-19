#include "MoE3Model.h"
#include "MoE3Template.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>����ʵ��3Dģ�͹�������</T>
//============================================================
FTemplate3dConsole::FTemplate3dConsole(){
   _pPools = MO_CREATE(FTemplate3dPoolDictionary);
}

//============================================================
// <T>����ʵ��3Dģ�͹�������</T>
//============================================================
FTemplate3dConsole::~FTemplate3dConsole(){
   FTemplate3dPoolDictionary::TIteratorC iterator =  _pPools->IteratorC();
   while(iterator.Next()){
      FTemplate3dPool* pPool = *iterator;
      while(pPool->HasFreeItem()){
         FTemplate3d* pTemplate = pPool->AllocFirst();
         MO_DELETE(pTemplate);
      }
      MO_DELETE(pPool);
   }
   MO_DELETE(_pPools);
}

//============================================================
// <T>����ģ��ʵ�塣</T>
//
// @param pName ����
// @return ģ��ʵ��
//============================================================
FTemplate3d* FTemplate3dConsole::Create(TCharC* pName){
   MO_CHECK(pName, return NULL);
   // ��������
   FTemplate3d* pTemplate = FTemplate3d::InstanceCreate();
   pTemplate->SetName(pName);
   // ������Դ
   Load(pTemplate, pName);
   return pTemplate;
}

//============================================================
// <T>�ռ�ģ��ʵ�塣</T>
//
// @param pName ����
// @return ģ��ʵ��
//============================================================
FTemplate3d* FTemplate3dConsole::Alloc(TCharC* pName){
   MO_CHECK(pName, return NULL);
   // ��û����
   FTemplate3dPool* pPool = _pPools->Find(pName);
   if(pPool == NULL){
      pPool = MO_CREATE(FTemplate3dPool);
      _pPools->Set(pName, pPool);
   }
   // ��ö���
   if(!pPool->HasFreeItem()){
      FTemplate3d* pTemplate = Create(pName);
      pPool->Store(pTemplate);
   }
   return pPool->AllocFirst();
}

//============================================================
// <T>����ģ����Դ��</T>
//
// @param pTemplate ģ��
// @param pName ����
//============================================================
TResult FTemplate3dConsole::Load(FTemplate3d* pTemplate, TCharC* pName){
   MO_CHECK(pTemplate, return ENull);
   MO_CHECK(pName, return ENull);
   // ���ģ��
   FRs3dTemplate* pResource = RResource3dManager::Instance().TemplateConsole()->Find(pName);
   // ������Դ
   pTemplate->SetName(pName);
   pTemplate->LoadResource(pResource);
   RStageManager::Instance().DisplayProcessor()->Register(pTemplate);
   return ESuccess;
}

//============================================================
// <T>�ͷ�ģ��ʵ�塣</T>
//
// @param pTemplate ģ��ʵ��
//============================================================
TResult FTemplate3dConsole::Free(FTemplate3d* pTemplate){
   MO_CHECK(pTemplate, return ENull);
   TCharC* pName = pTemplate->Name();
   // ��û����
   FTemplate3dPool* pPool = _pPools->Find(pName);
   if(pPool == NULL){
      MO_FATAL("Cant' find template pool. (name=%s)", pName);
      return EFailure;
   }
   // ��ö���
   pPool->FreeLast(pTemplate);
   return ESuccess;
}

//============================================================
// <T>������</T>
//
// @return ������
//============================================================
TResult FTemplate3dConsole::Suspend(){
   return ESuccess;
}

//============================================================
// <T>��������</T>
//
// @return ������
//============================================================
TResult FTemplate3dConsole::Resume(){
   return ESuccess;
}

//============================================================
// <T>��������</T>
//
// @return ������
//============================================================
TResult FTemplate3dConsole::Dispose(){
   return ESuccess;
}

MO_NAMESPACE_END
