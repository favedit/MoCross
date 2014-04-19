#include "MoFmRuntime.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>�������н������̨��</T>
//============================================================
FRuntimeFrameConsole::FRuntimeFrameConsole(){
}

//============================================================
// <T>�������н������̨��</T>
//============================================================
FRuntimeFrameConsole::~FRuntimeFrameConsole(){
}

//============================================================
// <T>���ô���</T>
//
// @return ������
//============================================================
TResult FRuntimeFrameConsole::Setup(){
   FUiControlConsole* pControlConsole = RFaceManager::Instance().ControlConsole();
   // ע�Ỻ���
   pControlConsole->PoolRegister(MO_CREATE(FFmRuntimeBarPool));
   pControlConsole->PoolRegister(MO_CREATE(FFmRuntimeWindowPool));
   return ESuccess;
}

MO_NAMESPACE_END
