#ifndef __MO_ER_SIMPLE_PIPELINE_H__
#define __MO_ER_SIMPLE_PIPELINE_H__
//************************************************************

#ifndef __MO_ER_COMMON_H__
#include "MoErCommon.h"
#endif // __MO_ER_COMMON_H__

#ifndef __MO_ER_TECHNIQUE_H__
#include "MoErTechnique.h"
#endif // __MO_ER_TECHNIQUE_H__

MO_NAMESPACE_BEGIN

//============================================================
// <T>����ɫ�Զ���Ⱦ����</T>
//============================================================
class MO_ER_DECLARE FSampleColorAutomaticEffect : public FColorAutomaticEffect
{
   MO_CLASS_DECLARE_INHERITS(FSampleColorAutomaticEffect, FColorAutomaticEffect);
protected:
   SFloatMatrix3d _modelMatrixs[MO_EG_CONST_MATRIX_MAX];
public:
   FSampleColorAutomaticEffect();
   MO_ABSTRACT ~FSampleColorAutomaticEffect();
};

//============================================================
// <T>����ɫ������Ⱦ����</T>
//============================================================
class MO_ER_DECLARE FSampleColorSkeletonEffect : public FColorAutomaticEffect
{
   MO_CLASS_DECLARE_INHERITS(FSampleColorSkeletonEffect, FColorAutomaticEffect);
protected:
   SFloatMatrix3d _modelMatrixs[MO_EG_CONST_MATRIX_MAX];
   SFloatMatrix3d _boneMatrixs[MO_EG_CONST_MATRIX_MAX];
public:
   FSampleColorSkeletonEffect();
   MO_ABSTRACT ~FSampleColorSkeletonEffect();
public:
   MO_OVERRIDE TResult OnSetup();
public:
   MO_OVERRIDE TResult BuildTemplate(SRenderableDescriptor& renderableDescriptor, MString* pCode, FTemplateContext* pTemplateContext);
public:
   MO_OVERRIDE TResult DrawRenderable(FRenderRegion* pRegion, FRenderable* pRenderable);
   MO_OVERRIDE TResult DrawInstanceRenderable(FRenderRegion* pRegion, FInstanceRenderable* pInstanceRenderable, TInt offset, TInt count);
};

//============================================================
// <T>����ɫ��Ⱦ���̡�</T>
//============================================================
class MO_ER_DECLARE FSimpleColorPass : public FPipelinePass
{
   MO_CLASS_DECLARE_INHERITS(FSimpleColorPass, FPipelinePass);
public:
   FSimpleColorPass();
   MO_ABSTRACT ~FSimpleColorPass();
public:
   MO_ABSTRACT TResult DrawRegion(FRenderRegion* pRegion);
};

//============================================================
// <T>����Ⱦ�ܵ���</T>
//============================================================
class MO_ER_DECLARE FSimplePipeline : public FPipeline
{
   MO_CLASS_DECLARE_INHERITS(FSimplePipeline, FPipeline);
public:
   FSimplePipeline();
   MO_ABSTRACT ~FSimplePipeline();
public:
   MO_OVERRIDE TResult OnSetup();
};

MO_NAMESPACE_END

//************************************************************
#endif // __MO_ER_SIMPLE_PIPELINE_H__
