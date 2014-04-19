#include "MoFrContent3dScene.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FRs3dSceneLight, FInstance);

//============================================================
// <T>���쳡����Դ��Դ��</T>
//============================================================
FRs3dSceneLight::FRs3dSceneLight(){
   _optionTrack = EFalse;
   _shadowAmbientMin = 0.0f;
   _shadowAmbientMax = 0.0f;
   _shadowAmbientThick = 0.0f;
   _shadowAmbientRange = 0.0f;
   _shadowMerge1Base = 0.0f;
   _shadowMerge1Rate = 0.0f;
   _shadowMerge2Base = 0.0f;
   _shadowMerge2Rate = 0.0f;
   _material = FRs3dSceneMaterial::InstanceCreate();
   _camera = FRs3dSceneCamera::InstanceCreate();
}

//============================================================
// <T>����������Դ��Դ��</T>
//============================================================
FRs3dSceneLight::~FRs3dSceneLight(){
}

//============================================================
// <T>���������ﷴ���л���Ϣ����</T>
//
// @param pInput ������
// @return ������
//============================================================
TResult FRs3dSceneLight::Unserialize(IDataInput* pInput){
   // ��ȡ����
   _typeName.UnserializeAutomatic(pInput);
   // ��ȡ����
   _optionTrack = RGeomFlag::ToBoolean(pInput->ReadInt32());
   // ��ȡ��Ӱ
   _shadow1.Unserialize(pInput);
   _shadow2.Unserialize(pInput);
   _shadow3.Unserialize(pInput);
   // ��ȡ��Ӱ����
   _shadowAmbientMin = pInput->ReadFloat();
   _shadowAmbientMax = pInput->ReadFloat();
   _shadowAmbientThick = pInput->ReadFloat();
   _shadowAmbientRange = pInput->ReadFloat();
   _shadowMerge1Base = pInput->ReadFloat();
   _shadowMerge1Rate = pInput->ReadFloat();
   _shadowMerge2Base = pInput->ReadFloat();
   _shadowMerge2Rate = pInput->ReadFloat();
   // ��ȡ����
   _material->Unserialize(pInput);
   // ��ȡ���
   _camera->Unserialize(pInput);
   return ESuccess;
}

MO_NAMESPACE_END
