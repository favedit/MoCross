#ifndef __MO_ER_SHADOW_PIPELINE_H__
#define __MO_ER_SHADOW_PIPELINE_H__
//************************************************************

#ifndef __MO_ER_COMMON_H__
#include "MoErCommon.h"
#endif // __MO_ER_COMMON_H__

#ifndef __MO_ER_TECHNIQUE_H__
#include "MoErTechnique.h"
#endif // __MO_ER_TECHNIQUE_H__

MO_NAMESPACE_BEGIN

//============================================================
// <T>��Ӱ����Զ���Ⱦ����</T>
//============================================================
class MO_ER_DECLARE FShadowDepthAutomaticEffect : public FAutomaticEffect
{
   MO_CLASS_DECLARE_INHERITS(FShadowDepthAutomaticEffect, FAutomaticEffect);
public:
   FShadowDepthAutomaticEffect();
   MO_ABSTRACT ~FShadowDepthAutomaticEffect();
public:
   MO_OVERRIDE TResult Setup();
public:
   MO_OVERRIDE TResult DrawRenderable(FRenderRegion* pRegion, FRenderable* pRenderable);
   MO_OVERRIDE TResult DrawGroup(FRenderRegion* pRegion, TInt offset, TInt count);
};

//============================================================
// <T>��Ӱ����Զ���Ⱦ����</T>
//============================================================
class MO_ER_DECLARE FShadowDepthSkeletonEffect : public FAutomaticEffect
{
   MO_CLASS_DECLARE_INHERITS(FShadowDepthSkeletonEffect, FAutomaticEffect);
public:
   FShadowDepthSkeletonEffect();
   MO_ABSTRACT ~FShadowDepthSkeletonEffect();
public:
   MO_OVERRIDE TResult Setup();
public:
   MO_OVERRIDE TResult DrawRenderable(FRenderRegion* pRegion, FRenderable* pRenderable);
   MO_OVERRIDE TResult DrawGroup(FRenderRegion* pRegion, TInt offset, TInt count);
};

//============================================================
// <T>��Ӱ��ɫ�Զ���Ⱦ����</T>
//============================================================
class MO_ER_DECLARE FShadowColorAutomaticEffect : public FColorAutomaticEffect
{
   MO_CLASS_DECLARE_INHERITS(FShadowColorAutomaticEffect, FColorAutomaticEffect);
public:
   FShadowColorAutomaticEffect();
   MO_ABSTRACT ~FShadowColorAutomaticEffect();
public:
   MO_OVERRIDE TResult Setup();
public:
   MO_OVERRIDE TResult DrawRenderable(FRenderRegion* pRegion, FRenderable* pRenderable);
   MO_OVERRIDE TResult DrawGroup(FRenderRegion* pRegion, TInt offset, TInt count);
};

//============================================================
// <T>��Ӱ��ɫ�Զ���Ⱦ����</T>
//============================================================
class MO_ER_DECLARE FShadowColorSkeletonEffect : public FColorAutomaticEffect
{
   MO_CLASS_DECLARE_INHERITS(FShadowColorSkeletonEffect, FColorAutomaticEffect);
public:
   FShadowColorSkeletonEffect();
   MO_ABSTRACT ~FShadowColorSkeletonEffect();
public:
   MO_OVERRIDE TResult Setup();
public:
   MO_OVERRIDE TResult DrawRenderable(FRenderRegion* pRegion, FRenderable* pRenderable);
   MO_OVERRIDE TResult DrawGroup(FRenderRegion* pRegion, TInt offset, TInt count);
};

//============================================================
// <T>Ӱ�������Ⱦ���̡�</T>
//============================================================
class MO_ER_DECLARE FShadowDepthPass : public FPipelinePass
{
   MO_CLASS_DECLARE_INHERITS(FShadowDepthPass, FPipelinePass);
protected:
   SIntSize2 _depthSize;
   FRenderTarget* _pRenderTarget;
   FRenderTexture* _pDepthTexture;
public:
   FShadowDepthPass();
   MO_ABSTRACT ~FShadowDepthPass();
public:
   //------------------------------------------------------------
   // <T>�����ȴ�С��</T>
   MO_INLINE SIntSize2& DepthSize(){
      return _depthSize;
   }
   //------------------------------------------------------------
   // <T>�����ȾĿ�ꡣ</T>
   MO_INLINE FRenderTarget* RenderTarget(){
      return _pRenderTarget;
   }
   //------------------------------------------------------------
   // <T>����������</T>
   MO_INLINE FRenderTexture* DepthTexture(){
      return _pDepthTexture;
   }
public:
   MO_ABSTRACT TResult Setup();
public:
   MO_OVERRIDE TResult DrawBegin(FRenderRegion* pRegion);
   MO_OVERRIDE TResult DrawRegion(FRenderRegion* pRegion);
   MO_OVERRIDE TResult DrawEnd(FRenderRegion* pRegion);
};

//============================================================
// <T>Ӱ����ɫ��Ⱦ���̡�</T>
//============================================================
class MO_ER_DECLARE FShadowColorPass : public FPipelinePass
{
   MO_CLASS_DECLARE_INHERITS(FShadowColorPass, FPipelinePass);
protected:
   GPtr<FRenderTexture> _lightDepthTexture;
public:
   FShadowColorPass();
   MO_ABSTRACT ~FShadowColorPass();
public:
   //------------------------------------------------------------
   // <T>��ù�������</T>
   MO_INLINE FRenderTexture* LightDepthTexture(){
      return _lightDepthTexture;
   }
   //------------------------------------------------------------
   // <T>���ù�������</T>
   MO_INLINE void SetLightDepthTexture(FRenderTexture* pLightDepthTexture){
      _lightDepthTexture = pLightDepthTexture;
   }
public:
   MO_ABSTRACT TResult Setup();
public:
   MO_OVERRIDE TResult DrawBegin(FRenderRegion* pRegion);
   MO_OVERRIDE TResult DrawRegion(FRenderRegion* pRegion);
   MO_OVERRIDE TResult DrawEnd(FRenderRegion* pRegion);
};

//============================================================
// <T>��Ӱ��Ⱦ�ܵ���</T>
//============================================================
class MO_ER_DECLARE FShadowPipeline : public FPipeline
{
   MO_CLASS_DECLARE_INHERITS(FShadowPipeline, FPipeline);
protected:
   FShadowDepthPass* _pShadowDepthPass;
   FShadowColorPass* _pShadowColorPass;
public:
   FShadowPipeline();
   MO_ABSTRACT ~FShadowPipeline();
public:
   MO_OVERRIDE TResult OnSetup();
};

MO_NAMESPACE_END

//************************************************************
#endif // __MO_ER_SHADOW_PIPELINE_H__
