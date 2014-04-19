#include "MoFrContent3dScene.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FRs3dSceneMaterial, FInstance);

//============================================================
// <T>���쳡��������Դ��</T>
//============================================================
FRs3dSceneMaterial::FRs3dSceneMaterial(){
}

//============================================================
// <T>��������������Դ��</T>
//============================================================
FRs3dSceneMaterial::~FRs3dSceneMaterial(){
}

//============================================================
// <T>���������ﷴ���л���Ϣ����</T>
//
// @param pInput ������
// @return ������
//============================================================
TResult FRs3dSceneMaterial::Unserialize(IDataInput* pInput){
   // ��ȡ����
   _name.UnserializeAutomatic(pInput);
   _label.UnserializeAutomatic(pInput);
   // ��ȡ����
   _info.Unserialize(pInput);
   // ��ȡ�߶�
   TFloat depth = pInput->ReadFloat();
   SetHeightDepth(depth);
   // ��ȡ����
   _surfaceRate = pInput->ReadFloat();
   _surfaceReflect = pInput->ReadFloat();
   _surfaceBright = pInput->ReadFloat();
   _surfaceBrightLevel = pInput->ReadFloat();
   _surfaceCoarse = pInput->ReadFloat();
   _surfaceCoarseLevel = pInput->ReadFloat();
   _surfaceMerge = pInput->ReadFloat();
   _surfacePower = pInput->ReadFloat();
   return ESuccess;
}

MO_NAMESPACE_END
