#include "MoCrFeature.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FFeature, FConsole);

//============================================================
// <T>���칦�ܡ�</T>
//============================================================
FFeature::FFeature(){
   _name = "Feature";
}

//============================================================
// <T>�������ܡ�</T>
//============================================================
FFeature::~FFeature(){
}

//============================================================
// <T>��������</T>
//
// @return ������
//============================================================
TResult FFeature::Startup(){
   MO_INFO("Feature startup. (name=%s)", (TCharC*)_name);
   return ESuccess;
}

//============================================================
// <T>������</T>
//
// @return ������
//============================================================
TResult FFeature::Suspend(){
   MO_INFO("Feature suspend. (name=%s)", (TCharC*)_name);
   return ESuccess;
}

//============================================================
// <T>��������</T>
//
// @return ������
//============================================================
TResult FFeature::Resume(){
   MO_INFO("Feature resume. (name=%s)", (TCharC*)_name);
   return ESuccess;
}

//============================================================
// <T>ֹͣ����</T>
//
// @return ������
//============================================================
TResult FFeature::Shutdown(){
   MO_INFO("Feature shutdown. (name=%s)", (TCharC*)_name);
   return ESuccess;
}

MO_NAMESPACE_END
