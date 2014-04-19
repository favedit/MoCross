#include "MoEngineOpenGL.h"
      
MO_NAMESPACE_BEGIN

//============================================================
// <T>��ʼ����Ⱦ���洦��</T>
//============================================================
void MoEngineOpenGLInitialize(){
   MO_STATIC_INFO("Engine OpenGL initialize.");
   // ��ʼ�����������
   RFontManager::Create(MO_CREATE(FEoFontConsole));
   RFontManager::Instance().Open();
   // ��ʼ������������
   RTechniqueManager::Create();
   // ע����Ⱦ�豸
   RDeviceManager::Instance().Register(FEoRenderDevice::Class(), FRenderDevice::Class());
}

//============================================================
// <T>������Ⱦ���洦��</T>
//============================================================
void MoEngineOpenGLStartup(){
   MO_STATIC_INFO("Engine OpenGL startup.");
   RTechniqueManager::Instance().Setup();
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
