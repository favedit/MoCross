#include "MoFrContentPipeline.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FContentPipeline, FInstance);

//============================================================
// <T>�������ݹܵ���</T>
//============================================================
FContentPipeline::FContentPipeline(){
}

//============================================================
// <T>�������ݹܵ���</T>
//============================================================
FContentPipeline::~FContentPipeline(){
}

//============================================================
// <T>���ݴ���</T>
//
// @param pLoader ������
// @return ������
//============================================================
TResult FContentPipeline::Process(FContentLoader* pLoader){
   MO_FATAL_UNSUPPORT();
   return ESuccess;
}

MO_NAMESPACE_END
