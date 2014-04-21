#include "MoScript.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FScriptProperty, FScriptObject);

//============================================================
// <T>����ű����ԡ�</T>
//============================================================
FScriptProperty::FScriptProperty(){
   MO_CLEAR(_pScriptClass);
}

//============================================================
// <T>�����ű����ԡ�</T>
//============================================================
FScriptProperty::~FScriptProperty(){
}

//============================================================
// <T>����������ݡ�</T>
//
// @param pInstance ʵ��
// @param pValue ����
// @return ������
//============================================================
TResult FScriptProperty::Get(FScriptInstance* pInstance, TAny* pValue){
   MO_FATAL_UNSUPPORT();
   return ESuccess;
}

//============================================================
// <T>�����������ݡ�</T>
//
// @param pInstance ʵ��
// @param pValue ����
// @return ������
//============================================================
TResult FScriptProperty::Set(FScriptInstance* pInstance, TAny* pValue){
   MO_FATAL_UNSUPPORT();
   return ESuccess;
}

MO_NAMESPACE_END
