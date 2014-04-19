#include "MoEngineRender.h"
      
MO_NAMESPACE_BEGIN

//============================================================
// <T>��ʼ����Ⱦ���洦��</T>
//============================================================
void MoEngineRenderInitialize(){
   MO_STATIC_INFO("Engine Render initialize.");
}

//============================================================
// <T>������Ⱦ���洦��</T>
//============================================================
void MoEngineRenderStartup(){
   MO_STATIC_INFO("Engine Render startup.");
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
}

//============================================================
// <T>�ر���Ⱦ���洦��</T>
//============================================================
void MoEngineRenderShutdown(){
   MO_STATIC_INFO("Engine Render shutdown.");
}

//============================================================
// <T>�ͷ���Ⱦ���洦��</T>
//============================================================
void MoEngineRenderRelease(){
   MO_STATIC_INFO("Engine Render release.");
}

MO_NAMESPACE_END
