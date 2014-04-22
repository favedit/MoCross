#include "MoEgDisplay.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FStage, FInstance);

//============================================================
// <T>������̨��</T>
//============================================================
FStage::FStage(){
   _backgroundColor.Set(0.0f, 0.0f, 0.0f, 1.0f);
   _pViews = MO_CREATE(FRenderViewCollection);
   _pLights = MO_CREATE(FLightCollection);
}

//============================================================
// <T>������̨��</T>
//============================================================
FStage::~FStage(){
   MO_DELETE(_pViews);
   MO_DELETE(_pLights);
}

//============================================================
// <T>����ָ�����Ƶ���̨�㡣</T>
//
// @param pName ����
// @return ��̨��
//============================================================
FStageLayer* FStage::LayerFind(TCharC* pName){
   TInt count = _layers.Count();
   for(TInt n = 0; n < count; n++){
      FStageLayer* pFrame = _layers.Get(n);
      if(RString::Equals(pFrame->Name(), pName)){
         return pFrame;
      }
   }
   return NULL;
}

//============================================================
// <T>����һ����̨�㡣</T>
//
// @param pLayer ��̨��
//============================================================
TResult FStage::LayerPush(FStageLayer* pLayer){
   MO_ASSERT(pLayer);
   pLayer->SetStage(this);
   _layers.Push(pLayer);
   return ESuccess;
}

//============================================================
// <T>�Ƴ�һ����̨�㡣</T>
//
// @param pLayer ��̨��
// @return ������
//============================================================
TResult FStage::LayerRemove(FStageLayer* pLayer){
   MO_ASSERT(pLayer);
   _layers.Remove(pLayer);
   pLayer->SetStage(NULL);
   return ESuccess;
}

//============================================================
// <T>�����̨�㼯�ϡ�</T>
//
// @return ������
//============================================================
TResult FStage::LayerClear(){
   _layers.Clear();
   return ESuccess;
}

//============================================================
// <T>���ô���</T>
//
// @return ������
//============================================================
TResult FStage::Setup(){
   return ESuccess;
}

//============================================================
// <T>�����</T>
//
// @return ������
//============================================================
TResult FStage::Active(){
   TInt count = _layers.Count();
   for(TInt n = 0; n < count; n++){
      FStageLayer* pFrame = _layers.Get(n);
      pFrame->Active();
   }
   return ESuccess;
}

//============================================================
// <T>ȡ�������</T>
//
// @return ������
//============================================================
TResult FStage::Deactive(){
   TInt count = _layers.Count();
   for(TInt n = 0; n < count; n++){
      FStageLayer* pFrame = _layers.Get(n);
      pFrame->Deactive();
   }
   return ESuccess;
}

//============================================================
// <T>������Ⱦ����</T>
//
// @param pRegion ��Ⱦ����
// @return ������
//============================================================
TResult FStage::BuildRegion(FRenderRegion* pRegion){
   MO_ASSERT(pRegion);
   // �����������
   if(!_pViews->IsEmpty()){
      pRegion->Views()->Assign(_pViews);
   }
   //............................................................
   // ���ù�Դ����
   pRegion->SetDirectionalLight(_directionalLight);
   if(!_pLights->IsEmpty()){
      pRegion->Lights()->Assign(_pLights);
   }
   return ESuccess;
}

//============================================================
// <T>���´���</T>
//
// @return ������
//============================================================
TResult FStage::Update(SProcessContext* pContext){
   TInt frameCount = _layers.Count();
   for(TInt n = 0; n < frameCount; n++){
      FStageLayer* pFrame = _layers.Get(n);
      pFrame->Update(pContext);
   }
   return ESuccess;
}

//============================================================
// <T>����ǰ�ô���</T>
//
// @return ������
//============================================================
TResult FStage::ProcessBefore(SProcessContext* pContext){
   // �������
   SFrameEvent event(this);
   _listenersFrameEnter.Process(&event);
   // ��������֡��ʼ
   TInt frameCount = _layers.Count();
   for(TInt n = 0; n < frameCount; n++){
      FStageLayer* pFrame = _layers.Get(n);
      pFrame->ProcessBefore(pContext);
   }
   return ESuccess;
}

//============================================================
// <T>���봦��</T>
//
// @return ������
//============================================================
TResult FStage::ProcessInput(){
   TInt frameCount = _layers.Count();
   for(TInt n = 0; n < frameCount; n++){
      FStageLayer* pFrame = _layers.Get(n);
      pFrame->ProcessInput();
   }
   return ESuccess;
}

//============================================================
// <T>�߼�����</T>
//
// @return ������
//============================================================
TResult FStage::ProcessLogic(){
   TInt frameCount = _layers.Count();
   for(TInt n = 0; n < frameCount; n++){
      FStageLayer* pFrame = _layers.Get(n);
      pFrame->ProcessLogic();
   }
   return ESuccess;
}

//============================================================
// <T>���ܺ��ô���</T>
//
// @return ������
//============================================================
TResult FStage::ProcessAfter(SProcessContext* pContext){
   // �������
   SFrameEvent event(this);
   _listenersFrameLeave.Process(&event);
   // ��������֡����
   TInt frameCount = _layers.Count();
   for(TInt n = 0; n < frameCount; n++){
      FStageLayer* pFrame = _layers.Get(n);
      pFrame->ProcessAfter(pContext);
   }
   return ESuccess;
}

//============================================================
// <T>������</T>
//
// @return ������
//============================================================
TResult FStage::Suspend(){
   TInt count = _layers.Count();
   for(TInt n = 0; n < count; n++){
      FStageLayer* pFrame = _layers.Get(n);
      pFrame->Suspend();
   }
   return ESuccess;
}

//============================================================
// <T>��������</T>
//
// @return ������
//============================================================
TResult FStage::Resume(){
   TInt count = _layers.Count();
   for(TInt n = 0; n < count; n++){
      FStageLayer* pFrame = _layers.Get(n);
      pFrame->Resume();
   }
   return ESuccess;
}

//============================================================
// <T>��������</T>
//
// @return ������
//============================================================
TResult FStage::Dispose(){
   return ESuccess;
}

MO_NAMESPACE_END
