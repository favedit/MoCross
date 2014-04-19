#include "MoFmCore.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>���춥��������</T>
//============================================================
FUiFrame::FUiFrame(){
   _code = 0;
   _objectCd |= EComponent_Renderable;
}

//============================================================
// <T>��������������</T>
//============================================================
FUiFrame::~FUiFrame(){
}

//============================================================
// <T>�������������л��������ݡ�</T>
//
// @param pInput ������
//============================================================
TResult FUiFrame::OnUnserialize(IDataInput* pInput){
   FUiControlContainer::OnUnserialize(pInput);
   _code = pInput->ReadInt32();
   _statusVisible = EFalse;
   _statusDirty = ETrue;
   return ESuccess;
}

//============================================================
// <T>���ƴ���</T>
//
// @return ������
//============================================================
TResult FUiFrame::OnPaint(){
   TResult result = FUiControlContainer::OnPaint();
   // ���ƴ���
   FBitmapCanvas* pCanvas = Canvas();
   FFont* pDefaultFont = RFontManager::Instance().DefaultFont();
   pCanvas->Clear(_backColor);
   pCanvas->Update();
   return result;
}

//============================================================
// <T>��ʾ����</T>
//
// @return ������
//============================================================
TResult FUiFrame::OnShow(){
   return ESuccess;
}

//============================================================
// <T>���ش���</T>
//
// @return ������
//============================================================
TResult FUiFrame::OnHide(){
   return ESuccess;
}

//============================================================
// <T>��ʾ����</T>
//
// @return ������
//============================================================
TResult FUiFrame::Show(){
   // ���״̬
   if(_statusVisible){
      return ESuccess;
   }
   // �����̨
   FStage* pStage = RStageManager::Instance().ActiveStage();
   if(pStage == NULL){
      return EFailure;
   }
   // ��ý�����̨
   //FDisplayLayer* pLayer = pStage->LayerFind(EDisplayLayer_Frame);
   //if(pLayer == NULL){
   //   return EFailure;
   //}
   //// ����λ��
   //SIntPoint2 location;
   //SIntSize2 size((TInt)_size.width, (TInt)_size.height);
   //SIntRectangle& screenRectangle = RDeviceManager::Instance().ScreenDevice()->Rectangle();
   //TResult result = RUiUtil::CalculateDock(&location, &screenRectangle, &size, _dockCd, &_dockPadding);
   //if(result == ESuccess){
   //   SetLocationInt2(location.x, location.y);
   //}
   // ��ʾ����
   //OnShow();
   // ������ʾ����
   //pLayer->DisplayPush(this);
   _statusVisible = ETrue;
   //return result;
   return ESuccess;
}

//============================================================
// <T>���ش���</T>
//
// @return ������
//============================================================
TResult FUiFrame::Hide(){
   // ���״̬
   if(!_statusVisible){
      return ESuccess;
   }
   // �����̨
   FStage* pStage = RStageManager::Instance().ActiveStage();
   if(pStage == NULL){
      return EFailure;
   }
   // ��ý�����̨
   //FDisplayLayer* pLayer = pStage->LayerFind(EDisplayLayer_Frame);
   //if(pLayer == NULL){
   //   return EFailure;
   //}
   //// ���ش���
   //OnHide();
   // ����ʾ�����Ƴ�
   //pLayer->ChildRemove(this);
   _statusVisible = EFalse;
   return ESuccess;
}

MO_NAMESPACE_END
