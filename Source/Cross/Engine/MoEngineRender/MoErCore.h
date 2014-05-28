#ifndef __MO_ER_CORE_H__
#define __MO_ER_CORE_H__
//************************************************************

#ifndef __MO_ER_COMMON_H__
#include "MoErCommon.h"
#endif // __MO_ER_COMMON_H__

#define MO_ER_EFFECT_PARAMETER_MAXCNT 256
#define MO_ER_EFFECT_ATTRIBUTE_MAXCNT 32
#define MO_ER_EFFECT_SAMPLER_MAXCNT   32

#define MO_ER_ATTRIBUTE_COLOR    TC("Color")
#define MO_ER_ATTRIBUTE_COORD    TC("Coord")
#define MO_ER_ATTRIBUTE_NORMAL   TC("Normal")
#define MO_ER_ATTRIBUTE_BINORMAL TC("Binormal")
#define MO_ER_ATTRIBUTE_TANGENT  TC("Tangent")

#define MO_ER_SAMPLER_DIFFUSE        TC("Diffuse")
#define MO_ER_SAMPLER_ALPHA          TC("Alpha")

#define MO_ER_SAMPLER_NORMAL         TC("Normal")
#define MO_ER_SAMPLER_SPECULAR_LEVEL TC("SpecularLevel")

#define MO_ER_SAMPLER_SPECULAR_COLOR TC("SpecularColor")
#define MO_ER_SAMPLER_HEIGHT         TC("Height")

#define MO_ER_SAMPLER_LIGHT          TC("Light")
#define MO_ER_SAMPLER_REFLECT        TC("Reflect")
#define MO_ER_SAMPLER_REFRACT        TC("Refract")
#define MO_ER_SAMPLER_EMISSIVE       TC("Emissive")

#define MO_ER_SAMPLER_ENVIRONMENT    TC("Environment")

MO_NAMESPACE_BEGIN

//============================================================
// <T>Ч���������塣</T>
//============================================================
enum EEffectParameterBuffer{
   EEffectParameterBuffer_Unknown,
   // ȫ�ֻ���
   EEffectParameterBuffer_Global,
   // Ч������
   EEffectParameterBuffer_EffectCamera,
   EEffectParameterBuffer_EffectLight,
   // ��Ⱦ����
   EEffectParameterBuffer_RenderTramsform,
   EEffectParameterBuffer_RenderMaterial,
   EEffectParameterBuffer_Count,
};

//============================================================
// <T>Ч���������ߡ�</T>
//============================================================
class MO_ER_DECLARE REffectParameterBuffer{
public:
   static TResult Parse(TCharC* pValue, EEffectParameterBuffer& bufferCd, TInt& slot);
   static TCharC* Format(EEffectParameterBuffer bufferCd);
};

//============================================================
// <T>Ч��������</T>
//============================================================
enum EEffectParameter{
   // δ֪
   EEffectParameter_Unknown,
   // �任����
   EEffectParameter_VertexInstance,
   EEffectParameter_VertexModelMatrix3x3,
   EEffectParameter_VertexModelMatrix4x4,
   EEffectParameter_VertexViewMatrix4x4,
   EEffectParameter_VertexProjectionMatrix4x4,
   EEffectParameter_VertexViewProjectionMatrix4x4,
   EEffectParameter_VertexModelViewProjectionMatrix3x3,
   EEffectParameter_VertexModelViewProjectionMatrix4x4,
   EEffectParameter_VertexBoneMatrix4x3,
   EEffectParameter_VertexBoneMatrix4x4,
   // �������
   EEffectParameter_VertexCameraPosition,
   EEffectParameter_VertexCameraDirection,
   // ��Դ����
   EEffectParameter_VertexLightModelMatrix4x4,
   EEffectParameter_VertexLightModelViewMatrix4x4,
   EEffectParameter_VertexLightModelViewProjectionMatrix4x4,
   EEffectParameter_VertexLightPosition,
   EEffectParameter_VertexLightDirection,
   //............................................................
   // �������
   EEffectParameter_FragmentCamera,
   EEffectParameter_FragmentCameraPosition,
   EEffectParameter_FragmentCameraDirection,
   // ��Դ����
   EEffectParameter_FragmentLightModelMatrix4x4,
   EEffectParameter_FragmentLightModelViewProjectrionMatrix4x4,
   EEffectParameter_FragmentLightPosition,
   EEffectParameter_FragmentLightDirection,
   EEffectParameter_FragmentLightDepth,
   // ���ʲ���
   EEffectParameter_FragmentShadowMaterial,
   EEffectParameter_FragmentShadowMaterialInv,
   EEffectParameter_FragmentColor,
   EEffectParameter_FragmentAlpha,
   EEffectParameter_FragmentVertexColor,
   EEffectParameter_FragmentAmbientColor,
   EEffectParameter_FragmentDiffuseColor,
   EEffectParameter_FragmentDiffuseViewColor,
   EEffectParameter_FragmentSpecularColor,
   EEffectParameter_FragmentSpecular,
   EEffectParameter_FragmentSpecularViewColor,
   EEffectParameter_FragmentSpecularView,
   EEffectParameter_FragmentReflectColor,
   //............................................................
   EEffectParameter_Count,
};

//============================================================
// <T>Ч���������ߡ�</T>
//============================================================
class MO_ER_DECLARE REffectParameter{
public:
   static TResult Parse(TCharC* pValue, EEffectParameter& parameterCd, ERenderShader& shaderCd, ERenderParameterFormat& formatCd);
   static TCharC* Format(EEffectParameter parameterCd);
};

//============================================================
// <T>Ч�����ԡ�</T>
//============================================================
enum EEffectAttribute{
   EEffectAttribute_Unknown,
   EEffectAttribute_Instance,
   EEffectAttribute_Position,
   EEffectAttribute_Color,
   EEffectAttribute_Coord,
   EEffectAttribute_CoordLight,
   EEffectAttribute_Normal,
   EEffectAttribute_Binormal,
   EEffectAttribute_Tangent,
   EEffectAttribute_BoneIndex,
   EEffectAttribute_BoneWeight,
   EEffectAttribute_Count,
};

//============================================================
// <T>Ч�����Թ��ߡ�</T>
//============================================================
class MO_ER_DECLARE REffectAttribute{
public:
   static TResult Parse(TCharC* pValue, EEffectAttribute& attributeCd, ERenderAttributeFormat& formatCd);
   static TCharC* Format(EEffectAttribute attributeCd);
};

//============================================================
// <T>Ч��ȡ�������͡�</T>
//============================================================
enum EEffectSampler{
   EEffectSampler_Diffuse,
   EEffectSampler_Normal,
   EEffectSampler_Specular,
   EEffectSampler_Light,
   EEffectSampler_Environment,
   EEffectSampler_LightDepth,
   EEffectSampler_Count,
};

//============================================================
// <T>Ч��ȡ�������͹��ߡ�</T>
//============================================================
class MO_ER_DECLARE REffectSampler{
public:
   static EEffectSampler Parse(TCharC* pValue, EEffectSampler samplerCd = EEffectSampler_Diffuse);
   static TCharC* Format(EEffectSampler samplerCd);
};

MO_NAMESPACE_END

//************************************************************
#endif // __MO_ER_CORE_H__
