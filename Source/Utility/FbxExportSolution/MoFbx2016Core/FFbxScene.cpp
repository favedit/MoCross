#include "MoFbxCore.h"

MO_NAMESPACE_BEGIN;

//============================================================
// <T>����FBX������</T>
//============================================================
FFbxScene::FFbxScene() {
   MO_CLEAR(_pManager);
   MO_CLEAR(_pFbxScene);
   _pMeshs = MO_CREATE(FObjects<FFbxMesh*>);
}

//============================================================
// <T>����FBX������</T>
//============================================================
FFbxScene::~FFbxScene() {
   MO_DESTORY(_pFbxScene);
   MO_CLEAR(_pManager);
   // �ͷ���������
   if(_pMeshs != NULL){
      TInt count = _pMeshs->Count();
      for(TInt n = 0; n < count; n++){
         FFbxMesh* pMesh = _pMeshs->Get(n);
         MO_DELETE(pMesh);
      }
      MO_DELETE(_pMeshs);
   }
}

//============================================================
// <T>���ô���</T>
//============================================================
TResult FFbxScene::Setup(){
   FbxManager* pFbxManager = _pManager->FbxManager();
   _pFbxScene = FbxScene::Create(pFbxManager, "");
   return ESuccess;
}

//============================================================
// <T>����ڵ㴦��</T>
//============================================================
TResult FFbxScene::ProcessMesh(FbxNode * pFbxNode){
   // �������
   FbxMesh* pFbxMesh = pFbxNode->GetMesh();
   if(pFbxMesh == NULL){
      return EFailure;
   }
   // ��������
   FFbxMesh* pMesh = MO_CREATE(FFbxMesh);
   pMesh->SetScene(this);
   pMesh->SetNodeHandle(pFbxNode);
   pMesh->Setup();
   _pMeshs->Push(pMesh);
   return ESuccess;
}

//============================================================
// <T>�ڵ㴦��</T>
//============================================================
TResult FFbxScene::ProcessNode(FbxNode * pFbxNode){
   // ����ǰ���
   TChar8C* pName = pFbxNode->GetName();
   printf("%s\n", pName);
   FbxNodeAttribute* pFbxNodeAttribute = pFbxNode->GetNodeAttribute();
   if(pFbxNodeAttribute != NULL){
      FbxNodeAttribute::EType typeCd = pFbxNodeAttribute->GetAttributeType();
      switch(typeCd){
         case FbxNodeAttribute::eMesh:
            ProcessMesh(pFbxNode);
            break;
         case FbxNodeAttribute::eSkeleton:
            //ProcessSkeleton(pFbxNode);
            break;
         case FbxNodeAttribute::eLight:
            //ProcessLight(pFbxNode);
            break;
         case FbxNodeAttribute::eCamera:
            //ProcessCamera(pFbxNode);
            break;
      }
   }
   // �����ӽ�㼯��
   TInt nodeCount = pFbxNode->GetChildCount();
   for(TInt32 i = 0; i < nodeCount; i++){
      FbxNode* pChildNode = pFbxNode->GetChild(i);
      ProcessNode(pChildNode);
   }
   return ESuccess;
}

//============================================================
// <T>���л����ݵ��������</T>
//
// @param pOutput �����
// @return ������
//============================================================
TResult FFbxScene::Serialize(IDataOutput* pOutput){
   MO_ASSERT_POINTER(pOutput);
   // д�����񼯺�
   TInt count = _pMeshs->Count();
   pOutput->WriteInt32((TInt32)count);
   for(TInt n = 0; n < count; n++){
      FFbxMesh* pMesh = _pMeshs->Get(n);
      pMesh->Serialize(pOutput);
   }
   MO_DELETE(_pMeshs);
   return ESuccess;
}

//============================================================
// <T>�����ļ���</T>
//
// @param pFileName �ļ�����
// @return ������
//============================================================
TResult FFbxScene::LoadFile(TCharC* pFileName){
   MO_ASSERT_POINTER(pFileName);
   // ��ò���
   FbxManager* pFbxManager = _pManager->FbxManager();
   FbxIOSettings* pFbxIoSettings = _pManager->FbxIoSettings();
   SFbxSdkVersion& managerVersion = _pManager->Version();
   TString8 fileName;
   fileName.Assign16(pFileName);
   // ����������
   FbxImporter* pImporter = FbxImporter::Create(pFbxManager, NULL);
   TBool initializeStatusCd = pImporter->Initialize(fileName.MemoryC(), -1, pFbxIoSettings);
   if(!initializeStatusCd){
      MO_FATAL(TC("Open fbx file failure. (file_name={1})"), pFileName);
   }
   // ��ð汾��
   SFbxSdkVersion version;
   pImporter->GetFileVersion(version.major, version.minor, version.revision);
   if(managerVersion.major < version.major){
      MO_FATAL(TC("Open fbx major version failure. (file_name={1})"), pFileName);
   }else if (managerVersion.minor < version.minor) {
      MO_FATAL(TC("Open fbx minor version failure. (file_name={1})"), pFileName);
   }
   // ���볡��
   _pFbxScene->Clear();
   TBool importStatusCd = pImporter->Import(_pFbxScene);
   if (!importStatusCd) {
      MO_FATAL(TC("Import fbx scene failure. (file_name={1})"), pFileName);
   }
   // �ͷŵ�����
   MO_DESTORY(pImporter);
   // ����ڵ�
   FbxNode* pRootNode = _pFbxScene->GetRootNode();
   ProcessNode(pRootNode);
   return ESuccess;
}

//============================================================
// <T>�洢�ļ���</T>
//
// @param pFileName �ļ�����
// @return ������
//============================================================
TResult FFbxScene::SaveFile(TCharC* pFileName){
   MO_ASSERT_POINTER(pFileName);
   FByteFile* pFile = MO_CREATE(FByteFile);
   pFile->EnsureSize(1024 * 1024);
   Serialize(pFile);
   MO_DELETE(pFile);
   return ESuccess;
}

MO_NAMESPACE_END;
