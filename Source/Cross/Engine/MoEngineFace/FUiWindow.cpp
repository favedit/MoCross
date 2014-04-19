#include "MoFmFrame.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>���춥�㴰�ڡ�</T>
//============================================================
FUiWindow::FUiWindow(){
   _objectCd |= EComponent_Mouseable;
   _controlCd = EControlType_Window;
   _titleHeight = 28;
}

//============================================================
// <T>�������㴰�ڡ�</T>
//============================================================
FUiWindow::~FUiWindow(){
}

//============================================================
// <T>ת�����͡�</T>
//
// @param componentCd ����
// @return ����
//============================================================
TAny* FUiWindow::Convert(EComponent componentCd){
   // ��ת������
   TAny* pResult = FUiControl::Convert(componentCd);
   if(pResult != NULL){
      return pResult;
   }
   // ת������
   if(componentCd == EComponent_Mouseable){
      return (IMouseable*)this;
   }
   return pResult;
}

//============================================================
// <T>���ƴ���</T>
//
// @return ������
//============================================================
TResult FUiWindow::OnPaint(){
   TResult result = FUiControl::OnPaint();
   // ���ƴ���
   FUiCanvas* pCanvas = Canvas();
   // ��������
   SIntRectangle rectangle;
   CalculateClientRectangle(&rectangle);
   pCanvas->ClientRectangle().Assign(rectangle);
   pCanvas->ClipRectangle().Assign(rectangle);
   // ��ձ���
   pCanvas->Clear(_backColor, &rectangle);
   // ������߿�
   if(!_borderOuter.IsEmpty()){
      pCanvas->DrawBorder(&rectangle, &_borderOuter);
      rectangle.Shrink(_borderOuter.left.width, _borderOuter.top.width, _borderOuter.right.width, _borderOuter.bottom.width);
   }
   // �����ڱ߿�
   if(!_borderInner.IsEmpty()){
      pCanvas->DrawBorder(&rectangle, &_borderInner);
      rectangle.Shrink(_borderInner.left.width, _borderInner.top.width, _borderInner.right.width, _borderInner.bottom.width);
   }
   SIntRectangle titleRectangle(rectangle.left, rectangle.top, rectangle.width, _titleHeight);
   PaintTitle(pCanvas, &titleRectangle);
   SIntRectangle bodyRectangle(rectangle.left, rectangle.top + _titleHeight, rectangle.width, rectangle.height - _titleHeight);
   PaintBody(pCanvas, &bodyRectangle);
   // ��������
   pCanvas->Update();
   return result;
}

//============================================================
TResult FUiWindow::PaintTitle(FUiCanvas* pCanvas, SIntRectangle* pRectangle){
   pCanvas->FillRectangle(0xFF999900, pRectangle->left + 2, pRectangle->top + 2, pRectangle->Right() - 2, pRectangle->Bottom() - 2);
   // ��������
   if(!_label.IsEmpty()){
      SFontInfo fontInfo;
      fontInfo.color = 0xFFFFFFFF;
      FFont* pDefaultFont = RFontManager::Instance().DefaultFont();
      pDefaultFont->CalculateWideSize(&fontInfo, (TWideCharC*)_label);
      TInt left = (pRectangle->width - fontInfo.width) >> 1;
      TInt top = (pRectangle->height - fontInfo.height) >> 1;
      SIntRectangle textRectangle(pRectangle->left + left, pRectangle->top + top, pRectangle->width - left, pRectangle->height - top);
      //pDefaultFont->DrawWideText(pCanvas, &textRectangle, &fontInfo, (TWideCharC*)_label);
   }
   return ESuccess;
}

//============================================================
TResult FUiWindow::PaintBody(FUiCanvas* pCanvas, SIntRectangle* pRectangle){
   return ESuccess;
}

//============================================================
TResult FUiWindow::MouseDown(SMouseEvent* pEvent){
   TInt cx = pEvent->position.x - _statusRectangle.left;
   TInt cy = pEvent->position.y - _statusRectangle.top;
   if(cy < _titleHeight){
      RFocusManager::Instance().DragDrawable(this, cx, cy);
   }
   return ESuccess;
}

//============================================================
TResult FUiWindow::MouseMove(SMouseEvent* pEvent){
   return ESuccess;
}

//============================================================
TResult FUiWindow::MouseUp(SMouseEvent* pEvent){
   return ESuccess;
}

//============================================================
TResult FUiWindow::DragBegin(){
   return ESuccess;
}

//============================================================
TResult FUiWindow::DragMove(){
   return ESuccess;
}

//============================================================
TResult FUiWindow::DragEnd(){
   return ESuccess;
}

MO_NAMESPACE_END
