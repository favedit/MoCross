#include "MoEgProcessor.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>�����첽�������̨��</T>
//============================================================
FProcessorConsole::FProcessorConsole(){
   _pProcessores = MO_CREATE(FProcessorCollection);
}

//============================================================
// <T>�����첽�������̨��</T>
//============================================================
FProcessorConsole::~FProcessorConsole(){
   MO_DELETE(_pProcessores);
}

//============================================================
// <T>ע��һ����������</T>
//
// @param pProcessor ������
// @return ������
//============================================================
TResult FProcessorConsole::Register(FProcessor* pProcessor){
   _pProcessores->Push(pProcessor);
   return ESuccess;
}

//============================================================
// <T>ע��һ����������</T>
//
// @param pProcessor ������
// @return ������
//============================================================
TResult FProcessorConsole::Unregister(FProcessor* pProcessor){
   _pProcessores->Remove(pProcessor);
   return ESuccess;
}

//============================================================
// <T>��������</T>
//
// @return ������
//============================================================
TResult FProcessorConsole::Startup(){
   FProcessorCollection::TIteratorC iterator = _pProcessores->IteratorC();
   while(iterator.Next()){
      FProcessor* pProcessor = *iterator;
      pProcessor->Startup();
   }
   return ESuccess;
}

//============================================================
// <T>��������</T>
//
// @return ������
//============================================================
TResult FProcessorConsole::Shutdown(){
   FProcessorCollection::TIteratorC iterator = _pProcessores->IteratorC();
   while(iterator.Next()){
      FProcessor* pProcessor = *iterator;
      pProcessor->Shutdown();
   }
   return ESuccess;
}

MO_NAMESPACE_END
