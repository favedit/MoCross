#include "MoEgProcessor.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>�����첽�����̡߳�</T>
//============================================================
FProcessorThread::FProcessorThread(){
   _name = "processor.thread";
   _interval = 10000;
   _looperLimit = 16;
   _pLooper = MO_CREATE(FProcessorLooper);
}

//============================================================
// <T>�����첽�����̡߳�</T>
//============================================================
FProcessorThread::~FProcessorThread(){
   MO_DELETE(_pLooper);
}

//============================================================
// <T>ע��һ����������</T>
//
// @param pProcessor ������
// @return ������
//============================================================
TResult FProcessorThread::Register(IProcessor* pProcessor){
   _locker.Enter();
   _pLooper->Push(pProcessor);
   _locker.Leave();
   return ESuccess;
}

//============================================================
// <T>ע��һ����������</T>
//
// @param pProcessor ������
// @return ������
//============================================================
TResult FProcessorThread::Unregister(IProcessor* pProcessor){
   _locker.Enter();
   _pLooper->Remove(pProcessor);
   _locker.Leave();
   return ESuccess;
}

//============================================================
// <T>�߼�����</T>
//
// @return ������
//============================================================
TResult FProcessorThread::Process(){
   while(!IsStop()){
      TBool statusPause = RDeviceManager::Instance().StatusPause();
      if(!statusPause){
         // ִ�д���
         _locker.Enter();
         _pLooper->Record();
         for(TInt n = 0; n < _looperLimit; n++){
            IProcessor* pProcessor = _pLooper->Next();
            if(pProcessor == NULL){
               break;
            }
            if(!IsStop()){
               pProcessor->AnsyProcess();
            }
         }
         _locker.Leave();
      }
      // ��Ϣ����
      SleepMicro(_interval);
   }
   return ESuccess;
}

//============================================================
// <T>��մ���</T>
//
// @return ������
//============================================================
TResult FProcessorThread::Clear(){
   _locker.Enter();
   _pLooper->Clear();
   _locker.Leave();
   return ESuccess;
}

MO_NAMESPACE_END
