#include "MoFrContent3dScene.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FRs3dSceneViewport, FInstance);

//============================================================
// <T>���쳡���ӽ���Դ��</T>
//============================================================
FRs3dSceneViewport::FRs3dSceneViewport(){
   _angle = 0.0f;
   _near = 0.0f;
   _far = 0.0f;
}

//============================================================
// <T>���������ӽ���Դ��</T>
//============================================================
FRs3dSceneViewport::~FRs3dSceneViewport(){
}

//============================================================
// <T>���������ﷴ���л���Ϣ����</T>
//
// @param pInput ������
// @return ������
//============================================================
TResult FRs3dSceneViewport::Unserialize(IDataInput* pInput){
   _angle = pInput->ReadFloat();
   _near = pInput->ReadFloat();
   _far = pInput->ReadFloat() * 2.0f;
   return ESuccess;
}

MO_NAMESPACE_END
