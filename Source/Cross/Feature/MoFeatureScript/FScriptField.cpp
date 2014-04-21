#include "MoScript.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FScriptField, FScriptObject);

//============================================================
// <T>����ű��ֶΡ�</T>
//============================================================
FScriptField::FScriptField(){
   MO_CLEAR(_pScriptClass);
}

//============================================================
// <T>�����ű��ֶΡ�</T>
//============================================================
FScriptField::~FScriptField(){
}

//============================================================
// <T>����ֶ����ݡ�</T>
//
// @param pInstance ʵ��
// @param pValue ����
// @return ������
//============================================================
TResult FScriptField::Get(FScriptInstance* pInstance, TAny* pValue){
   MO_FATAL_UNSUPPORT();
   return ESuccess;
}

//============================================================
// <T>�����ֶ����ݡ�</T>
//
// @param pInstance ʵ��
// @param pValue ����
// @return ������
//============================================================
TResult FScriptField::Set(FScriptInstance* pInstance, TAny* pValue){
   MO_FATAL_UNSUPPORT();
   return ESuccess;
}

//============================================================
// <T>����ֶ��ַ������ݡ�</T>
//
// @param pInstance ʵ��
// @param pValue ����
// @return ������
//============================================================
TResult FScriptField::GetString(FScriptInstance* pInstance, MString* pValue){
   MO_FATAL_UNSUPPORT();
   return ESuccess;
}

//============================================================
// <T>�����ֶ��ַ������ݡ�</T>
//
// @param pInstance ʵ��
// @param pValue ����
// @return ������
//============================================================
TResult FScriptField::SetString(FScriptInstance* pInstance, TCharC* pValue){
   MO_FATAL_UNSUPPORT();
   return ESuccess;
}

MO_NAMESPACE_END
