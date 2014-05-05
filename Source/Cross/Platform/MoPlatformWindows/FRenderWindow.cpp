#include "MoEwWindow.h"

MO_NAMESPACE_BEGIN

static TBool g_runable = ETrue;

//============================================================
// <T>������Ⱦ���ڡ�</T>
//============================================================
FRenderWindow::FRenderWindow(){
   _className = "MoRenderWindow";
   _title = "Render window";
   _statusRenderable = EFalse;
   _size.Set(1280, 800);
   _handle = 0;
   _atom = 0;
   MO_CLEAR(_pRenderThread);
   _pParticleController = MO_CREATE(FParticleController);
}

//============================================================
// <T>������Ⱦ���ڡ�</T>
//============================================================
FRenderWindow::~FRenderWindow(){
   if(_pRenderThread != NULL){
      _pRenderThread->Stop();
      _pRenderThread = NULL;
   }
}

//============================================================
// <T>��Ϣ����</T>
//
// @param hWnd ���ھ��
// @param message ��Ϣ����
// @param wParam �̲���
// @param lParam ������
// @return ������
//============================================================
LRESULT CALLBACK FRenderWindow::OnProcessMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam){
   switch(message){
      case WM_DESTROY:
         g_runable = EFalse;
         PostQuitMessage(0);
         break;
      default:
         return DefWindowProc(hWnd, message, wParam, lParam);
   }
   return 0;
}

//============================================================
// <T>ע�ᴰ����ʽ�ࡣ</T>
//============================================================
void FRenderWindow::RegisterClass(){
   TInstance hInstance = RApplication::Hinstance();
   WNDCLASSEX wcex;
   wcex.cbSize       = sizeof(WNDCLASSEX);
   wcex.style			= CS_HREDRAW | CS_VREDRAW;
   wcex.lpfnWndProc	= (WNDPROC)OnProcessMessage;
   wcex.cbClsExtra	= 0;
   wcex.cbWndExtra	= 0;
   wcex.hInstance		= hInstance;
   wcex.hIcon	      = LoadIcon(hInstance, IDC_ARROW);
   wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
   wcex.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
   wcex.lpszMenuName	 = NULL;
   wcex.lpszClassName = _className.MemoryC();
   wcex.hIconSm		 = NULL;
   _atom = RegisterClassEx(&wcex);
}

//============================================================
// <T>���ô���</T>
//
// @return ������
//============================================================
TResult FRenderWindow::Setup(){
   // ע�ᴰ����
   RegisterClass();
   // ��������
   TInstance hInstance = RApplication::Hinstance();
   _handle = CreateWindow((TCharC*)_className, (TCharC*)_title,
         WS_SYSMENU | WS_CAPTION | WS_VISIBLE,
         CW_USEDEFAULT, CW_USEDEFAULT, _size.width, _size.height,
         NULL, NULL, hInstance, NULL);
   MO_ASSERT(_handle);
   // ��ʾ����
   TInt commandShow = RApplication::CommandShow();
   ShowWindow(_handle, commandShow);
   //��ʼ�����ظ�ʽ
   PIXELFORMATDESCRIPTOR descriptor = {
      sizeof(PIXELFORMATDESCRIPTOR),    // ������ʽ�������Ĵ�С
      1,                                // �汾��
      PFD_DRAW_TO_WINDOW |              // ��ʽ֧�ִ���
      PFD_SUPPORT_OPENGL |              // ��ʽ����֧��OpenGL
      PFD_DOUBLEBUFFER,                 // ����֧��˫����
      PFD_TYPE_RGBA,                    // ����RGBA ��ʽ
      24,                               // ѡ��ɫ�����
      0, 0, 0, 0, 0, 0, 0, 0,           // ����RGBA
      0,                                // ���ۼӻ���
      0, 0, 0, 0,                       // ���Ծۼ�λ
      32,                               // 32λZ-����(��Ȼ���)
      0,                                // ���ɰ建��
      0,                                // �޸�������
      PFD_MAIN_PLANE,                   // ����ͼ��
      0,                                // Reserved
      0, 0, 0                           // ���Բ�����
   };
   // ���DC
   _hDC = GetDC(_handle);
   // ѡ��һ�����ʺ�pfd���������ظ�ʽ����ֵ
   TInt pixelFormat = ChoosePixelFormat(_hDC, &descriptor);
   SetPixelFormat(_hDC, pixelFormat, &descriptor);
   // ���´���
   UpdateWindow(_handle);
   // ���ô���
   RECT rect;
   GetClientRect(_handle, &rect);
   FScreenDevice* pScreenDevice = RDeviceManager::Instance().Find<FScreenDevice>();
   pScreenDevice->Resize(rect.right, rect.bottom);
   return ESuccess;
}

//============================================================
// <T>��������</T>
//
// @return ������
//============================================================
TResult FRenderWindow::Startup(){
   // ������Ⱦ�߳�
   _pRenderThread = MO_CREATE(FRenderThread);
   _pRenderThread->SetWindow(this);
   _pRenderThread->Start();
   // ������Ⱦ
   _statusRenderable = ETrue;
   // ��ʼ��ʱ��
   FTimerDevice* pTimerDevice = RDeviceManager::Instance().Find<FTimerDevice>();
   pTimerDevice->Setup();
   return ESuccess;
}

//============================================================
// <T>�ͷŴ���</T>
//
// @return ������
//============================================================
TResult FRenderWindow::Dispose(){
   _statusRenderable = EFalse;
   return ESuccess;
}

//============================================================
// <T>��Ⱦ����</T>
//
// @return ������
//============================================================
TResult FRenderWindow::ProcessRender(){
   // ���״̬
   if(!g_runable){
      return EContinue;
   }
   if(!_statusRenderable){
      return EContinue;
   }
   //............................................................
   // ������̨
   _locker.Enter();
   REngineManager::Instance().Process();
   _locker.Leave();
   return ESuccess;
}

//============================================================
// <T>�߼�����</T>
//============================================================
TInt FRenderWindow::Process(){
   MSG message;
   FMouseDevice* pMouseDevice = RDeviceManager::Instance().Find<FMouseDevice>();
   FKeyboardDevice* pKeyboardDevice = RDeviceManager::Instance().Find<FKeyboardDevice>();
   while(GetMessage(&message, NULL, 0, 0)){
      _locker.Enter();
      switch(message.message){
         case WM_LBUTTONDOWN:{
            POINTS point = MAKEPOINTS(message.lParam);
            pMouseDevice->DoMouseDown(EMouseButton_Left, point.x, point.y);
            break;
         }
         case WM_LBUTTONUP:{
            POINTS point = MAKEPOINTS(message.lParam);
            pMouseDevice->DoMouseUp(EMouseButton_Left, point.x, point.y);
            break;
         }
         case WM_MOUSEMOVE:{
            POINTS point = MAKEPOINTS(message.lParam);
            pMouseDevice->DoMouseMove(0, point.x, point.y);
            break;
         }
         case WM_KEYDOWN:{
            pKeyboardDevice->DoKeyDown(message.wParam);
            break;
         }
         case WM_KEYUP:{
            pKeyboardDevice->DoKeyUp(message.wParam);
            break;
         }
         case WM_DESTROY:{
            Dispose();
            PostQuitMessage(0);
            break;
         }
         default:{
            // �ַ���Ϣ
            TranslateMessage(&message);
            DispatchMessage(&message);
            break;
         }
      }
      _locker.Leave();
   }
   // ֹͣ�߳�
   _pRenderThread->Stop();
   return message.wParam;
}

MO_NAMESPACE_END
