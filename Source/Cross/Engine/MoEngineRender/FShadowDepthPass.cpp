#include "MoErShadowPipeline.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FShadowDepthPass, FPipelinePass);

//============================================================
// <T>����Ӱ����Ⱦ���̡�</T>
//============================================================
FShadowDepthPass::FShadowDepthPass(){
   _name = "depth";
   _depthSize.Set(2048, 2048);
   MO_CLEAR(_pRenderTarget);
   MO_CLEAR(_pDepthTexture);
}

//============================================================
// <T>����Ӱ����Ⱦ���̡�</T>
//============================================================
FShadowDepthPass::~FShadowDepthPass(){
   MO_DELETE(_pRenderTarget);
   MO_DELETE(_pDepthTexture);
}

//============================================================
// <T>���ô���</T>
//
// @return ������
//============================================================
TResult FShadowDepthPass::Setup(){
   TResult result = FPipelinePass::Setup();
   FRenderDevice* pRenderDevice = RDeviceManager::Instance().Find<FRenderDevice>();
   // ������ɫ����
   _pDepthTexture = pRenderDevice->CreateFlatTexture();
   _pDepthTexture->SetOwner(this);
   _pDepthTexture->Size().Assign(_depthSize);
   _pDepthTexture->Setup();
   // ������ȾĿ��
   _pRenderTarget = pRenderDevice->CreateTarget();
   _pRenderTarget->SetOptionDepth(ETrue);
   _pRenderTarget->Size().Assign(_depthSize);
   _pRenderTarget->Textures()->Push(_pDepthTexture);
   _pRenderTarget->Setup();
   return result;
}

//============================================================
// <T>���ƿ�ʼ����</T>
//
// @param pRegion ��Ⱦ����
// @return ������
//============================================================
TResult FShadowDepthPass::DrawBegin(FRenderRegion* pRegion){
   TResult resultCd = FPipelinePass::DrawBegin(pRegion);
   //............................................................
   // ���û���Ŀ��
   FRenderDevice* pRenderDevice = RDeviceManager::Instance().Find<FRenderDevice>();
   // ���û���Ŀ��
   if(pRegion->OptionRenderTarget()){
      pRenderDevice->SetRenderTarget(NULL);
   }else{
      pRenderDevice->SetRenderTarget(_pRenderTarget);
   }
   return resultCd;
}

//============================================================
// <T>����������</T>
//
// @return ������
//============================================================
TResult FShadowDepthPass::DrawRegion(FRenderRegion* pRegion){
   TResult resultCd = FPipelinePass::DrawRegion(pRegion);
   return resultCd;
}

//============================================================
// <T>���ƽ�������</T>
//
// @param pRegion ��Ⱦ����
// @return ������
//============================================================
TResult FShadowDepthPass::DrawEnd(FRenderRegion* pRegion){
   TResult resultCd = FPipelinePass::DrawEnd(pRegion);
   return resultCd;
}

MO_NAMESPACE_END
