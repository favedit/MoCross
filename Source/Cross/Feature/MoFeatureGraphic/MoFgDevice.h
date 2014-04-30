#ifndef __MO_FG_DEVICE_H__
#define __MO_FG_DEVICE_H__
//************************************************************

#ifndef __MO_FG_COMMON_H__
#include "MoFgCommon.h"
#endif // __MO_FG_COMMON_H__

#define MO_KEYBOARD_COUNT 256

MO_NAMESPACE_BEGIN

//============================================================
// <T>�ı��С�¼���</T>
//============================================================
class SScreenResizeEvent : public SEvent{
public:
   SIntSize2 size;
public:
   //------------------------------------------------------------
   // <T>����ı��С�¼���</T>
   SScreenResizeEvent(TAny* pSender, TInt width, TInt heigh) : SEvent(pSender){
      size.Set(width, heigh);
   }
};
//------------------------------------------------------------
typedef MO_FG_DECLARE TListeners<SScreenResizeEvent> TScreenResizeListeners;

//============================================================
// <T>��Ļ�豸��</T>
//============================================================
class MO_FG_DECLARE FScreenDevice : public FDevice
{
   MO_CLASS_DECLARE_INHERITS(FScreenDevice, FDevice);
protected:
   // �ߴ�
   SIntSize2 _size;
   // ����
   SIntRectangle _rectangle;
   // �ı��С����������
   TScreenResizeListeners _listenersResize;
public:
   FScreenDevice();
   MO_ABSTRACT ~FScreenDevice();
public:
   //------------------------------------------------------------
   // <T>��ô�С��</T>
   MO_INLINE SIntSize2& Size(){
      return _size;
   }
   //------------------------------------------------------------
   // <T>��ô�С��</T>
   MO_INLINE SIntRectangle& Rectangle(){
      return _rectangle;
   }
   //------------------------------------------------------------
   // <T>��øı��С���������ϡ�</T>
   MO_INLINE TScreenResizeListeners& ListenersResize(){
      return _listenersResize;
   }
public:
   MO_ABSTRACT TResult Setup();
   MO_ABSTRACT TResult Resize(TInt width, TInt height);
};

MO_NAMESPACE_END

//************************************************************
#endif // __MO_FG_DEVICE_H__
