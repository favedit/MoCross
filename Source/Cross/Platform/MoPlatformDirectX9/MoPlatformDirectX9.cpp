#include "MoPlatformDirectX9.h"
      
MO_NAMESPACE_BEGIN

//============================================================
// <T>��ʼ����Ⱦ���洦��</T>
//============================================================
void MoEngineDirectX9(){
   RFeatureManager::Instance().Register(FPlatformDirectX9Feature::Class());
}

MO_NAMESPACE_END
