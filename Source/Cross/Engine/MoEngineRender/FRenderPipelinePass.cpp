#include "MoErPipeline.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FRenderPipelinePass, FPipelinePass);

//============================================================
// <T>������Ⱦ�ܵ����̡�</T>
//============================================================
FRenderPipelinePass::FRenderPipelinePass(){
   MO_CLEAR(_pPipeline);
}

//============================================================
// <T>������Ⱦ�ܵ����̡�</T>
//============================================================
FRenderPipelinePass::~FRenderPipelinePass(){
}

//============================================================
// <T>����������</T>
//
// @return ������
//============================================================
TResult FRenderPipelinePass::DrawRegion(FRenderRegion* pRegion){
   FPipelinePass::DrawRegion(pRegion);
   return ESuccess;
}

MO_NAMESPACE_END
