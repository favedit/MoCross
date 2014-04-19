#include "MoFmCore.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>����ؼ��������̨��</T>
//============================================================
FUiFaceConsole::FUiFaceConsole(){
   _pControlConsole = MO_CREATE(FUiControlConsole);
   _pFrameConsole = MO_CREATE(FUiFrameConsole);
}

//============================================================
// <T>������ʾ�������̨��</T>
//============================================================
FUiFaceConsole::~FUiFaceConsole(){
   MO_DELETE(_pControlConsole);
   MO_DELETE(_pFrameConsole);
}

//============================================================
// <T>���ô���</T>
//
// @return ������
//============================================================
TResult FUiFaceConsole::Setup(){
   _pControlConsole->Setup();
   return ESuccess;
}

//============================================================
// <T>�򿪴���</T>
//
// @return ������
//============================================================
TResult FUiFaceConsole::Open(){
   _pFrameConsole->Open();
   return ESuccess;
}

MO_NAMESPACE_END
