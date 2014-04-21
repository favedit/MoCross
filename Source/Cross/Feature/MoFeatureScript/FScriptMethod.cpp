#include "MoScript.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FScriptMethod, FScriptObject);

//============================================================
// <T>����ű�������</T>
//============================================================
FScriptMethod::FScriptMethod(){
}

//============================================================
// <T>�����ű�������</T>
//============================================================
FScriptMethod::~FScriptMethod(){
}

//============================================================
// <T>����������</T>
//
// @param pDescriptor ������Ϣ
//============================================================
void FScriptMethod::SetDescriptor(TCharC* pDescriptor){
   _descriptor = pDescriptor;
   // �ָ�����
   TInt splitter = _name.IndexOf(TC('('));
   if(splitter != ENotFound){
      _name = _descriptor.LeftStrC(splitter);
   }else{
      _name.Clear();
   }
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
TResult FScriptMethod::InvokeParamaters(FScriptInstance* pInstance, TAny** ppResult, TInt paramCount, TAny** pParameters){
   MO_FATAL_UNSUPPORT();
   return ESuccess;
}

//============================================================
// <T>���ú�����</T>
//
// @param pInstance ʵ��
// @param ppResult ���
// @param paramCount ��������
// @param params ��������
// @return ������
//============================================================
TResult FScriptMethod::Invoke(FScriptInstance* pInstance, TAny** ppResult){
   return InvokeParamaters(pInstance, ppResult, 0, NULL);
}

//============================================================
// <T>���ú�����</T>
//
// @param pInstance ʵ��
// @param ppResult ���
// @param pParam1 ����1
// @return ������
//============================================================
TResult FScriptMethod::Invoke1(FScriptInstance* pInstance, TAny** ppResult, TAny* pParam1){
   TAny* params[] = {pParam1};
   return InvokeParamaters(pInstance, ppResult, 1, params);
}

//============================================================
// <T>���ú�����</T>
//
// @param pInstance ʵ��
// @param ppResult ���
// @param pParam1 ����1
// @param pParam2 ����2
// @return ������
//============================================================
TResult FScriptMethod::Invoke2(FScriptInstance* pInstance, TAny** ppResult, TAny* pParam1, TAny* pParam2){
   TAny* params[] = {pParam1, pParam2};
   return InvokeParamaters(pInstance, ppResult, 2, params);
}

//============================================================
// <T>���ú�����</T>
//
// @param pInstance ʵ��
// @param ppResult ���
// @param pParam1 ����1
// @param pParam2 ����2
// @param pParam3 ����3
// @return ������
//============================================================
TResult FScriptMethod::Invoke3(FScriptInstance* pInstance, TAny** ppResult, TAny* pParam1, TAny* pParam2, TAny* pParam3){
   TAny* params[] = {pParam1, pParam2, pParam3};
   return InvokeParamaters(pInstance, ppResult, 3, params);
}

//============================================================
// <T>���ú�����</T>
//
// @param pInstance ʵ��
// @param ppResult ���
// @param pParam1 ����1
// @param pParam2 ����2
// @param pParam3 ����3
// @param pParam4 ����4
// @return ������
//============================================================
TResult FScriptMethod::Invoke4(FScriptInstance* pInstance, TAny** ppResult, TAny* pParam1, TAny* pParam2, TAny* pParam3, TAny* pParam4){
   TAny* params[] = {pParam1, pParam2, pParam3, pParam4};
   return InvokeParamaters(pInstance, ppResult, 4, params);
}

//============================================================
// <T>���ú�����</T>
//
// @param pInstance ʵ��
// @param ppResult ���
// @param pParam1 ����1
// @param pParam2 ����2
// @param pParam3 ����3
// @param pParam4 ����4
// @param pParam5 ����5
// @return ������
//============================================================
TResult FScriptMethod::Invoke5(FScriptInstance* pInstance, TAny** ppResult, TAny* pParam1, TAny* pParam2, TAny* pParam3, TAny* pParam4, TAny* pParam5){
   TAny* params[] = {pParam1, pParam2, pParam3, pParam4, pParam5};
   return InvokeParamaters(pInstance, ppResult, 5, params);
}

//============================================================
// <T>���ú�����</T>
//
// @param pInstance ʵ��
// @param ppResult ���
// @param pParam1 ����1
// @param pParam2 ����2
// @param pParam3 ����3
// @param pParam4 ����4
// @param pParam5 ����5
// @param pParam6 ����6
// @return ������
//============================================================
TResult FScriptMethod::Invoke6(FScriptInstance* pInstance, TAny** ppResult, TAny* pParam1, TAny* pParam2, TAny* pParam3, TAny* pParam4, TAny* pParam5, TAny* pParam6){
   TAny* params[] = {pParam1, pParam2, pParam3, pParam4, pParam5, pParam6};
   return InvokeParamaters(pInstance, ppResult, 6, params);
}

MO_NAMESPACE_END
