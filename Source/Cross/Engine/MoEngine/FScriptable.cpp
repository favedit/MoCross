#include "MoEgDisplay.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FScriptable, FComponent);

//============================================================
// <T>����ű�����</T>
//============================================================
FScriptable::FScriptable(){
}

//============================================================
// <T>�����ű�����</T>
//============================================================
FScriptable::~FScriptable(){
}

//============================================================
// <T>����ǰ�ô���</T>
//
// @return ������
//============================================================
TResult FScriptable::ProcessBefore(SProcessContext* pContext){
   return ESuccess;
}

//============================================================
// <T>���ܺ��ô���</T>
//
// @return ������
//============================================================
TResult FScriptable::ProcessAfter(SProcessContext* pContext){
   return ESuccess;
}

MO_NAMESPACE_END
