#include "MoPsmScript.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FMonoClass, FScriptClass);

//============================================================
// <T>����ű������</T>
//============================================================
FMonoClass::FMonoClass(){
   MO_CLEAR(_pMonoClass);
}

//============================================================
// <T>�����ű������</T>
//============================================================
FMonoClass::~FMonoClass(){
}

//============================================================
// <T>����ʵ������</T>
//
// @return ʵ������
//============================================================
FScriptInstance* FMonoClass::CreateInstance(){
   FMonoMachine* pMachine = (FMonoMachine*)_pScriptLibrary->ScriptMachine();
   // ִ�к���
   MonoObject* pMonoObject = mono_object_new(pMachine->NativeDomain(), _pMonoClass);
   mono_runtime_object_init(pMonoObject);
   // ��������
   FMonoInstance* pInstance = FMonoInstance::InstanceCreate();
   pInstance->SetScriptClass(this);
   pInstance->SetNativeObject(pMonoObject);
   return pInstance;
}

//============================================================
// <T>�򿪴���</T>
//
// @return ������
//============================================================
TResult FMonoClass::Open(){
   TResult resultCd = FScriptClass::Open();
   // �����
   MO_CHECK(_pScriptLibrary, return ENull);
   FMonoLibrary* pLibrary = _pScriptLibrary->Convert<FMonoLibrary>();
   _pMonoClass = mono_class_from_name(pLibrary->NativeImage(), _spaceName, _className);
   MO_CHECK(_pMonoClass, return NULL);
   return resultCd;
}

//============================================================
// <T>�رմ���</T>
//
// @return ������
//============================================================
TResult FMonoClass::Close(){
   TResult resultCd = FScriptClass::Close();
   MO_CLEAR(_pMonoClass);
   return resultCd;
}

MO_NAMESPACE_END
