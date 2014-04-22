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

MO_NAMESPACE_END

//************************************************************
#endif // __MO_EG_DEVICE_H__
