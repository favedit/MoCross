#include "MoEfDisplay.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>����ؼ��������̨��</T>
//============================================================
FUiFrameConsole::FUiFrameConsole(){
   _pPools = MO_CREATE(FUiControlPoolCollection);
   _pFrames = MO_CREATE(FUiFrameSet);
}

//============================================================
// <T>������ʾ�������̨��</T>
//============================================================
FUiFrameConsole::~FUiFrameConsole(){
   MO_DELETE(_pPools);
   MO_DELETE(_pFrames);
}

//============================================================
// <T>���ô���</T>
//============================================================
TResult FUiFrameConsole::Setup(){
   //// ע�ᾫ�黺���
   //FSpritePool* pSpritePool = MO_CREATE(FSpritePool);
   //PoolRegister(pSpritePool);
   return ESuccess;
}

//============================================================
// <T>���ô���</T>
//
// @return ������
//============================================================
TResult FUiFrameConsole::Open(){
   // ��������
   FAssetStream* pStream = RAssetManager::Instance().OpenAssetStreamFormat("/db/frame.db");
   MO_ERROR_CHECK(pStream, return EFailure, "Open theme failure.");
   // ��֡����
   TFsName className;
   TInt count = pStream->ReadInt32();
   for(TInt n = 0; n < count; n++){
      EControlType controlCd = (EControlType)pStream->ReadInt16();
      className.Unserialize(pStream);
      FUiFrame* pFrame = (FUiFrame*)RFaceManager::Instance().ControlConsole()->Alloc(controlCd, (TCharC*)className);
      pFrame->Unserialize(pStream);
      _pFrames->Set(pFrame->Code(), pFrame);
   }
   RAssetManager::Instance().CloseAssetStream(pStream);
   return ESuccess;
}

//============================================================
// <T>���ݱ�Ų���һ��ҳ�档</T>
//
// @return ҳ��
//============================================================
FUiFrame* FUiFrameConsole::Find(TControlId frameId){
   FUiFrame* pFrame = _pFrames->Find(frameId);
   if(pFrame != NULL){
      pFrame->Setup();
   }
   return pFrame;
}

//============================================================
// <T>�ͷŴ���</T>
//
// @return ������
//============================================================
TResult FUiFrameConsole::Dispose(){
   return ESuccess;
}

MO_NAMESPACE_END
