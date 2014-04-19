#ifndef __MO_FI_TOUCH_H__
#define __MO_FI_TOUCH_H__
//************************************************************

#ifndef __MO_FI_COMMON_H__
#include "MoFiCommon.h"
#endif // __MO_FI_COMMON_H__

#ifndef __MO_FI_INPUT_H__
#include "MoFiInput.h"
#endif // __MO_FI_INPUT_H__

MO_NAMESPACE_BEGIN

//============================================================
// <T>�����¼����塣</T>
//============================================================
enum ETouchEvent{
   ETouchEvent_Down  = 0x01,
   ETouchEvent_Movie = 0x02,
   ETouchEvent_Up    = 0x03,
};

//============================================================
// <T>�����¼���</T>
//============================================================
class STouchEvent : public SInputEvent{
public:
   ETouchEvent touchCd;
   SIntPoint2 position;
public:
   //------------------------------------------------------------
   // <T>��������¼���</T>
   STouchEvent(TAny* pSender, ETouchEvent touchCd, TInt x, TInt y) : SInputEvent(pSender){
      this->touchCd = touchCd;
      this->position.Set(x, y);
   }
};
//------------------------------------------------------------
typedef MO_FI_DECLARE TListeners<STouchEvent> TTouchListeners;

//============================================================
// <T>�����豸��</T>
//============================================================
class MO_FI_DECLARE FTouchDevice : public FDevice
{
   MO_CLASS_DECLARE_INHERITS(FTouchDevice, FDevice);
protected:
   TTouchListeners _listenersTouchDown;
   TTouchListeners _listenersTouchMove;
   TTouchListeners _listenersTouchUp;
public:
   FTouchDevice();
   MO_ABSTRACT ~FTouchDevice();
public:
   //------------------------------------------------------------
   // <T>���������¼��������ϡ�</T>
   MO_INLINE TTouchListeners& ListenersTouchDown(){
      return _listenersTouchDown;
   }
   //------------------------------------------------------------
   // <T>�������ƶ����������ϡ�</T>
   MO_INLINE TTouchListeners& ListenersTouchMove(){
      return _listenersTouchMove;
   }
   //------------------------------------------------------------
   // <T>������̧����������ϡ�</T>
   MO_INLINE TTouchListeners& ListenersTouchUp(){
      return _listenersTouchUp;
   }
public:
   MO_ABSTRACT TResult Setup();
};

MO_NAMESPACE_END

//************************************************************
#endif // __MO_FI_TOUCH_H__
