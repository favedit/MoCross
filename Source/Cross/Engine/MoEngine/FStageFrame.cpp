#include "MoEgDisplay.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FStageLayer, FInstance);

//============================================================
// <T>������̨����</T>
//============================================================
FStageLayer::FStageLayer(){
   _backgroundColor.Set(0.0f, 0.0f, 0.0f, 1.0f);
   _pLayers = MO_CREATE(FDisplayLayerCollection);
}

//============================================================
// <T>������̨����</T>
//============================================================
FStageLayer::~FStageLayer(){
   MO_DELETE(_pLayers);
}

//============================================================
// <T>���ô���</T>
//
// @return ������
//============================================================
TResult FStageLayer::Setup(){
   return ESuccess;
}

//============================================================
// <T>����ָ�����͵���ʾ�㡣</T>
//
// @param layerCd ������
// @return ��ʾ��
//============================================================
FDisplayLayer* FStageLayer::LayerFind(TCharC* pName){
   TInt count = _pLayers->Count();
   for(TInt n = 0; n < count; n++){
      FDisplayLayer* pLayer = _pLayers->Get(n);
      if(RString::Equals(pLayer->Name(), pName)){
         return pLayer;
      }
   }
   return NULL;
}

//============================================================
// <T>����һ����ʾ�㡣</T>
//
// @param pLayer ��ʾ��
// @return ������
//============================================================
TResult FStageLayer::LayerPush(FDisplayLayer* pLayer){
   MO_CHECK(pLayer, return ENull);
   pLayer->SetStageLayer(this);
   _pLayers->Push(pLayer);
   return ESuccess;
}

//============================================================
// <T>�Ƴ�һ���㡣</T>
//
// @param pLayer ��ʾ��
// @return ������
//============================================================
TResult FStageLayer::LayerRemove(FDisplayLayer* pLayer){
   MO_CHECK(pLayer, return ENull);
   _pLayers->Remove(pLayer);
   pLayer->SetStageLayer(NULL);
   return ESuccess;
}

//============================================================
// <T>���������ʾ�㡣</T>
//
// @return ������
//============================================================
TResult FStageLayer::LayerClear(){
   _pLayers->Clear();
   return ESuccess;
}

//============================================================
// <T>������Դ���</T>
//
// @param pTester ������Ϣ
// @return ������
//============================================================
TResult FStageLayer::FocusTest(FFocusTester* pTester){
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
TResult FStageLayer::Active(){
   return ESuccess;
}

//============================================================
// <T>ȡ�������</T>
//
// @return ������
//============================================================
TResult FStageLayer::Deactive(){
   return ESuccess;
}

//============================================================
// <T>������Ⱦ����</T>
//
// @param pRegion ��Ⱦ����
// @return ������
//============================================================
TResult FStageLayer::BuildRegion(FRenderRegion* pRegion){
   MO_ASSERT(pRegion);
   return ESuccess;
}

//============================================================
// <T>���´���</T>
//
// @return ������
//============================================================
TResult FStageLayer::Update(SProcessContext* pContext){
   TInt layerCount = _pLayers->Count();
   for(TInt n = 0; n < layerCount; n++){
      FDisplayLayer* pLayer = _pLayers->Get(n);
      pLayer->Update(pContext);
   }
   return ESuccess;
}

//============================================================
// <T>����ǰ�ô���</T>
//
// @return ������
//============================================================
TResult FStageLayer::ProcessBefore(SProcessContext* pContext){
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
TResult FStageLayer::ProcessInput(){
   return ESuccess;
}

//============================================================
// <T>�߼�����</T>
//
// @return ������
//============================================================
TResult FStageLayer::ProcessLogic(){
   return ESuccess;
}

//============================================================
// <T>���ܺ��ô���</T>
//
// @return ������
//============================================================
TResult FStageLayer::ProcessAfter(SProcessContext* pContext){
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
TResult FStageLayer::Suspend(){
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
TResult FStageLayer::Resume(){
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
TResult FStageLayer::Dispose(){
   return ESuccess;
}

MO_NAMESPACE_END
