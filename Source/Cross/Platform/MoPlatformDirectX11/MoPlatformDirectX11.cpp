#include "MoPlatformDirectX11.h"
      
MO_NAMESPACE_BEGIN

//============================================================
// <T>��ʼ����Ⱦ���洦��</T>
//============================================================
void MoEngineDirectX11(){
   RFeatureManager::Instance().Register(FPlatformDirectX11Feature::Class());
}

MO_NAMESPACE_END
