#include "MoFrContent3dScene.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FRs3dScenePass, FInstance);

//============================================================
// <T>���쳡���������̡�</T>
//============================================================
FRs3dScenePass::FRs3dScenePass(){
}

//============================================================
// <T>���������������̡�</T>
//============================================================
FRs3dScenePass::~FRs3dScenePass(){
}

//============================================================
// <T>���������ﷴ���л���Ϣ����</T>
//
// @param pInput ������
// @return ������
//============================================================
TResult FRs3dScenePass::Unserialize(IDataInput* pInput){
   _name.UnserializeAutomatic(pInput);
   _renderTargetSize.Unserialize(pInput);
   return ESuccess;
}

MO_NAMESPACE_END
