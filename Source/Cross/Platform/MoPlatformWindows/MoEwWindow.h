#ifndef __MO_EW_WINDOW_H__
#define __MO_EW_WINDOW_H__

#ifndef __MO_EW_COMMON_H__
#include "MoEwCommon.h"
#endif // __MO_EW_COMMON_H__

MO_NAMESPACE_BEGIN

//============================================================
class FRenderThread;
class FRenderWindow;

//============================================================
// <T>��Ⱦ���ڡ�</T>
//============================================================
class MO_EW_DECLARE FRenderWindow : public FObject{
protected:
   TFsName _className;
   TFsLabel _title;
   SIntSize2 _size;
   TThreadLocker _locker;
   TBool _statusRenderable;
   HWND _handle;
   ATOM _atom;
   HDC _hDC;
   HGLRC _hRC;
   FRenderThread* _pRenderThread;
   FParticleController* _pParticleController;
public:
   FRenderWindow();
   MO_ABSTRACT ~FRenderWindow();
protected:
   static LRESULT CALLBACK OnProcessMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
   void RegisterClass();
public:
   //------------------------------------------------------------
   // <T>��ô�С��</T>
   MO_INLINE SIntSize2& Size(){
      return _size;
   }
   //------------------------------------------------------------
   // <T>��ô��ھ����</T>
   MO_INLINE HWND Handle(){
      return _handle;
   }
   //------------------------------------------------------------
   // <T>��ô���ԭ�ӡ�</T>
   MO_INLINE ATOM Atom(){
      return _atom;
   }
public:
   void Setup();
   void Dispose();
   void Startup();
public:
   void ProcessRender();
   TInt Process();
};

//============================================================
// <T>��Ⱦ�̡߳�</T>
//============================================================
class MO_EW_DECLARE FRenderThread : public FThread{
protected:
   TInt _interval;
   FRenderWindow* _pWindow;
public:
   FRenderThread();
   MO_ABSTRACT ~FRenderThread();
public:
   //------------------------------------------------------------
   // <T>��ô��ڶ���</T>
   MO_INLINE FRenderWindow* Window(){
      return _pWindow;
   }
   //------------------------------------------------------------
   // <T>���ô��ڶ���</T>
   MO_INLINE void SetWindow(FRenderWindow* pWindow){
      _pWindow = pWindow;
   }
public:
   MO_OVERRIDE TResult Process();
};

MO_NAMESPACE_END

#endif //__MO_EW_WINDOW_H__
