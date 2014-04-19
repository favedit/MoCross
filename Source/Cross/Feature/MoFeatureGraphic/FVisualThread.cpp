#include "MoFgVisual.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>����ɼ��̡߳�</T>
//============================================================
FVisualThread::FVisualThread(){
   _interval = 10000;
   MO_CLEAR(_pConsole);
}

//============================================================
// <T>�����ɼ��̡߳�</T>
//============================================================
FVisualThread::~FVisualThread(){
}

//============================================================
// <T>�߼�����</T>
//
// @return ������
//============================================================
TResult FVisualThread::Process(){
   while(!IsStop()){
      _pConsole->Process();
      SleepMicro(_interval);
   }
   return ESuccess;
}

MO_NAMESPACE_END
