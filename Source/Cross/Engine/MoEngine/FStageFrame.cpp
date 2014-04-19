#include "MoEgDisplay.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FStageFrame, FInstance);

//============================================================
// <T>������̨����</T>
//============================================================
FStageFrame::FStageFrame(){
   _frameCd = EStageFrame_Unknown;
   _backgroundColor.Set(0.0f, 0.0f, 0.0f, 1.0f);
   _pLayers = MO_CREATE(FDisplayLayerCollection);
}

//============================================================
// <T>������̨����</T>
//============================================================
FStageFrame::~FStageFrame(){
   MO_DELETE(_pLayers);
}

//============================================================
// <T>���ô���</T>
//
// @return ������
//============================================================
TResult FStageFrame::Setup(){
   return ESuccess;
}

//============================================================
// <T>����ָ�����͵���ʾ�㡣</T>
//
// @param layerCd ������
// @return ��ʾ��
//============================================================
FDisplayLayer* FStageFrame::LayerFind(EDisplayLayer layerCd){
   TInt count = _pLayers->Count();
   for(TInt n = 0; n < count; n++){
      FDisplayLayer* pLayer = _pLayers->Get(n);
      if(pLayer->LayerCd() == layerCd){
         return pLayer;
      }
   }
   return NULL;
}

//============================================================
// <T>���������ʾ�㡣</T>
//============================================================
void FStageFrame::LayerClear(){
   _pLayers->Clear();
}

//============================================================
// <T>����һ����ʾ�㡣</T>
//
// @param pLayer ��ʾ��
//============================================================
void FStageFrame::LayerPush(FDisplayLayer* pLayer){
   MO_ASSERT(pLayer);
   pLayer->SetStageFrame(this);
   _pLayers->Push(pLayer);
}

//============================================================
// <T>�Ƴ�һ���㡣</T>
//
// @param pLayer ��ʾ��
//============================================================
void FStageFrame::LayerRemove(FDisplayLayer* pLayer){
   MO_ASSERT(pLayer);
   _pLayers->Remove(pLayer);
   pLayer->SetStageFrame(NULL);
}

//============================================================
// <T>������Դ���</T>
//
// @param pTester ������Ϣ
// @return ������
//============================================================
TResult FStageFrame::FocusTest(FFocusTester* pTester){
   TInt layerCount = _pLayers->Count();
   for(TInt n = 0; n < layerCount; n++){
      FDisplayLayer* pLayer = _pLayers->Get(n);
      pLayer->FocusTest(pTester);
   }
   return ESuccess;
}

//============================================================
// <T>�����</T>
//
// @return ������
//============================================================
TResult FStageFrame::Active(){
   return ESuccess;
}

//============================================================
// <T>ȡ�������</T>
//
// @return ������
//============================================================
TResult FStageFrame::Deactive(){
   return ESuccess;
}

//============================================================
// <T>������Ⱦ����</T>
//
// @param pRegion ��Ⱦ����
// @return ������
//============================================================
TResult FStageFrame::BuildRegion(FRenderRegion* pRegion){
   MO_ASSERT(pRegion);
   return ESuccess;
}

//============================================================
// <T>����ǰ�ô���</T>
//
// @return ������
//============================================================
TResult FStageFrame::ProcessBefore(SProcessContext* pContext){
   TInt layerCount = _pLayers->Count();
   for(TInt n = 0; n < layerCount; n++){
      FDisplayLayer* pLayer = _pLayers->Get(n);
      pLayer->ProcessBefore(pContext);
   }
   return ESuccess;
}

//============================================================
// <T>���봦��</T>
//
// @return ������
//============================================================
TResult FStageFrame::ProcessInput(){
   return ESuccess;
}

//============================================================
// <T>�߼�����</T>
//
// @return ������
//============================================================
TResult FStageFrame::ProcessLogic(){
   return ESuccess;
}

//============================================================
// <T>���ܺ��ô���</T>
//
// @return ������
//============================================================
TResult FStageFrame::ProcessAfter(SProcessContext* pContext){
   TInt layerCount = _pLayers->Count();
   for(TInt n = 0; n < layerCount; n++){
      FDisplayLayer* pLayer = _pLayers->Get(n);
      pLayer->ProcessAfter(pContext);
   }
   return ESuccess;
}

//============================================================
// <T>������</T>
//
// @return ������
//============================================================
TResult FStageFrame::Suspend(){
   TInt layerCount = _pLayers->Count();
   for(TInt n = 0; n < layerCount; n++){
      FDisplayLayer* pLayer = _pLayers->Get(n);
      pLayer->Suspend();
   }
   return ESuccess;
}

//============================================================
// <T>��������</T>
//
// @return ������
//============================================================
TResult FStageFrame::Resume(){
   TInt layerCount = _pLayers->Count();
   for(TInt n = 0; n < layerCount; n++){
      FDisplayLayer* pLayer = _pLayers->Get(n);
      pLayer->Resume();
   }
   return ESuccess;
}

//============================================================
// <T>��������</T>
//
// @return ������
//============================================================
TResult FStageFrame::Dispose(){
   return ESuccess;
}

MO_NAMESPACE_END
