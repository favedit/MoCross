#include "MoEgDisplay.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FComponentProperties, FInstance);

//============================================================
// <T>����������Լ��ϡ�</T>
//============================================================
FComponentProperties::FComponentProperties(){
}

//============================================================
// <T>����������Լ��ϡ�</T>
//============================================================
FComponentProperties::~FComponentProperties(){
}

//============================================================
// <T>���л��������ݵ��������</T>
//
// @param pOutput �����
//============================================================
TResult FComponentProperties::Serialize(IDataOutput* pOutput){
   return ESuccess;
}

//============================================================
// <T>�������������л��������ݡ�</T>
//
// @param pInput ������
//============================================================
TResult FComponentProperties::Unserialize(IDataInput* pInput){
   return ESuccess;
}

MO_NAMESPACE_END
