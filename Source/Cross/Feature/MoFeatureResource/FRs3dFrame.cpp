#include "MoFrContent3dModel.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FRs3dFrame, FInstance);

//============================================================
// <T>������Դ3D֡��</T>
//============================================================
FRs3dFrame::FRs3dFrame(){
   _index = 0;
   _tick = 0;
   _alpha = 1.0f;
}

//============================================================
// <T>������Դ3D֡��</T>
//============================================================
FRs3dFrame::~FRs3dFrame(){
}

//============================================================
// <T>���������ﷴ���л���Ϣ����</T>
//
// @param pInput ������
// @return ������
//============================================================
TResult FRs3dFrame::Unserialize(IDataInput* pInput){
   MO_CHECK(pInput, return ENull);
   _tick = pInput->ReadUint16();
   _matrix.Unserialize(pInput);
   return ESuccess;
}

MO_NAMESPACE_END
