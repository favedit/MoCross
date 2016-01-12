//============================================================
//   DYNAMIC LINK LIBRARY : Mo3DSExporter Project Overview
//------------------------------------------------------------
// ��3DS MAX�е���ģ�͵Ķ�̬���ӿ⡣
//------------------------------------------------------------
// Copyright From MAOCY
// 2010-05-02 (^o^)
//============================================================

#include <MoCommon.h>
#include <MoFbx2016Core.h>
#include "MpFbxDefine.h"

MO_NAMESPACE_INCLUDE;
MO_NAMESPACE_USING(FBXSDK_NAMESPACE);

void ProcessNode(FbxNode* pNode){
   TChar8C* pName = pNode->GetName();
   printf("%s\n", pName);
   //FbxNodeAttribute::EType attributeType;
   //if(pNode->GetNodeAttribute()){
   //   switch(pNode->GetNodeAttribute()->GetAttributeType()){
   //      case KFbxNodeAttribute::eMESH:
   //         //ProcessMesh(pNode);
   //         break;
   //      case KFbxNodeAttribute::eSKELETON:
   //         //ProcessSkeleton(pNode);
   //         break;
   //      case KFbxNodeAttribute::eLIGHT:
   //         //ProcessLight(pNode);
   //         break;
   //      case KFbxNodeAttribute::eCAMERA:
   //         //ProcessCamera();
   //         break;
   //   }
   //}
   TInt nodeCount = pNode->GetChildCount();
   for(TInt32 i = 0; i < nodeCount; i++){
      FbxNode* pChildNode = pNode->GetChild(i);
      ProcessNode(pChildNode);
   }
}


//============================================================
// <T>���ض�̬�⡣</T>
//
// @param hInstance ʵ�����
// @param reason ��������
// @param pReserved ������
// @return ����
//============================================================
TInt32 main(TChar** pArguments, TInt count){
   MoInitialize();
   TString fileName = TC("D:/Resource/xiong/data.FBX");
   TString targetFileName = TC("D:/Resource/xiong/data.m3x");
   //TString8 fileName = "Help";
   //printf("%s\n", fileName.MemoryC());
   // ����������
   FFbxManager* pManager = MO_CREATE(FFbxManager);
   pManager->Setup();
   // ��������
   FFbxScene* pScene = MO_CREATE(FFbxScene);
   pScene->SetManager(pManager);
   pScene->Setup();
   pScene->LoadFile(fileName);
   pScene->SaveFile(targetFileName);
   MO_DELETE(pScene);
   MO_DELETE(pManager);
   // �ͷŴ���
   MoRelease();
   //getchar();
   return 0;
}
