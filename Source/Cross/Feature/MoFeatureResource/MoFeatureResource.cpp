#include "MoFeatureResource.h"
      
MO_NAMESPACE_BEGIN

//============================================================
// <T>��ʼ����Դ���ܴ���</T>
//============================================================
void MoFeatureResourceInitialize(){
   MO_STATIC_INFO(TC("Feature resource initialize."));
   RLoaderManager::Create();
   RContentManager::Create();
}

//============================================================
// <T>������Դ���ܴ���</T>
//============================================================
void MoFeatureResourceStartup(){
   MO_STATIC_INFO(TC("Feature resource startup."));
   RLoaderManager::Instance().Startup();
}

//============================================================
// <T>�ر���Դ���ܴ���</T>
//============================================================
void MoFeatureResourceShutdown(){
   MO_STATIC_INFO(TC("Feature resource shutdown."));
   RLoaderManager::Instance().Shutdown();
}

//============================================================
// <T>�ͷ���Դ���ܴ���</T>
//============================================================
void MoFeatureResourceRelease(){
   MO_STATIC_INFO(TC("Feature resource release."));
   RLoaderManager::Destroy();
   RContentManager::Destroy();
}

MO_NAMESPACE_END
