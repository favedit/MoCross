#include "MoEfDisplay.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>��������ߡ�</T>
//============================================================
SUiPicture::SUiPicture(){
   resourceId = 0;
   alignCd = EControlImageAlign_None;
}

//============================================================
// <T>�������������л��������ݡ�</T>
//
// @param pInput ������
// @return ������
//============================================================
TResult SUiPicture::Unserialize(IDataInput* pInput){
   resourceId = pInput->ReadInt32();
   alignCd = (EControlImageAlign)pInput->ReadInt8();
   location.Unserialize16(pInput);
   size.Unserialize16(pInput);
   padding.Unserialize16(pInput);
   return ESuccess;
}

MO_NAMESPACE_END
