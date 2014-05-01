#include "MoPlatformOpenGLES3.h"
      
MO_NAMESPACE_BEGIN

//============================================================
// <T>��ʼ����Ⱦ���洦��</T>
//============================================================
void MoEngineOpenGLInitialize(){
   MO_STATIC_INFO("Engine OpenGL initialize.");
   // ע����Ⱦ�豸
   RDeviceManager::Instance().Register(FPoe3RenderDevice::Class(), FRenderDevice::Class());
}

//============================================================
// <T>������Ⱦ���洦��</T>
//============================================================
void MoEngineOpenGLStartup(){
   MO_STATIC_INFO("Engine OpenGL startup.");
}

//============================================================
// <T>�ر���Ⱦ���洦��</T>
//============================================================
void MoEngineOpenGLShutdown(){
   MO_STATIC_INFO("Engine OpenGL shutdown.");
}

//============================================================
// <T>�ͷ���Ⱦ���洦��</T>
//============================================================
void MoEngineOpenGLRelease(){
   MO_STATIC_INFO("Engine OpenGL release.");
}

MO_NAMESPACE_END
