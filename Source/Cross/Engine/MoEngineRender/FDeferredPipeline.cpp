#include "MoErPipeline.h"

MO_NAMESPACE_BEGIN
   
MO_CLASS_IMPLEMENT_INHERITS(FDeferredPipeline, FPipeline);

//============================================================
// <T>�����ӳ���Ⱦ�ܵ���</T>
//============================================================
FDeferredPipeline::FDeferredPipeline(){
   _name = "deferred";
}

//============================================================
// <T>�����ӳ���Ⱦ�ܵ���</T>
//============================================================
FDeferredPipeline::~FDeferredPipeline(){
}

//============================================================
// <T>���ô���</T>
//
// @return ������
//============================================================
TResult FDeferredPipeline::OnSetup(){
   TResult result = FPipeline::OnSetup();
   return result;
}

MO_NAMESPACE_END
