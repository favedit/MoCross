#include "MoEngineRender.h"
      
MO_NAMESPACE_BEGIN

//============================================================
// <T>��ʼ��������Ⱦ���ܡ�</T>
//============================================================
void MoEngineRender(){
   RFeatureManager::Instance().Register(FEngineRenderFeature::Class());
}

MO_NAMESPACE_END
