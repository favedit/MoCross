#include "MoEgDisplay.h"
#include "MoEgEngine.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>������̨����̨��</T>
//============================================================
FEngineConsole::FEngineConsole(){
   _pRegion = MO_CREATE(FRenderRegion);
}

//============================================================
// <T>������̨����̨��</T>
//============================================================
FEngineConsole::~FEngineConsole(){
   MO_DELETE(_pRegion);
}

//============================================================
// <T>���ô���</T>
//
// @return ������
//============================================================
TResult FEngineConsole::Setup(){
   // ����ͳ����Ϣ
   _statistics = FEngineStatistics::InstanceCreate();
   _statistics->Setup();
   // ע����Ļ�����С�¼�
   FScreenDevice* pScreen = RDeviceManager::Instance().Find<FScreenDevice>();
   pScreen->ListenersResize().Register<FEngineConsole>(this, &FEngineConsole::OnResize);
   // ��ó�����Ⱦ��
   //_stageEffect = REffectManager::Instance().Find<FStageEffect>(TC("stage"));
   // ������Ⱦ����
   _renderRectangle = FRenderRectangle::InstanceCreate();
   _renderRectangle->Setup();
   return ESuccess;
}

//============================================================
// <T>�����С����</T>
//
// @param pEvent �¼�
// @return ������
//============================================================
TResult FEngineConsole::OnResize(SScreenResizeEvent* pEvent){
   TInt width = pEvent->size.width;
   TInt height = pEvent->size.height;
   FRenderDevice* pRenderDevice = RDeviceManager::Instance().Find<FRenderDevice>();
   pRenderDevice->SetBackBuffer(width, height, 1);
   return ESuccess;
}

//============================================================
// <T>�߼��㴦��</T>
//
// @param pLayer �����
// @return ������
//============================================================
TResult FEngineConsole::ProcessLayer(FDisplayLayer* pLayer){
   MO_CHECK(pLayer, return ENull);
   // ���²����
   SDrawableContext context;
   pLayer->UpdateAllMatrix(&context);
   //............................................................
   // �����ʾ����
   pLayer->FilterRegion(_pRegion);
   if(!_pRegion->TestRenderable()){
      return EContinue;
   }
   //............................................................
   // ���ÿɼ�����
   FVisualRegion* pVisualRegion = pLayer->VisualRegion();
   _pRegion->SetVisualRegion(pVisualRegion);
   // �ܵ�����
   FPipelinePass* pPass = _pRegion->ActivePass();
   pPass->DrawRegion(_pRegion);
   return ESuccess;
}

//============================================================
// <T>֡�㴦��</T>
//
// @param pFrame ��̨��
// @return ������
//============================================================
TResult FEngineConsole::ProcessFrame(FStageLayer* pFrame){
   MO_ASSERT(pFrame);
   // ����豸
   FRenderDevice* pRenderDevice = RDeviceManager::Instance().Find<FRenderDevice>();
   MO_CHECK(pRenderDevice, return ENull);
   //............................................................
   // ������Ⱦ����
   pFrame->BuildRegion(_pRegion);
   //............................................................
   // �����Ⱦͨ��
   FPipeline* pPipeline = RPipelineManager::Instance().ActivePipeline();
   _pRegion->SetActivePipeline(pPipeline);
   // ��Ⱦ���̼��ϴ���
   FPipelinePassCollection* pPasses = pPipeline->Passes();
   TInt passCount = pPasses->Count();
   TInt passLast = passCount - 1;
   for(TInt n = 0; n < passCount; n++){
      FPipelinePass* pPass = pPasses->Get(n);
      if(n == passLast){
         _pRegion->SetOptionRenderTarget(ETrue);
         // ������ȾĿ��
         FRenderTarget* pRenderTarget = pFrame->RenderTarget();
         pRenderDevice->SetRenderTarget(pRenderTarget);
         SFloatColor4 background = pRenderTarget ? pRenderTarget->BackgroundColor() : pFrame->BackgroundColor();
         pRenderDevice->Clear(background.red, background.green, background.blue, background.alpha);
      }else{
         _pRegion->SetOptionRenderTarget(EFalse);
      }
      _pRegion->SetActivePass(pPass);
      //............................................................
      // �������в�
      pPass->DrawBegin(_pRegion);
      FDisplayLayerCollection::TIteratorC layerIterator = pFrame->Layers()->IteratorC();
      while(layerIterator.Next()){
         FDisplayLayer* pLayer = *layerIterator;
         TResult layerResult = ProcessLayer(pLayer);
         if(layerResult == EContinue){
            continue;
         }else if(layerResult != ESuccess){
            return layerResult;
         }
      }
      pPass->DrawEnd(_pRegion);
   }
   return ESuccess;
}

//============================================================
// <T>�߼�����</T>
//
// @return ������
//============================================================
TResult FEngineConsole::Process(){
   // ���ͳ����
   FStatistics* pFrameStatistics = _statistics->FrameStatistics();
   FStatistics* pFrameProcessBeforeStatistics = _statistics->FrameProcessBeforeStatistics();
   FStatistics* pFrameDrawStatistics = _statistics->FrameDrawStatistics();
   FStatistics* pFrameProcessAfterStatistics = _statistics->FrameProcessAfterStatistics();
   //............................................................
   // ��鼤�����̨
   FStage* pStage = RStageManager::Instance().ActiveStage();
   if(pStage == NULL){
      return EContinue;
   }
   pFrameStatistics->Begin();
   pStage->BuildRegion(_pRegion);
   GStageLayerPtrs& layers = pStage->Layers();
   //............................................................
   // ����ʱ��
   FTimerDevice* pTimerDevice = RDeviceManager::Instance().Find<FTimerDevice>();
   pTimerDevice->Update();
   //............................................................
   // ���´���
   SProcessContext processContext;
   processContext.currentTick = pTimerDevice->CurrentTick();
   pStage->Update(&processContext);
   //............................................................
   // ����֡����
   SFrameEvent enterEvent(this);
   pFrameProcessBeforeStatistics->Begin();
   _listenersFrameEnter.Process(&enterEvent);
   pStage->ProcessBefore(&processContext);
   pFrameProcessBeforeStatistics->Finish();
   // ����֡����
   pStage->ProcessInput();
   // ����֡�߼�
   SFrameEvent logicEvent(this);
   _listenersFrameLogic.Process(&logicEvent);
   pStage->ProcessLogic();
   //............................................................
   // ����豸
   FRenderDevice* pRenderDevice = RDeviceManager::Instance().Find<FRenderDevice>();
   MO_CHECK(pRenderDevice, return ENull);
   // ֡����ʼ
   pRenderDevice->FrameBegin();
   // ����֡����
   pFrameDrawStatistics->Begin();
   // ����ӽǼ���
   FRenderViewCollection::TIteratorC viewIterator = _pRegion->Views()->IteratorC();
   while(viewIterator.Next()){
      // ����������Ϣ
      FRenderView* pView = *viewIterator;
      _pRegion->SetActiveView(pView);
      // ��Ⱦ���̼��ϴ���
      GStageLayerPtrs::TIteratorC layerIterator = layers.IteratorC();
      while(layerIterator.Next()){
         FStageLayer* pFrame = *layerIterator;
         ProcessFrame(pFrame);
      }
   }
   // ��ʾ����
   pRenderDevice->Present();
   pFrameDrawStatistics->Finish();
   //............................................................
   // ֡�������
   pRenderDevice->FrameEnd();
   //............................................................
   // ����֡�뿪
   SFrameEvent leaveEvent(this);
   pFrameProcessAfterStatistics->Begin();
   pStage->ProcessAfter(&processContext);
   _listenersFrameLeave.Process(&leaveEvent);
   pFrameProcessAfterStatistics->Finish();
   pFrameStatistics->Finish();
   return ESuccess;
}

MO_NAMESPACE_END
