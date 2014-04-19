#include "MoE3Scene.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FScene3dMaterial, FMaterial);

//============================================================
// <T>���쳡��3D���ʡ�</T>
//============================================================
FScene3dMaterial::FScene3dMaterial(){
}

//============================================================
// <T>��������3D���ʡ�</T>
//============================================================
FScene3dMaterial::~FScene3dMaterial(){
}

//============================================================
// <T>������ʾ��Դ��</T>
//
// @param pResource ��Դ����
// @return ������
//============================================================
TResult FScene3dMaterial::LoadSceneResource(FRs3dSceneMaterial* pResource){
   MO_CHECK(pResource, return ENull);
   SMaterialInfo& info = pResource->Info();
   _name = pResource->Name();
   // ��������
   _optionMerge = info.optionMerge;
   _optionSort = info.optionSort;
   _sortLevel = info.sortLevel;
   _optionAlpha = info.optionAlpha;
   _optionDepth = info.optionDepth;
   _optionCompare = (TCharC*)info.optionCompare;
   _optionDouble = info.optionDouble;
   _optionShadow = info.optionShadow;
   _optionShadowSelf = info.optionShadowSelf;
   // ������ɫ
   _color.Set(info.colorMin, info.colorMax, info.colorRate, info.colorMerge);
   // ����͸��
   _alpha.Set(info.alphaBase, info.alphaRate, info.alphaLevel, info.alphaMerge);
   // ���ò���
   _ambientColor.Assign(info.ambientColor);
   _ambientShadow = info.ambientShadow;
   _diffuseColor.Assign(info.diffuseColor);
   _diffuseShadow = info.diffuseShadow;
   _diffuseViewColor.Assign(info.diffuseViewColor);
   _diffuseViewShadow = info.diffuseViewShadow;
   _specularColor.Assign(info.specularColor);
   _specularShadow = info.specularShadow;
   _specularInfo.Set(info.specularBase, info.specularRate, info.specularAverage, info.specularShadow);
   _specularViewColor.Assign(info.specularViewColor);
   _specularViewShadow = info.specularViewShadow;
   _specularViewInfo.Set(info.specularViewBase, info.specularViewRate, info.specularViewAverage, info.specularViewShadow);
   _reflectColor.Assign(info.reflectColor);
   return ESuccess;
}

MO_NAMESPACE_END
