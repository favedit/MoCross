#include "MoFlLogger.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FLoggerFeature, FFeature);

//============================================================
// <T>������־���ܡ�</T>
//============================================================
 FLoggerFeature::FLoggerFeature(){
}

//============================================================
// <T>������־���ܡ�</T>
//============================================================
FLoggerFeature::~FLoggerFeature(){
}

//============================================================
// <T>���ô���</T>
//
// @return ������
//============================================================
TResult FLoggerFeature::Setup(){
   _netLoggerConsole = FNetLoggerConsole::InstanceCreate();
   return ESuccess;
}

//============================================================
// <T>��������</T>
//
// @return ������
//============================================================
TResult FLoggerFeature::Startup(){
   _netLoggerConsole->Startup();
   return ESuccess;
}

//============================================================
// <T>������</T>
//
// @return ������
//============================================================
TResult FLoggerFeature::Suspend(){
   _netLoggerConsole->Suspend();
   return ESuccess;
}

//============================================================
// <T>��������</T>
//
// @return ������
//============================================================
TResult FLoggerFeature::Resume(){
   _netLoggerConsole->Resume();
   return ESuccess;
}

//============================================================
// <T>ֹͣ����</T>
//
// @return ������
//============================================================
TResult FLoggerFeature::Shutdown(){
   _netLoggerConsole->Shutdown();
   return ESuccess;
}

MO_NAMESPACE_END
