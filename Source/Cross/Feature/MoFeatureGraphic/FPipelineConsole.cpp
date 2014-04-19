#include "MoFgPipeline.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>������Ⱦ�ܵ�����̨��</T>
//============================================================
FPipelineConsole::FPipelineConsole(){
   _pFactory = MO_CREATE(FClassInstanceFactory);
   MO_CLEAR(_pActivePipeline);
}

//============================================================
// <T>������Ⱦ�ܵ�����̨��</T>
//============================================================
FPipelineConsole::~FPipelineConsole(){
   MO_DELETE(_pFactory);
}

//============================================================
// <T>ѡ�񼤻����Ⱦ�ܵ���</T>
//
// @param pName ����
// return ��Ⱦ�ܵ�
//============================================================
FPipeline* FPipelineConsole::SelectPipeline(TCharC* pName){
   FPipeline* pPipeline = (FPipeline*)_pFactory->Get(pName);
   pPipeline->Setup();
   _pActivePipeline = pPipeline;
   return pPipeline;
}

MO_NAMESPACE_END
