#include "MoEfDisplay.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>���콻�������塣</T>
//============================================================
SUiFont::SUiFont(){
   color = 0xFF000000;
   size = 9;
   fix = EFalse;
   bold = EFalse;
   italic = EFalse;
   strikeout = EFalse;
   underline = EFalse;
}

//============================================================
// <T>�������������л��������ݡ�</T>
//
// @param pInput ������
// @return ������
//============================================================
TResult SUiFont::Unserialize(IDataInput* pInput){
   fontName.Unserialize(pInput);
   color = pInput->ReadInt32();
   size = pInput->ReadUint8();
   bold = pInput->ReadBool();
   italic = pInput->ReadBool();
   strikeout = pInput->ReadBool();
   underline = pInput->ReadBool();
   return ESuccess;
}

//============================================================
// <T>������Ϣ��</T>
//
// @param info ��Ϣ
//============================================================
void SUiFont::SaveInfo(SFontInfo& info){
   info.fontNamePtr = fontName;
   info.color = color;
   info.size = size;
   info.fix = fix;
   info.bold = bold;
   info.italic = italic;
   info.underline = underline;
   info.strikeout = strikeout;
}

MO_NAMESPACE_END
