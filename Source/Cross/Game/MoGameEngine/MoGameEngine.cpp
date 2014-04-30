#include <MoFeatureLogger.h>
#include <MoFeatureGraphic.h>
#include <MoEngine.h>
#include <MoEngineFace.h>
#include <MoEngineRender.h>
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
   MoFeatureResourceInitialize();
   MoEngineInitialize();
   MoEngine3dInitialize();
   MoEngineFaceInitialize();
#ifdef _MO_WINDOWS
   MoPlatformWindowsInitialize();
#endif // _MO_WINDOWS
#ifdef _MO_ANDROID
   MoPlatformAndroidInitialize();
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
   MoFeatureResourceStartup();
   MoEngineStartup();
   MoEngine3dStartup();
   MoEngineRenderStartup();
   //MoEngineFaceStartup();
}

//============================================================
// <T>�ر���Ϸ���洦��</T>
//============================================================
void MoGameEngineShutdown(){
   MO_STATIC_INFO("Game engine shutdown.");
   MoFeatureGraphicsShutdown();
   MoFeatureResourceShutdown();
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
   MoPlatformAndroidRelease();
#endif // _MO_ANDROID
   MoEngineFaceRelease();
   MoEngineRelease();
   MoFeatureResourceRelease();
   MoFeatureGraphicsRelease();
   MoCoreRelease();
   RClassManager::Instance().TrackActive();
   MoRelease();
}

MO_NAMESPACE_END
