#include "MoPsmScript.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FMonoInstance, FScriptInstance);

//============================================================
// <T>����ű�ʵ����</T>
//============================================================
FMonoInstance::FMonoInstance(){
   MO_CLEAR(_pMonoObject);
}

//============================================================
// <T>�����ű�ʵ����</T>
//============================================================
FMonoInstance::~FMonoInstance(){
}


MO_NAMESPACE_END
