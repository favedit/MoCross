#include "MoPsmScript.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FMonoField, FScriptField);

//============================================================
// <T>����ű��ֶΡ�</T>
//============================================================
FMonoField::FMonoField(){
   MO_CLEAR(_pMonoField);
}

//============================================================
// <T>�����ű��ֶΡ�</T>
//============================================================
FMonoField::~FMonoField(){
}

//============================================================
// <T>����ֶ����ݡ�</T>
//
// @param pInstance ʵ��
// @param pValue ����
// @return ������
//============================================================
TResult FMonoField::Get(FScriptInstance* pInstance, TAny* pValue){
   MO_CHECK(pInstance, return ENull);
   MO_CHECK(pValue, return ENull);
   FMonoInstance* pMonoInstance = pInstance->Convert<FMonoInstance>();
   mono_field_get_value(pMonoInstance->NativeObject(), _pMonoField, pValue);
   return ESuccess;
}

//============================================================
// <T>�����ֶ����ݡ�</T>
//
// @param pInstance ʵ��
// @param pValue ����
// @return ������
//============================================================
TResult FMonoField::Set(FScriptInstance* pInstance, TAny* pValue){
   MO_CHECK(pInstance, return ENull);
   MO_CHECK(pValue, return ENull);
   FMonoInstance* pMonoInstance = pInstance->Convert<FMonoInstance>();
   mono_field_set_value(pMonoInstance->NativeObject(), _pMonoField, pValue);
   return ESuccess;
}

//============================================================
// <T>����ֶ��ַ������ݡ�</T>
//
// @param pInstance ʵ��
// @param pValue ����
// @return ������
//============================================================
TResult FMonoField::GetString(FScriptInstance* pInstance, MString* pValue){
   MO_CHECK(pInstance, return ENull);
   MO_CHECK(pValue, return ENull);
   FMonoInstance* pMonoInstance = pInstance->Convert<FMonoInstance>();
   MonoString* pMonoString = NULL;
   mono_field_get_value(pMonoInstance->NativeObject(), _pMonoField, &pMonoString);
	TChar* pString = mono_string_to_utf8(pMonoString);
   pValue->Assign(pString);
	mono_free(pString);
   return ESuccess;
}

//============================================================
// <T>�����ֶ��ַ������ݡ�</T>
//
// @param pInstance ʵ��
// @param pValue ����
// @return ������
//============================================================
TResult FMonoField::SetString(FScriptInstance* pInstance, TCharC* pValue){
   MO_CHECK(pInstance, return ENull);
   MO_CHECK(pValue, return ENull);
   FMonoMachine* pMachine = (FMonoMachine*)_pScriptClass->ScriptMachine();
   MonoString* pMonoString =mono_string_new(pMachine->NativeDomain(), pValue);
   FMonoInstance* pMonoInstance = pInstance->Convert<FMonoInstance>();
   mono_field_set_value(pMonoInstance->NativeObject(), _pMonoField, &pMonoString);
   return ESuccess;
}

//============================================================
// <T>�򿪴���</T>
//
// @return ������
//============================================================
TResult FMonoField::Open(){
   TResult resultCd = FScriptField::Open();
   // �����
   MO_CHECK(_pScriptClass, return ENull);
   FMonoClass* pClass = _pScriptClass->Convert<FMonoClass>();
   _pMonoField = mono_class_get_field_from_name(pClass->NativeClass(), _name);
   MO_CHECK(_pMonoField, return NULL);
   return resultCd;
}

//============================================================
// <T>�رմ���</T>
//
// @return ������
//============================================================
TResult FMonoField::Close(){
   TResult resultCd = FScriptField::Close();
   MO_CLEAR(_pMonoField);
   return resultCd;
}

MO_NAMESPACE_END
