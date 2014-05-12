#include "MoBridge.h"
      
MO_NAMESPACE_BEGIN

//============================================================
// <T>��ʼ����Ⱦ���洦��</T>
//============================================================
void MoBridgeInitialize(){
   RBridgeManager::Create();
   RBridgeManager::Instance().ClassFactory()->Register("Instance", FInstance::Class());
}

//============================================================
// <T>�ͷ���Ⱦ���洦��</T>
//============================================================
void MoBridgeRelease(){
   RBridgeManager::Destroy();
}

MO_NAMESPACE_END

