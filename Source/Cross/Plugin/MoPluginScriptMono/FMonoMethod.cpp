#include "MoPsmScript.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FMonoMethod, FScriptMethod);

//============================================================
// <T>����ű�������</T>
//============================================================
FMonoMethod::FMonoMethod(){
   MO_CLEAR(_pMonoMethod);
}

//============================================================
// <T>�����ű�������</T>
//============================================================
FMonoMethod::~FMonoMethod(){
}

//============================================================
// <T>���ú�����</T>
//
// @param pInstance ʵ��
// @param ppResult ���
// @param paramCount ��������
// @param pParameters ��������
// @return ������
//============================================================
TResult FMonoMethod::InvokeParamaters(FScriptInstance* pInstance, TAny** ppResult, TInt paramCount, TAny** pParameters){
   MO_CHECK(pInstance, return ENull);
   MO_CHECK(paramCount < MO_SCRIPT_METHOD_PARAM_MAXCNT, return EMemory);
   // ���ú���
   FMonoInstance* pMonoInstance = pInstance->Convert<FMonoInstance>();
   MonoObject* pException = NULL;
   MonoObject* pResult = mono_runtime_invoke(_pMonoMethod, pMonoInstance->NativeObject(), pParameters, &pException);
   // �������
   if(pException != NULL){
      MO_FATAL("Invoke method failure. (method=%s, param_count=%d)", (TCharC*)_name, paramCount);
      return EFailure;
   }
   // �������
   if(ppResult != NULL){
      *ppResult = pResult;
   }
   return ESuccess;
}

//============================================================
// <T>�򿪴���</T>
//
// @return ������
//============================================================
TResult FMonoMethod::Open(){
   TResult resultCd = FScriptMethod::Open();
   // ��ýű���
   MO_CHECK(_pScriptClass, return ENull);
   FMonoClass* pClass = _pScriptClass->Convert<FMonoClass>();
   // ���ݺ����������������
   MonoMethodDesc* pDescriptor = mono_method_desc_new(_descriptor, false);
   MO_FATAL_CHECK(pDescriptor, return EFailure, "Create method descriptor failure. (descriptor=%s)", (TCharC*)_descriptor);
   _pMonoMethod = mono_method_desc_search_in_class(pDescriptor, pClass->NativeClass());
   MO_FATAL_CHECK(_pMonoMethod, return EFailure, "Find method in class failure. (class=%s, method=%s)", pClass->Name(), (TCharC*)_descriptor);
   mono_method_desc_free(pDescriptor);
   return resultCd;
}

//============================================================
// <T>�رմ���</T>
//
// @return ������
//============================================================
TResult FMonoMethod::Close(){
   TResult resultCd = FScriptMethod::Close();
   MO_CLEAR(_pMonoMethod);
   return resultCd;
}

MO_NAMESPACE_END
