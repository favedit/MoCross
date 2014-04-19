#include "MoE3Display.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>����ʵ��3D������������</T>
//============================================================
FAnimation3dConsole::FAnimation3dConsole(){
   _pThread = MO_CREATE(FAnimation3dThread);
}

//============================================================
// <T>����ʵ��3D������������</T>
//============================================================
FAnimation3dConsole::~FAnimation3dConsole(){
}

//============================================================
// <T>�������ƻ�ò���ʵ����</T>
//
// @param pName ����
// @return ����ʵ��
//============================================================
TResult FAnimation3dConsole::Register(FAnimation3d* pAnimation){
   TResult result = _pThread->Register(pAnimation);
   return result;
}

//============================================================
// <T>�������ƻ�ò���ʵ����</T>
//
// @param pName ����
// @return ����ʵ��
//============================================================
TResult FAnimation3dConsole::Unregister(FAnimation3d* pAnimation){
   TResult result = _pThread->Unregister(pAnimation);
   return result;
}

//============================================================
// <T>��������</T>
//
// @return ������
//============================================================
TResult FAnimation3dConsole::Startup(){
   _pThread->Start();
   return ESuccess;
}

//============================================================
// <T>��������</T>
//
// @return ������
//============================================================
TResult FAnimation3dConsole::Shutdown(){
   _pThread->Stop();
   return ESuccess;
}

//============================================================
// <T>��մ���</T>
//
// @return ������
//============================================================
TResult FAnimation3dConsole::Clear(){
   TResult result = _pThread->Clear();
   return result;
}

MO_NAMESPACE_END
