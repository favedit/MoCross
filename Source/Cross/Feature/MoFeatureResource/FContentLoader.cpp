#include "MoFrContent.h"
#include "MoFrContentPipeline.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FContentLoader, FLoader);

//============================================================
// <T>�������ݼ�������</T>
//============================================================
FContentLoader::FContentLoader(){
   MO_CLEAR(_pConsole);
}

//============================================================
// <T>�������ݼ�������</T>
//============================================================
FContentLoader::~FContentLoader(){
}

//============================================================
// <T>���ݴ���</T>
//
// @return ������
//============================================================
TResult FContentLoader::Process(){
   TCharC* pTypeName = _content->TypeName();
   FInstance* pPipelineInstance = _pConsole->PipelineFactory()->Find(pTypeName);
   MO_CHECK(pPipelineInstance, return ENull);
   FContentPipeline* pPipeline = pPipelineInstance->Convert<FContentPipeline>();
   pPipeline->Process(this);
   return ESuccess;
}

MO_NAMESPACE_END
