#include <MoFeatureLogger.h>
#include <MoFeatureGraphic.h>
#include <MoEngine.h>
#include <MoEngineFace.h>
#include <MoEngineRender.h>
#include <MoPlatformOpenGLES2.h>
#ifdef _MO_WINDOWS
#include <MoPlatformWindows.h>
#endif // _MO_WINDOWS
#ifdef _MO_ANDROID
#include <MoPlatformAndroid.h>
#endif // _MO_ANDROID
#include "MoGameEngine.h"
      
MO_NAMESPACE_BEGIN

//============================================================
// <T>��ʼ����Ϸ���洦��</T>
//============================================================
void MoGameEngineInitialize(){
   MO_STATIC_INFO("Game engine initialize.");
   MoInitialize();
   MoCoreInitialize();
   MoFeatureLoggerInitialize();
   MoFeatureGraphicsInitialize();
   MoEngineInitialize();
   MoEngine3dInitialize();
   MoEngineFaceInitialize();
   MoEngineOpenGLES2Initialize();
#ifdef _MO_WINDOWS
   MoPlatformWindowsInitialize();
#endif // _MO_WINDOWS
#ifdef _MO_ANDROID
   MoEngineAndroidInitialize();
#endif // _MO_ANDROID
   //............................................................
   RGameSceneManager::Create();
}

//============================================================
// <T>������Ϸ���洦��</T>
//============================================================
void MoGameEngineStartup(){
   MO_STATIC_INFO("Game engine startup.");
   MoFeatureGraphicsStartup();
   MoEngineStartup();
   MoEngine3dStartup();
   MoEngineOpenGLES2Startup();
   MoEngineRenderStartup();
   //MoEngineFaceStartup();
}

//============================================================
// <T>�ر���Ϸ���洦��</T>
//============================================================
void MoGameEngineShutdown(){
   MO_STATIC_INFO("Game engine shutdown.");
   MoFeatureGraphicsShutdown();
   MoEngine3dShutdown();
   MoEngineShutdown();
}

//============================================================
// <T>�ͷ���Ϸ���洦��</T>
//============================================================
void MoGameEngineRelease(){
   MO_STATIC_INFO("Game engine release.");
   RGameSceneManager::Destroy();
   //............................................................
#ifdef _MO_WINDOWS
   MoPlatformWindowsRelease();
#endif // _MO_WINDOWS
#ifdef _MO_ANDROID
   MoEngineAndroidRelease();
#endif // _MO_ANDROID
   MoEngineOpenGLES2Release();
   MoEngineFaceRelease();
   MoEngineRelease();
   MoFeatureGraphicsRelease();
   MoCoreRelease();
   RClassManager::Instance().TrackActive();
   MoRelease();
}

MO_NAMESPACE_END
