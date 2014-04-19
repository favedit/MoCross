#ifndef __MO_FG_MATERIAL_H__
#define __MO_FG_MATERIAL_H__
//************************************************************

#ifndef __MO_FG_COMMON_H__
#include "MoFgCommon.h"
#endif // __MO_FG_COMMON_H__

MO_NAMESPACE_BEGIN

//============================================================
// <T>�������</T>
//============================================================
class MO_FG_DECLARE FTexture : public FGraphicObject
{
   MO_CLASS_DECLARE_INHERITS(FTexture, FGraphicObject);
protected:
   TGraphicHandle _graphicHandle;
   SIntSize2 _size;
public:
   FTexture();
   MO_ABSTRACT ~FTexture();
public:
   //------------------------------------------------------------
   // <T>��þ����</T>
   MO_INLINE TGraphicHandle& GraphicHandle(){
      return _graphicHandle;
   }
   //------------------------------------------------------------
   // <T>��ô�С��</T>
   MO_INLINE SIntSize2& Size(){
      return _size;
   }
public:
   MO_ABSTRACT void Free();
};
//------------------------------------------------------------
typedef MO_FG_DECLARE FObjects<FTexture*> FTextureCollection;

//============================================================
// <T>������ɫ��Ϣ��</T>
//============================================================
struct SMaterialColorInfo
{
public:
   // ��ɫ��С
   TFloat min;
   // ��ɫ���
   TFloat max;
   // ��ɫ����
   TFloat rate;
   // ��ɫ�ں�
   TFloat merge;
public:
   //------------------------------------------------------------
   // <T>���������ɫ��Ϣ��</T>
   SMaterialColorInfo(){
      Reset();
   }
public:
   //------------------------------------------------------------
   // <T>���ô���</T>
   MO_INLINE void Set(TFloat minValue, TFloat maxValue, TFloat rateValue, TFloat mergeValue){
      min = minValue;
      max = maxValue;
      rate = rateValue;
      merge = mergeValue;
   }
   //------------------------------------------------------------
   // <T>������Ϣ��</T>
   MO_INLINE void Multiply(const SMaterialColorInfo& info){
      min *= info.min;
      max *= info.max;
      rate *= info.rate;
      merge *= info.merge;
   }
public:
   //------------------------------------------------------------
   // <T>������Ϣ��</T>
   MO_INLINE void Reset(){
      min = 0.0f;
      max = 1.0f;
      rate = 1.0f;
      merge = 1.0f;
   }
};
//============================================================
// <T>����͸����Ϣ��</T>
//============================================================
struct SMaterialAlphaInfo
{
public:
   // ͸������
   TFloat base;
   // ͸������
   TFloat rate;
   // ͸������
   TFloat level;
   // ͸���ϲ�
   TFloat merge;
public:
   //------------------------------------------------------------
   // <T>������ʸ߹���Ϣ��</T>
   SMaterialAlphaInfo(){
      Reset();
   }
public:
   //------------------------------------------------------------
   // <T>���ô���</T>
   MO_INLINE void Set(TFloat baseValue, TFloat rateValue, TFloat levelValue, TFloat mergeValue){
      base = baseValue;
      rate = rateValue;
      level = levelValue;
      merge = mergeValue;
   }
   //------------------------------------------------------------
   // <T>������Ϣ��</T>
   MO_INLINE void Multiply(const SMaterialAlphaInfo& info){
      base *= info.base;
      rate *= info.rate;
      level *= info.level;
      merge *= info.merge;
   }
public:
   //------------------------------------------------------------
   // <T>������Ϣ��</T>
   MO_INLINE void Reset(){
      base = 0.0f;
      rate = 1.0f;
      level = 1.0f;
      merge = 1.0f;
   }
};

//============================================================
// <T>���ʸ߹���Ϣ��</T>
//============================================================
struct SMaterialSpecularInfo
{
public:
   // ����
   TFloat base;
   // ����
   TFloat rate;
   // ƽ��
   TFloat average;
   // ��Ӱ
   TFloat shadow;
public:
   //------------------------------------------------------------
   // <T>������ʸ߹���Ϣ��</T>
   SMaterialSpecularInfo(){
      Reset();
   }
public:
   //------------------------------------------------------------
   // <T>���ô���</T>
   MO_INLINE void Set(TFloat baseValue, TFloat rateValue, TFloat avarageValue, TFloat shadowValue){
      base = baseValue;
      rate = rateValue;
      average = avarageValue;
      shadow = shadowValue;
   }
   //------------------------------------------------------------
   // <T>������Ϣ��</T>
   MO_INLINE void Multiply(const SMaterialSpecularInfo& info){
      base *= info.base;
      rate *= info.rate;
      average *= info.average;
      shadow *= info.shadow;
   }
public:
   //------------------------------------------------------------
   // <T>������Ϣ��</T>
   MO_INLINE void Reset(){
      base = 0.0f;
      rate = 0.0f;
      average = 0.0f;
      shadow = 0.0f;
   }
};

//============================================================
// <T>���ʡ�</T>
//============================================================
class MO_FG_DECLARE FMaterial : public FInstance
{
   MO_CLASS_DECLARE_INHERITS(FMaterial, FInstance);
protected:
   // ����
   TString _name;
   // Ч������
   TString _effectName;
   // �任����
   TString transformName;
protected:
   // ���ù�Դ
   //TBool _optionLight;
   // ���úϲ�
   TBool _optionMerge;
   // ��������
   TBool _optionSort;
   // ���򼶱�
   TInt _sortLevel;
   // ����͸��
   TBool _optionAlpha;
   // �������
   TBool _optionDepth;
   // ���ñȽ�
   TString _optionCompare;
   // ����˫��
   TBool _optionDouble;
   // ����Ӱ��
   TBool _optionShadow;
   // ��������Ӱ
   TBool _optionShadowSelf;
   //// ���ö�̬
   //TBool _optionDynamic;
   //// ����͸��
   //TBool _optionTransmittance;
   //// ���ò�͸����
   //TBool _optionOpacity;
   //// ���÷������� (δȷ��)
   //TBool _optionNormalScale;
   //// ���ñ��� (δȷ��)
   //TBool _optionBorder;
   //// ���ø߶� (δȷ��)
   //TBool _optionHeight;
   //// ����ǿ��
   //TFloat _powerRate;
   //// ����˥��
   //TFloat _powerAttenuation;
   //// �����ں�
   //TFloat _powerMerge;
   //// ������Ӱ
   //TFloat _powerShadow;
   //// ����λ��X
   //TFloat _coordX;
   //// ����λ��Y
   //TFloat _coordY;
   //// �����ȱ���
   //TFloat _coordRateWidth;
   //// ����߶ȱ���
   //TFloat _coordRateHeight;
   // ��ɫ��Ϣ
   SMaterialColorInfo _color;
   // ͸����Ϣ
   SMaterialAlphaInfo _alpha;
   // ��������ɫ (RGB=��ɫ��A=ǿ��)
   SFloatColor4 _ambientColor;
   // ��������Ӱ
   TFloat _ambientShadow;
   // ɢ�����ɫ (RGB=��ɫ��A=ǿ��)
   SFloatColor4 _diffuseColor;
   // ɢ�����Ӱ
   TFloat _diffuseShadow;
   // ɢ��������ɫ (RGB=��ɫ��A=ǿ��)
   SFloatColor4 _diffuseViewColor;
   // ɢ����ӽ���Ӱ
   TFloat _diffuseViewShadow;
   // �߹���ɫ (RGB=��ɫ��A=ǿ��)
   SFloatColor4 _specularColor;
   // �߹���Ӱ
   TFloat _specularShadow;
   // �߹���Ϣ
   SMaterialSpecularInfo _specularInfo;
   // �߹��ӽ���ɫ (RGB=��ɫ��A=ǿ��)
   SFloatColor4 _specularViewColor;
   // �߹��ӽ���Ϣ
   SMaterialSpecularInfo _specularViewInfo;
   // �߹��ӽ���Ӱ
   TFloat _specularViewShadow;
   // ������ɫ (RGB=��ɫ��A=ǿ��)
   SFloatColor4 _reflectColor;
   //// �����ں�
   //TFloat _reflectMerge;
   //// ������Ӱ
   //TFloat _reflectShadow;
   //// ����������ɫ (RGB=��ɫ��A=ǿ��)
   //SFloatColor4 _refractFrontColor;
   //// ���������ں�
   //TFloat _refractFrontMerge;
   //// ����������Ӱ
   //TFloat _refractFrontShadow;
   //// ���䱳����ɫ (RGB=��ɫ��A=ǿ��)
   //SFloatColor4 _refractBackColor;
   //// ���䱳���ں�
   //TFloat _refractBackMerge;
   //// ���䱳����Ӱ
   //TFloat _refractBackShadow;
   //// ��͸����ɫ (RGB=��ɫ��A=ǿ��)
   //SFloatColor4 _opacityColor;
   //// ��͸������
   //TFloat _opacityRate;
   //// ��͸��͸��
   //TFloat _opacityAlpha;
   //// ��͸�����
   //TFloat _opacityDepth;
   //// ��͸��͸��
   //TFloat _opacityTransmittance;
   //// �Է�����ɫ
   //SFloatColor4 _emissiveColor;
   //// �Է�������
   //SFloatColor4 _emissive;
   //ERenderBlendMode _blendSourceMode;
   //ERenderBlendMode _blendTargetMode;
   //FRenderTextures* _pTextures;
public:
   FMaterial();
   MO_ABSTRACT ~FMaterial();
public:
   //------------------------------------------------------------
   // <T>������ơ�</T>
   MO_INLINE TCharC* Name(){
      return _name;
   }
   //------------------------------------------------------------
   // <T>�������ơ�</T>
   MO_INLINE void SetName(TCharC* pName){
      _name = pName;
   }
   //------------------------------------------------------------
   // <T>�����ȾЧ�����ơ�</T>
   MO_INLINE TCharC* EffectName(){
      return _effectName;
   }
   //------------------------------------------------------------
   // <T>������ȾЧ�����ơ�</T>
   MO_INLINE void SetEffectName(TCharC* pEffectName){
      _effectName = pEffectName;
   }
   //------------------------------------------------------------
   // <T>������úϲ���</T>
   MO_INLINE TBool OptionMerge(){
      return _optionMerge;
   }
   //------------------------------------------------------------
   // <T>�������úϲ���</T>
   MO_INLINE void SetOptionMerge(TBool optionMerge){
      _optionMerge = optionMerge;
   }
   //------------------------------------------------------------
   // <T>������úϲ���</T>
   MO_INLINE TBool OptionSort(){
      return _optionSort;
   }
   //------------------------------------------------------------
   // <T>������������</T>
   MO_INLINE void SetOptionSort(TBool optionSort){
      _optionSort = optionSort;
   }
   //------------------------------------------------------------
   // <T>������򼶱�</T>
   MO_INLINE TInt SortLevel(){
      return _sortLevel;
   }
   //------------------------------------------------------------
   // <T>�������򼶱�</T>
   MO_INLINE void SetSortLevel(TInt sortLevel){
      _sortLevel = sortLevel;
   }
   //------------------------------------------------------------
   // <T>�������͸����</T>
   MO_INLINE TBool OptionAlpha(){
      return _optionAlpha;
   }
   //------------------------------------------------------------
   // <T>��������͸����</T>
   MO_INLINE void SetOptionAlpha(TBool optionAlpha){
      _optionAlpha = optionAlpha;
   }
   //------------------------------------------------------------
   // <T>���������ȡ�</T>
   MO_INLINE TBool OptionDepth(){
      return _optionDepth;
   }
   //------------------------------------------------------------
   // <T>����������ȡ�</T>
   MO_INLINE void SetOptionDepth(TBool optionDepth){
      _optionDepth = optionDepth;
   }
   //------------------------------------------------------------
   // <T>��ñȽϷ�ʽ��</T>
   MO_INLINE TCharC* OptionCompare(){
      return _optionCompare;
   }
   //------------------------------------------------------------
   // <T>���ñȽϷ�ʽ��</T>
   MO_INLINE void SetOptionCompare(TCharC* pOptionCompare){
      _optionCompare = pOptionCompare;
   }
   //------------------------------------------------------------
   // <T>�������˫�档</T>
   MO_INLINE TBool OptionDouble(){
      return _optionDouble;
   }
   //------------------------------------------------------------
   // <T>��������˫�档</T>
   MO_INLINE void SetOptionDouble(TBool _optionDouble){
      _optionDouble = _optionDouble;
   }
   //------------------------------------------------------------
   // <T>���������Ӱ��</T>
   MO_INLINE TBool OptionShadow(){
      return _optionShadow;
   }
   //------------------------------------------------------------
   // <T>����������Ӱ��</T>
   MO_INLINE void SetOptionShadow(TBool _optionShadow){
      _optionShadow = _optionShadow;
   }
   //------------------------------------------------------------
   // <T>�����������Ӱ��</T>
   MO_INLINE TBool OptionShadowSelf(){
      return _optionShadowSelf;
   }
   //------------------------------------------------------------
   // <T>������������Ӱ��</T>
   MO_INLINE void SetOptionShadowSelf(TBool _optionShadowSelf){
      _optionShadowSelf = _optionShadowSelf;
   }
   ////------------------------------------------------------------
   //// <T>��û����Դ��ʽ��</T>
   //MO_INLINE ERenderBlendMode BlendSourceMode(){
   //   return _blendSourceMode;
   //}
   ////------------------------------------------------------------
   //// <T>���û����Դ��ʽ��</T>
   //MO_INLINE void SetBlendSourceMode(ERenderBlendMode blendSourceMode){
   //   _blendSourceMode = blendSourceMode;
   //}
   ////------------------------------------------------------------
   //// <T>��û��Ŀ�귽ʽ��</T>
   //MO_INLINE ERenderBlendMode BlendTargetMode(){
   //   return _blendTargetMode;
   //}
   ////------------------------------------------------------------
   //// <T>���û��Ŀ�귽ʽ��</T>
   //MO_INLINE void SetBlendTargetMode(ERenderBlendMode blendTargetMode){
   //   _blendTargetMode = blendTargetMode;
   //}
   ////------------------------------------------------------------
   //// <T>�ж��Ƿ�������</T>
   //MO_INLINE TBool HasTexture(){
   //   return (_pTextures != NULL) ? !_pTextures->Textures()->IsEmpty() : EFalse;
   //}
   ////------------------------------------------------------------
   //// <T>������������</T>
   //MO_INLINE TInt TextureCount(){
   //   return (_pTextures != NULL) ? _pTextures->Textures()->Count() : 0;
   //}
   ////------------------------------------------------------------
   //// <T>��������ϡ�</T>
   //MO_INLINE FRenderTextures* Textures(){
   //   return _pTextures;
   //}
public:
   //------------------------------------------------------------
   // <T>�����ɫ��Ϣ��</T>
   MO_INLINE SMaterialColorInfo& Color(){
      return _color;
   }
   //------------------------------------------------------------
   // <T>���͸����Ϣ��</T>
   MO_INLINE SMaterialAlphaInfo& Alpha(){
      return _alpha;
   }
   //------------------------------------------------------------
   // <T>��û�������ɫ��</T>
   MO_INLINE SFloatColor4& AmbientColor(){
      return _ambientColor;
   }
   //------------------------------------------------------------
   // <T>��û�������Ӱ��</T>
   MO_INLINE TFloat AmbientShadow(){
      return _ambientShadow;
   }
   //------------------------------------------------------------
   // <T>���ɢ�����ɫ��</T>
   MO_INLINE SFloatColor4& DiffuseColor(){
      return _diffuseColor;
   }
   //------------------------------------------------------------
   // <T>���ɢ�����Ӱ��</T>
   MO_INLINE TFloat DiffuseShadow(){
      return _diffuseShadow;
   }
   //------------------------------------------------------------
   // <T>���ɢ��������ɫ��</T>
   MO_INLINE SFloatColor4& DiffuseViewColor(){
      return _diffuseViewColor;
   }
   //------------------------------------------------------------
   // <T>���ɢ����ӽ���Ӱ��</T>
   MO_INLINE TFloat DiffuseViewShadow(){
      return _diffuseViewShadow;
   }
   //------------------------------------------------------------
   // <T>��ø߹���ɫ��</T>
   MO_INLINE SFloatColor4& SpecularColor(){
      return _specularColor;
   }
   //------------------------------------------------------------
   // <T>��ø߹���Ӱ��</T>
   MO_INLINE TFloat SpecularShadow(){
      return _specularShadow;
   }
   //------------------------------------------------------------
   // <T>��ø߹���Ϣ��</T>
   MO_INLINE SMaterialSpecularInfo& SpecularInfo(){
      return _specularInfo;
   }
   //------------------------------------------------------------
   // <T>��ø߹��ӽ���ɫ��</T>
   MO_INLINE SFloatColor4& SpecularViewColor(){
      return _specularViewColor;
   }
   //------------------------------------------------------------
   // <T>��ø߹��ӽ���Ӱ��</T>
   MO_INLINE TFloat SpecularViewShadow(){
      return _specularViewShadow;
   }
   //------------------------------------------------------------
   // <T>��ø߹��ӽ���Ϣ��</T>
   MO_INLINE SMaterialSpecularInfo& SpecularViewInfo(){
      return _specularViewInfo;
   }
   //------------------------------------------------------------
   // <T>��÷�����ɫ��</T>
   MO_INLINE SFloatColor4 ReflectColor(){
      return _reflectColor;
   }
public:
   TInt Compare(FMaterial* pMaterial);
public:
   //void TextureClear();
   //void TextureSet(FRenderTexture* pTexture);
   //void TexturePush(FRenderTexture* pTexture);
   //void TextureRemove(FRenderTexture* pTexture);
public:
   MO_ABSTRACT TResult AssignOption(FMaterial* pMaterial);
   MO_ABSTRACT TResult AssignValue(FMaterial* pMaterial);
   MO_ABSTRACT TResult Merge(FMaterial* pMaterial);
   MO_ABSTRACT TResult Reset();
};
//------------------------------------------------------------
typedef MO_FG_DECLARE FObjects<FMaterial*> FMaterialCollection;
typedef MO_FG_DECLARE FDictionary<FMaterial*> FMaterialDictionary;
typedef MO_FG_DECLARE GPtrDictionary<FMaterial> GMaterialPtrDictionary;

//============================================================
// <T>���ʿ���̨��</T>
//============================================================
class MO_FG_DECLARE FMaterialConsole : public FConsole{
protected:
   FMaterialCollection* _pMaterials;
public:
   FMaterialConsole();
   MO_ABSTRACT ~FMaterialConsole();
public:
   //------------------------------------------------------------
   // <T>��ò��ʼ��ϡ�</T>
   MO_INLINE FMaterialCollection* Materials(){
      return _pMaterials;
   }
//public:
   //FMaterial* MaterialFind(FBitmap* pBitmap);
   //FMaterial* MaterialSync(FBitmap* pBitmap);
};

//============================================================
// <T>���ʹ�������</T>
//============================================================
class MO_FG_DECLARE RMaterialManager : public RSingleton<FMaterialConsole>{
};

MO_NAMESPACE_END

//************************************************************
#endif // __MO_FG_MATERIAL_H__
