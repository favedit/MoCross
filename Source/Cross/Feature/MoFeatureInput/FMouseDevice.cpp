#include "MoFiMouse.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FMouseDevice, FDevice);

//============================================================
// <T>��������豸��</T>
//============================================================
FMouseDevice::FMouseDevice(){
   _name = "mouse.device";
   _buttonLeftDown = EFalse;
   _buttonMiddleDown = EFalse;
   _buttonRightDown = EFalse;
}

//============================================================
// <T>��������豸��</T>
//============================================================
FMouseDevice::~FMouseDevice(){
}

//============================================================
// <T>���ô���</T>
//
// @return ������
//============================================================
TResult FMouseDevice::Setup(){
   return ESuccess;
}

//============================================================
// <T>����������¡�</T>
//
// @param buttons ��������
// @return �Ƿ�����
//============================================================
TBool FMouseDevice::TestMouseDownLeft(){
   return TestMouseDown(EMouseButton_Left);
}

//============================================================
// <T>����������¡�</T>
//
// @param buttons ��������
// @return �Ƿ�����
//============================================================
TBool FMouseDevice::TestMouseDownMiddle(){
   return TestMouseDown(EMouseButton_Middle);
}

//============================================================
// <T>����������¡�</T>
//
// @param buttons ��������
// @return �Ƿ�����
//============================================================
TBool FMouseDevice::TestMouseDownRight(){
   return TestMouseDown(EMouseButton_Right);
}

//============================================================
// <T>����������¡�</T>
//
// @param buttons ��������
// @return �Ƿ�����
//============================================================
TBool FMouseDevice::TestMouseDown(TMouseButtons buttons){
   TBool result = EFalse;
   // �������
   if((buttons & EMouseButton_Left) == EMouseButton_Left){
      if(!_buttonLeftDown){
         return EFalse;
      }
      result = ETrue;
   }
   // �����м�
   if((buttons & EMouseButton_Middle) == EMouseButton_Middle){
      if(!_buttonMiddleDown){
         return EFalse;
      }
      result = ETrue;
   }
   // �����Ҽ�
   if((buttons & EMouseButton_Right) == EMouseButton_Right){
      if(!_buttonRightDown){
         return EFalse;
      }
      result = ETrue;
   }
   return result;
}

//============================================================
// <T>��������</T>
//
// @param buttons ����
// @param x ������
// @param y ������
//============================================================
void FMouseDevice::DoClick(TMouseButtons buttons, TInt x, TInt y){
   // ��������
   _position.Set(x, y);
   // �ַ�����
   SMouseEvent event(this, buttons, x, y);
   _listenersClick.Process(&event);
}

//============================================================
// <T>˫������</T>
//
// @param buttons ����
// @param x ������
// @param y ������
//============================================================
void FMouseDevice::DoDoubleClick(TMouseButtons buttons, TInt x, TInt y){
   // ��������
   _position.Set(x, y);
   // �ַ�����
   SMouseEvent event(this, buttons, x, y);
   _listenersDoubleClick.Process(&event);
}

//============================================================
// <T>������´���</T>
//
// @param buttons ����
// @param x ������
// @param y ������
//============================================================
void FMouseDevice::DoMouseDown(TMouseButtons buttons, TInt x, TInt y){
   // ���ð���
   if((buttons & EMouseButton_Left) == EMouseButton_Left){
      _buttonLeftDown = ETrue;
   }
   if((buttons & EMouseButton_Middle) == EMouseButton_Middle){
      _buttonMiddleDown = ETrue;
   }
   if((buttons & EMouseButton_Right) == EMouseButton_Right){
      _buttonRightDown = ETrue;
   }
   // ��������
   _positionDown.Set(x, y);
   _position.Set(x, y);
   // �ַ�����
   SMouseEvent event(this, buttons, x, y);
   _listenersMouseDown.Process(&event);
}

//============================================================
// <T>����ƶ�����</T>
//
// @param buttons ����
// @param x ������
// @param y ������
//============================================================
void FMouseDevice::DoMouseMove(TMouseButtons buttons, TInt x, TInt y){
   // ��������
   _position.Set(x, y);
   // �ַ�����
   SMouseEvent event(this, buttons, x, y);
   _listenersMouseMove.Process(&event);
}

//============================================================
// <T>���̧����</T>
//
// @param buttons ����
// @param x ������
// @param y ������
//============================================================
void FMouseDevice::DoMouseUp(TMouseButtons buttons, TInt x, TInt y){
   // ���ð���
   if((buttons & EMouseButton_Left) == EMouseButton_Left){
      _buttonLeftDown = EFalse;
   }
   if((buttons & EMouseButton_Middle) == EMouseButton_Middle){
      _buttonMiddleDown = EFalse;
   }
   if((buttons & EMouseButton_Right) == EMouseButton_Right){
      _buttonRightDown = EFalse;
   }
   // ��������
   _position.Set(x, y);
   // �ַ�����
   SMouseEvent event(this, buttons, x, y);
   _listenersMouseUp.Process(&event);
}

MO_NAMESPACE_END
