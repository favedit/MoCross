#include "MoPlatformOpenGLES2.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FPlatformOpenGLES2Feature, FConsole);

//============================================================
// <T>����ƽ̨OpenGL2���ܡ�</T>
//============================================================
FPlatformOpenGLES2Feature::FPlatformOpenGLES2Feature(){
   _name = "OpenGLES2.0";
}

//============================================================
// <T>����ƽ̨OpenGL2���ܡ�</T>
//============================================================
FPlatformOpenGLES2Feature::~FPlatformOpenGLES2Feature(){
}

//============================================================
// <T>���������</T>
//
// @return ������
//============================================================
TResult FPlatformOpenGLES2Feature::Construct(){
   TResult resultCd = FFeature::Construct();
   // ע����Ⱦ�豸
   RDeviceManager::Instance().Register(FPoe2RenderDevice::Class(), FRenderDevice::Class());
   return resultCd;
}

//============================================================
// <T>��������</T>
//
// @return ������
//============================================================
TResult FPlatformOpenGLES2Feature::Startup(){
   TResult resultCd = FFeature::Startup();
   RTechniqueManager::Instance().Setup();
   return resultCd;
}

//============================================================
// <T>������</T>
//
// @return ������
//============================================================
TResult FPlatformOpenGLES2Feature::Suspend(){
   TResult resultCd = FFeature::Suspend();
   return resultCd;
}

//============================================================
// <T>��������</T>
//
// @return ������
//============================================================
TResult FPlatformOpenGLES2Feature::Resume(){
   TResult resultCd = FFeature::Resume();
   return resultCd;
}

//============================================================
// <T>ֹͣ����</T>
//
// @return ������
//============================================================
TResult FPlatformOpenGLES2Feature::Shutdown(){
   TResult resultCd = FFeature::Shutdown();
   return resultCd;
}

//============================================================
// <T>�ͷ������</T>
//
// @return ������
//============================================================
TResult FPlatformOpenGLES2Feature::Dispose(){
   TResult resultCd = FFeature::Dispose();
   // ע����Ⱦ�豸
   RDeviceManager::Instance().Unregister(FRenderDevice::Class());
   return resultCd;
}

MO_NAMESPACE_END
