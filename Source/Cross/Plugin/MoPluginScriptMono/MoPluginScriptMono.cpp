#include "MoPluginScriptMono.h"
      
MO_NAMESPACE_BEGIN

//============================================================
// <T>��ʼ���������洦��</T>
//============================================================
void MoPluginScriptMonoInitialize(){
   MO_STATIC_INFO("Plugin script mono initialize.");
}

//============================================================
// <T>�����������洦��</T>
//============================================================
void MoPluginScriptMonoStartup(){
   MO_STATIC_INFO("Plugin script mono startup.");
}

//============================================================
// <T>�رմ������洦��</T>
//============================================================
void MoPluginScriptMonoShutdown(){
   MO_STATIC_INFO("Plugin script mono shutdown.");
}

//============================================================
// <T>�ͷŴ������洦��</T>
//============================================================
void MoPluginScriptMonoRelease(){
   MO_STATIC_INFO("Plugin script mono release.");
}

MO_NAMESPACE_END
