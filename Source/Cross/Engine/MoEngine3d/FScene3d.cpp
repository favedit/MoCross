#include "MoE3Scene.h"
#include "MoE3Instance.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FScene3d, FStage);

//============================================================
// <T>����ʵ��3Dģ�͡�</T>
//============================================================
FScene3d::FScene3d(){
}

//============================================================
// <T>����ʵ��3Dģ�͡�</T>
//============================================================
FScene3d::~FScene3d(){
}

//============================================================
// <T>���ؼ�����Դ��</T>
//
// @param pResource ��Դ����
// @return ������
//============================================================
TResult FScene3d::LoadTechniqueResource(FRs3dSceneTechnique* pResource){
   MO_CHECK(pResource, return ENull);
   return ESuccess;
}

//============================================================
// <T>����������Դ��</T>
//
// @param pResource ��Դ����
// @return ������
//============================================================
TResult FScene3d::LoadRegionResource(FRs3dSceneRegion* pResource){
   MO_CHECK(pResource, return ENull);
   // ������ɫ
   _sceneFrame->BackgroundColor().Assign(pResource->Color());
   FScreenDevice* pScreenDevice = RDeviceManager::Instance().Find<FScreenDevice>();
   SIntSize2& screenSize = pScreenDevice->Size();
   //............................................................
   FRs3dSceneCamera* pCameraResource = pResource->Camera();
   FRs3dSceneViewport* pViewportResource = pCameraResource->Viewport();
   // ����ͶӰ
   FPerspectiveProjection* pProjection = FPerspectiveProjection::InstanceCreate();
   pProjection->Size().Set(screenSize.width, screenSize.height);
   pProjection->SetZ(pViewportResource->Near(), pViewportResource->Far());
   pProjection->SetAngle(pViewportResource->Angle());
   pProjection->Update();
   // �������
   FCamera* pCamera = FPerspectiveCamera::InstanceCreate();
   pCamera->Position().Assign(pCameraResource->Position());
   pCamera->Direction().Assign(pCameraResource->Direction());
   pCamera->SetProjection(pProjection);
   pCamera->Update();
   // �����ӽ�
   FViewport* pViewport = FViewport::InstanceCreate();
   pViewport->Set(0, 0, screenSize.width, screenSize.height);
   // �����ӽ�
   FRenderView* pView = FRenderView::InstanceCreate();
   pView->SetCamera(pCamera);
   pView->SetViewport(pViewport);
   _activeView = pView;
   _pViews->Push(pView);
   //............................................................
   FRs3dSceneLight* pLightResource = pResource->Light();
   FRs3dSceneCamera* pLightCameraResource = pLightResource->Camera();
   FRs3dSceneViewport* pLightViewportResource = pLightCameraResource->Viewport();
   // ���ù�ԴͶӰ
   FPerspectiveProjection* pLightProjection = FPerspectiveProjection::InstanceCreate();
   pLightProjection->Size().Set(1024, 1024);
   pLightProjection->SetZ(pLightViewportResource->Near(), pLightViewportResource->Far());
   pLightProjection->SetAngle(pLightViewportResource->Angle());
   pLightProjection->Update();
   // ���ù�Դ���
   FCamera* pLightCamera = FPerspectiveCamera::InstanceCreate();
   pLightCamera->Position().Assign(pLightCameraResource->Position());
   pLightCamera->Direction().Assign(pLightCameraResource->Direction());
   pLightCamera->SetProjection(pLightProjection);
   pLightCamera->Update();
   // ���ù�Դ�ӽ�
   FViewport* pLightViewport = FViewport::InstanceCreate();
   pLightViewport->Set(0, 0, 1024, 1024);
   // ���ò���
   FRs3dSceneMaterial* pLightMaterialResource = pLightResource->Material();
   GPtr<FScene3dMaterial> lightMaterial = FScene3dMaterial::InstanceCreate();
   lightMaterial->LoadSceneResource(pLightMaterialResource);
   // ���ù�Դ
   FDirectionalLight* pLight = FDirectionalLight::InstanceCreate();
   pLight->SetCamera(pLightCamera);
   pLight->SetViewport(pLightViewport);
   pLight->Direction().Assign(pLightCamera->Direction());
   pLight->SetMaterial(lightMaterial);
   SetDirectionalLight(pLight);
   return ESuccess;
}

//============================================================
// <T>������ʾ��Դ��</T>
//
// @param pResource ��Դ����
// @return ������
//============================================================
TResult FScene3d::LoadDisplayResource(FDisplayLayer* pLayer, FRs3dSceneDisplay* pResource){
   MO_CHECK(pResource, return ENull);
   TCharC* pSource = pResource->Source();
   // ���س�����Դ
   FScene3dDisplay* pDisplay = FScene3dDisplay::InstanceCreate();
   pDisplay->LoadSceneResource(pResource);
   // ������Ⱦ����
   RInstance3dManager::Instance().TemplateConsole()->Load(pDisplay, pSource);
   //............................................................
   // ��ȡ��Ⱦ���󼯺�
   FMaterial* pLightMaterial = _directionalLight->Material();
   if(pDisplay->Renderables() != NULL){
      GRenderablePtrs::TIteratorC iterator = pDisplay->Renderables().IteratorC();
      while(iterator.Next()){
         FTemplate3dRenderable* pRenderable = (*iterator)->Convert<FTemplate3dRenderable>();
         pRenderable->UpdateMaterial(pLightMaterial);
      }
   }
   // ���뼯��
   pLayer->DisplayPush(pDisplay);
   return ESuccess;
}

//============================================================
// <T>���������Դ��</T>
//
// @param pResource ��Դ����
// @return ������
//============================================================
TResult FScene3d::LoadSkyResource(FRs3dSceneSky* pResource){
   MO_CHECK(pResource, return ENull);
   GRs3dSceneDisplayPtrs::TIteratorC displayIterator = pResource->Displays().IteratorC();
   while(displayIterator.Next()){
      FRs3dSceneDisplay* pDisplay = *displayIterator;
      TResult resultCd = LoadDisplayResource(_sceneFrame->MapLayer(), pDisplay);
      if(resultCd != ESuccess){
         return resultCd;
      }
   }
   return ESuccess;
}

//============================================================
// <T>���ص�ͼ��Դ��</T>
//
// @param pResource ��Դ����
// @return ������
//============================================================
TResult FScene3d::LoadMapResource(FRs3dSceneMap* pResource){
   MO_CHECK(pResource, return ENull);
   GRs3dSceneDisplayPtrs::TIteratorC displayIterator = pResource->Displays().IteratorC();
   while(displayIterator.Next()){
      FRs3dSceneDisplay* pDisplay = *displayIterator;
      TResult resultCd = LoadDisplayResource(_sceneFrame->MapLayer(), pDisplay);
      if(resultCd != ESuccess){
         return resultCd;
      }
   }
   return ESuccess;
}

//============================================================
// <T>���ؿռ���Դ��</T>
//
// @param pResource ��Դ����
// @return ������
//============================================================
TResult FScene3d::LoadSpaceResource(FRs3dSceneSpace* pResource){
   MO_CHECK(pResource, return ENull);
   GRs3dSceneDisplayPtrs::TIteratorC displayIterator = pResource->Displays().IteratorC();
   while(displayIterator.Next()){
      FRs3dSceneDisplay* pDisplay = *displayIterator;
      TResult resultCd = LoadDisplayResource(_sceneFrame->SpaceLayer(), pDisplay);
      if(resultCd != ESuccess){
         return resultCd;
      }
   }
   return ESuccess;
}

//============================================================
// <T>������Դ��</T>
//
// @param pResource ��Դ����
//============================================================
TResult FScene3d::LoadResource(FRs3dScene* pResource){
   MO_CHECK(pResource, return ENull);
   // ��������
   _pResource = pResource;
   // ���ؼ�����Դ
   FRs3dSceneTechnique* pTechniqueResource = pResource->Technique();
   LoadTechniqueResource(pTechniqueResource);
   // ����������Դ
   FRs3dSceneRegion* pRegionResource = pResource->Region();
   LoadRegionResource(pRegionResource);
   // ���������Դ
   FRs3dSceneSky* pSkyResource = pResource->Sky();
   LoadSkyResource(pSkyResource);
   // ���ص�ͼ��Դ
   FRs3dSceneMap* pMapResource = pResource->Map();
   LoadMapResource(pMapResource);
   // ���ؿռ���Դ
   FRs3dSceneSpace* pSpaceResource = pResource->Space();
   LoadSpaceResource(pSpaceResource);
   return ESuccess;
}

//============================================================
// <T>���ô���</T>
//
// @return ������
//============================================================
TResult FScene3d::Setup(){
   TResult resultCd = FStage::Setup();
   // ��������֡
   _sceneFrame = FScene3dFrame::InstanceCreate();
   _sceneFrame->Setup();
   _layers.Push(_sceneFrame);
   return resultCd;
}

//============================================================
// <T>������</T>
//
// @return ������
//============================================================
TResult FScene3d::Suspend(){
   return FStage::Suspend();
}

//============================================================
// <T>��������</T>
//
// @return ������
//============================================================
TResult FScene3d::Resume(){
   return FStage::Resume();
}

//============================================================
// <T>��������</T>
//
// @return ������
//============================================================
TResult FScene3d::Dispose(){
   return FStage::Dispose();
}

MO_NAMESPACE_END
