#include "MoFlNet.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FNetLoggerConsole, FConsole);

//============================================================
// <T>����������־����̨��</T>
//============================================================
FNetLoggerConsole::FNetLoggerConsole(){
   _name = "Net.Logger.Console";
}

//============================================================
// <T>����������־����̨��</T>
//============================================================
FNetLoggerConsole::~FNetLoggerConsole(){
}

//============================================================
// <T>ע��һ����д����</T>
//
// @param pWriter ��д��
//============================================================
void FNetLoggerConsole::Register(FNetLoggerWriter* pWriter){
   _writers.Push(pWriter);
   RLoggerManager::Instance().Register(pWriter);
}

//============================================================
// <T>ע��һ����д����</T>
//
// @param pWriter ��д��
//============================================================
void FNetLoggerConsole::Unregister(FNetLoggerWriter* pWriter){
   _writers.Remove(pWriter);
}

//============================================================
// <T>��������</T>
//
// @return ������
//============================================================
TResult FNetLoggerConsole::Startup(){
   return ESuccess;
}

//============================================================
// <T>������</T>
//
// @return ������
//============================================================
TResult FNetLoggerConsole::Suspend(){
   return ESuccess;
}

//============================================================
// <T>��������</T>
//
// @return ������
//============================================================
TResult FNetLoggerConsole::Resume(){
   return ESuccess;
}

//============================================================
// <T>ֹͣ����</T>
//
// @return ������
//============================================================
TResult FNetLoggerConsole::Shutdown(){
   return ESuccess;
}

MO_NAMESPACE_END
