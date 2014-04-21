#include "MoScript.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FScriptMachine, FInstance);

//============================================================
// <T>����ű���������</T>
//============================================================
FScriptMachine::FScriptMachine(){
   _pClassFactory = MO_CREATE(FClassFactory);
}

//============================================================
// <T>�����ű���������</T>
//============================================================
FScriptMachine::~FScriptMachine(){
   MO_DELETE(_pClassFactory);
}

MO_NAMESPACE_END
