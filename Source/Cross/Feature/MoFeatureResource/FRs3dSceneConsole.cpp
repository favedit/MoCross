#include "MoFrContent3dScene.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>������Դ��������̨��</T>
//============================================================
FRs3dSceneConsole::FRs3dSceneConsole(){
}

//============================================================
// <T>������Դ��������̨��</T>
//============================================================
FRs3dSceneConsole::~FRs3dSceneConsole(){
}

//============================================================
// <T>������Դ���������Դ����</T>
//
// @param resourceId ��Դ����
// @return ��Դ����
//============================================================
FRs3dScene* FRs3dSceneConsole::Load(TCharC* pName){
   MO_CHECK(pName, return NULL);
   FAssetStream* pStream = RAssetManager::Instance().OpenAssetStreamFormat(TC("asset:scene/%s.ser"), pName);
   MO_ERROR_CHECK(pStream, return NULL, TC("Open scene stream failure. (resource=%s)"), pName);
   // ��������
   FRs3dScene* pScene = FRs3dScene::InstanceCreate();
   pScene->Unserialize(pStream);
   // �ͷ���Դ
   RAssetManager::Instance().CloseAssetStream(pStream);
   return pScene;
}

//============================================================
// <T>������Դ���������Դ����</T>
//
// @param resourceId ��Դ����
// @return ��Դ����
//============================================================
FRs3dScene* FRs3dSceneConsole::Find(TCharC* pName){
   FRs3dScene* pTexture = _scenes.Find(pName);
   if(pTexture == NULL){
      pTexture = Load(pName);
      _scenes.Set(pName, pTexture);
   }
   return pTexture;
}

//============================================================
// <T>������Դ�������Դ����</T>
//
// @param resourceId ��Դ����
// @return ��Դ����
//============================================================
FRs3dScene* FRs3dSceneConsole::Open(TCharC* pName){
   FRs3dScene* pTexture = Find(pName);
   if(pTexture != NULL){
      pTexture->Open();
   }
   return pTexture;
}

//============================================================
// <T>������ݡ�</T>
//============================================================
void FRs3dSceneConsole::Clear(){
   _scenes.Clear();
}

MO_NAMESPACE_END
