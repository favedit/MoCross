#include "MoEwWindow.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>������Ⱦ�̡߳�</T>
//============================================================
FRenderThread::FRenderThread(){
   _interval = 10000;
   MO_CLEAR(_pWindow);
}

//============================================================
// <T>������Ⱦ�̡߳�</T>
//============================================================
FRenderThread::~FRenderThread(){
}

//============================================================
// <T>�߼�����</T>
//
// @return ������
//============================================================
TResult FRenderThread::Process(){
   while(!IsStop()){
      TBool statusPause = RDeviceManager::Instance().StatusPause();
      if(!statusPause){
         _pWindow->ProcessRender();
      }
      SleepMicro(_interval);
   }
   return ESuccess;
}

MO_NAMESPACE_END
