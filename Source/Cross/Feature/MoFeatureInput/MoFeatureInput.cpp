#include "MoFeatureInput.h"
      
MO_NAMESPACE_BEGIN

//============================================================
// <T>��ʼ�����빦�ܴ���</T>
//============================================================
void MoFeatureInputInitialize(){
   MO_STATIC_INFO("Feature input initialize.");
}

//============================================================
// <T>�������빦�ܴ���</T>
//============================================================
void MoFeatureInputStartup(){
   MO_STATIC_INFO("Feature input startup.");
}

//============================================================
// <T>�ر����빦�ܴ���</T>
//============================================================
void MoFeatureInputShutdown(){
   MO_STATIC_INFO("Feature sound shutdown.");
}

//============================================================
// <T>�ͷ����빦�ܴ���</T>
//============================================================
void MoFeatureInputRelease(){
   MO_STATIC_INFO("Feature input release.");
}

MO_NAMESPACE_END
