#include "MoFrContent3dScene.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FRs3dSceneMovie, FInstance);

//============================================================
// <T>������Դ����������</T>
//============================================================
FRs3dSceneMovie::FRs3dSceneMovie(){
   _interval = 0;
}

//============================================================
// <T>������Դ����������</T>
//============================================================
FRs3dSceneMovie::~FRs3dSceneMovie(){
}

//============================================================
// <T>���������ﷴ���л���Ϣ����</T>
//
// @param pInput ������
// @return ������
//============================================================
TResult FRs3dSceneMovie::Unserialize(IDataInput* pInput){
   _typeName.UnserializeAutomatic(pInput);
   _interval = pInput->ReadInt32();
   _rotation.Unserialize(pInput);
   return ESuccess;
}

MO_NAMESPACE_END
