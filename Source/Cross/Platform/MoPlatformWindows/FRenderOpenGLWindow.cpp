#include "MoEwWindow.h"

MO_NAMESPACE_BEGIN

static TBool g_runable = ETrue;

//============================================================
// <T>������Ⱦ���ڡ�</T>
//============================================================
FRenderOpenGLWindow::FRenderOpenGLWindow(){
   _title = "Render OpenGL";
}

//============================================================
// <T>������Ⱦ���ڡ�</T>
//============================================================
FRenderOpenGLWindow::~FRenderOpenGLWindow(){
}

//============================================================
// <T>���ô���</T>
//
// @return ������
//============================================================
TResult FRenderOpenGLWindow::Setup(){
   TResult resultCd = FRenderWindow::Setup();
   // ����RC
   _hRC = wglCreateContext(_hDC);
   TBool makeResult = wglMakeCurrent(_hDC, _hRC);
   MO_FATAL_CHECK(makeResult, return EFailure, "wglMakeCurrent failure.");
   return resultCd;
}

//============================================================
// <T>��������</T>
//
// @return ������
//============================================================
TResult FRenderOpenGLWindow::Startup(){
   TBool makeResult = wglMakeCurrent(NULL, NULL);
   MO_FATAL_CHECK(makeResult, return EFailure, "wglMakeCurrent failure.");
   return FRenderWindow::Startup();
}

//============================================================
// <T>�ͷŴ���</T>
//
// @return ������
//============================================================
TResult FRenderOpenGLWindow::Dispose(){
   if(_hRC != NULL){
      wglDeleteContext(_hRC);
      _hRC = NULL;
   }
   if(_hDC != NULL){
      ReleaseDC(_handle, _hDC);
      _hDC = NULL;
   }
   return FRenderWindow::Dispose();
}

//============================================================
// <T>��Ⱦ����</T>
//============================================================
TResult FRenderOpenGLWindow::ProcessRender(){
   // ���״̬
   if(!g_runable){
      return EContinue;
   }
   if(!_statusRenderable){
      return EContinue;
   }
   //............................................................
   _locker.Enter();
   // ѡ��RC��Ϊ��ǰ�̵߳�RC
   TBool result = wglMakeCurrent(_hDC, _hRC);
   if(!result){
      return EContinue;
   }
   MO_FATAL_CHECK(result, return EFailure, "wglMakeCurrent failure.");
   // ��̨����������
   if(!g_runable){
      return EContinue;
   }
   // ������̨
   REngineManager::Instance().Process();
   //������ǰ�������ͺ�̨������
   if(!g_runable){
      return EContinue;
   }
   result = SwapBuffers(_hDC);
   MO_FATAL_CHECK(result, return EFailure, "SwapBuffers failure.");
   // ȡ����ǰ�߳�ѡ�е�RC
   result = wglMakeCurrent(NULL, NULL);
   MO_FATAL_CHECK(result, return EFailure, "wglMakeCurrent failure.");
   _locker.Leave();
   return ESuccess;
}

MO_NAMESPACE_END
