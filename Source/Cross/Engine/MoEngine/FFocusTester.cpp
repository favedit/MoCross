#include "MoEgDisplay.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>���콹���������</T>
//============================================================
FFocusTester::FFocusTester(){
   _pDrawables = MO_CREATE(FDrawableCollection);
}

//============================================================
// <T>�����������̨��</T>
//============================================================
FFocusTester::~FFocusTester(){
   MO_DELETE(_pDrawables);
}

MO_NAMESPACE_END
