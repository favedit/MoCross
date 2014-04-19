#include "MoEgFont.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FFontConsole, FConsole);

//============================================================
// <T>�������塣</T>
//============================================================
FFontConsole::FFontConsole(){
   _statusOpen = EFalse;
   MO_CLEAR(_pDefaultFont);
   _pFonts = MO_CREATE(FFontCollection);
}

//============================================================
// <T>�������塣</T>
//============================================================
FFontConsole::~FFontConsole(){
   MO_DELETE(_pFonts);
}

//============================================================
// <T>���ݴ��������塣</T>
//
// @param code ����
// @return ����
//============================================================
FFont* FFontConsole::FindFontByCode(TInt code){
   TInt count = _pFonts->Count();
   for(TInt n = 0; n < count; n++){
      FFont* pFont = _pFonts->Get(n);
      if(pFont->Code() == code){
         return pFont;
      }
   }
   return NULL;
}

//============================================================
// <T>�������ƻ�����塣</T>
//
// @param pName ����
// @return ����
//============================================================
FFont* FFontConsole::FindFontByName(TCharC* pName){
   TInt count = _pFonts->Count();
   for(TInt n = 0; n < count; n++){
      FFont* pFont = _pFonts->Get(n);
      if(RString::Equals(pFont->Name(), pName)){
         return pFont;
      }
   }
   return NULL;
}

//============================================================
// <T>ע��һ�����塣</T>
//
// @param pFont ����
//============================================================
void FFontConsole::RegisterFont(FFont* pFont){
   MO_ASSERT(pFont);
   // ������
   pFont->SetConsole(this);
   if(!pFont->IsStatusOpen()){
      pFont->Open();
   }
   // ���뻺��
   _pFonts->Push(pFont);
   // ע��ĵ�һ������ΪĬ������
   if(_pDefaultFont == NULL){
      _pDefaultFont = pFont;
   }
}

//============================================================
// <T>ע��һ�����塣</T>
//
// @param pFont ����
//============================================================
void FFontConsole::UnregisterFont(FFont* pFont){
   MO_ASSERT(pFont);
   _pFonts->Remove(pFont);
}

//============================================================
// <T>�򿪴���</T>
//============================================================
void FFontConsole::Open(){
   _statusOpen = ETrue;
}

//============================================================
// <T>�رմ���</T>
//============================================================
void FFontConsole::Close(){
   _statusOpen = EFalse;
}

MO_NAMESPACE_END
