#include "MoEgDisplay.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>����������ԡ�</T>
//============================================================
FComponentProperty::FComponentProperty(){
}

//============================================================
// <T>����������ԡ�</T>
//============================================================
FComponentProperty::~FComponentProperty(){
}

//============================================================
// <T>���л��������ݵ��������</T>
//
// @param pOutput �����
//============================================================
TResult FComponentProperty::Serialize(IDataOutput* pOutput){
   return ESuccess;
}

//============================================================
// <T>�������������л��������ݡ�</T>
//
// @param pInput ������
//============================================================
TResult FComponentProperty::Unserialize(IDataInput* pInput){
   return ESuccess;
}

MO_NAMESPACE_END
