#ifndef __MO_FG_BASE_H__
#define __MO_FG_BASE_H__
//************************************************************

#ifndef __MO_FG_COMMON_H__
#include "MoFgCommon.h"
#endif // __MO_FG_COMMON_H__

#ifndef __MO_FG_CORE_H__
#include "MoFgCore.h"
#endif // __MO_FG_CORE_H__

MO_NAMESPACE_BEGIN

//==========================================================
#define MO_RENDEROBJECT_SHADERPARAMETER "ShaderParameter"
#define MO_RENDEROBJECT_SHADERATTRIBUTE "ShaderAttribute"
#define MO_RENDEROBJECT_SHADERSAMPLER   "ShaderSampler"
#define MO_RENDEROBJECT_VERTEXBUFFER    "VertexBuffer"
#define MO_RENDEROBJECT_INDEXBUFFER     "IndexBuffer"
#define MO_RENDEROBJECT_TEXTURE2D       "Texture2d"
#define MO_RENDEROBJECT_TEXTURE3D       "Texture3d"
#define MO_RENDEROBJECT_TARGET          "Target"
#define MO_RENDEROBJECT_VERTEXSHADER    "VertexShader"
#define MO_RENDEROBJECT_FRAGMENTSHADER  "FragmentShader"
#define MO_RENDEROBJECT_PROGRAM         "Program"

//==========================================================
class FMaterial;
class FRenderable;
class FRenderTexture;
typedef MO_FG_DECLARE FObjects<FRenderTexture*> FRenderTextureCollection;
class FRenderVertexStreams;
class FRenderIndexBuffer;
class FEffect;
typedef MO_FG_DECLARE FObjects<FEffect*> FEffectCollection;
typedef MO_FG_DECLARE FDictionary<FEffect*> FEffectDictionary;
class FRenderDevice;

//==========================================================
typedef TInt32 TColor;

//============================================================
// <T>��Ⱦ�豸���͡�</T>
//============================================================
enum ERenderDevice{
   ERenderDevice_Unknown,
   ERenderDevice_DirectX9,
   ERenderDevice_DirectX10,
   ERenderDevice_DirectX11,
   ERenderDevice_Opgl2,
   ERenderDevice_Opgl3,
   ERenderDevice_Opgl4,
   ERenderDevice_OpglEs2,
   ERenderDevice_OpglEs3,
};

//============================================================
// <T>��Ⱦ�ű����͡�</T>
//============================================================
enum ERenderScript{
   ERenderScript_Unknown,
   ERenderScript_Hlsl,
   ERenderScript_Glsl,
};

//============================================================
// <T>��Ⱦ��ģʽ��</T>
//============================================================
enum ERenderFillMode{
   ERenderFillMode_Unknown,
   ERenderFillMode_Point,
   ERenderFillMode_Line,
   ERenderFillMode_Fill,
};

//============================================================
// <T>��Ⱦ��ģʽ���ߡ�</T>
//============================================================
class MO_FG_DECLARE RRenderFillMode{
public:
   static ERenderFillMode Parse(TCharC* pValue, ERenderFillMode fillModeCd = ERenderFillMode_Fill);
   static TCharC* Format(ERenderFillMode fillModeCd);
};

//============================================================
// <T>��Ⱦ���ģʽ��</T>
//============================================================
enum ERenderDepthMode{
   ERenderDepthMode_None,
   ERenderDepthMode_Equal,
   ERenderDepthMode_NotEqual,
   ERenderDepthMode_Less,
   ERenderDepthMode_LessEqual,
   ERenderDepthMode_Greater,
   ERenderDepthMode_GreaterEqual,
   ERenderDepthMode_Always,
};

//============================================================
// <T>��Ⱦ���ģʽ���ߡ�</T>
//============================================================
class MO_FG_DECLARE RRenderDepthMode{
public:
   static ERenderDepthMode Parse(TCharC* pValue, ERenderDepthMode depthModeCd = ERenderDepthMode_None);
   static TCharC* Format(ERenderDepthMode depthModeCd);
};

//============================================================
// <T>��Ⱦ�޳�ģʽ��</T>
//============================================================
enum ERenderCullMode{
   ERenderCullMode_None,
   ERenderCullMode_Front,
   ERenderCullMode_Back,
   ERenderCullMode_Both,
};

//============================================================
// <T>��Ⱦ�޳�ģʽ���ߡ�</T>
//============================================================
class MO_FG_DECLARE RRenderCullMode{
public:
   static ERenderCullMode Parse(TCharC* pValue, ERenderCullMode cullModeCd = ERenderCullMode_Back);
   static TCharC* Format(ERenderCullMode cullModeCd);
};

//============================================================
// <T>��Ⱦ�ں�ģʽ��</T>
//============================================================
enum ERenderBlendMode{
   ERenderBlendMode_None,
   ERenderBlendMode_SourceAlpha,
   ERenderBlendMode_OneMinusSourceAlpha,
};

//============================================================
// <T>��Ⱦ�ں�ģʽ���ߡ�</T>
//============================================================
class MO_FG_DECLARE RRenderBlendMode{
public:
   static ERenderBlendMode Parse(TCharC* pValue, ERenderBlendMode blendModeCd = ERenderBlendMode_None);
   static TCharC* Format(ERenderBlendMode blendModeCd);
};

//============================================================
// <T>��Ⱦʹ��ģʽ��</T>
//============================================================
enum ERenderUsage{
   ERenderUsage_Unknown,
   ERenderUsage_Read,
   ERenderUsage_Write,
   ERenderUsage_ReadWrite,
};

//============================================================
// <T>��Ⱦ�����ʽ��</T>
//============================================================
enum ERenderVertexFormat{
   ERenderVertexFormat_Unknown = 0,
   ERenderVertexFormat_Float1 = 1,
   ERenderVertexFormat_Float2 = 2,
   ERenderVertexFormat_Float3 = 3,
   ERenderVertexFormat_Float4 = 4,
   ERenderVertexFormat_Byte4 = 5,
   ERenderVertexFormat_ByteNormal4 = 6,
};

//============================================================
// <T>��Ⱦ��ģʽ���ߡ�</T>
//============================================================
class MO_FG_DECLARE RRenderVertexFormat{
public:
   static ERenderVertexFormat Parse(TCharC* pValue, ERenderVertexFormat formatCd = ERenderVertexFormat_Unknown);
   static TCharC* Format(ERenderVertexFormat formatCd);
};

//============================================================
// <T>��Ⱦ���㻺�塣</T>
//============================================================
enum ERenderVertexBuffer{
   ERenderVertexBuffer_Unknown = 0,
   ERenderVertexBuffer_Instance = 1,
   ERenderVertexBuffer_Position = 2,
   ERenderVertexBuffer_Color = 3,
   ERenderVertexBuffer_Coord = 4,
   ERenderVertexBuffer_CoordLight = 5,
   ERenderVertexBuffer_Normal = 6,
   ERenderVertexBuffer_Binormal = 7,
   ERenderVertexBuffer_Tangent = 8,
   ERenderVertexBuffer_BoneIndex = 9,
   ERenderVertexBuffer_BoneWeight = 10,
   ERenderVertexBuffer_Count = 11,
};

//============================================================
// <T>��Ⱦ���㻺�幤�ߡ�</T>
//============================================================
class MO_FG_DECLARE RRenderVertexBuffer{
public:
   static ERenderVertexBuffer Parse(TCharC* pValue, ERenderVertexBuffer bufferCd = ERenderVertexBuffer_Unknown);
   static TCharC* Format(ERenderVertexBuffer bufferCd);
};

//============================================================
// <T>��Ⱦ������ȡ�</T>
//============================================================
enum ERenderIndexStride{
   ERenderIndexStride_Unknown = 0,
   ERenderIndexStride_Uint16 = 1,
   ERenderIndexStride_Uint32 = 2,
};

//============================================================
// <T>��Ⱦ�������͡�</T>
//============================================================
enum ERenderShader{
   ERenderShader_Unknown,
   ERenderShader_Vertex,
   ERenderShader_Fragment,
};

//============================================================
// <T>��Ⱦ�������͹��ߡ�</T>
//============================================================
class MO_FG_DECLARE RRenderShader{
public:
   static ERenderShader Parse(TCharC* pValue, ERenderShader shaderCd = ERenderShader_Unknown);
   static TCharC* Format(ERenderShader shaderCd);
};

//============================================================
// <T>��Ⱦ���������͡�</T>
//============================================================
enum ERenderShaderParameterFormat{
   ERenderShaderParameterFormat_Unknown,
   ERenderShaderParameterFormat_Float1,
   ERenderShaderParameterFormat_Float2,
   ERenderShaderParameterFormat_Float3,
   ERenderShaderParameterFormat_Float4,
   ERenderShaderParameterFormat_Float3x3,
   ERenderShaderParameterFormat_Float4x3,
   ERenderShaderParameterFormat_Float4x4,
};

//============================================================
// <T>��Ⱦ���������ߡ�</T>
//============================================================
class MO_FG_DECLARE RRenderShaderParameterFormat{
public:
   static ERenderShaderParameterFormat Parse(TCharC* pValue, ERenderShaderParameterFormat formatCd = ERenderShaderParameterFormat_Unknown);
   static TCharC* Format(ERenderShaderParameterFormat formatCd);
};

//============================================================
// <T>��Ⱦ�����������͡�</T>
//============================================================
enum ERenderShaderAttributeFormat{
   ERenderShaderAttributeFormat_Unknown,
   ERenderShaderAttributeFormat_Float1,
   ERenderShaderAttributeFormat_Float2,
   ERenderShaderAttributeFormat_Float3,
   ERenderShaderAttributeFormat_Float4,
   ERenderShaderAttributeFormat_Byte4,
   ERenderShaderAttributeFormat_Byte4Normal,
};

//============================================================
// <T>��Ⱦ�������Թ��ߡ�</T>
//============================================================
class MO_FG_DECLARE RRenderShaderAttributeFormat{
public:
   static ERenderShaderAttributeFormat Parse(TCharC* pValue, ERenderShaderAttributeFormat formatCd = ERenderShaderAttributeFormat_Unknown);
   static TCharC* Format(ERenderShaderAttributeFormat formatCd);
};

//============================================================
// <T>��Ⱦ�������͡�</T>
//============================================================
enum ERenderTexture{
   ERenderTexture_Unknown,
   ERenderTexture_Flat2d,
   ERenderTexture_Flat3d,
   ERenderTexture_Cube,
};

//============================================================
// <T>��Ⱦȡ�������͡�</T>
//============================================================
enum ERenderSampler{
   ERenderSampler_Unknown,
   ERenderSampler_Ambient,
   ERenderSampler_Diffuse,
   ERenderSampler_Alpha,
   ERenderSampler_Normal,
   ERenderSampler_Height,
   ERenderSampler_SpecularColor,
   ERenderSampler_SpecularLevel,
   ERenderSampler_TransmittanceColor,
   ERenderSampler_TransmittanceLevel,
   ERenderSampler_Light,
   ERenderSampler_Reflect,
   ERenderSampler_Refract,
   ERenderSampler_Emissive,
   ERenderSampler_Environment,
   ERenderSampler_LayerMerge,
   ERenderSampler_Layer1,
   ERenderSampler_Layer2,
   ERenderSampler_Layer3,
   ERenderSampler_Layer4,
   ERenderSampler_PackDiffuse,
   ERenderSampler_PackNormal,
   ERenderSampler_PackSpecular,
   ERenderSampler_PackTransmittance,
   ERenderSampler_PackLight,
   ERenderSampler_LightDepth,
   ERenderSampler_Count,
};

//============================================================
// <T>��Ⱦȡ�������͹��ߡ�</T>
//============================================================
class MO_FG_DECLARE RRenderSampler{
public:
   static ERenderSampler Parse(TCharC* pValue, ERenderSampler samplerCd = ERenderSampler_Unknown);
   static TCharC* Format(ERenderSampler samplerCd);
};

//============================================================
// <T>��Ⱦ�����ʽ��</T>
//============================================================
enum ERenderTextureFormat{
   ERenderTextureFormat_Unknown,
   ERenderTextureFormat_BGRA,
   ERenderTextureFormat_A8R8B8G8,
   ERenderTextureFormat_A32R32G32B32,
   ERenderTextureFormat_Depth,
};

//============================================================
// <T>��Ⱦ������ˡ�</T>
//============================================================
enum ERenderTextureFilter{
   ERenderTextureFilter_None,
   ERenderTextureFilter_Nearest,
   ERenderTextureFilter_Linear,
};

//============================================================
// <T>��Ⱦ����չ����</T>
//============================================================
enum ERenderTextureWrap{
   ERenderTextureWrap_None,
   ERenderTextureWrap_Clamp,
   ERenderTextureWrap_Repeat,
};

//============================================================
// <T>Ч���������ԡ�</T>
//============================================================
enum EEffectVertexAttribute{
   EEffectVertexAttribute_Unknown,
   EEffectVertexAttribute_Position,
   EEffectVertexAttribute_Color,
   EEffectVertexAttribute_Coord,
   EEffectVertexAttribute_Normal,
   EEffectVertexAttribute_Binormal,
   EEffectVertexAttribute_Tangent,
   EEffectVertexAttribute_BoneIndex,
   EEffectVertexAttribute_BoneWeight,
   EEffectVertexAttribute_Count,
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
class MO_FG_DECLARE REffectSampler{
public:
   static EEffectSampler Parse(TCharC* pValue, EEffectSampler samplerCd = EEffectSampler_Diffuse);
   static TCharC* Format(EEffectSampler samplerCd);
};

//============================================================
// <T>��Ⱦ��Ϣ��</T>
//============================================================
class MO_FG_DECLARE FRenderableInfo : public FInstance
{
   MO_CLASS_DECLARE_INHERITS(FRenderableInfo, FInstance);
public:
   FRenderable* _pRenderable;
public:
   FRenderableInfo();
   MO_ABSTRACT ~FRenderableInfo();
public:
   //------------------------------------------------------------
   // <T>�����Ⱦ����</T>
   MO_INLINE FRenderable* Renderable(){
      return _pRenderable;
   }
   //------------------------------------------------------------
   // <T>������Ⱦ����</T>
   MO_INLINE void SetRenderable(FRenderable* pRenderable){
      _pRenderable = pRenderable;
   }
};
//------------------------------------------------------------
typedef MO_FG_DECLARE FObjects<FRenderableInfo*> FRenderableInfoCollection;

//============================================================
// <T>��Ⱦ��־��</T>
//============================================================
class MO_FG_DECLARE SRenderableDescriptor{
public:
   TBool setuped;
public:
   // ����ʵ��
   TBool optionInstanced;
   // ���ð���
   TBool optionBinder;
   // ���ò���
   TBool optionMaterial;
   //// ���÷���
   //TBool optionNormal;
   //// ���÷������� (�Ƿ��и����ߺ�����)
   //TBool optionNormalFull;
   //// ���÷������� (�Ƿ�ʹ�÷�������)
   //TBool optionNormalScale;
   //// ���ù�������
   //TBool optionBoneScale;
   //// �������
   //TBool optionDepth;
   // ������Ӱ
   TBool optionShadow;
   // ��������Ӱ
   TBool optionShadowSelf;
   //// ���ù�Դ��ͼ
   //TBool optionLightMap;
   //// ����͸��
   //TBool optionTransmittance;
public:
   // ֧�ֶ�����ɫ����
   TBool supportVertexColor;
   // ֧�ֶ���������
   TBool supportVertexCoord;
   // ֧�ַ��߼���
   TBool supportVertexNormal;
   // ֧�ָ����߼���
   TBool supportVertexNormalFull;
   // ֧�ֹ�ͷ����
   TBool supportVertexBone;
public:
   // ֧��͸������
   TBool supportAlpha;
   // ֧�ְ�͹����
   TBool supportBump;
   // ֧�ֻ�������
   TBool supportAmbient;
   // ֧��ɢ�似��
   TBool supportDiffuse;
   // ֧�ַ��߼���
   TBool supportNormal;
   // ֧�ָ߹⼼��
   TBool supportSpecularColor;
   // ֧�ָ߹⼶����
   TBool supportSpecularLevel;
   // ֧�ֻ�������
   TBool supportEnvironment;
   // ֧���ܹ�⼼��
   TBool supportLight;
   // ֧�ַ��似��
   TBool supportReflect;
   // ֧�����似��
   TBool supportRefract;
   // ֧�ַ��⼼��
   TBool supportEmissive;
   // ֧�ָ߶ȼ���
   TBool supportHeight;
   //// ֧�ֻ���ɢ�似��
   //TBool supportDiffuseCamera;
   //// ֧�ְ�͹�������
   //TBool supportBumpCamera;
   //// ֧�ָ߹��������
   //TBool supportSpecularCamera;
   //// ֧�ָ߹����������
   //TBool supportSpecularCameraLevel;
public:
   // �������
   TBool vertexCount;
   // ��ͷ����
   TBool boneCount;
public:
   // ���㻺��
   TBool vertexBuffers[ERenderVertexBuffer_Count];
   // ȡ��������
   TBool samplers[ERenderSampler_Count];
public:
   SRenderableDescriptor();
public:
   //------------------------------------------------------------
   // <T>�����Ƿ���ָ�����塣</T>
   MO_INLINE TBool ContainsBuffer(ERenderVertexBuffer bufferCd){
      return vertexBuffers[bufferCd];
   }
   //------------------------------------------------------------
   // <T>�����Ƿ���ָ��ȡ������</T>
   MO_INLINE TBool ContainsSampler(ERenderSampler samplerCd){
      return samplers[samplerCd];
   }
public:
   void Assign(SRenderableDescriptor* pFlag);
   void Build();
   void Reset();
};

//============================================================
// <T>��Ⱦ��Ŀ��Ϣ��</T>
//============================================================
struct MO_FG_DECLARE SRenderableItem{
public:
   // ����
   SFloatPoint3 location;
   // �ߴ�
   SFloatSize3 size;
   // ��ת
   SFloatVector3 rotation;
   // ������ɫ
   SFloatColor4 groundColor;
   // ��������
   SFloatCoord coord;
   // ����
   SFloatMatrix3d matrix;
public:
   //------------------------------------------------------------
   // <T>���측������ɫ��</T>
   MO_INLINE SRenderableItem(){
   }
};
//------------------------------------------------------------
typedef MO_FG_DECLARE TFixVector<SRenderableItem, 64> SRenderableItems;

//============================================================
// <T>��Ⱦ��Ϣ��</T>
//============================================================
struct MO_FG_DECLARE SRenderable{
public:
   SRenderableItems items;
public:
   //------------------------------------------------------------
   // <T>���측������ɫ��</T>
   MO_INLINE SRenderable(){
   }
public:
   //------------------------------------------------------------
   // <T>�ռ�һ����Ŀ��</T>
   MO_INLINE SRenderableItem& Alloc(){
      TInt index = items.Count();
      items.SetCount(index + 1);
      return items.Get(index);
   }
   //------------------------------------------------------------
   // <T>����Ҫ����Ŀ��</T>
   MO_INLINE void Push(SRenderableItem& item){
      items.Push(item);
   }
};

//============================================================
// <T>����Ⱦ����</T>
//============================================================
class MO_FG_DECLARE FRenderable : public FInstance
{
   MO_CLASS_DECLARE_INHERITS(FRenderable, FInstance);
protected:
   // ����
   TString _name;
   // ��������
   TString _typeName;
   // �任����
   SMatrix3d _matrix;
   // ��־����
   SRenderableDescriptor _descriptor;
   // ����
   GPtr<FMaterial> _material;
   // ����
   GPtr<FMaterial> _materialReference;
   // ��Ⱦ��Ϣ
   FRenderableInfo* _pVisualInfo;
   // ������
   FRenderTextureCollection* _pTextures;
   // ����������
   FRenderVertexStreams* _pVertexStreams;
   // ������
   FRenderIndexBuffer* _pIndexBuffer;
   // ����Ч����
   FEffect* _pActiveEffect;
   // Ч��������
   FEffectCollection* _pEffects;
public:
   FRenderable();
   MO_ABSTRACT ~FRenderable();
public:
   //------------------------------------------------------------
   // <T>������ơ�</T>
   MO_OVERRIDE TCharC* Name(){
      return _name;
   }
   //------------------------------------------------------------
   // <T>�������ơ�</T>
   MO_OVERRIDE void SetName(TCharC* pName){
      _name = pName;
   }
   //------------------------------------------------------------
   // <T>����������ơ�</T>
   MO_OVERRIDE TCharC* TypeName(){
      return _typeName;
   }
   //------------------------------------------------------------
   // <T>�����������ơ�</T>
   MO_OVERRIDE void SetTypeName(TCharC* pTypeName){
      _typeName = pTypeName;
   }
   //------------------------------------------------------------
   // <T>��þ���</T>
   MO_OVERRIDE SMatrix3d& Matrix(){
      return _matrix;
   }
   //------------------------------------------------------------
   // <T>��ñ�־���ϡ�</T>
   MO_OVERRIDE SRenderableDescriptor& Descriptor(){
      return _descriptor;
   }
   //------------------------------------------------------------
   // <T>��ÿɼ���Ϣ��</T>
   MO_OVERRIDE FRenderableInfo* VisualInfo(){
      return _pVisualInfo;
   }
   //------------------------------------------------------------
   // <T>���ÿɼ���Ϣ��</T>
   MO_INLINE void SetVisualInfo(FRenderableInfo* pVisualInfo){
      _pVisualInfo = pVisualInfo;
   }
   //------------------------------------------------------------
   // <T>������ò��ʡ�</T>
   MO_OVERRIDE FMaterial* MaterialReference(){
      return _materialReference;
   }
   //------------------------------------------------------------
   // <T>�������ò��ʡ�</T>
   MO_INLINE void SetMaterialReference(FMaterial* pMaterialReference){
      _materialReference = pMaterialReference;
   }
   //------------------------------------------------------------
   // <T>��ò��ʡ�</T>
   MO_OVERRIDE FMaterial* Material(){
      return _material;
   }
   //------------------------------------------------------------
   // <T>���ò��ʡ�</T>
   MO_INLINE void SetMaterial(FMaterial* pMaterial){
      _material = pMaterial;
   }
   //------------------------------------------------------------
   // <T>��������ϡ�</T>
   MO_INLINE FRenderTextureCollection* Textures(){
      return _pTextures;
   }
   //------------------------------------------------------------
   // <T>��ö��������ϡ�</T>
   MO_INLINE FRenderVertexStreams* VertexStreams(){
      return _pVertexStreams;
   }
   //------------------------------------------------------------
   // <T>���ö��������ϡ�</T>
   MO_INLINE void SetVertexStreams(FRenderVertexStreams* pVertexStreams){
      _pVertexStreams = pVertexStreams;
   }
   //------------------------------------------------------------
   // <T>�����������</T>
   MO_INLINE FRenderIndexBuffer* IndexBuffer(){
      return _pIndexBuffer;
   }
   //------------------------------------------------------------
   // <T>������������</T>
   MO_INLINE void SetIndexBuffer(FRenderIndexBuffer* pIndexBuffer){
      _pIndexBuffer = pIndexBuffer;
   }
   //------------------------------------------------------------
   // <T>��ü���Ч������</T>
   MO_OVERRIDE FEffect* ActiveEffect(){
      return _pActiveEffect;
   }
   //------------------------------------------------------------
   // <T>���ü���Ч������</T>
   MO_INLINE void SetActiveEffect(FEffect* pEffect){
      _pActiveEffect = pEffect;
   }
   //------------------------------------------------------------
   // <T>���Ч�������ϡ�</T>
   MO_OVERRIDE FEffectCollection* Effects(){
      return _pEffects;
   }
public:
   FEffect* EffectFind(TCharC* pName);
   TResult EffectBind(FEffect* pEffect);
public:
   MO_ABSTRACT TResult CalculateModelMatrix(SFloatMatrix3d& matrix);
   MO_ABSTRACT TInt CalculateBoneMatrix(SFloatMatrix3d* pMatrix, TInt offset = 0, TInt capacity = 0);
   MO_ABSTRACT TResult BuildDescriptor();
   FRenderTexture* FindTexture(ERenderSampler samplerCd);
   FRenderTexture* GetTexture(ERenderSampler samplerCd);
public:
   MO_ABSTRACT TResult Update(TAny* pParameter = NULL);
   MO_ABSTRACT TResult ProcessBefore(TAny* pParameter = NULL);
   MO_ABSTRACT TResult ProcessAfter(TAny* pParameter = NULL);
   MO_ABSTRACT TResult Free();
public:
   MO_OVERRIDE TResult Suspend();
   MO_OVERRIDE TResult Resume();
   MO_OVERRIDE TResult Dispose();
};
//------------------------------------------------------------
typedef MO_FG_DECLARE FObjects<FRenderable*> FRenderableCollection;
typedef MO_FG_DECLARE GPtrs<FRenderable> GRenderablePtrs;

MO_NAMESPACE_END

//************************************************************
#endif // __MO_FG_BASE_H__
