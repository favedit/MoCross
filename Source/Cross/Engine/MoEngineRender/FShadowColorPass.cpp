#include "MoErShadowPipeline.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FShadowColorPass, FPipelinePass);

//============================================================
// <T>����Ӱ����Ⱦ���̡�</T>
//============================================================
FShadowColorPass::FShadowColorPass(){
   _name = "color";
}

//============================================================
// <T>����Ӱ����Ⱦ���̡�</T>
//============================================================
FShadowColorPass::~FShadowColorPass(){
}

//============================================================
// <T>���ô���</T>
//
// @return ������
//============================================================
TResult FShadowColorPass::Setup(){
   TResult result = FPipelinePass::Setup();
   return result;
}

//============================================================
// <T>���ƿ�ʼ����</T>
//
// @param pRegion ��Ⱦ����
// @return ������
//============================================================
TResult FShadowColorPass::DrawBegin(FRenderRegion* pRegion){
   FPipelinePass::DrawBegin(pRegion);
   //............................................................
   // ���û���Ŀ��
   FRenderDevice* pRenderDevice = RDeviceManager::Instance().Find<FRenderDevice>();
   pRenderDevice->SetRenderTarget();
   return ESuccess;
}

//============================================================
// <T>����������</T>
//
// @return ������
//============================================================
TResult FShadowColorPass::DrawRegion(FRenderRegion* pRegion){
   // ��������
   pRegion->Textures()->PushUnique(_lightDepthTexture);
   // ��������
   FPipelinePass::DrawRegion(pRegion);
   return ESuccess;
}

//============================================================
// <T>���ƽ�������</T>
//
// @param pRegion ��Ⱦ����
// @return ������
//============================================================
TResult FShadowColorPass::DrawEnd(FRenderRegion* pRegion){
   TResult resultCd = FPipelinePass::DrawEnd(pRegion);
   return resultCd;
}

MO_NAMESPACE_END
