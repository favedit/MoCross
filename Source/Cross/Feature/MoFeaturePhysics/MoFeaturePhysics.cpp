#include "MoFeaturePhysics.h"
      
MO_NAMESPACE_BEGIN

//============================================================
// <T>��ʼ�������ܴ���</T>
//============================================================
void MoFeaturePhysicsInitialize(){
   MO_STATIC_INFO("Feature physics initialize.");
}

//============================================================
// <T>���������ܴ���</T>
//============================================================
void MoFeaturePhysicsStartup(){
   MO_STATIC_INFO("Feature physics startup.");
}

//============================================================
// <T>�ر������ܴ���</T>
//============================================================
void MoFeaturePhysicsShutdown(){
   MO_STATIC_INFO("Feature physics shutdown.");
}

//============================================================
// <T>�ͷ������ܴ���</T>
//============================================================
void MoFeaturePhysicsRelease(){
   MO_STATIC_INFO("Feature physics release.");
}

MO_NAMESPACE_END
