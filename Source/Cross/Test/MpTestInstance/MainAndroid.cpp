#ifdef _MO_ANDROID
#include <MoEngine.h>
#include <MoEngine3d.h>
#include <MoEngineFace.h>
#include <MoEngineRender.h>
#include <MoEngineAndroid.h>
#include <MoEngineOpenGL.h>
#include <MoGameEngine.h>
#include "MoTestLogic.h"
#include "MpMain.h"

MO_NAMESPACE_INCLUDE;

#ifdef __cplusplus
extern "C" {
#endif

#define MO_RESOURCE_CODE 910010001

typedef TLooper<FTemplate3d*> TTemplate3dLooper;

TTimeTick g_lastTick = 0;
TTimeTick g_templateTick = 0;
FPerspectiveProjection* g_pProjection = NULL;
TTemplate3dLooper g_pTemplates;

static TThreadLocker _locker;

//============================================================
// <T>����¼�����</T>
//
// @param pEvent �¼�
// @return ������
//============================================================
TResult OnMouseDown(SMouseEvent* pEvent){
   TFloat x = (TFloat)pEvent->position.x;
   TFloat y = (TFloat)pEvent->position.y;
   return DoParticle(x, y);
}

//============================================================
// <T>����¼�����</T>
//
// @param pEvent �¼�
// @return ������
//============================================================
TResult OnMouseMove(SMouseEvent* pEvent){
   TResult result = ESuccess;
   TFloat x = (TFloat)pEvent->position.x;
   TFloat y = (TFloat)pEvent->position.y;
   //if(RDeviceManager::Instance().MouseDevice()->TestMouseDownLeft()){
      result = DoParticle(x, y);
   //}
   return result;
}

//============================================================
// <T>����¼�����</T>
//
// @param pEvent �¼�
// @return ������
//============================================================
TResult OnMouseUp(SMouseEvent* pEvent){
   return ESuccess;
}

//============================================================
// <T>����¼�����</T>
//
// @param pEvent �¼�
// @return ������
//============================================================
TResult OnEnterFrame(SFrameEvent* pEvent){
   TTimeTick currentTick = RTimeTick::Current();
   if(g_templateTick == 0){
      g_lastTick = currentTick;
      g_templateTick = currentTick;
      return ESuccess;
   }
   TTimeSpan span = currentTick - g_templateTick;
   TFloat rate = (TFloat)span / 1000000.0f;
   for(TInt n = 0; n < 256; n++){
      FTemplate3d* pTemplate = g_pTemplates.Next();
      pTemplate->MatrixModel().SetRotation(0.0f, MO_PI_FLOAT / 180.0f * 220.0f + rate * 1.0f, 0.0f);
      pTemplate->MatrixModel().UpdateForce();
   }
   // ��ʾͳ����Ϣ
   TTimeSpan spanSecond = (currentTick - g_lastTick) / 1000000;
   if(spanSecond >= 5){
      RStatisticsManager::Instance().Track();
      RStatisticsManager::Instance().Reset();
      FRenderDevice* pRenderDevice = RDeviceManager::Instance().Find<FRenderDevice>();
      FRenderStatistics* pStatistics = pRenderDevice->Statistics();
      pStatistics->Track();
      pStatistics->Reset();
      g_lastTick = currentTick;
   }
   return ESuccess;
}

//============================================================
// <T>���ô���</T>
//============================================================
JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM* pJavaVM, void* pReserved){
	return JNI_VERSION_1_4;
}

//============================================================
// <T>��ʼ������</T>
//
// @param pEnvironment ����
// @param pObject ����
//============================================================
JNIEXPORT void JNICALL Java_mo_android_api_RNativeApi_initialize(JNIEnv * pEnvironment, jobject pObject, jobject assetManager){
   // ��ʼ������
   MoInitialize();
   MoCoreInitialize();
   MoFeatureGraphicsInitialize();
   MoEngineInitialize();
   MoEngine3dInitialize();
   MoEngineFaceInitialize();
   MoEngineOpenGLInitialize();
   MoEngineAndroidInitialize();
   MoGameEngineInitialize();
   //............................................................
   // ��������
   //MoEngineFaceStartup();
   //............................................................
   // ������Դ������
   FEaAssetConsole* pAssetConsole = (FEaAssetConsole*)RAssetManager::InstancePtr();
   pAssetConsole->Link(pEnvironment, assetManager);
   pAssetConsole->Setup();
}

//============================================================
// <T>���û�����</T>
//
// @param pEnvironment ����
// @param pObject ����
// @param code ����
// @param value ����
//============================================================
JNIEXPORT void JNICALL Java_mo_android_api_RNativeApi_setEnvironment(JNIEnv* pEnvironment, jobject pObject, jstring code, jstring value){
   // �������
   TCharC* pCode = pEnvironment->GetStringUTFChars(code, NULL);
   if(pCode == NULL){
      return;
   }
   TCharC* pValue = pEnvironment->GetStringUTFChars(value, NULL);
   if(pValue == NULL){
      return;
   }
   MO_STATIC_INFO("Set environment. (code=%s, value=%s)", pCode, pValue);
   // ������Ļ���
   if(RString::Equals(pCode, "screen.width")){
      FScreenDevice* pScreenDevice = RDeviceManager::Instance().Find<FScreenDevice>();
      pScreenDevice->Size().width = RInt::Parse(pValue);
   }
   // ������Ļ�߶�
   if(RString::Equals(pCode, "screen.height")){
      FScreenDevice* pScreenDevice = RDeviceManager::Instance().Find<FScreenDevice>();
      pScreenDevice->Size().height = RInt::Parse(pValue);
   }
   // �ͷ�����
   pEnvironment->ReleaseStringUTFChars(code, pCode);
   pEnvironment->ReleaseStringUTFChars(value, pValue);
}

//============================================================
// <T>���ô���</T>
//
// @param pEnvironment ����
// @param pObject ����
//============================================================
JNIEXPORT void JNICALL Java_mo_android_api_RNativeApi_setup(JNIEnv * pEnvironment, jobject pObject){
   // ������Ļ��С
   FScreenDevice* pScreenDevice = RDeviceManager::Instance().Find<FScreenDevice>();
   SIntSize2& screenSize = pScreenDevice->Size();;
   MO_STATIC_INFO("Native api setup. (width=%d, height=%d)", screenSize.width, screenSize.height);
   // ���Ļ����С
   //............................................................
   // �����豸
   FRenderDevice* pRenderDevice = RDeviceManager::Instance().Find<FRenderDevice>();
   pRenderDevice->Setup();
   pRenderDevice->SetBackBuffer(screenSize.width, screenSize.height, 1);
   //............................................................
   // ��ʼ����̨
   MoFeatureGraphicsStartup();
   MoEngineStartup();
   MoEngine3dStartup();
   MoEngineOpenGLStartup();
   MoEngineRenderStartup();
   //MoEngineFaceStartup();
   // ѡ����Ⱦ��ʽ
   RPipelineManager::Instance().SelectPipeline("simple");
   RTechniqueManager::Instance().SetOptionInstance(ETrue);
   // ע������
   FEoFont* pFont = MO_CREATE(FEoFont);
   pFont->CharSize().Set(14, 14);
   //pFont->SetAssetName("asset:/ft/DroidSansFallback.ttf");
   //RFontManager::Instance().RegisterFont(pFont);
   //............................................................
   // ����Դ������
   RResource3dManager::Instance().ThemeConsole()->Open("asset:/theme/color.ser");
   // RInstance3dManager::Instance().AnimationConsole()->SetLooperLimit(1024);
   //............................................................
   // ע���¼�
   FMouseDevice* pMouseDevice = RDeviceManager::Instance().Find<FMouseDevice>();
   pMouseDevice->ListenersMouseDown().Register(&OnMouseDown);
   pMouseDevice->ListenersMouseMove().Register(&OnMouseMove);
   pMouseDevice->ListenersMouseUp().Register(&OnMouseUp);
   //............................................................
   // ������̨
   FGameStage* pStage = MO_CREATE(FGameStage);
   //pStage->Size().Set(512, 1024);
   //pStage->Size().Assign(screenSize);
   pStage->Setup();
   // ����ͶӰ
   g_pProjection = FPerspectiveProjection::InstanceCreate();
   g_pProjection->Size().Set(screenSize.width, screenSize.height);
   g_pProjection->SetZ(0.1f, 1000.0f);
   g_pProjection->SetAngle(30.0f);
   g_pProjection->Update();
   // �������
   FCamera* pCamera = FPerspectiveCamera::InstanceCreate();
   pCamera->Position().Set(0.0f, 80.0f, -80.0f);
   pCamera->LookAt(0.0f, 0.0f, 0.0f);
   pCamera->SetProjection(g_pProjection);
   pCamera->Update();
   // �����ӽ�
   FViewport* pViewport = FViewport::InstanceCreate();
   pViewport->Set(0, 0, 500, 800);
   // �����ӽ�
   FRenderView* pView = FRenderView::InstanceCreate();
   pView->SetCamera(pCamera);
   pView->SetViewport(pViewport);
   pStage->SceneFrame()->Views()->Push(pView);
   pStage->SceneFrame()->BackgroundColor().Set(1.0f, 1.0f, 1.0f, 1.0f);
   // ����ͶӰ
   FPerspectiveProjection* pLightProjection = FPerspectiveProjection::InstanceCreate();
   pLightProjection->Size().Set(1024, 1024);
   pLightProjection->SetZ(0.1f, 1000.0f);
   pLightProjection->SetAngle(30.0f);
   pLightProjection->Update();
   // ���ù�Դ���
   FCamera* pLightCamera = FPerspectiveCamera::InstanceCreate();
   pLightCamera->Position().Set(200.0f, 100.0f, -80.0f);
   pLightCamera->LookAt(0.0f, 0.0f, 0.0f);
   pLightCamera->SetProjection(pLightProjection);
   pLightCamera->Update();
   // ���ù�Դ�ӽ�
   FViewport* pLightViewport = FViewport::InstanceCreate();
   pLightViewport->Set(0, 0, 1024, 1024);
   // ���ù�Դ
   FDirectionalLight* pLight = FDirectionalLight::InstanceCreate();
   pLight->SetCamera(pLightCamera);
   pLight->SetViewport(pLightViewport);
   pLight->Direction().Set(MO_PI_FLOAT / 4.0f, -MO_PI_FLOAT / 4.0f, MO_PI_FLOAT / 4.0f);
   pStage->SetDirectionalLight(pLight);
   // ������̨
   RStageManager::Instance().SelectStage(pStage);
   //pStage->ListenersFrameEnter().Register(&OnEnterFrame);
   pStage->ListenersFrameLeave().Register(&OnEnterFrame);
   //............................................................
   //for(TInt y = 0; y < 6; y++){
   //   for(TInt x = 0; x < 6; x++){
   //      FTemplate3d* pTemplate = RInstance3dManager::Instance().TemplateConsole()->Alloc("pvw.show.item.001");
   //      pTemplate->MatrixModel().SetTranslate(10.0f * x - 25.0f, 5.0f, 10.0f * y - 50.0f);
   //      pTemplate->MatrixModel().SetRotation(0.0f, MO_PI_FLOAT / 180.0f * 220.0f, 0.0f);
   //      pTemplate->MatrixModel().SetScale(3.0f, 3.0f, 3.0f);
   //      pTemplate->MatrixModel().UpdateForce();
   //      pStage->SpriteLayer()->DisplayPush(pTemplate);
   //      g_pTemplates.Push(pTemplate);
   //   }
   //}
   //............................................................
   for(TInt y = 0; y < 20; y++){
      for(TInt x = 0; x < 20; x++){
         FTemplate3d* pTemplate = RInstance3dManager::Instance().TemplateConsole()->Alloc("entity.001.001");
         pTemplate->MatrixModel().SetTranslate(1.4f * x - 12.0f, 0.0f, 4.0f * y - 30.0f);
         pTemplate->MatrixModel().SetRotation(0.0f, MO_PI_FLOAT / 180.0f * 220.0f, 0.0f);
         pTemplate->MatrixModel().SetScale(0.03f, 0.03f, 0.03f);
         pTemplate->MatrixModel().UpdateForce();
         pTemplate->Animation()->SetBaseTick(10000000 * y + 100000 * x);
         pStage->SpriteLayer()->DisplayPush(pTemplate);
         g_pTemplates.Push(pTemplate);
      }
   }
   // ��ʼʱ��
   RDeviceManager::Instance().Find<FTimerDevice>()->Setup();
   MO_STATIC_INFO("Setup success");
}

//============================================================
// <T>���ô�С��</T>
//
// @param pEnvironment ����
// @param pObject ����
//============================================================
JNIEXPORT void JNICALL Java_mo_android_api_RNativeApi_resize(JNIEnv * pEnvironment, jobject pObject, jint width, jint height){
   MO_STATIC_INFO("Native api resize. (width=%d, height=%d)", width, height);
   _locker.Enter();
   // ������Ļ��С
   FScreenDevice* pScreenDevice = RDeviceManager::Instance().Find<FScreenDevice>();
   pScreenDevice->Resize(width, height);
   // ���Ļ����С
   FRenderDevice* pRenderDevice = RDeviceManager::Instance().Find<FRenderDevice>();
   pRenderDevice->SetBackBuffer(width, height, 1);
   // ����ͶӰ
   if(g_pProjection != NULL){
      g_pProjection->Size().Set(width, height);
      g_pProjection->Update();
   }
   _locker.Leave();
}

//============================================================
// <T>ѭ������</T>
//
// @param pEnvironment ����
// @param pObject ����
//============================================================
JNIEXPORT void JNICALL Java_mo_android_api_RNativeApi_process(JNIEnv * pEnvironment, jobject pObject){
   // ���洦��
   _locker.Enter();
   REngineManager::Instance().Process();
   _locker.Leave();
}

//============================================================
// <T>�ͷŴ���</T>
//
// @param pEnvironment ����
// @param pObject ����
//============================================================
JNIEXPORT void JNICALL Java_mo_android_api_RNativeApi_release(JNIEnv * pEnvironment, jobject pObject){
   MO_STATIC_INFO("Native api release.");
   MoEngineOpenGLRelease();
   MoEngineAndroidRelease();
   MoEngineFaceRelease();
   MoEngine3dRelease();
   MoEngineRelease();
   MoFeatureGraphicsRelease();
   MoCoreRelease();
   MoRelease();
}

//============================================================
// <T>������´���</T>
//
// @param pEnvironment ����
// @param pObject ����
//============================================================
void JNICALL Java_mo_android_api_RNativeApi_onMouseDown(JNIEnv* pEnvironment, jobject pObject, jint buttonCd, jfloat x, jfloat y){
   _locker.Enter();
   RDeviceManager::Instance().Find<FMouseDevice>()->DoMouseDown(buttonCd, x, y);
   _locker.Leave();
}

//============================================================
// <T>����ƶ�����</T>
//
// @param pEnvironment ����
// @param pObject ����
//============================================================
void JNICALL Java_mo_android_api_RNativeApi_onMouseMove(JNIEnv* pEnvironment, jobject pObject, jint buttonCd, jfloat x, jfloat y){
   _locker.Enter();
   RDeviceManager::Instance().Find<FMouseDevice>()->DoMouseMove(buttonCd, x, y);
   _locker.Leave();
}

//============================================================
// <T>���̧����</T>
//
// @param pEnvironment ����
// @param pObject ����
//============================================================
void JNICALL Java_mo_android_api_RNativeApi_onMouseUp(JNIEnv* pEnvironment, jobject pObject, jint buttonCd, jfloat x, jfloat y){
   _locker.Enter();
   RDeviceManager::Instance().Find<FMouseDevice>()->DoMouseUp(buttonCd, x, y);
   _locker.Leave();
}

#ifdef __cplusplus
}
#endif

#endif // _MO_ANDROID
