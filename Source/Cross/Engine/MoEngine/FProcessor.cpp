#include "MoEgProcessor.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FProcessor, FInstance);

//============================================================
// <T>����ʵ��3D������������</T>
//============================================================
FProcessor::FProcessor(){
   _pThread = MO_CREATE(FProcessorThread);
}

//============================================================
// <T>����ʵ��3D������������</T>
//============================================================
FProcessor::~FProcessor(){
}

//============================================================
// <T>ע��һ����������</T>
//
// @param pProcessor ������
// @return ������
//============================================================
TResult FProcessor::Register(IProcessor* pProcessor){
   TResult result = _pThread->Register(pProcessor);
   return result;
}

//============================================================
// <T>ע��һ����������</T>
//
// @param pProcessor ������
// @return ������
//============================================================
TResult FProcessor::Unregister(IProcessor* pProcessor){
   TResult result = _pThread->Unregister(pProcessor);
   return result;
}

//============================================================
// <T>��������</T>
//
// @return ������
//============================================================
TResult FProcessor::Startup(){
   _pThread->Start();
   return ESuccess;
}

//============================================================
// <T>��������</T>
//
// @return ������
//============================================================
TResult FProcessor::Shutdown(){
   _pThread->Stop();
   _pThread->Terminate();
   return ESuccess;
}

//============================================================
// <T>��մ���</T>
//
// @return ������
//============================================================
TResult FProcessor::Clear(){
   TResult result = _pThread->Clear();
   return result;
}

MO_NAMESPACE_END
