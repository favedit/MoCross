#include "MoEgDisplay.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>����������Լ��ϡ�</T>
//============================================================
FComponentProperties::FComponentProperties(){
   _pProperties = MO_CREATE(FComponentPropertyCollection);
}

//============================================================
// <T>����������Լ��ϡ�</T>
//============================================================
FComponentProperties::~FComponentProperties(){
   MO_DELETE(_pProperties);
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
