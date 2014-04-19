#include "MoFiInput.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FInputDevice, FDevice);

//============================================================
// <T>���������豸��</T>
//============================================================
FInputDevice::FInputDevice(){
   _name = "keyboard.device";
   _processLimit = 16;
   _pEvents = MO_CREATE(FInputEventList);
}

//============================================================
// <T>���������豸��</T>
//============================================================
FInputDevice::~FInputDevice(){
   MO_DELETE(_pEvents);
}

//============================================================
// <T>����һ���¼���</T>
//
// @param pEvent �¼�
// @return ������
//============================================================
TResult FInputDevice::DoEvent(SInputEvent* pEvent){
   MO_CHECK(pEvent, return ENull);
   _pEvents->Push(pEvent);
   return ESuccess;
}

//============================================================
// <T>�����¼���</T>
//
// @return ������
//============================================================
TResult FInputDevice::Process(){
   _locker.Enter();
   TInt count = _pEvents->Count();
   TInt loop = MO_LIB_MIN(count, _processLimit);
   for(TInt n = 0; n < loop; n++){
      SInputEvent* pEvent = _pEvents->Shift();
      _listenersInput.Process(pEvent);
      MO_DELETE(pEvent);
   }
   _locker.Leave();
   return ESuccess;
}

MO_NAMESPACE_END
