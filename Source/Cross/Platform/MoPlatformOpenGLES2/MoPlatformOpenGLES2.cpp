#include "MoPlatformOpenGLES2.h"
      
MO_NAMESPACE_BEGIN

//============================================================
// <T>��ʼ����Ⱦ���洦��</T>
//============================================================
void MoEngineOpenGLES2Initialize(){
   MO_STATIC_INFO("Engine OpenGLES2 initialize.");
   // ��ʼ������������
   RTechniqueManager::Create();
   // ע����Ⱦ�豸
   RDeviceManager::Instance().Register(FEoRenderDevice::Class(), FRenderDevice::Class());
}

//============================================================
// <T>������Ⱦ���洦��</T>
//============================================================
void MoEngineOpenGLES2Startup(){
   MO_STATIC_INFO("Engine OpenGLES2 startup.");
   RTechniqueManager::Instance().Setup();
}

//============================================================
// <T>�ر���Ⱦ���洦��</T>
//============================================================
void MoEngineOpenGLES2Shutdown(){
   MO_STATIC_INFO("Engine OpenGLES2 shutdown.");
}

//============================================================
// <T>�ͷ���Ⱦ���洦��</T>
//============================================================
void MoEngineOpenGLES2Release(){
   MO_STATIC_INFO("Engine OpenGLES2 release.");
}

MO_NAMESPACE_END
