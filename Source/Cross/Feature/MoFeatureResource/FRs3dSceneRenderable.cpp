#include "MoFrContent3dScene.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FRs3dSceneRenderable, FInstance);

//============================================================
// <T>���쳡����Ⱦ��Դ��</T>
//============================================================
FRs3dSceneRenderable::FRs3dSceneRenderable(){
}

//============================================================
// <T>����������Ⱦ��Դ��</T>
//============================================================
FRs3dSceneRenderable::~FRs3dSceneRenderable(){
}

//============================================================
// <T>���������ﷴ���л���Ϣ����</T>
//
// @param pInput ������
// @return ������
//============================================================
TResult FRs3dSceneRenderable::Unserialize(IDataInput* pInput){
   _name.UnserializeAutomatic(pInput);
   return ESuccess;
}

MO_NAMESPACE_END
