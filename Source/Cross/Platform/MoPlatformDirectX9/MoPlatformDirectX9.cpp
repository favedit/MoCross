#include "MoPlatformDirectX9.h"
      
MO_NAMESPACE_BEGIN

//============================================================
// <T>��ʼ����Ⱦ���洦��</T>
//============================================================
void MoEngineDirectX9(){
   RFeatureManager::Instance().Register(FPlatformDirectX9Feature::Class());
}

//============================================================
// <T>��ʼ����Ⱦ���洦��</T>
//============================================================
TResult SetupFeature(){
   RFeatureManager::Instance().Register(FPlatformDirectX9Feature::Class());
   return ESuccess;
}

MO_NAMESPACE_END
