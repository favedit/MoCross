#ifdef _MO_LINUX
#include <unistd.h>
#endif
#include "MoCmMonitor.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>����������̡߳�</T>
//============================================================
FMonitorThread::FMonitorThread(FMonitorMachine* pMachine){
   _pMachine = pMachine;
}

//============================================================
// <T>��������������̡߳�</T>
//
// @return ������
//============================================================
TResult FMonitorThread::Process(){
   // �������
   TTimeSpan interval = _pMachine->Interval();
   // ѭ������
   while(!IsStop()){
      // ��������
      _pMachine->Process();
      // ����
      MO_LIB_SLEEP(interval);
   }
   return ESuccess;
}

MO_NAMESPACE_END
