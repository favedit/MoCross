#include "MoFeatureGraphic.h"
      
MO_NAMESPACE_BEGIN

//============================================================
// <T>��ʼ����Ⱦ���档</T>
//============================================================
void MoFeatureGraphics(){
   RFeatureManager::Instance().Register(FFeatureGraphicFeature::Class());
}

MO_NAMESPACE_END
