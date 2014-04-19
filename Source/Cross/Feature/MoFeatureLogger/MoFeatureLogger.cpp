#include "MoFeatureLogger.h"
      
MO_NAMESPACE_BEGIN

//============================================================
// <T>��ʼ���������ܴ���</T>
//============================================================
void MoFeatureLoggerInitialize(){
   MO_STATIC_INFO("Feature logger initialize.");
   RLoggerFeature::Create();
   RLoggerFeature::Instance().Setup();
}

//============================================================
// <T>�����������ܴ���</T>
//============================================================
void MoFeatureLoggerStartup(){
   MO_STATIC_INFO("Feature logger startup.");
}

//============================================================
// <T>�ر��������ܴ���</T>
//============================================================
void MoFeatureLoggerShutdown(){
   MO_STATIC_INFO("Feature logger shutdown.");
}

//============================================================
// <T>�ͷ��������ܴ���</T>
//============================================================
void MoFeatureLoggerRelease(){
   MO_STATIC_INFO("Feature logger release.");
   RLoggerFeature::Destroy();
}

MO_NAMESPACE_END
