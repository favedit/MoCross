#include "MoE3Scene.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FScene3dConsole, FConsole);

//============================================================
// <T>����ʵ��3D��������̨��</T>
//============================================================
FScene3dConsole::FScene3dConsole(){
   _pScenes = MO_CREATE(FScene3dDictionary);
}

//============================================================
// <T>����ʵ��3D��������̨��</T>
//============================================================
FScene3dConsole::~FScene3dConsole(){
   MO_DELETE(_pScenes);
}

//============================================================
// <T>�ռ�ģ��ʵ�塣</T>
//
// @param pName ����
// @return ģ��ʵ��
//============================================================
FScene3d* FScene3dConsole::Load(TCharC* pName){
   MO_CHECK(pName, return NULL);
   // ��û����
   FScene3d* pScene = _pScenes->Find(pName);
   if(pScene == NULL){
      pScene = FScene3d::InstanceCreate();
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
TResult FScene3dConsole::Free(FScene3d* pScene){
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
TResult FScene3dConsole::Suspend(){
   FScene3dDictionary::TIteratorC iterator = _pScenes->IteratorC();
   while(iterator.Next()){
      FScene3d* pScene = *iterator;
      pScene->Suspend();
   }
   return ESuccess;
}

//============================================================
// <T>��������</T>
//
// @return ������
//============================================================
TResult FScene3dConsole::Resume(){
   FScene3dDictionary::TIteratorC iterator = _pScenes->IteratorC();
   while(iterator.Next()){
      FScene3d* pScene = *iterator;
      pScene->Resume();
   }
   return ESuccess;
}

//============================================================
// <T>��������</T>
//
// @return ������
//============================================================
TResult FScene3dConsole::Dispose(){
   return ESuccess;
}

MO_NAMESPACE_END
