#ifndef __MO_EG_DEVICE_H__
#define __MO_EG_DEVICE_H__
//************************************************************

#ifndef __MO_EG_COMMON_H__
#include "MoEgCommon.h"
#endif // __MO_EG_COMMON_H__

#define MO_KEYBOARD_COUNT 256

MO_NAMESPACE_BEGIN

//============================================================
// <T>��Ļ�豸��</T>
//============================================================
class MO_EG_DECLARE FScreenDevice : public FDevice
{
   MO_CLASS_DECLARE_INHERITS(FScreenDevice, FDevice);
protected:
   // �ߴ�
   SIntSize2 _size;
   // ����
   SIntRectangle _rectangle;
   // �ı��С����������
   TResizeListeners _listenersResize;
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
   MO_INLINE TResizeListeners& ListenersResize(){
      return _listenersResize;
   }
public:
   MO_ABSTRACT TResult Setup();
   MO_ABSTRACT TResult Resize(TInt width, TInt height);
};

//============================================================
// <T>ʱ���豸��</T>
//============================================================
class MO_EG_DECLARE FTimerDevice : public FDevice
{
   MO_CLASS_DECLARE_INHERITS(FTimerDevice, FDevice);
protected:
   TInt _frameCount;
   TTimeTick _startTick;
   TTimeTick _currentTick;
public:
   FTimerDevice();
   MO_ABSTRACT ~FTimerDevice();
public:
   //------------------------------------------------------------
   // <T>��ÿ�ʼʱ�̡�</T>
   MO_INLINE TTimeTick StartTick(){
      return _startTick;
   }
   //------------------------------------------------------------
   // <T>��õ�ǰʱ�̡�</T>
   MO_INLINE TTimeTick CurrentTick(){
      return _currentTick;
   }
   //------------------------------------------------------------
   // <T>��ü����</T>
   MO_INLINE TInt SpanTick(TTimeTick tick){
      return (TInt)(_currentTick - tick);
   }
   //------------------------------------------------------------
   // <T>��ü���롣</T>
   MO_INLINE TFloat SpanSecond(TTimeTick tick){
      return (TFloat)(_currentTick - tick) / 1000000.0f;
   }
public:
   MO_ABSTRACT TInt FramePerSecond();
public:
   MO_ABSTRACT TResult Setup();
   MO_ABSTRACT TResult Update();
};

MO_NAMESPACE_END

//************************************************************
#endif // __MO_EG_DEVICE_H__
