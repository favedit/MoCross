#include "MoFrContent.h"
#include "MoFrContentPipeline.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FContentConsole, FLoader);

//============================================================
// <T>�������ݿ���̨��</T>
//============================================================
FContentConsole::FContentConsole(){
   _pipelineFactory = FClassInstanceFactory::InstanceCreate();
   _pipelineFactory->SetDefaultClass(FContentAssetPipeline::Class());
}

//============================================================
// <T>�������ݿ���̨��</T>
//============================================================
FContentConsole::~FContentConsole(){
}

//============================================================
// <T>����һ����������</T>
//
// @param pLoader ������
// @return ������
//============================================================
TResult FContentConsole::PushLoader(FContentLoader* pLoader){
   pLoader->SetConsole(this);
   RLoaderManager::Instance().PushWaitLoader(pLoader);
   return ESuccess;
}

MO_NAMESPACE_END
