#include "MoEngineAnimation.h"
      
MO_NAMESPACE_BEGIN

//============================================================
// <T>��ʼ���������洦��</T>
//============================================================
void MoEngineAnimationInitialize(){
   MO_STATIC_INFO("Engine animation initialize.");
}

//============================================================
// <T>�����������洦��</T>
//============================================================
void MoEngineAnimationStartup(){
   MO_STATIC_INFO("Engine animation startup.");
}

//============================================================
// <T>�رն������洦��</T>
//============================================================
void MoEngineAnimationShutdown(){
   MO_STATIC_INFO("Engine animation shutdown.");
}

//============================================================
// <T>�ͷŶ������洦��</T>
//============================================================
void MoEngineAnimationRelease(){
   MO_STATIC_INFO("Engine animation release.");
}

MO_NAMESPACE_END
