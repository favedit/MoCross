#include "MoFmRuntime.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>��������״̬����</T>
//============================================================
FFmRuntimeBar::FFmRuntimeBar(){
   MO_CLEAR(_pInfoLabel);
   MO_CLEAR(_pWindowButton);
   _lastRefreshTick = 0;
}

//============================================================
// <T>��������״̬����</T>
//============================================================
FFmRuntimeBar::~FFmRuntimeBar(){
}

//============================================================
// <T>����������Ϣ���ڡ�</T>
//
// @param pEvent �¼�
// @return ������
//============================================================
TResult FFmRuntimeBar::OnRuntimeWindowClick(SMouseEvent* pEvent){
   FUiFrame* pFrame = RFaceManager::Instance().FrameConsole()->Find(EFmRuntime_RuntimeWindow);
   if(pFrame->StatusVisible()){
      pFrame->Hide();
   }else{
      pFrame->Show();
   }
   return ESuccess;
}

//============================================================
// <T>���ú��ô���</T>
//
// @return ������
//============================================================
TResult FFmRuntimeBar::OnSetupAfter(){
   TResult result = FUiBar::OnSetupAfter();
   //_pInfoLabel = (FUiLabel*)ChildGet("labInfo");
   //_pWindowButton = (FUiButton*)ChildGet("btnRuntimeWindow");
   //_pWindowButton->ListenersClick().Register<FFmRuntimeBar>(this, &FFmRuntimeBar::OnRuntimeWindowClick);
   return result;
}

//============================================================
// <T>�߼�ǰ�ô���</T>
//
// @return ������
//============================================================
TResult FFmRuntimeBar::OnProcessBefore(){
   //TResult result = FUiBar::OnProcessBefore();
   RefreshStatus();
   //return result;
   return ESuccess;
}

//============================================================
// <T>ˢ��״̬��</T>
//
// @return ������
//============================================================
TResult FFmRuntimeBar::RefreshStatus(){
   // �����ʱ��
   //FTimerDevice* pTimerDevice = RDeviceManager::Instance().Find<FTimerDevice>();
   //TTimeTick currentTick = pTimerDevice->CurrentTick();
   //if(currentTick - _lastRefreshTick < 1000000){
   //   return EContinue;
   //}
   //// �����̨��Ϣ
   //FStage* pStage = RStageManager::Instance().ActiveStage();
   //FDisplayLayer* pSpriteLayer = pStage->LayerFind(EDisplayLayer_Sprite);
   //TInt spriteCount = 0;
   //TInt particleCount = 0;
   //if(pSpriteLayer != NULL){
   //   //spriteCount = pSpriteLayer->ChildCount();
   //   particleCount = pSpriteLayer->ParticleController()->ParticleCount();
   //}
   // ����Կ�ͳ����Ϣ
   //FRenderStatistics* pRenderStatistics = (FRenderStatistics*)RStatisticsManager::Instance().StatisticsFind(MoRenderStatisticsDevice);
   //TInt drawFaceCount = pRenderStatistics->DrawFaceCount();
   //TInt drawCount = pRenderStatistics->DrawCount();
   //TInt optionDeepCount = pRenderStatistics->OptionDeepCount();
   //TInt optionBlendCount = pRenderStatistics->OptionBlendCount();
   //TInt vertexBufferCount = pRenderStatistics->VertexBufferCount();
   //TInt programCount = pRenderStatistics->ProgramCount();
   //TInt samplerCount = pRenderStatistics->SamplerCount();
   //FTechnique* pTechnique = RTechniqueManager::Instance().FindTechnique(ERenderTechnique_2d);
   //FEffect* pEffect = pTechnique->FindFEffect(ERenderEffect_2dTexture);
   //// ���������ַ���
   //TFsText info;
   //info.AppendFormat("Display: frame=%d, draw_count=%d, draw_face=%d, sprite=%d, particle=%d", pTimerDevice->FramePerSecond(), drawCount, drawFaceCount, spriteCount, particleCount);
   //info.AppendFormat("\nGPU: option=(D:%d,B:%d) program=(P:%d, V:%d, S:%d)", optionDeepCount, optionBlendCount, programCount, vertexBufferCount, samplerCount);
   ////info.AppendFormat(L"\nEntity=%d", pSpriteLayer->EntityCount());
   ////info.AppendFormat("\nTechnique: limit_count=%d, count=%d", pDisplayTextureTechnique->LimitCount(), pDisplayTextureTechnique->Count());
   ////FGmMapStage* pMapStage = (FGmMapStage*)RStageManager::Instance().ActiveStage();
   ////FGmMapSpriteLayer* pSpriteLayer = pMapStage->SpriteLayer();
   ////FDisplayTextureTechnique* pDisplayTextureTechnique = (FDisplayTextureTechnique*)RTechniqueManager::Instance().FindTechnique(ETechnique_DisplayTexture);
   //TWideFixString<MO_FS_TEXT_LENGTH> infoSource;
   //infoSource.Assign8(info);
   //// _pInfoLabel->Font().fix = ETrue;
   //_pInfoLabel->SetText(infoSource);
   //_lastRefreshTick = currentTick;
   return ESuccess;
}

//============================================================
// <T>��ʾ����</T>
//
// @return ������
//============================================================
TResult FFmRuntimeBar::Show(){
   // ���óߴ�
   //SIntSize2& size = RDeviceManager::Instance().Screen()->Size();
   //_size.width = size.width - 4;
   //_pInfoLabel->Size().width = size.width - 100;
   // ��ʾ����
   return FUiBar::Show();
}

MO_NAMESPACE_END
