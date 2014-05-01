#include "MoPlatformDirectX11.h"
      
MO_NAMESPACE_BEGIN

//============================================================
// <T>��ʼ����Ⱦ���洦��</T>
//============================================================
void MoEngineDirectX11Initialize(){
   MO_STATIC_INFO("Engine DirectX 11 initialize.");
   // ��ʼ������������
   RTechniqueManager::Create();
   // ע����Ⱦ�豸
   RDeviceManager::Instance().Register(FPd11RenderDevice::Class(), FRenderDevice::Class());
}

//============================================================
// <T>������Ⱦ���洦��</T>
//============================================================
void MoEngineDirectX11Startup(){
   MO_STATIC_INFO("Engine DirectX 11 startup.");
   RTechniqueManager::Instance().Setup();
}

//============================================================
// <T>�ر���Ⱦ���洦��</T>
//============================================================
void MoEngineDirectX11Shutdown(){
   MO_STATIC_INFO("Engine DirectX 11 shutdown.");
}

//============================================================
// <T>�ͷ���Ⱦ���洦��</T>
//============================================================
void MoEngineDirectX11Release(){
   MO_STATIC_INFO("Engine DirectX 11 release.");
}

MO_NAMESPACE_END
