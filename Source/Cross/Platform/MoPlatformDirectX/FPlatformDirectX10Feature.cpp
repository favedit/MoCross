#include "MoPlatformDirectX10.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FPlatformDirectX10Feature, FFeature);

//============================================================
// <T>����ƽ̨DirectX10���ܡ�</T>
//============================================================
FPlatformDirectX10Feature::FPlatformDirectX10Feature(){
   _name = "DirectX 10";
}

//============================================================
// <T>����ƽ̨DirectX10���ܡ�</T>
//============================================================
FPlatformDirectX10Feature::~FPlatformDirectX10Feature(){
}

//============================================================
// <T>���������</T>
//
// @return ������
//============================================================
TResult FPlatformDirectX10Feature::Construct(){
   TResult resultCd = FFeature::Construct();
   // ע����Ⱦ�豸
   RDeviceManager::Instance().Register(FPd10RenderDevice::Class(), FRenderDevice::Class());
   return resultCd;
}

//============================================================
// <T>��������</T>
//
// @return ������
//============================================================
TResult FPlatformDirectX10Feature::Startup(){
   TResult resultCd = FFeature::Startup();
   RTechniqueManager::Instance().Setup();
   return resultCd;
}

//============================================================
// <T>������</T>
//
// @return ������
//============================================================
TResult FPlatformDirectX10Feature::Suspend(){
   TResult resultCd = FFeature::Suspend();
   return resultCd;
}

//============================================================
// <T>��������</T>
//
// @return ������
//============================================================
TResult FPlatformDirectX10Feature::Resume(){
   TResult resultCd = FFeature::Resume();
   return resultCd;
}

//============================================================
// <T>ֹͣ����</T>
//
// @return ������
//============================================================
TResult FPlatformDirectX10Feature::Shutdown(){
   TResult resultCd = FFeature::Shutdown();
   return resultCd;
}

//============================================================
// <T>�ͷ������</T>
//
// @return ������
//============================================================
TResult FPlatformDirectX10Feature::Dispose(){
   TResult resultCd = FFeature::Dispose();
   // ע����Ⱦ�豸
   RDeviceManager::Instance().Unregister(FRenderDevice::Class());
   return resultCd;
}

MO_NAMESPACE_END
