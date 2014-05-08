#include "MoPlatformDirectX9.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FPlatformDirectX9Feature, FFeature);

//============================================================
// <T>����ƽ̨DirectX9���ܡ�</T>
//============================================================
FPlatformDirectX9Feature::FPlatformDirectX9Feature(){
   _name = "DirectX 9";
}

//============================================================
// <T>����ƽ̨DirectX9���ܡ�</T>
//============================================================
FPlatformDirectX9Feature::~FPlatformDirectX9Feature(){
}

//============================================================
// <T>���������</T>
//
// @return ������
//============================================================
TResult FPlatformDirectX9Feature::Construct(){
   TResult resultCd = FFeature::Construct();
   // ע����Ⱦ�豸
   RDeviceManager::Instance().Register(FPd9RenderDevice::Class(), FRenderDevice::Class());
   return resultCd;
}

//============================================================
// <T>��������</T>
//
// @return ������
//============================================================
TResult FPlatformDirectX9Feature::Startup(){
   TResult resultCd = FFeature::Startup();
   RTechniqueManager::Instance().Setup();
   return resultCd;
}

//============================================================
// <T>������</T>
//
// @return ������
//============================================================
TResult FPlatformDirectX9Feature::Suspend(){
   TResult resultCd = FFeature::Suspend();
   return resultCd;
}

//============================================================
// <T>��������</T>
//
// @return ������
//============================================================
TResult FPlatformDirectX9Feature::Resume(){
   TResult resultCd = FFeature::Resume();
   return resultCd;
}

//============================================================
// <T>ֹͣ����</T>
//
// @return ������
//============================================================
TResult FPlatformDirectX9Feature::Shutdown(){
   TResult resultCd = FFeature::Shutdown();
   return resultCd;
}

//============================================================
// <T>�ͷ������</T>
//
// @return ������
//============================================================
TResult FPlatformDirectX9Feature::Dispose(){
   TResult resultCd = FFeature::Dispose();
   // ע����Ⱦ�豸
   RDeviceManager::Instance().Unregister(FRenderDevice::Class());
   return resultCd;
}

MO_NAMESPACE_END
