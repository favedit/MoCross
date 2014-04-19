#ifndef __MO_FI_INPUT_H__
#define __MO_FI_INPUT_H__
//************************************************************

#ifndef __MO_FI_COMMON_H__
#include "MoFiCommon.h"
#endif // __MO_FI_COMMON_H__

MO_NAMESPACE_BEGIN

//============================================================
// <T>�����¼����塣</T>
//============================================================
enum EInputEvent{
   EInputEvent_Down,
   EInputEvent_Move,
   EInputEvent_Up,
};
//------------------------------------------------------------
typedef TInt TInputCode;

//============================================================
// <T>�����¼���</T>
//============================================================
class SInputEvent : public SEvent{
public:
   EInputEvent eventCd;
public:
   //------------------------------------------------------------
   // <T>���������¼���</T>
   SInputEvent(TAny* pSender) : SEvent(pSender){
   }
};
//------------------------------------------------------------
typedef MO_FI_DECLARE FList<SInputEvent*> FInputEventList;
typedef MO_FI_DECLARE TListeners<SInputEvent> TInputListeners;

//============================================================
// <T>�����豸��</T>
//============================================================
class MO_FI_DECLARE FInputDevice : public FDevice
{
   MO_CLASS_DECLARE_INHERITS(FInputDevice, FDevice);
protected:
   TThreadLocker _locker;
   TInt _processLimit;
   FInputEventList* _pEvents;
   TInputListeners _listenersInput;
public:
   FInputDevice();
   MO_ABSTRACT ~FInputDevice();
public:
   //------------------------------------------------------------
   // <T>���������������ϡ�</T>
   MO_INLINE TInputListeners& ListenersInput(){
      return _listenersInput;
   }
public:
   MO_ABSTRACT TResult DoEvent(SInputEvent* pEvent);
public:
   MO_ABSTRACT TResult Process();
};

MO_NAMESPACE_END

//************************************************************
#endif // __MO_FI_INPUT_H__
