#ifndef __MO_FI_MOUSE_H__
#define __MO_FI_MOUSE_H__
//************************************************************

#ifndef __MO_FI_COMMON_H__
#include "MoFiCommon.h"
#endif // __MO_FI_COMMON_H__

MO_NAMESPACE_BEGIN

//============================================================
// <T>��갴�����塣</T>
//============================================================
enum EMouseButton{
   EMouseButton_Left = 0x01,
   EMouseButton_Middle = 0x02,
   EMouseButton_Right = 0x04,
};
//------------------------------------------------------------
typedef TInt TMouseButtons;

//============================================================
// <T>����¼���</T>
//============================================================
class SMouseEvent : public SEvent{
public:
   TMouseButtons buttons;
   SIntPoint2 position;
public:
   //------------------------------------------------------------
   // <T>��������¼���</T>
   SMouseEvent(TAny* pSender, TMouseButtons buttons, TInt x, TInt y) : SEvent(pSender){
      this->buttons = buttons;
      this->position.Set(x, y);
   }
};
//------------------------------------------------------------
typedef MO_FI_DECLARE TListeners<SMouseEvent> TMouseListeners;

//============================================================
// <T>����豸��</T>
//============================================================
class MO_FI_DECLARE FMouseDevice : public FDevice
{
   MO_CLASS_DECLARE_INHERITS(FMouseDevice, FDevice);
protected:
   TBool _buttonLeftDown;
   TBool _buttonMiddleDown;
   TBool _buttonRightDown;
   SIntPoint2 _positionDown;
   SIntPoint2 _position;
   TMouseListeners _listenersClick;
   TMouseListeners _listenersDoubleClick;
   TMouseListeners _listenersMouseDown;
   TMouseListeners _listenersMouseMove;
   TMouseListeners _listenersMouseUp;
public:
   FMouseDevice();
   MO_ABSTRACT ~FMouseDevice();
public:
   //------------------------------------------------------------
   // <T>������ꡣ</T>
   MO_INLINE SIntPoint2& Position(){
      return _position;
   }
   //------------------------------------------------------------
   // <T>��õ������������ϡ�</T>
   MO_INLINE TMouseListeners& ListenersClick(){
      return _listenersClick;
   }
   //------------------------------------------------------------
   // <T>���˫�����������ϡ�</T>
   MO_INLINE TMouseListeners& ListenersDoubleClick(){
      return _listenersDoubleClick;
   }
   //------------------------------------------------------------
   // <T>���������¼��������ϡ�</T>
   MO_INLINE TMouseListeners& ListenersMouseDown(){
      return _listenersMouseDown;
   }
   //------------------------------------------------------------
   // <T>�������ƶ����������ϡ�</T>
   MO_INLINE TMouseListeners& ListenersMouseMove(){
      return _listenersMouseMove;
   }
   //------------------------------------------------------------
   // <T>������̧����������ϡ�</T>
   MO_INLINE TMouseListeners& ListenersMouseUp(){
      return _listenersMouseUp;
   }
   //------------------------------------------------------------
   // <T>���������º��ƶ���Ϣ��</T>
   MO_INLINE SIntPoint2 CalculateMove(){
      return SIntPoint2(_position.x - _positionDown.x, _position.y - _positionDown.y);
   }
public:
   MO_ABSTRACT TResult Setup();
public:
   TBool TestMouseDownLeft();
   TBool TestMouseDownMiddle();
   TBool TestMouseDownRight();
   TBool TestMouseDown(TMouseButtons buttons);
public:
   MO_ABSTRACT void DoClick(TMouseButtons buttons, TInt x, TInt y);
   MO_ABSTRACT void DoDoubleClick(TMouseButtons buttons, TInt x, TInt y);
   MO_ABSTRACT void DoMouseDown(TMouseButtons buttons, TInt x, TInt y);
   MO_ABSTRACT void DoMouseMove(TMouseButtons buttons, TInt x, TInt y);
   MO_ABSTRACT void DoMouseUp(TMouseButtons buttons, TInt x, TInt y);
};

MO_NAMESPACE_END

//************************************************************
#endif // __MO_FI_MOUSE_H__
