#include "MoFeatureParticle.h"
      
MO_NAMESPACE_BEGIN

//============================================================
// <T>��ʼ�����ӹ��ܴ���</T>
//============================================================
void MoFeatureParticleInitialize(){
   MO_STATIC_INFO("Feature particle initialize.");
}

//============================================================
// <T>�������ӹ��ܴ���</T>
//============================================================
void MoFeatureParticleStartup(){
   MO_STATIC_INFO("Feature particle startup.");
}

//============================================================
// <T>�ر����ӹ��ܴ���</T>
//============================================================
void MoFeatureParticleShutdown(){
   MO_STATIC_INFO("Feature particle shutdown.");
}

//============================================================
// <T>�ͷ����ӹ��ܴ���</T>
//============================================================
void MoFeatureParticleRelease(){
   MO_STATIC_INFO("Feature particle release.");
}

MO_NAMESPACE_END
