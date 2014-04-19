#include "MoFrContent3dBase.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>����ʵ��3D���ʡ�</T>
//============================================================
SMaterialInfo::SMaterialInfo(){
   // ���ù�Դ
   optionLight = ETrue;
   // ���úϲ�
   optionMerge = EFalse;
   // ��������
   optionSort = ETrue;
   // ���򼶱�
   sortLevel = 0;
   // ����͸��
   optionAlpha = EFalse;
   // �������
   optionDepth = ETrue;
   // ���ñȽ�
   // optionCompare = EGeCompare.Less;
   // ����˫��
   optionDouble = EFalse;
   // ����Ӱ��
   optionShadow = ETrue;
   // ��������Ӱ
   optionShadowSelf = ETrue;
   // ���ö�̬
   optionDynamic = EFalse;
   // ����͸��
   optionTransmittance = EFalse;
   // ���ò�͸����
   optionOpacity = EFalse;
   // ���÷������� (δȷ��)
   optionNormalScale = ETrue;
   // ���ñ��� (δȷ��)
   optionBorder = ETrue;
   // ���ø߶� (δȷ��)
   optionHeight = EFalse;
   // ����ǿ��
   powerRate = 1.0f;
   // ����˥��
   powerAttenuation = 1.0f;
   // �����ں�
   powerMerge = 1.0f;
   // ������Ӱ
   powerShadow = 1.0f;
   // ����λ��X
   coordX = 0.0f;
   // ����λ��Y
   coordY = 0.0f;
   // �����ȱ���
   coordRateWidth = 1.0f;
   // ����߶ȱ���
   coordRateHeight = 1.0f;
   // ��ɫ��С
   colorMin = 0.0f;
   // ��ɫ���
   colorMax = 1.0f;
   // ��ɫ����
   colorRate = 1.0f;
   // ��ɫ�ں�
   colorMerge = 0.5f;
   // ͸������
   alphaBase = 0.2f;
   // ͸������
   alphaRate = 1.0f;
   // ͸������
   alphaLevel = 1.0f;
   // ͸���ϲ�
   alphaMerge = 1.0f;
   // ��������ɫ (RGB=��ɫ��A=ǿ��)
   ambientColor.Set(0.0f, 0.0f, 0.0f, 1.0f);
   // ��������Ӱ
   ambientShadow = 1.0f;
   // ɢ�����ɫ (RGB=��ɫ��A=ǿ��)
   diffuseColor.Set(0.0f, 0.0f, 0.0f, 1.0f);
   // ɢ�����Ӱ
   diffuseShadow = 1.0f;
   // ɢ��������ɫ (RGB=��ɫ��A=ǿ��)
   diffuseViewColor.Set(1.0f, 1.0f, 1.0f, 0.0f);
   // ɢ����ӽ���Ӱ
   diffuseViewShadow = 1.0f;
   // �߹���ɫ (RGB=��ɫ��A=ǿ��)
   specularColor.Set(1.0f, 1.0f, 1.0f, 0.0f);
   // �߹����
   specularBase = 1.0f;
   // �߹����
   specularRate = 1.0f;
   // �߹�ƽ��
   specularAverage = 1.0f;
   // �߹���Ӱ
   specularShadow = 1.0f;
   // �߹������ɫ (RGB=��ɫ��A=ǿ��)
   specularViewColor.Set(1.0f, 1.0f, 1.0f, 0.0f);
   // �ӽǸ߹����
   specularViewBase = 1.0f;
   // �ӽǸ߹����
   specularViewRate = 1.0f;
   // �ӽǸ߹�ƽ��
   specularViewAverage = 1.0f;
   // �ӽǸ߹���Ӱ
   specularViewShadow = 1.0f;
   // ������ɫ (RGB=��ɫ��A=ǿ��)
   reflectColor.Set(1.0f, 1.0f, 1.0f, 0.0f);
   // �����ں�
   reflectMerge = 1.0f;
   // ������Ӱ
   reflectShadow = 1.0f;
   // ����������ɫ (RGB=��ɫ��A=ǿ��)
   refractFrontColor.Set(1.0f, 1.0f, 1.0f, 0.0f);
   // ���������ں�
   refractFrontMerge = 1.0f;
   // ����������Ӱ
   refractFrontShadow = 1.0f;
   // ���䱳����ɫ (RGB=��ɫ��A=ǿ��)
   refractBackColor.Set(1.0f, 1.0f, 1.0f, 0.0f);
   // ���䱳���ں�
   refractBackMerge = 1.0f;
   // ���䱳����Ӱ
   refractBackShadow = 1.0f;
   // ��͸����ɫ (RGB=��ɫ��A=ǿ��)
   opacityColor.Set(1.0f, 1.0f, 1.0f, 0.0f);
   // ��͸������
   opacityRate = 0.0f;
   // ��͸��͸��
   opacityAlpha = 0.0f;
   // ��͸�����
   opacityDepth = 0.0f;
   // ��͸��͸��
   opacityTransmittance = 0.0f;
   // �Է�����ɫ
   emissiveColor.Set(0.0f, 0.0f, 0.0f, 0.0f);
   // �Է�������
   emissive.Set(1.0f, 1.0f, 1.0f, 0.0f);
}

//============================================================
// <T>����ʵ��3D���ʡ�</T>
//============================================================
SMaterialInfo::~SMaterialInfo(){
}

//============================================================
// <T>�������á�</T>
//
// @param p:material ���ʻ���
//============================================================
void SMaterialInfo::AssignOption(SMaterialInfo* pMaterial){
   //// ��������
   //effectName = p.effectName;
   //transformName = p.transformName;
   //// ��������
   //optionLight = p.optionLight;
   //optionMerge = p.optionMerge;
   //optionSort = p.optionSort;
   //sortLevel = p.sortLevel;
   //optionAlpha = p.optionAlpha;
   //optionDepth = p.optionDepth;
   //optionCompare = p.optionCompare;
   //optionDouble = p.optionDouble;
   //optionShadow = p.optionShadow;
   //optionShadowSelf = p.optionShadowSelf;
   //optionDynamic = p.optionDynamic;
   //optionTransmittance = p.optionTransmittance;
   //optionOpacity = p.optionOpacity;
}
      
//============================================================
// <T>���չ��ա�</T>
//
// @param p:material ���ʻ���
//============================================================
void SMaterialInfo::AssignLight(SMaterialInfo* pMaterial){
   //// ���ܶ���ɫ
   //colorMin = p.colorMin;
   //colorMax = p.colorMax;
   //colorRate = p.colorRate;
   //colorMerge = p.colorMerge;
   //// ����͸��
   //alphaBase = p.alphaBase;
   //alphaRate = p.alphaRate;
   //alphaLevel = p.alphaLevel;
   //alphaMerge = p.alphaMerge;
   //// ���ػ�������
   //ambientColor.assign(p.ambientColor);
   //ambientShadow = p.ambientShadow;
   //diffuseColor.assign(p.diffuseColor);
   //diffuseShadow = p.diffuseShadow;
   //diffuseViewColor.assign(p.diffuseViewColor);
   //diffuseViewShadow = p.diffuseViewShadow;
   //specularColor.assign(p.specularColor);
   //specularBase = p.specularBase;
   //specularRate = p.specularRate;
   //specularAverage = p.specularAverage;
   //specularShadow = p.specularShadow;
   //specularViewColor.assign(p.specularViewColor);
   //specularViewBase = p.specularViewBase;
   //specularViewRate = p.specularViewRate;
   //specularViewAverage = p.specularViewAverage;
   //specularViewShadow = p.specularViewShadow;
   //emissiveColor.assign(p.emissive);
}
      
//============================================================
// <T>�����л�������Ϣ��</T>
//
// @param p:input ����������
//============================================================
void SMaterialInfo::Unserialize(IDataInput* pInput){
   // ��ȡ����
   effectName.UnserializeAutomatic(pInput);
   transformName.UnserializeAutomatic(pInput);
   optionLight = RGeomFlag::ToBoolean(pInput->ReadInt8(), optionLight);
   optionMerge = RGeomFlag::ToBoolean(pInput->ReadInt8(), optionMerge);
   optionSort = RGeomFlag::ToBoolean(pInput->ReadInt8(), optionSort);
   sortLevel = pInput->ReadInt32();
   optionAlpha = RGeomFlag::ToBoolean(pInput->ReadInt8(), optionAlpha);
   optionDepth = RGeomFlag::ToBoolean(pInput->ReadInt8(), optionDepth);
   optionCompare.UnserializeAutomatic(pInput);
   optionDouble = RGeomFlag::ToBoolean(pInput->ReadInt8(), optionDouble);
   optionShadow = RGeomFlag::ToBoolean(pInput->ReadInt8(), optionShadow);
   optionShadowSelf = RGeomFlag::ToBoolean(pInput->ReadInt8(), optionShadowSelf);
   optionDynamic = RGeomFlag::ToBoolean(pInput->ReadInt8(), optionDynamic);
   optionTransmittance = RGeomFlag::ToBoolean(pInput->ReadInt8(), optionTransmittance);
   optionOpacity = RGeomFlag::ToBoolean(pInput->ReadInt8(), optionOpacity);
   // ��ȡ����
   coordRateWidth = pInput->ReadFloat();
   coordRateHeight = pInput->ReadFloat();
   // ��ȡ��ɫ
   colorMin = pInput->ReadFloat();
   colorMax = pInput->ReadFloat();
   colorRate = pInput->ReadFloat();
   colorMerge = pInput->ReadFloat();         
   // ��ȡ͸��
   alphaBase = pInput->ReadFloat();
   alphaRate = pInput->ReadFloat();
   alphaLevel = pInput->ReadFloat();
   alphaMerge = pInput->ReadFloat();
   // ��ȡ��ɫ
   ambientColor.Unserialize(pInput);
   ambientShadow = pInput->ReadFloat();
   diffuseColor.Unserialize(pInput);
   diffuseShadow = pInput->ReadFloat();
   diffuseViewColor.Unserialize(pInput);
   diffuseViewShadow = pInput->ReadFloat();
   specularColor.Unserialize(pInput);
   specularBase = pInput->ReadFloat();
   specularRate = pInput->ReadFloat();
   specularAverage = pInput->ReadFloat();
   specularShadow = pInput->ReadFloat();
   specularViewColor.Unserialize(pInput);
   specularViewBase = pInput->ReadFloat();
   specularViewRate = pInput->ReadFloat();
   specularViewAverage = pInput->ReadFloat();
   specularViewShadow = pInput->ReadFloat();
   reflectColor.Unserialize(pInput);
   reflectMerge = pInput->ReadFloat();
   reflectShadow = pInput->ReadFloat();
   refractFrontColor.Unserialize(pInput);
   refractBackColor.Unserialize(pInput);
   opacityColor.Unserialize(pInput);
   opacityRate = pInput->ReadFloat();
   opacityAlpha = pInput->ReadFloat();
   opacityDepth = pInput->ReadFloat();
   opacityTransmittance = pInput->ReadFloat();
   emissive.Unserialize(pInput);
}
      
//============================================================
// <T>�������ݡ�</T>
//============================================================
void SMaterialInfo::Reset(){
   // ��������
   coordRateWidth = 1.0f;
   coordRateHeight = 1.0f;
   // ������ɫ
   colorMin = 0.0f;
   colorMax = 1.0f;
   colorRate = 1.0f;
   colorMerge = 0.5f;
   // ����͸��
   alphaBase = 0.2f;
   alphaRate = 1.0f;
   alphaLevel = 1.0f;
   alphaMerge = 1.0f;
   // ������ɫ
   ambientColor.SetAll(1.0f);
   ambientShadow = 1.0f;
   diffuseColor.SetAll(1.0f);
   diffuseShadow = 1.0f;
   diffuseViewColor.SetAll(1.0f);
   diffuseViewShadow = 1.0f;
   specularColor.SetAll(1.0f);
   specularBase = 1.0f;
   specularRate = 1.0f;
   specularAverage = 1.0f;
   specularShadow = 1.0f;
   specularViewColor.SetAll(1.0f);
   specularViewBase = 1.0f;
   specularViewRate = 1.0f;
   specularViewAverage = 1.0f;
   specularViewShadow = 1.0f;
   reflectMerge = 1.0f;
   reflectShadow = 1.0f;
   refractFrontColor.SetAll(1.0f);
   refractBackColor.SetAll(1.0f);
   opacityColor.SetAll(1.0f);
   opacityRate = 1.0f;
   opacityAlpha = 1.0f;
   opacityDepth = 1.0f;
   opacityTransmittance = 1.0f;
   emissive.SetAll(1.0f);
}
      
MO_NAMESPACE_END
