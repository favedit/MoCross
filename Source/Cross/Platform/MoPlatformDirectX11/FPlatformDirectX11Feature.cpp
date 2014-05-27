#include "MoPlatformDirectX11.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FPlatformDirectX11Feature, FFeature);

//============================================================
// <T>����ƽ̨DirectX11���ܡ�</T>
//============================================================
FPlatformDirectX11Feature::FPlatformDirectX11Feature(){
   _name = "DirectX 11";
}

//============================================================
// <T>����ƽ̨DirectX11���ܡ�</T>
//============================================================
FPlatformDirectX11Feature::~FPlatformDirectX11Feature(){
}

//============================================================
// <T>���������</T>
//
// @return ������
//============================================================
TResult FPlatformDirectX11Feature::Construct(){
   TResult resultCd = FFeature::Construct();
   // ע����Ⱦ�豸
   _renderDevice = FPd11RenderDevice::InstanceCreate();
   RDeviceManager::Instance().Register(_renderDevice);
   return resultCd;
}

//============================================================
// <T>��������</T>
//
// @return ������
//============================================================
TResult FPlatformDirectX11Feature::Startup(){
   TResult resultCd = FFeature::Startup();
   RTechniqueManager::Instance().Setup();
   return resultCd;
}

//============================================================
// <T>������</T>
//
// @return ������
//============================================================
TResult FPlatformDirectX11Feature::Suspend(){
   TResult resultCd = FFeature::Suspend();
   return resultCd;
}

//============================================================
// <T>��������</T>
//
// @return ������
//============================================================
TResult FPlatformDirectX11Feature::Resume(){
   TResult resultCd = FFeature::Resume();
   return resultCd;
}

//============================================================
// <T>ֹͣ����</T>
//
// @return ������
//============================================================
TResult FPlatformDirectX11Feature::Shutdown(){
   TResult resultCd = FFeature::Shutdown();
   return resultCd;
}

//============================================================
// <T>�ͷ������</T>
//
// @return ������
//============================================================
TResult FPlatformDirectX11Feature::Dispose(){
   TResult resultCd = FFeature::Dispose();
   // ע���豸
   //RDeviceManager::Instance().Unregister(FRenderDevice::Class());
   return resultCd;
}

MO_NAMESPACE_END
