#include "MoPlatformDirectX9.h"
      
MO_NAMESPACE_BEGIN

//============================================================
// <T>��ʼ����Ⱦ���洦��</T>
//============================================================
void MoEngineDirectX9Initialize(){
   MO_STATIC_INFO("Engine OpenGLES2 initialize.");
   // ע����Ⱦ�豸
   RDeviceManager::Instance().Register(FPd9RenderDevice::Class(), FRenderDevice::Class());
}

//============================================================
// <T>������Ⱦ���洦��</T>
//============================================================
void MoEngineDirectX9Startup(){
   MO_STATIC_INFO("Engine OpenGLES2 startup.");
}

//============================================================
// <T>�ر���Ⱦ���洦��</T>
//============================================================
void MoEngineDirectX9Shutdown(){
   MO_STATIC_INFO("Engine OpenGLES2 shutdown.");
}

//============================================================
// <T>�ͷ���Ⱦ���洦��</T>
//============================================================
void MoEngineDirectX9Release(){
   MO_STATIC_INFO("Engine OpenGLES2 release.");
}

MO_NAMESPACE_END
