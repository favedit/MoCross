#include "MoEgDisplay.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FDisplayLayer, FDisplay);

//============================================================
// <T>����ɻ��ƶ���㡣</T>
//============================================================
FDisplayLayer::FDisplayLayer(){
   _objectCd |= EComponent_DrawableLayer;
   _layerCd = EDisplayLayer_Unknown;
   MO_CLEAR(_pStageFrame);
   MO_CLEAR(_pDisplays);
   MO_CLEAR(_pParticleController);
}

//============================================================
// <T>�����ɻ��ƶ���㡣</T>
//============================================================
FDisplayLayer::~FDisplayLayer(){
   MO_DELETE(_pParticleController);
}

//============================================================
// <T>������Դ���</T>
//
// @param pTester ������Ϣ
// @return ������
//============================================================
TResult FDisplayLayer::OnFocusTest(FFocusTester* pTester){
   pTester->SetStatusInRange(EFalse);
   //pTester->SetStatusChildren(_pChildren != NULL);
   return ESuccess;
}

//============================================================
// <T>���ô���</T>
//
// @return ������
//============================================================
TResult FDisplayLayer::Setup(){
   MO_ASSERT(!_pParticleController);
   _pParticleController = MO_CREATE(FParticleController);
   _visualRegion = FVisualRegion::InstanceCreate();
   RVisualManager::Instance().RegionRegister(_visualRegion);
   return ESuccess;
}

//============================================================
// <T>������Ⱦ����</T>
//
// @param pRegion ��Ⱦ����
// @return ������
//============================================================
TResult FDisplayLayer::FilterRegion(FRenderRegion* pRegion){
   FRenderableCollection* pRenderables = pRegion->Renderables();
   pRenderables->Clear();
   return FDisplay::FilterRegion(pRegion);
}

//============================================================
// <T>����ǰ�ô���</T>
//
// @return ������
//============================================================
TResult FDisplayLayer::ProcessBefore(SProcessContext* pContext){
   // ���߼�����
   TResult result = FDisplay::ProcessBefore(pContext);
   // �������ӿ�����
   if(_pParticleController != NULL){
      _pParticleController->Process();
   }
   return result;
}

//============================================================
// <T>���ܺ��ô���</T>
//
// @return ������
//============================================================
TResult FDisplayLayer::ProcessAfter(SProcessContext* pContext){
   // ���߼�����
   TResult result = FDisplay::ProcessAfter(pContext);
   return result;
}

MO_NAMESPACE_END
