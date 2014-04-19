#include "MoE3Display.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>����ʵ��3D������</T>
//============================================================
FAnimation3dThread::FAnimation3dThread(){
   _looperLimit = 256;
   _pLooper = MO_CREATE(FAnimation3dLooper);
}

//============================================================
// <T>����ʵ��3D������</T>
//============================================================
FAnimation3dThread::~FAnimation3dThread(){
   MO_DELETE(_pLooper);
}

//============================================================
// <T>�������ƻ�ò���ʵ����</T>
//
// @param pName ����
// @return ����ʵ��
//============================================================
TResult FAnimation3dThread::Register(FAnimation3d* pAnimation){
   _locker.Enter();
   _pLooper->Push(pAnimation);
   _locker.Leave();
   return ESuccess;
}

//============================================================
// <T>�������ƻ�ò���ʵ����</T>
//
// @param pName ����
// @return ����ʵ��
//============================================================
TResult FAnimation3dThread::Unregister(FAnimation3d* pAnimation){
   _locker.Enter();
   _pLooper->Remove(pAnimation);
   _locker.Leave();
   return ESuccess;
}

//============================================================
// <T>�߼�����</T>
//
// @return ������
//============================================================
TResult FAnimation3dThread::Process(){
   // MO_INFO("Process looper limit. (limit=%d, count=%d)", _looperLimit, _pLooper->Count());
   while(!IsStop()){
      // ִ�д���
      _locker.Enter();
      _pLooper->Record();
      for(TInt n = 0; n < _looperLimit; n++){
         FAnimation3d* pAnimation = _pLooper->Next();
         if(pAnimation == NULL){
            break;
         }
         if(!IsStop()){
            pAnimation->Process();
         }
      }
      _locker.Leave();
      // ��Ϣ����
      SleepMicro(10);
   }
   return ESuccess;
}

//============================================================
// <T>��մ���</T>
//
// @return ������
//============================================================
TResult FAnimation3dThread::Clear(){
   _locker.Enter();
   _pLooper->Clear();
   _locker.Leave();
   return ESuccess;
}

MO_NAMESPACE_END
