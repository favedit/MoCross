#include "MoFeatureSound.h"
      
MO_NAMESPACE_BEGIN

//============================================================
// <T>��ʼ���������ܴ���</T>
//============================================================
void MoFeatureSoundInitialize(){
   MO_STATIC_INFO("Feature sound initialize.");
}

//============================================================
// <T>�����������ܴ���</T>
//============================================================
void MoFeatureSoundStartup(){
   MO_STATIC_INFO("Feature sound startup.");
}

//============================================================
// <T>�ر��������ܴ���</T>
//============================================================
void MoFeatureSoundShutdown(){
   MO_STATIC_INFO("Feature sound shutdown.");
}

//============================================================
// <T>�ͷ��������ܴ���</T>
//============================================================
void MoFeatureSoundRelease(){
   MO_STATIC_INFO("Feature sound release.");
}

MO_NAMESPACE_END
