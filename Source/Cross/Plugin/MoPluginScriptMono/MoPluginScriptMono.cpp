#include "MoPluginScriptMono.h"
      
MO_NAMESPACE_BEGIN

//============================================================
// <T>����ű�Mono���ܡ�</T>
//============================================================
void MoPluginScriptMono(){
   RFeatureManager::Instance().Register(FPluginScriptMonoFeature::Class());
}

MO_NAMESPACE_END
