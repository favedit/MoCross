#include "MoFrContent3dScene.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FRs3dSceneRegion, FInstance);

//============================================================
// <T>���쳡��������Դ��</T>
//============================================================
FRs3dSceneRegion::FRs3dSceneRegion(){
   _camera = FRs3dSceneCamera::InstanceCreate();
   _light = FRs3dSceneLight::InstanceCreate();
}

//============================================================
// <T>��������������Դ��</T>
//============================================================
FRs3dSceneRegion::~FRs3dSceneRegion(){
}

//============================================================
// <T>���������ﷴ���л���Ϣ����</T>
//
// @param pInput ������
// @return ������
//============================================================
TResult FRs3dSceneRegion::Unserialize(IDataInput* pInput){
   // ��ȡ��ɫ
   _color.Unserialize(pInput);
   // ��ȡ��ɫ����
   _colorLevel.Unserialize(pInput);
   // ��ȡ��
   _fog.Unserialize(pInput);
   // ��ȡ�߽�
   _edge.Unserialize(pInput);
   // ��ȡƽ��
   _face.Unserialize(pInput);
   // ��ȡ���
   _camera->Unserialize(pInput);
   // ��ȡ��Դ
   _light->Unserialize(pInput);
   return ESuccess;
}

MO_NAMESPACE_END
