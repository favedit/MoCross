#include "MoPlatformOpenGLES2.h"
      
MO_NAMESPACE_BEGIN

//============================================================
// <T>��ʼ����Ⱦ���洦��</T>
//============================================================
void MoEngineOpenGLES2(){
   RFeatureManager::Instance().Register(FPlatformOpenGLES2Feature::Class());
}

MO_NAMESPACE_END
