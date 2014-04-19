#include "MoErPipeline.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FShadowPipeline, FPipeline);

//============================================================
// <T>������Ӱ��Ⱦ�ܵ���</T>
//============================================================
FShadowPipeline::FShadowPipeline(){
   _name = "shadow";
}

//============================================================
// <T>������Ӱ��Ⱦ�ܵ���</T>
//============================================================
FShadowPipeline::~FShadowPipeline(){
}

//============================================================
// <T>���ô���</T>
//
// @return ������
//============================================================
TResult FShadowPipeline::OnSetup(){
   TResult result = FPipeline::OnSetup();
   // ������Ӱ��Ⱦ����
   _pShadowDepthPass = MO_CREATE(FShadowDepthPass);
   _pShadowDepthPass->SetPipeline(this);
   _pShadowDepthPass->Setup();
   _pPasses->Push(_pShadowDepthPass);
   // ������ɫ��Ⱦ����
   _pShadowColorPass = MO_CREATE(FShadowColorPass);
   _pShadowColorPass->Setup();
   _pShadowColorPass->SetPipeline(this);
   _pPasses->Push(_pShadowColorPass);
   // ���ù���
   FRenderTexture* pDepthTexture = _pShadowDepthPass->DepthTexture();
   _pShadowColorPass->SetLightDepthTexture(pDepthTexture);
   return result;
}

MO_NAMESPACE_END
