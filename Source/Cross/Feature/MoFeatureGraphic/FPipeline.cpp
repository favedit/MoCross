#include "MoFgRender.h"
#include "MoFgPipeline.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FPipeline, FInstance);

//============================================================
// <T>������Ⱦ�ܵ���</T>
//============================================================
FPipeline::FPipeline(){
   _setuped = EFalse;
   _pPasses = MO_CREATE(FPipelinePassCollection);
}

//============================================================
// <T>������Ⱦ�ܵ���</T>
//============================================================
FPipeline::~FPipeline(){
   MO_DELETE(_pPasses);
}

//============================================================
// <T>���ô���</T>
//
// @return ������
//============================================================
TResult FPipeline::OnSetup(){
   if(_setuped){
   }
   return ESuccess;
}

//============================================================
// <T>���ô���</T>
//
// @return ������
//============================================================
TResult FPipeline::Setup(){
   TResult result = EFailure;
   if(!_setuped){
      result  = OnSetup();
      _setuped = ETrue;
   }
   return result;
}

//============================================================
// <T>�����С��</T>
//
// @return ������
//============================================================
TResult FPipeline::Resize(TInt width, TInt height){
   return ESuccess;
}

//============================================================
// <T>���ƿ�ʼ����</T>
//
// @param pRegion ��Ⱦ����
// @return ������
//============================================================
TResult FPipeline::DrawBegin(FRenderRegion* pRegion){
   MO_CHECK(pRegion, return ENull);
   return ESuccess;
}

//============================================================
// <T>����������</T>
//
// @return ������
//============================================================
TResult FPipeline::DrawRegion(FRenderRegion* pRegion){
   MO_CHECK(pRegion, return ENull);
   // �ӽǼ��ϴ���
   FRenderViewCollection* pViews = pRegion->Views();
   TInt count = pViews->Count();
   for(TInt n = 0; n < count; n++){
      // ����������Ϣ
      FRenderView* pView = pViews->Get(n);
      pRegion->SetActiveView(pView);
      // ��Ⱦ���̼��ϴ���
      TInt passCount = _pPasses->Count();
      for(TInt i = 0; i < passCount; i++){
         FPipelinePass* pPass = _pPasses->Get(i);
         pRegion->SetOptionRenderTarget(i == passCount - 1);
         pPass->DrawRegion(pRegion);
      }
   }
   return ESuccess;
}

//============================================================
// <T>���ƽ�������</T>
//
// @param pRegion ��Ⱦ����
// @return ������
//============================================================
TResult FPipeline::DrawEnd(FRenderRegion* pRegion){
   MO_CHECK(pRegion, return ENull);
   return ESuccess;
}

MO_NAMESPACE_END
