#include "MoGeDisplay.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FGameStage, FStageLayer);

//============================================================
// <T>�������̨����</T>
//============================================================
FGameStage::FGameStage(){
   MO_CLEAR(_pSpriteLayer);
   // �����̨֡
   MO_CLEAR(_pGroundFrame);
   MO_CLEAR(_pSceneFrame);
   MO_CLEAR(_pFaceFrame);
}

//============================================================
// <T>��������̨����</T>
//============================================================
FGameStage::~FGameStage(){
   MO_DELETE(_pGroundFrame);
   MO_DELETE(_pSceneFrame);
   MO_DELETE(_pFaceFrame);
}

//============================================================
// <T>���ô���</T>
//
// @return ������
//============================================================
TResult FGameStage::Setup(){
   TResult result = FStage::Setup();
   // �����Ļ��С
   FScreenDevice* pScreenDevice = RDeviceManager::Instance().Find<FScreenDevice>();
   FRenderDevice* pRenderDevice = RDeviceManager::Instance().Find<FRenderDevice>();
   SIntSize2& screenSize = pScreenDevice->Size();
   //............................................................
   //// ������ȾĿ��
   //FRenderTexture* pGroundTexture = pRenderDevice->CreateFlatTexture();
   //pGroundTexture->Size().Assign(_size);
   //pGroundTexture->Setup();
   //FRenderTarget* pGroundTarget = pRenderDevice->CreateRenderTarget();
   //pGroundTarget->SetOptionDepth(ETrue);
   //pGroundTarget->Size().Assign(_size);
   //pGroundTarget->Textures()->Push(pGroundTexture);
   //pGroundTarget->Setup();
   //// ���������
   //FDisplayLayer* pGroundLayer = MO_CREATE(FDisplayLayer);
   //pGroundLayer->SetLayerCd(EDisplayLayer_Ground);
   //pGroundLayer->Setup();
   //// ��������֡
   //_pGroundFrame = MO_CREATE(FStageLayer);
   //_pGroundFrame->SetFrameCd(EStageFrame_Ground);
   //_pGroundFrame->LayerPush(pGroundLayer);
   //_pGroundFrame->SetRenderTarget(pGroundTarget);
   //_pGroundFrame->Setup();
   //FramePush(_pGroundFrame);
   //............................................................
   // ������ȾĿ��
   //FRenderTexture* pSceneTexture = pRenderDevice->CreateFlatTexture();
   //pSceneTexture->Size().Assign(_size);
   //pSceneTexture->Setup();
   //FRenderTarget* pSceneTarget = pRenderDevice->CreateRenderTarget();
   //pSceneTarget->SetOptionDepth(ETrue);
   //pSceneTarget->Size().Assign(_size);
   //pSceneTarget->Textures()->Push(pSceneTexture);
   //pSceneTarget->Setup();
   // �������β�
   //FDisplayLayer* pTerrainLayer = MO_CREATE(FDisplayLayer);
   //pTerrainLayer->SetLayerCd(EDisplayLayer_Terrain);
   //pTerrainLayer->Setup();
   // ���������
   _pSpriteLayer = FDisplayLayer::InstanceCreate();
   _pSpriteLayer->SetName("Sprite");
   _pSpriteLayer->Setup();
   // ���������
   //FDisplayLayer* pParticleLayer = MO_CREATE(FDisplayLayer);
   //pParticleLayer->SetLayerCd(EDisplayLayer_Particle);
   //pParticleLayer->Setup();
   // ��������֡
   _pSceneFrame = FStageLayer::InstanceCreate();
   _pSceneFrame->SetName("Scene");
   //_pSceneFrame->LayerPush(pTerrainLayer);
   _pSceneFrame->LayerPush(_pSpriteLayer);
   //_pSceneFrame->LayerPush(pParticleLayer);
   //_pSceneFrame->SetRenderTarget(pSceneTarget);
   _pSceneFrame->Setup();
   LayerPush(_pSceneFrame);
   //............................................................
   //// ������ȾĿ��
   //FRenderTexture* pFaceTexture = pRenderDevice->CreateFlatTexture();
   //pFaceTexture->Size().Assign(_size);
   //pFaceTexture->Setup();
   //FRenderTarget* pFaceTarget = pRenderDevice->CreateRenderTarget();
   //pFaceTarget->Size().Assign(_size);
   //pFaceTarget->Textures()->Push(pFaceTexture);
   //pFaceTarget->Setup();
   //// ���������
   //FDisplayLayer* pFaceLayer = MO_CREATE(FDisplayLayer);
   //pFaceLayer->SetLayerCd(EDisplayLayer_Face);
   //pFaceLayer->Setup();
   //// ��������֡
   //_pFaceFrame = MO_CREATE(FStageLayer);
   //_pFaceFrame->SetFrameCd(EStageFrame_Face);
   //_pFaceFrame->LayerPush(pFaceLayer);
   //_pFaceFrame->SetRenderTarget(pFaceTarget);
   //_pFaceFrame->Setup();
   //FramePush(_pFaceFrame);
   return result;
}

//============================================================
// <T>���ô���</T>
//
// @return ������
//============================================================
TResult FGameStage::ProcessInput(){
   //FStage::ProcessInput();
   return ESuccess;
}

MO_NAMESPACE_END
