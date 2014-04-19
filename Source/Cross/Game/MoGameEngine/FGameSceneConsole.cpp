#include "MoGeDisplay.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FGameSceneConsole, FConsole);

//============================================================
// <T>����ʵ��3D��������̨��</T>
//============================================================
FGameSceneConsole::FGameSceneConsole(){
   _pScenes = MO_CREATE(FGameSceneDictionary);
}

//============================================================
// <T>����ʵ��3D��������̨��</T>
//============================================================
FGameSceneConsole::~FGameSceneConsole(){
   MO_DELETE(_pScenes);
}

//============================================================
// <T>�ռ�ģ��ʵ�塣</T>
//
// @param pName ����
// @return ģ��ʵ��
//============================================================
FGameScene* FGameSceneConsole::Load(TCharC* pName){
   MO_CHECK(pName, return NULL);
   // ��û����
   FGameScene* pScene = _pScenes->Find(pName);
   if(pScene == NULL){
      pScene = FGameScene::InstanceCreate();
      pScene->Setup();
      FRs3dScene* pRsScene = RResource3dManager::Instance().SceneConsole()->Load(pName);
      pScene->LoadResource(pRsScene);
      _pScenes->Set(pName, pScene);
   }
   return pScene;
}

//============================================================
// <T>�ͷ�ģ��ʵ�塣</T>
//
// @param pTemplate ģ��ʵ��
//============================================================
TResult FGameSceneConsole::Free(FGameScene* pScene){
   MO_CHECK(pScene, return ENull);
   //TCharC* pName = pScene->Name();
   //// ��û����
   //FScene3d* pScene = _pScenes->Find(pName);
   //if(pScene == NULL){
   //   MO_FATAL("Cant' find scene in dictionary. (name=%s)", pName);
   //   return EFailure;
   //}
   //// ��ö���
   //pScene->Release();
   return ESuccess;
}

//============================================================
// <T>������</T>
//
// @return ������
//============================================================
TResult FGameSceneConsole::Suspend(){
   FGameSceneDictionary::TIteratorC iterator = _pScenes->IteratorC();
   while(iterator.Next()){
      FGameScene* pScene = *iterator;
      pScene->Suspend();
   }
   return ESuccess;
}

//============================================================
// <T>��������</T>
//
// @return ������
//============================================================
TResult FGameSceneConsole::Resume(){
   FGameSceneDictionary::TIteratorC iterator = _pScenes->IteratorC();
   while(iterator.Next()){
      FGameScene* pScene = *iterator;
      pScene->Resume();
   }
   return ESuccess;
}

//============================================================
// <T>��������</T>
//
// @return ������
//============================================================
TResult FGameSceneConsole::Dispose(){
   return ESuccess;
}

MO_NAMESPACE_END
