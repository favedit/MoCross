#include "MoFmCore.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>����ؼ�������</T>
//============================================================
FUiControlContainer::FUiControlContainer(){
}

//============================================================
// <T>�����ؼ�������</T>
//============================================================
FUiControlContainer::~FUiControlContainer(){
}

//============================================================
// <T>�������������л��������ݡ�</T>
//
// @param pInput ������
//============================================================
TResult FUiControlContainer::Unserialize(IDataInput* pInput){
   MO_CHECK(pInput, return ENull);
   // ��ȡ����
   TResult result = FUiControl::Unserialize(pInput);
   return result;
}

MO_NAMESPACE_END
