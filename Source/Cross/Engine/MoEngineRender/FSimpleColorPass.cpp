#include "MoErSimplePipeline.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FSimpleColorPass, FPipelinePass);

//============================================================
// <T>�������ɫ��Ⱦ���̡�</T>
//============================================================
FSimpleColorPass::FSimpleColorPass(){
   _name = "color";
}

//============================================================
// <T>��������ɫ��Ⱦ���̡�</T>
//============================================================
FSimpleColorPass::~FSimpleColorPass(){
}

//============================================================
// <T>����������</T>
//
// @return ������
//============================================================
TResult FSimpleColorPass::DrawRegion(FRenderRegion* pRegion){
   FPipelinePass::DrawRegion(pRegion);
   return ESuccess;
}

MO_NAMESPACE_END
