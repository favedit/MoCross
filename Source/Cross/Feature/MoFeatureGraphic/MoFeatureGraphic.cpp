#include "MoFeatureGraphic.h"
      
MO_NAMESPACE_BEGIN

//============================================================
// <T>��ʼ����Ⱦ���洦��</T>
//============================================================
void MoFeatureGraphicsInitialize(){
   MO_STATIC_INFO("Feature Graphic initialize.");
   // ��ʼ���ɼ�������
   RVisualManager::Create();
   // ��ʼ������������
   RTechniqueManager::Create();
}

//============================================================
// <T>������Ⱦ���洦��</T>
//============================================================
void MoFeatureGraphicsStartup(){
   MO_STATIC_INFO("Feature Graphic startup.");
   // �����ɼ�������
   RVisualManager::Instance().Startup();
}

//============================================================
// <T>�ر���Ⱦ���洦��</T>
//============================================================
void MoFeatureGraphicsShutdown(){
   MO_STATIC_INFO("Feature Graphic shutdown.");
   // ֹͣ�ɼ�������
   RVisualManager::Instance().Shutdown();
}

//============================================================
// <T>�ͷ���Ⱦ���洦��</T>
//============================================================
void MoFeatureGraphicsRelease(){
   MO_STATIC_INFO("Feature Graphic release.");
   // �ͷż���������
   RTechniqueManager::Destroy();
   // �ͷſɼ�������
   RVisualManager::Destroy();
}

MO_NAMESPACE_END
