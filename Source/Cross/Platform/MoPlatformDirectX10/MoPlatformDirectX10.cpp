#include "MoPlatformDirectX10.h"
      
MO_NAMESPACE_BEGIN

//============================================================
// <T>��ʼ����Ⱦ���洦��</T>
//============================================================
void MoEngineDirectX10Initialize(){
   MO_STATIC_INFO("Engine DirectX 10 initialize.");
   // ��ʼ������������
   RTechniqueManager::Create();
   // ע����Ⱦ�豸
   RDeviceManager::Instance().Register(FPd10RenderDevice::Class(), FRenderDevice::Class());
}

//============================================================
// <T>������Ⱦ���洦��</T>
//============================================================
void MoEngineDirectX10Startup(){
   MO_STATIC_INFO("Engine DirectX 10 startup.");
   RTechniqueManager::Instance().Setup();
}

//============================================================
// <T>�ر���Ⱦ���洦��</T>
//============================================================
void MoEngineDirectX10Shutdown(){
   MO_STATIC_INFO("Engine DirectX 10 shutdown.");
}

//============================================================
// <T>�ͷ���Ⱦ���洦��</T>
//============================================================
void MoEngineDirectX10Release(){
   MO_STATIC_INFO("Engine DirectX 10 release.");
}

MO_NAMESPACE_END
