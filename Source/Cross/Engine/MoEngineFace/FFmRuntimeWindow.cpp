#include "MoFmRuntime.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>�������д��ڡ�</T>
//============================================================
FFmRuntimeWindow::FFmRuntimeWindow(){
   MO_CLEAR(_pCloseButton);
}

//============================================================
// <T>�������д��ڡ�</T>
//============================================================
FFmRuntimeWindow::~FFmRuntimeWindow(){
}

//============================================================
// <T>�ر��¼�����</T>
//
// @param pEvent �¼�
// @return ������
//============================================================
TResult FFmRuntimeWindow::OnCloseClick(SMouseEvent* pEvent){
   Hide();
   return ESuccess;
}

//============================================================
// <T>���ú��ô���</T>
//
// @return ������
//============================================================
TResult FFmRuntimeWindow::OnSetupAfter(){
   TResult result = FUiWindow::OnSetupAfter();
   //_pCloseButton = (FUiButton*)ChildGet("btnClose");
   //_pCloseButton->ListenersClick().Register<FFmRuntimeWindow>(this, &FFmRuntimeWindow::OnCloseClick);
   return result;
}

MO_NAMESPACE_END
