#ifndef __MO_FR_CONTENT3D_BASE_H__
#define __MO_FR_CONTENT3D_BASE_H__
//************************************************************

#ifndef __MO_FR_COMMON_H__
#include "MoFrCommon.h"
#endif // __MO_FR_COMMON_H__

#ifndef __MO_FR_CONTENT_H__
#include "MoFrContent.h"
#endif // __MO_FR_CONTENT_H__

MO_NAMESPACE_BEGIN

//============================================================
class FRs3dThemeConsole;
class FRs3dTextureConsole;
class FRs3dMaterialConsole;
class FRs3dModelConsole;
class FRs3dTemplateConsole;
class FRs3dSceneConsole;

//============================================================
// <T>��Դ3D���͡�</T>
//============================================================
enum EResource3d{
   EResource3d_Unknown   = 0,
   EResource3d_Texture   = 1,
};

//============================================================
// <T>��Ⱦ�������͡�</T>
//============================================================
enum EContent3dTexture{
   EContent3dTexture_Unknown,
   EContent3dTexture_Flat2d,
   EContent3dTexture_Flat3d,
   EContent3dTexture_Cube,
};

//============================================================
// <T>��Ⱦȡ�������͡�</T>
//============================================================
enum EContent3dSampler{
   EContent3dSampler_Unknown,
   EContent3dSampler_Ambient,
   EContent3dSampler_Diffuse,
   EContent3dSampler_Alpha,
   EContent3dSampler_Normal,
   EContent3dSampler_Height,
   EContent3dSampler_SpecularColor,
   EContent3dSampler_SpecularLevel,
   EContent3dSampler_TransmittanceColor,
   EContent3dSampler_TransmittanceLevel,
   EContent3dSampler_Light,
   EContent3dSampler_Reflect,
   EContent3dSampler_Refract,
   EContent3dSampler_Emissive,
   EContent3dSampler_Environment,
   EContent3dSampler_LayerMerge,
   EContent3dSampler_Layer1,
   EContent3dSampler_Layer2,
   EContent3dSampler_Layer3,
   EContent3dSampler_Layer4,
   EContent3dSampler_PackDiffuse,
   EContent3dSampler_PackNormal,
   EContent3dSampler_PackSpecular,
   EContent3dSampler_PackTransmittance,
   EContent3dSampler_PackLight,
   EContent3dSampler_Count,
};

//============================================================
// <T>��Ⱦ�����ʽ��</T>
//============================================================
enum EContent3dVertexFormat{
   EContent3dVertexFormat_Unknown = 0,
   EContent3dVertexFormat_Float1 = 1,
   EContent3dVertexFormat_Float2 = 2,
   EContent3dVertexFormat_Float3 = 3,
   EContent3dVertexFormat_Float4 = 4,
   EContent3dVertexFormat_Byte4 = 5,
   EContent3dVertexFormat_ByteNormal4 = 6,
};

//============================================================
// <T>��Ⱦ������ȡ�</T>
//============================================================
enum EContent3dIndexStride{
   EContent3dIndexStride_Unknown = 0,
   EContent3dIndexStride_Uint16 = 1,
   EContent3dIndexStride_Uint32 = 2,
};

//============================================================
// <T>����Ϣ��</T>
//============================================================
struct MO_FR_DECLARE SFogInfo{
public:
   // ��ƽ��
   TFloat _near;
   // Զƽ��
   TFloat _far;
   // ����
   TFloat _rate;
   // ˥��
   TFloat _attenuation;
   // ��ɫ
   SFloatColor4 _color;
public:
   //------------------------------------------------------------
   // <T>��������Ϣ��</T>
   SFogInfo(){
      _near = 0.0f;
      _far = 1.0f;
      _rate = 1.0f;
      _attenuation = 1.0f;
      _color.SetAll(1.0f);
   }
public:
   //------------------------------------------------------------
   // <T>���������з����л����ݡ�</T>
   void Unserialize(IDataInput* pInput){
      _near = pInput->ReadFloat();
      _far = pInput->ReadFloat();
      _rate = pInput->ReadFloat();
      _attenuation = pInput->ReadFloat();
      _color.Unserialize(pInput);
   }
};

//============================================================
// <T>�߽���Ϣ��</T>
//============================================================
struct MO_FR_DECLARE SEdgeInfo{
public:
   // ����
   TFloat _rate;
   // �㼶
   TFloat _level;
   // ���
   TFloat _width;
   // ��ɫ
   SFloatColor4 _color;
public:
   //------------------------------------------------------------
   // <T>����߽���Ϣ��</T>
   SEdgeInfo(){
      _rate = 0.0f;
      _level = 1.0f;
      _width = 1.0f;
      _color.SetAll(1.0f);
   }
public:
   //------------------------------------------------------------
   // <T>���������з����л����ݡ�</T>
   void Unserialize(IDataInput* pInput){
      _rate = pInput->ReadFloat();
      _level = pInput->ReadFloat();
      _width = pInput->ReadFloat();
      _color.Unserialize(pInput);
   }
};

//============================================================
// <T>ƽ����Ϣ��</T>
//============================================================
struct MO_FR_DECLARE SFaceInfo{
public:
   // ��Χ
   TFloat _range;
   // ����
   TFloat _limit;
   // ����
   TFloat _rate;
public:
   //------------------------------------------------------------
   // <T>����ƽ����Ϣ��</T>
   SFaceInfo(){
      _range = 0.0f;
      _limit = 1.0f;
      _rate = 1.0f;
   }
public:
   //------------------------------------------------------------
   // <T>���������з����л����ݡ�</T>
   void Unserialize(IDataInput* pInput){
      _range = pInput->ReadFloat();
      _limit = pInput->ReadFloat();
      _rate = pInput->ReadFloat();
   }
};

//============================================================
// <T>��Ӱ��Ϣ��</T>
//============================================================
struct MO_FR_DECLARE SShadowInfo{
public:
   // ����
   TFloat base;
   // ����
   TFloat rate;
   // �㼶
   TFloat level;
   // ��Χ
   TFloat range;
public:
   //------------------------------------------------------------
   // <T>������Ӱ��Ϣ��</T>
   SShadowInfo(){
      base = 0.00000005f;
      rate = 0.5f;
      level = 0.000004f;
      range = 0.0f;
   }
public:
   //------------------------------------------------------------
   // <T>���������з����л����ݡ�</T>
   void Unserialize(IDataInput* pInput){
      base = pInput->ReadFloat();
      rate = pInput->ReadFloat();
      level = pInput->ReadFloat();
      range = pInput->ReadFloat();
   }
};

//============================================================
// <T>������Ϣ��</T>
//============================================================
struct MO_FR_DECLARE SMaterialInfo{
public:
   // ���ʴ���
   TFsName code;
   // ���ʱ�ǩ
   TWideString label;
   // Ч������
   TFsName effectName;
   // �任����
   TFsName transformName;
   // ���ù�Դ
   TBool optionLight;
   // ���úϲ�
   TBool optionMerge;
   // ��������
   TBool optionSort;
   // ���򼶱�
   TInt sortLevel;
   // ����͸��
   TBool optionAlpha;
   // �������
   TBool optionDepth;
   // ���ñȽ�
   TFsName optionCompare;
   // ����˫��
   TBool optionDouble;
   // ����Ӱ��
   TBool optionShadow;
   // ��������Ӱ
   TBool optionShadowSelf;
   // ���ö�̬
   TBool optionDynamic;
   // ����͸��
   TBool optionTransmittance;
   // ���ò�͸����
   TBool optionOpacity;
   // ���÷������� (δȷ��)
   TBool optionNormalScale;
   // ���ñ��� (δȷ��)
   TBool optionBorder;
   // ���ø߶� (δȷ��)
   TBool optionHeight;
   // ����ǿ��
   TFloat powerRate;
   // ����˥��
   TFloat powerAttenuation;
   // �����ں�
   TFloat powerMerge;
   // ������Ӱ
   TFloat powerShadow;
   // ����λ��X
   TFloat coordX;
   // ����λ��Y
   TFloat coordY;
   // �����ȱ���
   TFloat coordRateWidth;
   // ����߶ȱ���
   TFloat coordRateHeight;
   // ��ɫ��С
   TFloat colorMin;
   // ��ɫ���
   TFloat colorMax;
   // ��ɫ����
   TFloat colorRate;
   // ��ɫ�ں�
   TFloat colorMerge;
   // ͸������
   TFloat alphaBase;
   // ͸������
   TFloat alphaRate;
   // ͸������
   TFloat alphaLevel;
   // ͸���ϲ�
   TFloat alphaMerge;
   // ��������ɫ (RGB=��ɫ��A=ǿ��)
   SFloatColor4 ambientColor;
   // ��������Ӱ
   TFloat ambientShadow;
   // ɢ�����ɫ (RGB=��ɫ��A=ǿ��)
   SFloatColor4 diffuseColor;
   // ɢ�����Ӱ
   TFloat diffuseShadow;
   // ɢ��������ɫ (RGB=��ɫ��A=ǿ��)
   SFloatColor4 diffuseViewColor;
   // ɢ����ӽ���Ӱ
   TFloat diffuseViewShadow;
   // �߹���ɫ (RGB=��ɫ��A=ǿ��)
   SFloatColor4 specularColor;
   // �߹����
   TFloat specularBase;
   // �߹����
   TFloat specularRate;
   // �߹�ƽ��
   TFloat specularAverage;
   // �߹���Ӱ
   TFloat specularShadow;
   // �߹������ɫ (RGB=��ɫ��A=ǿ��)
   SFloatColor4 specularViewColor;
   // �ӽǸ߹����
   TFloat specularViewBase;
   // �ӽǸ߹����
   TFloat specularViewRate;
   // �ӽǸ߹�ƽ��
   TFloat specularViewAverage;
   // �ӽǸ߹���Ӱ
   TFloat specularViewShadow;
   // ������ɫ (RGB=��ɫ��A=ǿ��)
   SFloatColor4 reflectColor;
   // �����ں�
   TFloat reflectMerge;
   // ������Ӱ
   TFloat reflectShadow;
   // ����������ɫ (RGB=��ɫ��A=ǿ��)
   SFloatColor4 refractFrontColor;
   // ���������ں�
   TFloat refractFrontMerge;
   // ����������Ӱ
   TFloat refractFrontShadow;
   // ���䱳����ɫ (RGB=��ɫ��A=ǿ��)
   SFloatColor4 refractBackColor;
   // ���䱳���ں�
   TFloat refractBackMerge;
   // ���䱳����Ӱ
   TFloat refractBackShadow;
   // ��͸����ɫ (RGB=��ɫ��A=ǿ��)
   SFloatColor4 opacityColor;
   // ��͸������
   TFloat opacityRate;
   // ��͸��͸��
   TFloat opacityAlpha;
   // ��͸�����
   TFloat opacityDepth;
   // ��͸��͸��
   TFloat opacityTransmittance;
   // �Է�����ɫ
   SFloatColor4 emissiveColor;
   // �Է�������
   SFloatColor4 emissive;
public:
   SMaterialInfo();
   MO_ABSTRACT ~SMaterialInfo();
public:
   void AssignOption(SMaterialInfo* pMaterial);
   void AssignLight(SMaterialInfo* pMaterial);
   void Unserialize(IDataInput* pInput);
   void Reset();
};

//============================================================
// <T>��Դ3D��</T>
//============================================================
class MO_FR_DECLARE FResource3d : public FContent
{
   MO_CLASS_DECLARE_INHERITS(FResource3d, FContent);
protected:
   EResource3d _typeCd;
   TResourceHandle _handle;
   TString _code;
   TWideString _label;
   TFsName _name;
   TInt _timeout;
   TBool _statusOpen;
   TBool _statusReady;
public:
   FResource3d();
   MO_ABSTRACT ~FResource3d();
public:
   //------------------------------------------------------------
   // <T>������͡�</T>
   MO_INLINE EResource3d TypeCd(){
      return _typeCd;
   }
   //------------------------------------------------------------
   // <T>�������͡�</T>
   MO_INLINE void SetTypeCd(EResource3d typeCd){
      _typeCd = typeCd;
   }
   //------------------------------------------------------------
   // <T>��þ����</T>
   MO_INLINE TResourceHandle& Handle(){
      return _handle;
   }
   //------------------------------------------------------------
   // <T>��ô��롣</T>
   MO_INLINE TCharC* Code(){
      return _code;
   }
   //------------------------------------------------------------
   // <T>���ô��롣</T>
   MO_INLINE void SetCode(TCharC* pCode){
      _code = pCode;
   }
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
   // <T>��ó�ʱ��</T>
   MO_INLINE TInt Timeout(){
      return _timeout;
   }
   //------------------------------------------------------------
   // <T>���ó�ʱ��</T>
   MO_INLINE void SetTimeout(TInt timeout){
      _timeout = timeout;
   }
public:
   MO_ABSTRACT TBool TestReady();
   MO_ABSTRACT TBool TestValid();
public:
   MO_ABSTRACT TResult Unserialize(IDataInput* pInput);
public:
   MO_ABSTRACT TResult OnOpen();
   MO_ABSTRACT TResult OnClose();
public:
   TResult Open();
   TResult Close();
};
//------------------------------------------------------------
typedef MO_FR_DECLARE FVector<FResource3d*> FResource3dVector;
typedef MO_FR_DECLARE FList<FResource3d*> FResource3dList;
//typedef MO_FR_DECLARE FSet<TResourceId, FResource3d*> FResource3dSet;

//============================================================
// <T>��Դ3D����̨��</T>
//============================================================
class MO_FR_DECLARE FResource3dConsole : public FConsole
{
   MO_CLASS_DECLARE_INHERITS(FResource3dConsole, FInstance);
protected:
   FRs3dThemeConsole* _pThemeConsole;
   FRs3dTextureConsole* _pTextureConsole;
   FRs3dMaterialConsole* _pMaterialConsole;
   FRs3dModelConsole* _pModelConsole;
   FRs3dTemplateConsole* _pTemplateConsole;
   FRs3dSceneConsole* _pSceneConsole;
public:
   FResource3dConsole();
   MO_ABSTRACT ~FResource3dConsole();
public:
   //------------------------------------------------------------
   // <T>��������������</T>
   MO_INLINE FRs3dThemeConsole* ThemeConsole(){
      return _pThemeConsole;
   }
   //------------------------------------------------------------
   // <T>���ģ�͹�������</T>
   MO_INLINE FRs3dTextureConsole* TextureConsole(){
      return _pTextureConsole;
   }
   //------------------------------------------------------------
   // <T>��ò��ʹ�������</T>
   MO_INLINE FRs3dMaterialConsole* MaterialConsole(){
      return _pMaterialConsole;
   }
   //------------------------------------------------------------
   // <T>���ģ�͹�������</T>
   MO_INLINE FRs3dModelConsole* ModelConsole(){
      return _pModelConsole;
   }
   //------------------------------------------------------------
   // <T>���ģ���������</T>
   MO_INLINE FRs3dTemplateConsole* TemplateConsole(){
      return _pTemplateConsole;
   }
   //------------------------------------------------------------
   // <T>��ó�����������</T>
   MO_INLINE FRs3dSceneConsole* SceneConsole(){
      return _pSceneConsole;
   }
public:
   MO_ABSTRACT TResult Setup();
   MO_OVERRIDE TResult Startup();
   MO_OVERRIDE TResult Shutdown();
};

//============================================================
// <T>��Դ3D��������</T>
//============================================================
class MO_FR_DECLARE RResource3dManager : public RSingleton<FResource3dConsole>{
};

MO_NAMESPACE_END

//************************************************************
#endif // __MO_FR_CONTENT3D_BASE_H__
