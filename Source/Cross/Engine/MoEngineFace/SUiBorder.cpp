#include "MoEfDisplay.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>�������߿�</T>
//============================================================
SUiBorder::SUiBorder(){
}

//============================================================
// <T>�������������л��������ݡ�</T>
//
// @param pInput ������
//============================================================
TResult SUiBorder::Unserialize(IDataInput* pInput){
   left.Unserialize(pInput);
   top.Unserialize(pInput);
   right.Unserialize(pInput);
   bottom.Unserialize(pInput);
   return ESuccess;
}

MO_NAMESPACE_END
