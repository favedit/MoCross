#include "MoFeatureProfile.h"
      
MO_NAMESPACE_BEGIN

//============================================================
// <T>��ʼ���������ܴ���</T>
//============================================================
void MoFeatureProfileInitialize(){
   MO_STATIC_INFO("Feature profile initialize.");
}

//============================================================
// <T>�����������ܴ���</T>
//============================================================
void MoFeatureProfileStartup(){
   MO_STATIC_INFO("Feature profile startup.");
}

//============================================================
// <T>�ر��������ܴ���</T>
//============================================================
void MoFeatureProfileShutdown(){
   MO_STATIC_INFO("Feature profile shutdown.");
}

//============================================================
// <T>�ͷ��������ܴ���</T>
//============================================================
void MoFeatureProfileRelease(){
   MO_STATIC_INFO("Feature profile release.");
}

MO_NAMESPACE_END
