#include "MoFmControl.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>�����ǩ�ؼ���</T>
//============================================================
FUiLabel::FUiLabel(){
   _controlCd = EControlType_Label;
   _textAlignCd = EControlTextAlign_None;
}

//============================================================
// <T>������ǩ�ؼ���</T>
//============================================================
FUiLabel::~FUiLabel(){
}

//============================================================
// <T>�����ı����뷽ʽ��</T>
//
// @param textAlignCd �ı����뷽ʽ
// @return ������
//============================================================
TResult FUiLabel::SetTextAlignCd(EControlTextAlign textAlignCd){
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
TResult FUiLabel::SetText(TWideCharC* pText){
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
TResult FUiLabel::OnUnserialize(IDataInput* pInput){
   // ����Ϣ�����л�
   TResult result = FUiControl::OnUnserialize(pInput);
   // ��ȡ����
   _font.Unserialize(pInput);
   _textAlignCd = (EControlTextAlign)pInput->ReadUint8();
   _text.UnserializeAutomatic(pInput);
   return result;
}

//============================================================
// <T>���ƴ���</T>
//
// @return ������
//============================================================
TResult FUiLabel::OnPaint(){
   // ���ƴ���
   FBitmapCanvas* pCanvas = Canvas();
   // ��������
   SIntRectangle rectangle;
   CalculateClientRectangle(&rectangle);
   pCanvas->ClientRectangle().Assign(rectangle);
   pCanvas->ClipRectangle().Assign(rectangle);
   // ��ձ���
   pCanvas->Clear(_backColor);
   // ��������
   if(!_text.IsEmpty()){
      SFontInfo fontInfo;
      _font.SaveInfo(fontInfo);
      FFont* pDefaultFont = RFontManager::Instance().DefaultFont();
      pDefaultFont->CalculateWideSize(&fontInfo, (TWideCharC*)_text);
      TInt top = (rectangle.height - fontInfo.height) >> 1;
      SIntRectangle textRectangle(rectangle.left, rectangle.top + top, rectangle.width, rectangle.height - top);
      //pDefaultFont->DrawWideText(pCanvas, &textRectangle, &fontInfo, (TWideCharC*)_text);
   }
   // ��������
   pCanvas->Update();
   return ESuccess;
}

MO_NAMESPACE_END
