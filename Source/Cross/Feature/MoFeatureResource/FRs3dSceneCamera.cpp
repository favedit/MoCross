#include "MoFrContent3dScene.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FRs3dSceneCamera, FInstance);

//============================================================
// <T>���쳡�������Դ��</T>
//============================================================
FRs3dSceneCamera::FRs3dSceneCamera(){
   _centerFront = 0.0f;
   _centerBack = 0.0f;
   _focalNear = 0.0f;
   _focalFar = 0.0f;
   _viewport = FRs3dSceneViewport::InstanceCreate();
}

//============================================================
// <T>�������������Դ��</T>
//============================================================
FRs3dSceneCamera::~FRs3dSceneCamera(){
}

//============================================================
// <T>���������ﷴ���л���Ϣ����</T>
//
// @param pInput ������
// @return ������
//============================================================
TResult FRs3dSceneCamera::Unserialize(IDataInput* pInput){
   // ��ȡ����
   _typeName.UnserializeAutomatic(pInput);
   // ��ȡ����
   _centerFront = pInput->ReadFloat();
   _centerBack = pInput->ReadFloat();
   // ��ȡλ��
   _position.Unserialize(pInput);
   // ��ȡ����
   _direction.Unserialize(pInput);
   // ��ȡ��ƽ��
   _focalNear = pInput->ReadFloat();
   _focalFar = pInput->ReadFloat();
   // ��ȡ�ӽ�
   _viewport->Unserialize(pInput);
   return ESuccess;
}

MO_NAMESPACE_END
