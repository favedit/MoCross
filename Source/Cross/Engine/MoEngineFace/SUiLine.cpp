#include "MoFmCore.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>��������ߡ�</T>
//============================================================
SUiLine::SUiLine(){
   color = 0;
   width = 0;
   styleCd = EUiLineStyle_Solid;
}

//============================================================
// <T>�������������л��������ݡ�</T>
//
// @param pInput ������
// @return ������
//============================================================
TResult SUiLine::Unserialize(IDataInput* pInput){
   color = pInput->ReadInt32();
   width = pInput->ReadInt8();
   styleCd = (EUiLineStyle)pInput->ReadInt8();
   return ESuccess;
}

MO_NAMESPACE_END
