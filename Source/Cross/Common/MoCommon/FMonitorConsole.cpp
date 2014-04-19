#include "MoCmMonitor.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>����̱߳�ʶ��</T>
//
// @return ��ǰʵ��ָ��
//============================================================
FMonitorConsole::FMonitorConsole(){
   _pMachine = MO_CREATE(FMonitorMachine);
   _pThread = NULL;

}
//============================================================
FMonitorConsole::~FMonitorConsole(){
   MO_DELETE(_pMachine);
}

//============================================================
FMonitorMachine* FMonitorConsole::Machine(){
   return _pMachine;
}

//============================================================
void FMonitorConsole::Register(IMonitor* pMonitor){
   _pMachine->Register(pMonitor);
}

//============================================================
void FMonitorConsole::Unregister(IMonitor* pMonitor){
   _pMachine->Unregister(pMonitor);
}

//============================================================
void FMonitorConsole::Startup(){
   // ���������
   _pMachine->Startup();
   // ���������߳�
   _pThread = MO_CREATE(FMonitorThread, _pMachine);
   _pThread->Start();
}

//============================================================
void FMonitorConsole::Shutdown(){
   MO_ASSERT(_pThread);
   _pThread->Stop();
}

void FMonitorConsole::Execute(){
   _pMachine->Execute();
}

MO_NAMESPACE_END
