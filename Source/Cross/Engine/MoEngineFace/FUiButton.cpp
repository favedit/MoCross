#include "MoEfControl.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>����ؼ�����</T>
//============================================================
FUiButton::FUiButton(){
   _controlCd = EControlType_Button;
   _optionHand = EFalse;
   _statusDown = EFalse;
   _statusHover = EFalse;
   _validInterval = 0;
   _textAlignCd = EControlTextAlign_None;
}

//============================================================
// <T>�����ؼ�����</T>
//============================================================
FUiButton::~FUiButton(){
}

//============================================================
// <T>�����ı����뷽ʽ��</T>
//
// @param textAlignCd �ı����뷽ʽ
// @return ������
//============================================================
TResult FUiButton::SetTextAlignCd(EControlTextAlign textAlignCd){
   // �������
   if(_textAlignCd == textAlignCd){
      return ESuccess;
   }
   // ��������
   _textAlignCd = textAlignCd;
   return Dirty();
}

//============================================================
// <T>�����ı����ݡ�</T>
//
// @param pText �ı�����
// @return ������
//============================================================
TResult FUiButton::SetText(TWideCharC* pText){
   // �������
   if(_text.Equals(pText)){
      return ESuccess;
   }
   // ��������
   _text = pText;
   return Dirty();
}

//============================================================
// <T>�������������л��������ݡ�</T>
//
// @param pInput ������
// @return ������
//============================================================
TResult FUiButton::OnUnserialize(IDataInput* pInput){
   // ����Ϣ�����л�
   TResult result = FUiControl::OnUnserialize(pInput);
   // ��ȡ����
   _optionHand = pInput->ReadBool();
   _font.Unserialize(pInput);
   _text.UnserializeAutomatic(pInput);
   _validInterval = pInput->ReadUint16();
   // ��ȡ����
   if(TestFlag(EControlFlag_LayerGround)){
      _groundPicture.Unserialize(pInput);
   }
   // ��ȡ�ȵ���Ϣ
   _borderHoverOuter.Unserialize(pInput);
   _borderHoverInner.Unserialize(pInput);
   _backHoverColor = pInput->ReadInt32();
   // ��ȡѡ����Ϣ
   _borderSelectOuter.Unserialize(pInput);
   _borderSelectInner.Unserialize(pInput);
   _backSelectColor = pInput->ReadInt32();
   // ��õ���ؼ�
   _onClickControl.Unserialize(pInput);
   return result;
}

//============================================================
// <T>���ƴ���</T>
//
// @return ������
//============================================================
TResult FUiButton::OnPaint(){
   TResult result = FUiControl::OnPaint();
   //// ���ƴ���
   //FUiCanvas* pCanvas = Canvas();
   //// ��������
   //SIntRectangle rectangle;
   //CalculateClientRectangle(&rectangle);
   //pCanvas->ClientRectangle().Assign(rectangle);
   //pCanvas->ClipRectangle().Assign(rectangle);
   //// ��ձ���
   //if(_statusDown){
   //   pCanvas->Clear(_backSelectColor, &rectangle);
   //}else if(_statusHover){
   //   pCanvas->Clear(_backHoverColor, &rectangle);
   //}else{
   //   pCanvas->Clear(_backColor, &rectangle);
   //}
   //// ���Ƶ�ͼ
   //if(_groundPicture.IsValid()){
   //   FPictureResource* pPictureResource = (FPictureResource*)RResourceManager::Instance().Find(_groundPicture.resourceId);
   //   //pCanvas->DrawBitmap(pPictureResource->Bitmap(), ETrue, 0, 0);
   //   //TInt right = pPictureResource->Size().width;
   //   //TInt bottom = pPictureResource->Size().height;
   //   //SIntRectangle sourceRectangle(0, 0, right, bottom);
   //   //SIntRectangle targetRectangle(0, 0, (TInt)Size().width, (TInt)Size().height);
   //   //pCanvas->DrawBitmap(pPictureResource->Bitmap(),ETrue,&sourceRectangle,&targetRectangle);
   //}
   ////............................................................
   //if(_statusDown){
   //   // ������߿�
   //   if(!_borderSelectOuter.IsEmpty()){
   //      pCanvas->DrawBorder(&rectangle, &_borderSelectOuter);
   //      rectangle.Shrink(_borderSelectOuter.left.width, _borderSelectOuter.top.width, _borderSelectOuter.right.width, _borderSelectOuter.bottom.width);
   //   }
   //   // �����ڱ߿�
   //   if(!_borderHoverInner.IsEmpty()){
   //      pCanvas->DrawBorder(&rectangle, &_borderHoverInner);
   //      rectangle.Shrink(_borderHoverInner.left.width, _borderHoverInner.top.width, _borderHoverInner.right.width, _borderHoverInner.bottom.width);
   //   }
   //}else if(_statusHover){
   //   // ������߿�
   //   if(!_borderHoverOuter.IsEmpty()){
   //      pCanvas->DrawBorder(&rectangle, &_borderHoverOuter);
   //      rectangle.Shrink(_borderHoverOuter.left.width, _borderHoverOuter.top.width, _borderHoverOuter.right.width, _borderHoverOuter.bottom.width);
   //   }
   //   // �����ڱ߿�
   //   if(!_borderHoverInner.IsEmpty()){
   //      pCanvas->DrawBorder(&rectangle, &_borderHoverInner);
   //      rectangle.Shrink(_borderHoverInner.left.width, _borderHoverInner.top.width, _borderHoverInner.right.width, _borderHoverInner.bottom.width);
   //   }
   //}else{
   //   // ������߿�
   //   if(!_borderOuter.IsEmpty()){
   //      pCanvas->DrawBorder(&rectangle, &_borderOuter);
   //      rectangle.Shrink(_borderOuter.left.width, _borderOuter.top.width, _borderOuter.right.width, _borderOuter.bottom.width);
   //   }
   //   // �����ڱ߿�
   //   if(!_borderInner.IsEmpty()){
   //      pCanvas->DrawBorder(&rectangle, &_borderInner);
   //      rectangle.Shrink(_borderInner.left.width, _borderInner.top.width, _borderInner.right.width, _borderInner.bottom.width);
   //   }
   //}
   ////............................................................
   //// ��������
   //if(!_text.IsEmpty()){
   //   SFontInfo fontInfo;
   //   fontInfo.color = _font.color;
   //   FFont* pDefaultFont = RFontManager::Instance().DefaultFont();
   //   pDefaultFont->CalculateWideSize(&fontInfo, (TWideCharC*)_text);
   //   TInt left = (rectangle.width - fontInfo.width) >> 1;
   //   TInt top = (rectangle.height - fontInfo.height) >> 1;
   //   SIntRectangle textRectangle(rectangle.left + left, rectangle.top + top, rectangle.width - left, rectangle.height - top);
   //   //pDefaultFont->DrawWideText(pCanvas, &textRectangle, &fontInfo, (TWideCharC*)_text);
   //}
   //// ��������
   //pCanvas->Update();
   return result;
}

//============================================================
// <T>������´���</T>
//
// @param pEvent ����¼�
// @return ������
//============================================================
TResult FUiButton::MouseDown(SMouseEvent* pEvent){
   _statusDown = ETrue;
   // �ַ��¼�
   SMouseEvent event(this, pEvent->buttons, pEvent->position.x, pEvent->position.y);
   _listenersClick.Process(&event);
   return Dirty();
}

//============================================================
// <T>����ƶ�����</T>
//
// @param pEvent ����¼�
// @return ������
//============================================================
TResult FUiButton::MouseMove(SMouseEvent* pEvent){
   return ESuccess;
}

//============================================================
// <T>���̧����</T>
//
// @param pEvent ����¼�
// @return ������
//============================================================
TResult FUiButton::MouseUp(SMouseEvent* pEvent){
   _statusDown = EFalse;
   return Dirty();
}

//============================================================
// <T>�ȵ���봦��</T>
//
// @return ������
//============================================================
TResult FUiButton::HoverEnter(){
   _statusHover = ETrue;
   Dirty();
   return ESuccess;
}

//============================================================
// <T>�ȵ��뿪����</T>
//
// @return ������
//============================================================
TResult FUiButton::HoverLeave(){
   _statusHover = EFalse;
   _statusDown = EFalse;
   Dirty();
   return ESuccess;
}

MO_NAMESPACE_END
