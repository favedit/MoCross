#include "MoE3Material.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FMaterial3d, FMaterial);

//============================================================
// <T>����ʵ��3D���ʡ�</T>
//============================================================
FMaterial3d::FMaterial3d(){
}

//============================================================
// <T>����ʵ��3D���ʡ�</T>
//============================================================
FMaterial3d::~FMaterial3d(){
}

//============================================================
// <T>������Ⱦ��־��</T>
//
// @param flags ��־����
// @return ������
//============================================================
TResult FMaterial3d::BuildDescriptor(SRenderableDescriptor& descriptor){
   // ����͸��֧��
   descriptor.supportAlpha = _optionAlpha;
   // ���û��弯��
   TInt count = _materialTextures.Count();
   for(TInt n = 0; n < count; n++){
      FMaterial3dTexture* pTexture = _materialTextures.Get(n);
      ERenderSampler samplerCd = (ERenderSampler)pTexture->Resource()->SamplerCd();
      switch(samplerCd){
         case ERenderSampler_PackDiffuse:
            descriptor.samplers[ERenderSampler_Diffuse] = ETrue;
            descriptor.samplers[ERenderSampler_Alpha] = ETrue;
            break;
         case ERenderSampler_PackNormal:
            descriptor.samplers[ERenderSampler_Normal] = ETrue;
            descriptor.samplers[ERenderSampler_SpecularLevel] = ETrue;
            break;
         case ERenderSampler_PackSpecular:
            descriptor.samplers[ERenderSampler_SpecularColor] = ETrue;
            descriptor.samplers[ERenderSampler_Height] = ETrue;
            break;
         case ERenderSampler_PackTransmittance:
            descriptor.samplers[ERenderSampler_TransmittanceColor] = ETrue;
            descriptor.samplers[ERenderSampler_TransmittanceLevel] = ETrue;
            break;
         case ERenderSampler_PackLight:
            descriptor.samplers[ERenderSampler_Light] = ETrue;
            descriptor.samplers[ERenderSampler_Reflect] = ETrue;
            descriptor.samplers[ERenderSampler_Refract] = ETrue;
            descriptor.samplers[ERenderSampler_Emissive] = ETrue;
            break;
         case ERenderSampler_Environment:
            descriptor.samplers[ERenderSampler_Environment] = ETrue;
            break;
         default:
            descriptor.samplers[samplerCd] = ETrue;
            break;
      }
   }
   return ESuccess;
}

//============================================================
// <T>������Դ��</T>
//
// @param pResource ��Դ����
//============================================================
TResult FMaterial3d::LoadResource(FRs3dMaterial* pResource){
   MO_CHECK(pResource, return ENull);
   SMaterialInfo& info = pResource->Info();
   // ����Ч��
   _name = pResource->Name();
   _effectName = info.effectName;
   MO_CHECK(!_effectName.IsEmpty(), return EFailure);
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
   //// ������ɫ
   //_color.Set(info.colorMin, info.colorMax, info.colorRate, info.colorMerge);
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
   //_specularInfo.Set(info.specularBase, info.specularRate, info.specularAverage, info.specularShadow);
   //_specularViewColor.Assign(info.specularViewColor);
   //_specularViewShadow = info.specularViewShadow;
   //_specularViewInfo.Set(info.specularViewBase, info.specularViewRate, info.specularViewAverage, info.specularViewShadow);
   //_reflectColor.Assign(info.reflectColor);
   // ����������
   GRs3dMaterialTexturePtrs& rsTextures = pResource->Textures();
   TInt textureCount = rsTextures.Count();
   for(TInt n = 0; n < textureCount; n++){
      FRs3dMaterialTexture* pRsTexture = rsTextures.Get(n);
      // ��������
      FMaterial3dTexture* pTexture = FMaterial3dTexture::InstanceCreate();
      pTexture->LoadResource(pRsTexture);
      _materialTextures.Push(pTexture);
   }
   return ESuccess;
}

MO_NAMESPACE_END
