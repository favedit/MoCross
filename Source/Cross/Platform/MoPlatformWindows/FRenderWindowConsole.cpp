#include "MoEwWindow.h"

MO_NAMESPACE_BEGIN

static TBool g_runable = ETrue;

//============================================================
// <T>������Ⱦ���ڿ���̨��</T>
//============================================================
FRenderWindowConsole::FRenderWindowConsole(){
   _pWindows = MO_CREATE(FRenderWindowCollection);
}

//============================================================
// <T>������Ⱦ���ڿ���̨��</T>
//============================================================
FRenderWindowConsole::~FRenderWindowConsole(){
   MO_DELETE(_pWindows);
}

//============================================================
// <T>���ݾ�����Ҵ��ڶ���</T>
//
// @param hWindow ���ھ��
// @return ���ڶ���
//============================================================
FRenderWindow* FRenderWindowConsole::FindByHandle(HWND hWindow){
   TInt count = _pWindows->Count();
   for(TInt n = 0; n < count; n++){
      FRenderWindow* pWindow = _pWindows->Get(n);
      if(pWindow->Handle() == hWindow){
         return pWindow;
      }
   }
   return NULL;
}

//============================================================
// <T>ע��һ�����ڶ���</T>
//
// @param pWindow ����
// @return ������
//============================================================
TResult FRenderWindowConsole::Register(FRenderWindow* pWindow){
   MO_CHECK(pWindow, return ENull);
   _pWindows->Push(pWindow);
   return ESuccess;
}

//============================================================
// <T>ע��һ�����ڶ���</T>
//
// @param pWindow ����
// @return ������
//============================================================
TResult FRenderWindowConsole::Unregister(FRenderWindow* pWindow){
   MO_CHECK(pWindow, return ENull);
   _pWindows->Remove(pWindow);
   return ESuccess;
}

MO_NAMESPACE_END
