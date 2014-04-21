#include "MoPsmScript.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FMonoProperty, FScriptProperty);

//============================================================
// <T>����ű����ԡ�</T>
//============================================================
FMonoProperty::FMonoProperty(){
   MO_CLEAR(_pMonoProperty);
}

//============================================================
// <T>�����ű����ԡ�</T>
//============================================================
FMonoProperty::~FMonoProperty(){
}

//============================================================
// <T>����ֶ����ݡ�</T>
//
// @param pInstance ʵ��
// @param pValue ����
// @return ������
//============================================================
TResult FMonoProperty::Get(FScriptInstance* pInstance, TAny* pValue){
   MO_CHECK(pInstance, return ENull);
   MO_CHECK(pValue, return ENull);
   FMonoInstance* pMonoInstance = pInstance->Convert<FMonoInstance>();
   MonoObject* pException = NULL;
   MonoObject* pObject = mono_property_get_value(_pMonoProperty, pMonoInstance->NativeObject(), NULL, &pException);
   if(pException == NULL){
      MO_FATAL("Get property failure. (class=%s, property=%s)", _pScriptClass->Name(), (TCharC*)_name);
      return EFailure;
   }
   return ESuccess;
}

//============================================================
// <T>�����ֶ����ݡ�</T>
//
// @param pInstance ʵ��
// @param pValue ����
// @return ������
//============================================================
TResult FMonoProperty::Set(FScriptInstance* pInstance, TAny* pValue){
   MO_CHECK(pInstance, return ENull);
   MO_CHECK(pValue, return ENull);
   FMonoInstance* pMonoInstance = pInstance->Convert<FMonoInstance>();
   MonoObject* pException = NULL;
   mono_property_set_value(_pMonoProperty, pMonoInstance->NativeObject(), (TAny**)pValue, &pException);
   if(pException == NULL){
      MO_FATAL("Set property failure. (class=%s, property=%s)", _pScriptClass->Name(), (TCharC*)_name);
      return EFailure;
   }
   return ESuccess;
}

//============================================================
// <T>����ֶ��ַ������ݡ�</T>
//
// @param pInstance ʵ��
// @param pValue ����
// @return ������
//============================================================
TResult FMonoProperty::GetString(FScriptInstance* pInstance, MString* pValue){
   MO_CHECK(pInstance, return ENull);
   MO_CHECK(pValue, return ENull);
 //  FMonoInstance* pMonoInstance = pInstance->Convert<FMonoInstance>();
 //  MonoString* pMonoString = NULL;
 //  mono_field_get_value(pMonoInstance->NativeObject(), _pMonoProperty, &pMonoString);
	//TChar* pString = mono_string_to_utf8(pMonoString);
 //  pValue->Assign(pString);
	//mono_free(pString);
   return ESuccess;
}

//============================================================
// <T>�����ֶ��ַ������ݡ�</T>
//
// @param pInstance ʵ��
// @param pValue ����
// @return ������
//============================================================
TResult FMonoProperty::SetString(FScriptInstance* pInstance, TCharC* pValue){
   MO_CHECK(pInstance, return ENull);
   MO_CHECK(pValue, return ENull);
   //FMonoMachine* pMachine = (FMonoMachine*)_pScriptClass->ScriptMachine();
   //MonoString* pMonoString =mono_string_new(pMachine->NativeDomain(), pValue);
   //FMonoInstance* pMonoInstance = pInstance->Convert<FMonoInstance>();
   //mono_field_set_value(pMonoInstance->NativeObject(), _pMonoProperty, &pMonoString);
   return ESuccess;
}

//============================================================
// <T>�򿪴���</T>
//
// @return ������
//============================================================
TResult FMonoProperty::Open(){
   TResult resultCd = FScriptProperty::Open();
   // �����
   MO_CHECK(_pScriptClass, return ENull);
   FMonoClass* pClass = _pScriptClass->Convert<FMonoClass>();
   _pMonoProperty = mono_class_get_property_from_name(pClass->NativeClass(), _name);
   MO_CHECK(_pMonoProperty, return NULL);
   return resultCd;
}

//============================================================
// <T>�رմ���</T>
//
// @return ������
//============================================================
TResult FMonoProperty::Close(){
   TResult resultCd = FScriptProperty::Close();
   MO_CLEAR(_pMonoProperty);
   return resultCd;
}

MO_NAMESPACE_END
