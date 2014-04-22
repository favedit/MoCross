#include "MoEgDisplay.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FComponentProperty, FInstance);

//============================================================
// <T>����������ԡ�</T>
//============================================================
FComponentProperty::FComponentProperty(){
   _version = 0;
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
