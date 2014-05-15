#include "MoEngineRender.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FEngineRenderFeature, FFeature);

//============================================================
// <T>����ƽ̨DirectX11���ܡ�</T>
//============================================================
FEngineRenderFeature::FEngineRenderFeature(){
   _name = "DirectX 11";
}

//============================================================
// <T>����ƽ̨DirectX11���ܡ�</T>
//============================================================
FEngineRenderFeature::~FEngineRenderFeature(){
}

//============================================================
// <T>���������</T>
//
// @return ������
//============================================================
TResult FEngineRenderFeature::Construct(){
   TResult resultCd = FFeature::Construct();
   // ע��ö����Ϣ
   //REnumeratorManager::Instance().Find<>();
   //MO_RENDERENUM_PARAMETER         "EnumRenderParameter"
   //MO_RENDERENUM_ATTRIBUTE         "EnumRenderAttribute"
   //MO_RENDERENUM_SAMPLER           "EnumRenderSampler"
   // ע����Ⱦ�ܵ�
   RPipelineManager::Instance().Factory()->Register("simple", FSimplePipeline::Class());
   RPipelineManager::Instance().Factory()->Register("shadow", FShadowPipeline::Class());
   RPipelineManager::Instance().Factory()->Register("deferred", FDeferredPipeline::Class());
   // ע����ȾЧ��
   REffectManager::Instance().Factory()->Register("simple.color.automatic", FSampleColorAutomaticEffect::Class());
   REffectManager::Instance().Factory()->Register("simple.color.skeleton", FSampleColorSkeletonEffect::Class());
   REffectManager::Instance().Factory()->Register("shadow.depth.automatic", FShadowDepthAutomaticEffect::Class());
   REffectManager::Instance().Factory()->Register("shadow.depth.skeleton", FShadowDepthSkeletonEffect::Class());
   REffectManager::Instance().Factory()->Register("shadow.color.automatic", FShadowColorAutomaticEffect::Class());
   REffectManager::Instance().Factory()->Register("shadow.color.skeleton", FShadowColorSkeletonEffect::Class());
   REffectManager::Instance().Factory()->Register("color", FBlurEffect::Class());
   REffectManager::Instance().Factory()->Register("blur", FBlurEffect::Class());
   return resultCd;
}

//============================================================
// <T>��������</T>
//
// @return ������
//============================================================
TResult FEngineRenderFeature::Startup(){
   TResult resultCd = FFeature::Startup();
   return resultCd;
}

//============================================================
// <T>������</T>
//
// @return ������
//============================================================
TResult FEngineRenderFeature::Suspend(){
   TResult resultCd = FFeature::Suspend();
   return resultCd;
}

//============================================================
// <T>��������</T>
//
// @return ������
//============================================================
TResult FEngineRenderFeature::Resume(){
   TResult resultCd = FFeature::Resume();
   return resultCd;
}

//============================================================
// <T>ֹͣ����</T>
//
// @return ������
//============================================================
TResult FEngineRenderFeature::Shutdown(){
   TResult resultCd = FFeature::Shutdown();
   return resultCd;
}

//============================================================
// <T>�ͷ������</T>
//
// @return ������
//============================================================
TResult FEngineRenderFeature::Dispose(){
   TResult resultCd = FFeature::Dispose();
   return resultCd;
}

MO_NAMESPACE_END
