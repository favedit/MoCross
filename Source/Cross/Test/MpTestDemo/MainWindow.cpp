#include <ft2build.h>
#include FT_FREETYPE_H 
#include <MoFeatureLogger.h>
#include <MoFeatureGraphic.h>
#include <MoEngine.h>
#include <MoEngineFace.h>
#include <MoEngineRender.h>
#include <MoPlatformOpenGLES2.h>
//#include <MoPlatformDirectX10.h>
#include <MoPlatformDirectX11.h>
#include <MoPlatformWindows.h>
#include <MoGameEngine.h>
#include "MoTestLogic.h"
#include "MpMain.h"

#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>
#include <xnamath.h>

MO_NAMESPACE_INCLUDE;

#define MO_RESOURCE_CODE 910010001


//--------------------------------------------------------------------------------------
// Structures
//--------------------------------------------------------------------------------------
struct SimpleVertex
{
    XMFLOAT3 Pos;
    XMFLOAT2 Tex;
};

struct CBNeverChanges
{
    XMMATRIX mView;
};

struct CBChangeOnResize
{
    XMMATRIX mProjection;
};

struct CBChangesEveryFrame
{
    XMMATRIX mWorld;
    XMFLOAT4 vMeshColor;
};


//--------------------------------------------------------------------------------------
// Global Variables
//--------------------------------------------------------------------------------------
ID3D11Buffer* g_pCBNeverChanges = NULL;
ID3D11Buffer* g_pCBChangeOnResize = NULL;
ID3D11Buffer* g_pCBChangesEveryFrame = NULL;
XMMATRIX      g_World;
XMMATRIX      g_View;
XMMATRIX      g_Projection;
XMFLOAT4      g_vMeshColor( 0.7f, 0.7f, 0.7f, 1.0f );

typedef TVector<FTemplate3d*> TTemplate3dVector;
TTimeTick g_lastTick = 0;
TTimeTick g_templateTick = 0;
TTemplate3dVector g_pTemplates;
FEffect* g_pEffect = NULL;
FPd11RenderVertexBuffer* g_pVertexBuffer = NULL;
FPd11RenderIndexBuffer* g_pIndexBuffer = NULL;
FPd11RenderLayout* g_pLayout = NULL;
FPd11RenderFlatTexture* g_pTexture = NULL;

//============================================================
// <T>鼠标事件处理。</T>
//
// @param pEvent 事件
// @return 处理结果
//============================================================
TResult OnMouseDown(SMouseEvent* pEvent){
   TFloat x = (TFloat)pEvent->position.x;
   TFloat y = (TFloat)pEvent->position.y;
   return DoParticle(x, y);
}

//============================================================
// <T>鼠标事件处理。</T>
//
// @param pEvent 事件
// @return 处理结果
//============================================================
TResult OnMouseMove(SMouseEvent* pEvent){
   TResult result = ESuccess;
   TFloat x = (TFloat)pEvent->position.x;
   TFloat y = (TFloat)pEvent->position.y;
   //if(RDeviceManager::Instance().MouseDevice()->TestMouseDownLeft()){
   //   result = DoParticle(x, y);
   //}
   return result;
}

//============================================================
// <T>鼠标事件处理。</T>
//
// @param pEvent 事件
// @return 处理结果
//============================================================
TResult OnMouseUp(SMouseEvent* pEvent){
   return ESuccess;
}

//============================================================
// <T>鼠标事件处理。</T>
//
// @param pEvent 事件
// @return 处理结果
//============================================================
TResult OnKeyDown(SKeyboardEvent* pEvent){
   if(pEvent->keyCode == EKeyCode_P){
      TBool pause = RDeviceManager::Instance().StatusPause();
      if(pause){
         RDeviceManager::Instance().Resume();
         REffectManager::Instance().Resume();
         RGameSceneManager::Instance().Resume();
      }else{
         RDeviceManager::Instance().Suspend();
         REffectManager::Instance().Suspend();
         RGameSceneManager::Instance().Suspend();
      }
   }
   return ESuccess;
}

//============================================================
// <T>鼠标事件处理。</T>
//
// @param pEvent 事件
// @return 处理结果
//============================================================
TResult OnEnterFrame(SFrameEvent* pEvent){
   MO_STATIC_INFO("------------------------------------------------------------");
   FPd11RenderDevice* pRenderDevice = RDeviceManager::Instance().Find<FPd11RenderDevice>();
    // Update our time
    static float t = 0.0f;
      static DWORD dwTimeStart = 0;
      DWORD dwTimeCur = GetTickCount();
      if( dwTimeStart == 0 )
         dwTimeStart = dwTimeCur;
      t = ( dwTimeCur - dwTimeStart ) / 1000.0f;

    // Rotate cube around the origin
    g_World = XMMatrixRotationY( t );
    // Modify the color
    g_vMeshColor.x = ( sinf( t * 1.0f ) + 1.0f ) * 0.5f;
    g_vMeshColor.y = ( cosf( t * 3.0f ) + 1.0f ) * 0.5f;
    g_vMeshColor.z = ( sinf( t * 5.0f ) + 1.0f ) * 0.5f;
    //
    // Clear the back buffer
    //
    pRenderDevice->Clear(0.0f, 0.125f, 0.3f, 1.0f);
    //
    // Update variables that change once per frame
    //
    CBChangesEveryFrame cb;
    cb.mWorld = XMMatrixTranspose( g_World );
    cb.vMeshColor = g_vMeshColor;

   FPd11RenderProgram* pProgram = (FPd11RenderProgram*)g_pEffect->Program();

    pRenderDevice->NativeContext()->UpdateSubresource( g_pCBChangesEveryFrame, 0, NULL, &cb, 0, 0 );

    pRenderDevice->SetProgram(g_pEffect->Program());

    pRenderDevice->NativeContext()->IASetInputLayout(pProgram->NativeInputLayout());
    //pRenderDevice->BindVertexBuffer(0, g_pVertexBuffer, 0, ERenderVertexFormat_Float3);
    pRenderDevice->SetLayout(g_pLayout);

    pRenderDevice->NativeContext()->VSSetConstantBuffers( 0, 1, &g_pCBNeverChanges );
    pRenderDevice->NativeContext()->VSSetConstantBuffers( 1, 1, &g_pCBChangeOnResize );
    pRenderDevice->NativeContext()->VSSetConstantBuffers( 2, 1, &g_pCBChangesEveryFrame );

    pRenderDevice->NativeContext()->PSSetConstantBuffers( 2, 1, &g_pCBChangesEveryFrame );

    ID3D11ShaderResourceView* pView = g_pTexture->NativeView();
    pRenderDevice->NativeContext()->PSSetShaderResources(0, 1, &pView);

    pRenderDevice->DrawTriangles(g_pIndexBuffer, 0, g_pIndexBuffer->Count());
    pRenderDevice->Present();

   // return ESuccess;
   //TTimeTick currentTick = RTimeTick::Current();
   //if(g_templateTick == 0){
   //   g_lastTick = currentTick;
   //   g_templateTick = currentTick;
   //   return ESuccess;
   //}
   //TTimeSpan span = currentTick - g_templateTick;
   //TFloat rate = (TFloat)span / 1000000.0f;
   //TTemplate3dVector::TIteratorC iterator = g_pTemplates.IteratorC();
   //while(iterator.Next()){
   //   FTemplate3d* pTemplate = *iterator;
   //   pTemplate->MatrixModel().SetRotation(0.0f, MO_PI_FLOAT / 180.0f * 220.0f + rate * 0.7f, 0.0f);
   //   pTemplate->MatrixModel().UpdateForce();
   //}
   //// 显示统计信息
   //TTimeSpan spanSecond = (currentTick - g_lastTick) / 1000000;
   //if(spanSecond >= 5){
   //   RStatisticsManager::Instance().Track();
   //   RStatisticsManager::Instance().Reset();
   //   FRenderDevice* pRenderDevice = RDeviceManager::Instance().Find<FRenderDevice>();
   //   FRenderStatistics* pStatistics = pRenderDevice->Statistics();
   //   pStatistics->Track();
   //   pStatistics->Reset();
   //   g_lastTick = currentTick;
   //}
   return ESuccess;
}

//============================================================
// <T>释放游戏库。</T>
//============================================================
TInt WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpszCmdLine, TInt nCmdShow){
   // 初始化处理
   MoGameEngineInitialize();
   //MoEngineOpenGLES2();
   //MoEngineDirectX10Initialize();
   MoEngineDirectX11();
   RFeatureManager::Instance().Construct();
   //............................................................
   // 设置信息
   //RApplication::Instance().Parameters()->Setup(lpszCmdLine);
   FApplicationParameter* pApplicationParameter = MO_CREATE(FApplicationParameter);
   pApplicationParameter->SetName("-home");
   pApplicationParameter->SetValue("E:/ZW-MoCross/Demo/Android/MpTestDemo/assets");
   RApplication::Instance().Parameters()->Parameters()->Push(pApplicationParameter);
   RApplication::Instance().SetHinstance(hInstance);
   RApplication::Instance().SetCommandShow(nCmdShow);
   RAssetManager::Instance().Setup();
   //RTechniqueManager::Instance().Capability().optionInstance = ETrue;
   //RTechniqueManager::Instance().Capability().optionMerge = ETrue;
   //............................................................
   // 设置日志
   FNetLoggerWriter* pWriter = FNetLoggerWriter::InstanceCreate();
   pWriter->SetHost("127.0.0.1");
   pWriter->SetPort(9999);
   //pWriter->Open();
   //RLoggerFeature::Instance().NetLoggerConsole()->Register(pWriter);
   // 注册环境信息
   //TCharC* pHomePath = RApplication::Instance().Parameters()->FindValue("-home");
   //TCharC* pConfigName = RApplication::Instance().Parameters()->FindValue("-config");
   //TFsPath configFileName;
   //configFileName.AppendFormat("%s\\%s.xml", pHomePath, pConfigName);
   //GPtr<FXmlParser> xmlParser = FXmlParser::InstanceCreate();
   //GPtr<FXmlNode> configNode = xmlParser->LoadNodeFile(configFileName);
   //RConfigurationManager::Instance().LoadConfiguration(configFileName);
   //REnvironmentManager::Instance().Register("home", pHomePath);
   //............................................................
   // 创建窗口
   SIntSize2 screenSize(1200, 800);
   FRenderWindow* pWindow = MO_CREATE(FRenderDirectXWindow);
   //FRenderWindow* pWindow = MO_CREATE(FRenderOpenGLWindow);
   pWindow->Size().Assign(screenSize);
   pWindow->Setup();
   // 初始化渲染设备
   //FRenderDevice* pRenderDevice = RDeviceManager::Instance().Find<FRenderDevice>();
   //FPd10RenderDevice* pRenderDevice = (FPd10RenderDevice*)RDeviceManager::Instance().Find<FRenderDevice>();
   FPd11RenderDevice* pRenderDevice = (FPd11RenderDevice*)RDeviceManager::Instance().Find<FRenderDevice>();
   pRenderDevice->SetWindowHandle(pWindow->Handle());
   pRenderDevice->Setup();
   // 初始化舞台
   MoGameEngineStartup();
   RFeatureManager::Instance().Startup();
   // 选择渲染方式
   RPipelineManager::Instance().SelectPipeline("simple");
   //RPipelineManager::Instance().SelectPipeline("shadow");
   // 注册字体
   FEoFont* pFont = FEoFont::InstanceCreate();
   pFont->CharSize().Set(14, 14);
   pFont->SetAssetName("asset:/font/DroidSansFallback.ttf");
   RFontManager::Instance().RegisterFont(pFont);
   //............................................................
   // 打开资源管理器
   RResource3dManager::Instance().ThemeConsole()->Open("asset:/theme/color.ser");
   //RResource3dManager::Instance().ThemeConsole()->Open("asset:/theme/shadow.ser");
   //RGmResourceManager::Instance().Open();
   //RGmTemplateConsole::Instance().Open();
   //............................................................
   // 注册事件
   FMouseDevice* pMouseDevice = RDeviceManager::Instance().Find<FMouseDevice>();
   pMouseDevice->ListenersMouseDown().Register(&OnMouseDown);
   pMouseDevice->ListenersMouseMove().Register(&OnMouseMove);
   pMouseDevice->ListenersMouseUp().Register(&OnMouseUp);
   FKeyboardDevice* pKeyboardDevice = RDeviceManager::Instance().Find<FKeyboardDevice>();
   pKeyboardDevice->ListenersKeyDown().Register(&OnKeyDown);
   //............................................................
   // 激活舞台
   //RInstance3dManager::Instance().TemplateConsole()->Alloc("pvw.sc.courtyard.item.02.022");
   FGameScene* pScene = RGameSceneManager::Instance().Load("pvw.show.item.001");
   FDisplayLayer* pDisplayLayer = pScene->Layers().Get(0)->Layers()->Get(2);
   FDisplay* pDisplay = pDisplayLayer->Displays().Get(0);
   FRenderable* pRenderable = pDisplay->Renderables().Get(0);
   g_pVertexBuffer = (FPd11RenderVertexBuffer*)pRenderable->VertexStreams()->Buffers()->Get(0);
   g_pIndexBuffer = (FPd11RenderIndexBuffer*)pRenderable->IndexBuffer();
   g_pTexture = (FPd11RenderFlatTexture*)pRenderable->Textures()->Get(0);
   //FGameScene* pScene = RGameSceneManager::Instance().Load("pvw.sc.car.01.001");
   //FGameScene* pScene = RGameSceneManager::Instance().Load("pvw.sc.car.01.002");
   //FGameScene* pScene = RGameSceneManager::Instance().Load("pvw.sc.car.01.003");
   //FGameScene* pScene = RGameSceneManager::Instance().Load("pvw.sc.house.01.scene");
   //FGameScene* pScene = RGameSceneManager::Instance().Load("pvw.show.skeleton.01");
   //FGameScene* pScene = RGameSceneManager::Instance().Load("pvw.show.skeleton.02");
   //FGameScene* pScene = RGameSceneManager::Instance().Load("pvw.show.skeleton.05");
   //FGameScene* pScene = RGameSceneManager::Instance().Load("pvw.sc.courtyard.scene");
   pScene->ListenersFrameEnter().Register(&OnEnterFrame);
   RStageManager::Instance().SelectStage(pScene);

   g_pEffect = REffectManager::Instance().Find("simple.color.automatic", pRenderable);
   FRenderableEffect* pRenderableEffect = pRenderable->EffectBind(g_pEffect);
   pRenderable->SetActiveEffect(pRenderableEffect);
   g_pLayout = pRenderDevice->CreateObject<FPd11RenderLayout>(MO_RENDEROBJECT_LAYOUT);
   g_pLayout->SetProgram(g_pEffect->Program());
   g_pLayout->SetRenderable(pRenderable);
   g_pLayout->Setup();
   //pRenderableEffect->SetLayout();
   
    HRESULT hr = S_OK;

    RECT rc;
    GetClientRect( pWindow->Handle(), &rc );
    UINT width = rc.right - rc.left;
    UINT height = rc.bottom - rc.top;

    //GRenderShaderBufferPtrs& buffers = g_pEffect->Program()->Buffers();
    //FPd11RenderShaderBuffer* pBuffer1 = (FPd11RenderShaderBuffer*)buffers.Get(0);
    //g_pCBNeverChanges = pBuffer1->NativeiBuffer();

    //FPd11RenderShaderBuffer* pBuffer2 = (FPd11RenderShaderBuffer*)buffers.Get(1);
    //g_pCBChangeOnResize = pBuffer2->NativeiBuffer();

    //FPd11RenderShaderBuffer* pBuffer3 = (FPd11RenderShaderBuffer*)buffers.Get(2);
    //g_pCBChangesEveryFrame = pBuffer3->NativeiBuffer();

    // Initialize the world matrices
    g_World = XMMatrixIdentity();

    // Initialize the view matrix
    XMVECTOR Eye = XMVectorSet( 0.0f, 3.0f, -6.0f, 0.0f );
    XMVECTOR At = XMVectorSet( 0.0f, 1.0f, 0.0f, 0.0f );
    XMVECTOR Up = XMVectorSet( 0.0f, 1.0f, 0.0f, 0.0f );
    g_View = XMMatrixLookAtLH( Eye, At, Up );

    CBNeverChanges cbNeverChanges;
    cbNeverChanges.mView = XMMatrixTranspose( g_View );
    pRenderDevice->NativeContext()->UpdateSubresource( g_pCBNeverChanges, 0, NULL, &cbNeverChanges, 0, 0 );

    // Initialize the projection matrix
    g_Projection = XMMatrixPerspectiveFovLH( XM_PIDIV4, width / (FLOAT)height, 0.01f, 10000.0f );
    
    CBChangeOnResize cbChangesOnResize;
    cbChangesOnResize.mProjection = XMMatrixTranspose( g_Projection );
    pRenderDevice->NativeContext()->UpdateSubresource( g_pCBChangeOnResize, 0, NULL, &cbChangesOnResize, 0, 0 );

   //............................................................
   // 处理窗口
   pWindow->Startup();
   pWindow->Process();
   //............................................................
   MoGameEngineShutdown();
   //RFeatureManager::Instance().Release();
   //............................................................
   // 释放处理
   MoGameEngineRelease();
	return 0;
}