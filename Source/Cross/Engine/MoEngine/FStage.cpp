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
   _pFrames = MO_CREATE(FStageFrameCollection);
}

//============================================================
// <T>������̨��</T>
//============================================================
FStage::~FStage(){
   MO_DELETE(_pViews);
   MO_DELETE(_pLights);
   MO_DELETE(_pFrames);
}

//============================================================
// <T>����ָ�����͵���̨֡��</T>
//
// @param frameCd ֡����
// @return ��̨֡
//============================================================
FStageFrame* FStage::FrameFind(EStageFrame frameCd){
   TInt count = _pFrames->Count();
   for(TInt n = 0; n < count; n++){
      FStageFrame* pFrame = _pFrames->Get(n);
      if(pFrame->FrameCd() == frameCd){
         return pFrame;
      }
   }
   return NULL;
}

//============================================================
// <T>���������̨֡��</T>
//============================================================
void FStage::FrameClear(){
   _pFrames->Clear();
}

//============================================================
// <T>����һ����̨֡��</T>
//
// @param pFrame ��̨֡
//============================================================
void FStage::FramePush(FStageFrame* pFrame){
   MO_ASSERT(pFrame);
   pFrame->SetStage(this);
   _pFrames->Push(pFrame);
}

//============================================================
// <T>�Ƴ�һ����̨֡��</T>
//
// @param pFrame ��̨֡
//============================================================
void FStage::FrameRemove(FStageFrame* pFrame){
   MO_ASSERT(pFrame);
   _pFrames->Remove(pFrame);
   pFrame->SetStage(NULL);
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
   TInt count = _pFrames->Count();
   for(TInt n = 0; n < count; n++){
      FStageFrame* pFrame = _pFrames->Get(n);
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
   TInt count = _pFrames->Count();
   for(TInt n = 0; n < count; n++){
      FStageFrame* pFrame = _pFrames->Get(n);
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
      pRegion->Views()->AssignPointer(_pViews);
   }
   //............................................................
   // ���ù�Դ����
   pRegion->SetDirectionalLight(_directionalLight);
   if(!_pLights->IsEmpty()){
      pRegion->Lights()->AssignPointer(_pLights);
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
   TInt frameCount = _pFrames->Count();
   for(TInt n = 0; n < frameCount; n++){
      FStageFrame* pFrame = _pFrames->Get(n);
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
   TInt frameCount = _pFrames->Count();
   for(TInt n = 0; n < frameCount; n++){
      FStageFrame* pFrame = _pFrames->Get(n);
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
   TInt frameCount = _pFrames->Count();
   for(TInt n = 0; n < frameCount; n++){
      FStageFrame* pFrame = _pFrames->Get(n);
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
   TInt frameCount = _pFrames->Count();
   for(TInt n = 0; n < frameCount; n++){
      FStageFrame* pFrame = _pFrames->Get(n);
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
   TInt count = _pFrames->Count();
   for(TInt n = 0; n < count; n++){
      FStageFrame* pFrame = _pFrames->Get(n);
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
   TInt count = _pFrames->Count();
   for(TInt n = 0; n < count; n++){
      FStageFrame* pFrame = _pFrames->Get(n);
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
