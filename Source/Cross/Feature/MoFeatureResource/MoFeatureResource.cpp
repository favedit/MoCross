#include "MoFeatureResource.h"
      
MO_NAMESPACE_BEGIN

//============================================================
// <T>��ʼ����Դ���ܴ���</T>
//============================================================
void MoFeatureResourceInitialize(){
   MO_STATIC_INFO("Feature resource initialize.");
}

//============================================================
// <T>������Դ���ܴ���</T>
//============================================================
void MoFeatureResourceStartup(){
   MO_STATIC_INFO("Feature resource startup.");
}

//============================================================
// <T>�ر���Դ���ܴ���</T>
//============================================================
void MoFeatureResourceShutdown(){
   MO_STATIC_INFO("Feature resource shutdown.");
}

//============================================================
// <T>�ͷ���Դ���ܴ���</T>
//============================================================
void MoFeatureResourceRelease(){
   MO_STATIC_INFO("Feature resource release.");
}

MO_NAMESPACE_END
