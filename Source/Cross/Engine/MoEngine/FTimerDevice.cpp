#include "MoEgDevice.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FTimerDevice, FDevice);

//============================================================
// <T>����ʱ���豸��</T>
//============================================================
FTimerDevice::FTimerDevice(){
   _name = "timer.device";
   _frameCount = 0;
   _startTick = 0;
   _currentTick = 0;
}

//============================================================
// <T>����ʱ���豸��</T>
//============================================================
FTimerDevice::~FTimerDevice(){
}

//============================================================
TInt FTimerDevice::FramePerSecond(){
   if(_frameCount == 0){
      return 0;
   }
   TTimeSpan span = (_currentTick - _startTick);
   return (TInt)(1000000 / (span / _frameCount));
}

//============================================================
// <T>���ô���</T>
//============================================================
TResult FTimerDevice::Setup(){
   _frameCount = 0;
   _startTick = RTimeTick::Current();
   _currentTick = _startTick;
   return ESuccess;
}

//============================================================
// <T>���´���</T>
//============================================================
TResult FTimerDevice::Update(){
   _frameCount++;
   _currentTick = RTimeTick::Current();
   return ESuccess;
}

MO_NAMESPACE_END
