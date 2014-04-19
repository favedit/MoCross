#include "MoCrStatistics.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>����ͳ����Ϣ��������</T>
//============================================================
FStatisticsMonitor::FStatisticsMonitor(){
   _name = TC("Core.Statistics.Monitor");
   MO_CLEAR(_pConsole);
}

//============================================================
// <T>����ͳ����Ϣ��������</T>
//============================================================
FStatisticsMonitor::~FStatisticsMonitor(){
}

//============================================================
// <T>ˢ�´���</T>
//
// @return ������
//============================================================
TResult FStatisticsMonitor::Process(){
   TInt result = ESuccess;
   if(NULL != _pConsole){
      result = _pConsole->TriggerRefresh(_currentTimeTick);
   }
   return result;
}

MO_NAMESPACE_END
