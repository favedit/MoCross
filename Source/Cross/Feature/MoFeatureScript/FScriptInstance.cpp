#include "MoScript.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FScriptInstance, FInstance);

//============================================================
// <T>����ű�ʵ����</T>
//============================================================
FScriptInstance::FScriptInstance(){
   MO_CLEAR(_pScriptClass);
}

//============================================================
// <T>�����ű�ʵ����</T>
//============================================================
FScriptInstance::~FScriptInstance(){
}

//============================================================
// <T>����ֶ����ݡ�</T>
//
// @param pFileName �ֶ�����
// @param pFieldValue �ֶ�����
// @return ������
//============================================================
TResult FScriptInstance::FieldGet(TCharC* pFileName, TAny* pFieldValue){
   MO_CHECK(_pScriptClass, return ENull);
   FScriptField* pField = _pScriptClass->FindField(pFileName);
   MO_CHECK(pField, return ENull);
   TResult resultCd = pField->Get(this, pFieldValue);
   return resultCd;
}

//============================================================
// <T>�����ֶ����ݡ�</T>
//
// @param pFileName �ֶ�����
// @param pFieldValue �ֶ�����
// @return ������
//============================================================
TResult FScriptInstance::FieldSet(TCharC* pFileName, TAny* pFieldValue){
   MO_CHECK(_pScriptClass, return ENull);
   FScriptField* pField = _pScriptClass->FindField(pFileName);
   MO_CHECK(pField, return ENull);
   TResult resultCd = pField->Set(this, pFieldValue);
   return resultCd;
}

//============================================================
// <T>����ֶ��ַ������ݡ�</T>
//
// @param pFileName �ֶ�����
// @param pFieldValue �ֶ�����
// @return ������
//============================================================
TResult FScriptInstance::FieldGetString(TCharC* pFileName, MString* pFieldValue){
   MO_CHECK(_pScriptClass, return ENull);
   FScriptField* pField = _pScriptClass->FindField(pFileName);
   MO_CHECK(pField, return ENull);
   TResult resultCd = pField->GetString(this, pFieldValue);
   return resultCd;
}

//============================================================
// <T>�����ֶ��ַ������ݡ�</T>
//
// @param pFileName �ֶ�����
// @param pFieldValue �ֶ�����
// @return ������
//============================================================
TResult FScriptInstance::FieldSetString(TCharC* pFileName, TCharC* pFieldValue){
   MO_CHECK(_pScriptClass, return ENull);
   FScriptField* pField = _pScriptClass->FindField(pFileName);
   MO_CHECK(pField, return ENull);
   TResult resultCd = pField->SetString(this, pFieldValue);
   return resultCd;
}

MO_NAMESPACE_END
