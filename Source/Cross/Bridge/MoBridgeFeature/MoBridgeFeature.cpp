#include "MoPlatformDirectX10.h"
      
MO_NAMESPACE_BEGIN

//============================================================
// <T>��ʼ����Ⱦ���洦��</T>
//============================================================
void MoEngineDirectX10(){
   RFeatureManager::Instance().Register(FPlatformDirectX10Feature::Class());
}

MO_NAMESPACE_END
