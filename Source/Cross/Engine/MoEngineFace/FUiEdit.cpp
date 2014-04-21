#include "MoFmControl.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>����༭�ؼ���</T>
//============================================================
FUiEdit::FUiEdit(){
   _controlCd = EControlType_Edit;
   _textAlignCd = EControlTextAlign_None;
}

//============================================================
// <T>�����༭�ؼ���</T>
//============================================================
FUiEdit::~FUiEdit(){
}

//============================================================
// <T>�����ı����뷽ʽ��</T>
//
// @param textAlignCd �ı����뷽ʽ
// @return ������
//============================================================
TResult FUiEdit::SetTextAlignCd(EControlTextAlign textAlignCd){
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
TResult FUiEdit::SetText(TWideCharC* pText){
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
TResult FUiEdit::OnUnserialize(IDataInput* pInput){
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
TResult FUiEdit::OnPaint(){
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
   // ��������
   if(!_text.IsEmpty()){
      SFontInfo fontInfo;
      fontInfo.color = _font.color;
      FFont* pDefaultFont = RFontManager::Instance().DefaultFont();
      pDefaultFont->CalculateWideSize(&fontInfo, (TWideCharC*)_text);
      TInt top = (rectangle.height - fontInfo.height) >> 1;
      SIntRectangle textRectangle(rectangle.left, rectangle.top + top, rectangle.width, rectangle.height - top);
      //pDefaultFont->DrawWideText(pCanvas, &textRectangle, &fontInfo, (TWideCharC*)_text);
   }
   // ��������
   pCanvas->Update();
   return result;
}

MO_NAMESPACE_END
