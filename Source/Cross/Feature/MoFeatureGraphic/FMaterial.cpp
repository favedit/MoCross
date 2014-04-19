#include "MoFgMaterial.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FMaterial, FInstance);

//============================================================
// <T>������ʡ�</T>
//============================================================
FMaterial::FMaterial(){
   _effectName = "automatic";
   Reset();
   //_level = 0;
   //_optionDepth = EFalse;
   //_optionAlpha = EFalse;
   //_blendSourceMode = ERenderBlendMode_SourceAlpha;
   //_blendTargetMode = ERenderBlendMode_OneMinusSourceAlpha;
   //MO_CLEAR(_pTextures);
}

//============================================================
// <T>�������ʡ�</T>
//============================================================
FMaterial::~FMaterial(){
   //MO_DELETE(_pTextures);
}

//============================================================
// <T>�ж����������Ƿ���ȡ�</T>
//
// @param pMaterial ����
//============================================================
TInt FMaterial::Compare(FMaterial* pMaterial){
   //// �Ƚϼ���
   //ERenderTechnique techniqueCd = pMaterial->TechniqueCd();
   //if(_techniqueCd != techniqueCd){
   //   return _techniqueCd - techniqueCd;
   //}
   //// �Ƚ�Ч��
   //ERenderEffect effectCd = pMaterial->EffectCd();
   //if(_effectCd != effectCd){
   //   return _effectCd - effectCd;
   //}
   //// �Ƚϲ㼶
   //TInt level = pMaterial->Level();
   //if(_level != level){
   //   return _level - level;
   //}
   //// �Ƚ�����
   //TInt count = TextureCount();
   //TInt targetCount = pMaterial->TextureCount();
   //if(targetCount != count){
   //   return count - targetCount;
   //}
   //for(TInt n = 0; n < count; n++){
   //   ITexture* piTexture = _pTextures->Textures()->Get(n);
   //   ITexture* piTargetTexture = pMaterial->Textures()->Textures()->Get(n);
   //   if(piTexture != piTargetTexture){
   //      return piTexture - piTargetTexture;
   //   }
   //}
   return 0;
}

//============================================================
// <T>�����������</T>
//
// @param pTexture ����
//============================================================
//void FMaterial::TextureClear(){
//   if(_pTextures != NULL){
//      _pTextures->Textures()->Clear();
//   }
//}
//
////============================================================
//// <T>����һ������</T>
////
//// @param pTexture ����
////============================================================
//void FMaterial::TextureSet(FRenderTexture* pTexture){
//   MO_ASSERT(pTexture);
//   if(_pTextures == NULL){
//      _pTextures = MO_CREATE(FRenderTextures);
//   }
//   _pTextures->Textures()->Clear();
//   _pTextures->Textures()->Push(pTexture);
//}
//
////============================================================
//// <T>����һ������</T>
////
//// @param pTexture ����
////============================================================
//void FMaterial::TexturePush(FRenderTexture* pTexture){
//   MO_ASSERT(pTexture);
//   if(_pTextures == NULL){
//      _pTextures = MO_CREATE(FRenderTextures);
//   }
//   _pTextures->Textures()->Push(pTexture);
//}
//
////============================================================
//// <T>����һ������</T>
////
//// @param pTexture ����
////============================================================
//void FMaterial::TextureRemove(FRenderTexture* pTexture){
//   MO_ASSERT(pTexture);
//   if(_pTextures != NULL){
//      _pTextures->Textures()->Remove(pTexture);
//   }
//}

//============================================================
// <T>����һ�����ʡ�</T>
//
// @param pMaterial ����
// @return ������
//============================================================
TResult FMaterial::AssignOption(FMaterial* pMaterial){
   MO_CHECK(pMaterial, return ENull);
   _name.Assign(pMaterial->Name());
   _effectName.Assign(pMaterial->EffectName());
   // ��������
   _optionMerge = pMaterial->OptionMerge();
   _optionSort = pMaterial->OptionSort();
   _sortLevel = pMaterial->SortLevel();
   _optionAlpha = pMaterial->OptionAlpha();
   _optionDepth = pMaterial->OptionDepth();
   _optionCompare.Assign(pMaterial->OptionCompare());
   _optionDouble = pMaterial->OptionDouble();
   _optionShadow = pMaterial->OptionShadow();
   _optionShadowSelf = pMaterial->OptionShadowSelf();
   return ESuccess;
}

//============================================================
// <T>����һ�����ʡ�</T>
//
// @param pMaterial ����
// @return ������
//============================================================
TResult FMaterial::AssignValue(FMaterial* pMaterial){
   MO_CHECK(pMaterial, return ENull);
   // ������ɫ
   _color = pMaterial->Color();
   _alpha = pMaterial->Alpha();
   // ���ò���
   _ambientColor.Assign(pMaterial->AmbientColor());
   _ambientShadow = pMaterial->AmbientShadow();
   _diffuseColor.Assign(pMaterial->DiffuseColor());
   _diffuseShadow = pMaterial->DiffuseShadow();
   _diffuseViewColor.Assign(pMaterial->DiffuseViewColor());
   _diffuseViewShadow = pMaterial->DiffuseViewShadow();
   _specularColor.Assign(pMaterial->SpecularColor());
   _specularShadow = pMaterial->SpecularShadow();
   _specularInfo = pMaterial->SpecularInfo();
   _specularViewColor.Assign(pMaterial->SpecularViewColor());
   _specularViewShadow = pMaterial->SpecularViewShadow();
   _specularViewInfo = pMaterial->SpecularViewInfo();
   _reflectColor.Assign(pMaterial->ReflectColor());
   return ESuccess;
}

//============================================================
// <T>�ϲ�һ�����ʡ�</T>
//
// @param pMaterial ����
// @return ������
//============================================================
TResult FMaterial::Merge(FMaterial* pMaterial){
   MO_CHECK(pMaterial, return ENull);
   // �ں���ɫ
   _color.Multiply(pMaterial->Color());
   _alpha.Multiply(pMaterial->Alpha());
   // �ںϲ���
   _ambientColor.AssignPower(pMaterial->AmbientColor());
   _diffuseColor.AssignPower(pMaterial->DiffuseColor());
   _diffuseViewColor.AssignPower(pMaterial->DiffuseViewColor());
   _specularColor.AssignPower(pMaterial->SpecularColor());
   _specularInfo.Multiply(pMaterial->SpecularInfo());
   _specularViewColor.AssignPower(pMaterial->SpecularViewColor());
   _specularViewInfo.Multiply(pMaterial->SpecularViewInfo());
   _reflectColor.AssignPower(pMaterial->ReflectColor());
   return ESuccess;
}

//============================================================
// <T>�������в�����</T>
//
// @param pMaterial ����
// @return ������
//============================================================
TResult FMaterial::Reset(){
   // ���ò���
   _optionMerge = EFalse;
   _optionSort = EFalse;
   _sortLevel = 0;
   _optionAlpha = EFalse;
   _optionDepth = ETrue;
   _optionCompare.Assign("Less");
   _optionDouble = EFalse;
   _optionShadow = ETrue;
   _optionShadowSelf = ETrue;
   // ������ɫ
   _ambientColor.SetAll(1.0f);
   _ambientShadow = 0.0f;
   _diffuseColor.SetAll(1.0f);
   _diffuseShadow = 0.0f;
   _diffuseViewColor.SetAll(1.0f);
   _diffuseViewShadow = 0.0f;
   _specularColor.SetAll(1.0f);
   _specularShadow = 0.0f;
   _specularInfo.Set(1.0, 1.0, 1.0, 1.0);
   _specularViewColor.SetAll(1.0f);
   _specularViewShadow = 0.0f;
   _specularViewInfo.Set(1.0, 1.0, 1.0, 1.0);
   _reflectColor.SetAll(1.0f);
   return ESuccess;
}

MO_NAMESPACE_END
