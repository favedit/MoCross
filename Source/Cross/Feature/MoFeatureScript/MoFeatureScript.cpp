#include "MoFeatureScript.h"
      
MO_NAMESPACE_BEGIN

//============================================================
// <T>��ʼ���ű����ܴ���</T>
//============================================================
void MoFeatureScriptInitialize(){
   MO_STATIC_INFO("Feature script initialize.");
}

//============================================================
// <T>�����ű����ܴ���</T>
//============================================================
void MoFeatureScriptStartup(){
   MO_STATIC_INFO("Feature script startup.");
}

//============================================================
// <T>�رսű����ܴ���</T>
//============================================================
void MoFeatureScriptShutdown(){
   MO_STATIC_INFO("Feature script shutdown.");
}

//============================================================
// <T>�ͷŽű����ܴ���</T>
//============================================================
void MoFeatureScriptRelease(){
   MO_STATIC_INFO("Feature script release.");
}

MO_NAMESPACE_END
