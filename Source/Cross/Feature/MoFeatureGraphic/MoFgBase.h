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
#define MO_RENDERENUM_PARAMETER           "EnumRenderParameter"
#define MO_RENDERENUM_ATTRIBUTE           "EnumRenderAttribute"
#define MO_RENDERENUM_SAMPLER             "EnumRenderSampler"

//==========================================================
#define MO_RENDEROBJECT_LAYOUT            "Layout"
#define MO_RENDEROBJECT_BUFFER_VERTEX     "VertexBuffer"
#define MO_RENDEROBJECT_BUFFER_INDEX      "IndexBuffer"
#define MO_RENDEROBJECT_SHADER_VERTEX     "VertexShader"
#define MO_RENDEROBJECT_SHADER_FRAGMENT   "FragmentShader"
#define MO_RENDEROBJECT_PROGRAM_BUFFER    "ProgramBuffer"
#define MO_RENDEROBJECT_PROGRAM_PARAMETER "ProgramParameter"
#define MO_RENDEROBJECT_PROGRAM_ATTRIBUTE "ProgramAttribute"
#define MO_RENDEROBJECT_PROGRAM_SAMPLER   "ProgramSampler"
#define MO_RENDEROBJECT_PROGRAM_LAYOUT    "ProgramLayout"
#define MO_RENDEROBJECT_PROGRAM           "Program"
#define MO_RENDEROBJECT_TEXTURE_2D        "Texture2d"
#define MO_RENDEROBJECT_TEXTURE_3D        "Texture3d"
#define MO_RENDEROBJECT_TEXTURE_CUBE      "TextureCube"
#define MO_RENDEROBJECT_TARGET            "Target"

//==========================================================
#define MO_RENDER_ATTRIBUTE_MAXCNT        64

//==========================================================
class FMaterial;
class FRenderable;
class FRenderTexture;
typedef MO_FG_DECLARE FObjects<FRenderTexture*> FRenderTextureCollection;
class FRenderVertexStream;
class FRenderVertexStreams;
class FRenderIndexBuffer;
class FRenderLayout;
class FEffect;
typedef MO_FG_DECLARE FObjects<FEffect*> FEffectCollection;
typedef MO_FG_DECLARE FDictionary<FEffect*> FEffectDictionary;
class FRenderProgramLayout;
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
   ERenderDevice_OpenGL2,
   ERenderDevice_OpenGL3,
   ERenderDevice_OpenGL4,
   ERenderDevice_OpenGLEs2,
   ERenderDevice_OpenGLEs3,
};

//============================================================
// <T>��Ⱦ�豸���ߡ�</T>
//============================================================
class MO_FG_DECLARE RRenderDevice{
public:
   static ERenderDevice Parse(TCharC* pValue, ERenderDevice deviceCd = ERenderDevice_Unknown);
   static TCharC* Format(ERenderDevice deviceCd);
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
// <T>��Ⱦ�ű����ߡ�</T>
//============================================================
class MO_FG_DECLARE RRenderScript{
public:
   static ERenderScript Parse(TCharC* pValue, ERenderScript scriptCd = ERenderScript_Unknown);
   static TCharC* Format(ERenderScript scriptCd);
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
// <T>��Ⱦ���򻺳����͡�</T>
//============================================================
enum ERenderShaderBuffer{
   ERenderShaderBuffer_Unknown,
   ERenderShaderBuffer_Global,
   ERenderShaderBuffer_GlobalStatic,
   ERenderShaderBuffer_GlobalDynamic,
   ERenderShaderBuffer_Technique,
   ERenderShaderBuffer_TechniqueStatic,
   ERenderShaderBuffer_TechniqueDynamic,
   ERenderShaderBuffer_Effect,
   ERenderShaderBuffer_EffectStatic,
   ERenderShaderBuffer_EffectDynamic,
   ERenderShaderBuffer_Renderable,
   ERenderShaderBuffer_RenderableDynamic,
   ERenderShaderBuffer_RenderableMaterial,
   ERenderShaderBuffer_Count,
};

//============================================================
// <T>��Ⱦ���򻺳幤�ߡ�</T>
//============================================================
class MO_FG_DECLARE RRenderShaderBuffer{
public:
   static ERenderShaderBuffer Parse(TCharC* pValue, ERenderShaderBuffer bufferCd = ERenderShaderBuffer_Unknown);
   static ERenderShaderBuffer ParseGroup(ERenderShaderBuffer bufferCd);
   static TInt ParseSlot(ERenderShaderBuffer bufferCd);
   static TCharC* Format(ERenderShaderBuffer formatCd);
};

//============================================================
// <T>��Ⱦ���������͡�</T>
//============================================================
enum ERenderParameterFormat{
   ERenderParameterFormat_Unknown,
   ERenderParameterFormat_Float1,
   ERenderParameterFormat_Float2,
   ERenderParameterFormat_Float3,
   ERenderParameterFormat_Float4,
   ERenderParameterFormat_Float3x3,
   ERenderParameterFormat_Float4x3,
   ERenderParameterFormat_Float4x4,
};

//============================================================
// <T>��Ⱦ���������ߡ�</T>
//============================================================
class MO_FG_DECLARE RRenderParameterFormat{
public:
   static ERenderParameterFormat Parse(TCharC* pValue, ERenderParameterFormat formatCd = ERenderParameterFormat_Unknown);
   static TCharC* Format(ERenderParameterFormat formatCd);
};

//============================================================
// <T>��Ⱦ�����������͡�</T>
//============================================================
enum ERenderAttributeFormat{
   ERenderAttributeFormat_Unknown,
   ERenderAttributeFormat_Float1,
   ERenderAttributeFormat_Float2,
   ERenderAttributeFormat_Float3,
   ERenderAttributeFormat_Float4,
   ERenderAttributeFormat_Byte4,
   ERenderAttributeFormat_Byte4Normal,
};

//============================================================
// <T>��Ⱦ�������Թ��ߡ�</T>
//============================================================
class MO_FG_DECLARE RRenderAttributeFormat{
public:
   static ERenderAttributeFormat Parse(TCharC* pValue, ERenderAttributeFormat formatCd = ERenderAttributeFormat_Unknown);
   static TCharC* Format(ERenderAttributeFormat formatCd);
   static TInt CalculateSize(ERenderAttributeFormat formatCd);
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
// <T>��Ⱦ������Ϣ��</T>
//============================================================
class MO_FG_DECLARE FRenderableVisual : public FInstance
{
   MO_CLASS_DECLARE_INHERITS(FRenderableVisual, FInstance);
public:
   FRenderable* _pRenderable;
public:
   FRenderableVisual();
   MO_ABSTRACT ~FRenderableVisual();
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

//============================================================
// <T>��Ⱦ��־��</T>
//============================================================
class MO_FG_DECLARE SRenderableDescriptor{
public:
   // ����ʵ��
   TBool optionInstanced;
   // ���ð���
   TBool optionBinder;
   // ���ò���
   TBool optionMaterial;
   // ���÷���
   TBool optionNormal;
   // ���÷������� (�Ƿ��и����ߺ�����)
   TBool optionNormalFull;
   // ���÷������� (�Ƿ�ʹ�÷�������)
   TBool optionNormalScale;
   // ���ù�������
   TBool optionBoneScale;
   // �������
   TBool optionDepth;
   // ������Ӱ
   TBool optionShadow;
   // ��������Ӱ
   TBool optionShadowSelf;
   // ���ù�Դ��ͼ
   TBool optionLightMap;
   // ����͸��
   TBool optionTransmittance;
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
   // �������
   TBool vertexCount;
   // ��ͷ����
   TBool boneCount;
public:
   SRenderableDescriptor();
public:
   TResult Assign(SRenderableDescriptor* pFlag);
   TResult Build();
   TResult Reset();
};

//============================================================
// <T>��Ⱦ�������ԡ�</T>
//============================================================
class MO_FG_DECLARE FRenderableAttribute : public FInstance
{
   MO_CLASS_DECLARE_INHERITS(FRenderableAttribute, FInstance);
protected:
   // ��Ч��
   TBool _valid;
   // ����
   TString _code;
   // ���ݸ�ʽ
   ERenderAttributeFormat _formatCd;
   // ���ݻ����е�ƫ��λ��
   TInt _offset;
   // ͼԪ����
   GGraphicInstancePtr _graphicsObject;
   //TInt _slot;
public:
   FRenderableAttribute();
   MO_ABSTRACT ~FRenderableAttribute();
public:
   //------------------------------------------------------------
   // <T>�ж��Ƿ���Ч��</T>
   MO_INLINE TBool IsValid(){
      return _valid;
   }
   //------------------------------------------------------------
   // <T>�ж��Ƿ�ָ�����롣</T>
   MO_INLINE TBool IsCode(TCharC* pCode){
      return _code.Equals(pCode);
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
   // <T>����������͡�</T>
   MO_INLINE ERenderAttributeFormat FormatCd(){
      return _formatCd;
   }
   //------------------------------------------------------------
   // <T>�����������͡�</T>
   MO_INLINE void SetFormatCd(ERenderAttributeFormat formatCd){
      _formatCd = formatCd;
   }
   //------------------------------------------------------------
   // <T>���ƫ�ơ�</T>
   MO_INLINE TInt Offset(){
      return _offset;
   }
   //------------------------------------------------------------
   // <T>����ƫ�ơ�</T>
   MO_INLINE void SetOffset(TInt offset){
      _offset = offset;
   }
   //------------------------------------------------------------
   // <T>���ͼԪ����</T>
   MO_INLINE FGraphicInstance* GraphicsObject(){
      return _graphicsObject;
   }
   //------------------------------------------------------------
   // <T>���ͼԪ����</T>
   template <class T>
   MO_INLINE T* GraphicsObject(){
      return _graphicsObject->Convert<T>();
   }
   //------------------------------------------------------------
   // <T>����ͼԪ����</T>
   MO_INLINE void SetGraphicsObject(FGraphicInstance* pGraphicsObject){
      _graphicsObject = pGraphicsObject;
   }
   ////------------------------------------------------------------
   //// <T>��ò�ۡ�</T>
   //MO_INLINE TInt Slot(){
   //   return _slot;
   //}
   ////------------------------------------------------------------
   //// <T>���ò�ۡ�</T>
   //MO_INLINE void SetSlot(TInt slot){
   //   _slot = slot;
   //}
public:
   TBool CheckValid();
};
//------------------------------------------------------------
typedef MO_FG_DECLARE GPtr<FRenderableAttribute> GRenderableAttributePtr;
typedef MO_FG_DECLARE GPtrs<FRenderableAttribute> GRenderableAttributePtrs;

//============================================================
// <T>��Ⱦ���󼸺��塣</T>
//============================================================
class MO_FG_DECLARE FRenderableGeometry : public FInstance
{
   MO_CLASS_DECLARE_INHERITS(FRenderableGeometry, FInstance);
protected:
   // �������
   TInt _vertexCount;
   // ���Լ���
   GRenderableAttributePtrs _attributes;
   // ������
   FRenderIndexBuffer* _pIndexBuffer;
public:
   FRenderableGeometry();
   MO_ABSTRACT ~FRenderableGeometry();
public:
   //------------------------------------------------------------
   // <T>��ö��������</T>
   MO_INLINE TInt VertexCount(){
      return _vertexCount;
   }
   //------------------------------------------------------------
   // <T>���ö��������</T>
   MO_INLINE void SetVertexCount(TInt vertexCount){
      _vertexCount = vertexCount;
   }
   //------------------------------------------------------------
   // <T>������Լ��ϡ�</T>
   MO_INLINE GRenderableAttributePtrs& Attributes(){
      return _attributes;
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
public:
   FRenderableAttribute* AttributeFind(TCharC* pCode);
   FRenderableAttribute* AttributeGet(TCharC* pCode);
   TResult AttributePush(FRenderableAttribute* pAttribute);
   TResult AttributeRemove(FRenderableAttribute* pAttribute);
public:
   TResult Assign(FRenderableGeometry* pData);
};
//------------------------------------------------------------
typedef MO_FG_DECLARE GPtr<FRenderableGeometry> GRenderableGeometryPtr;

//============================================================
// <T>��Ⱦ����ȡ������</T>
//============================================================
class MO_FG_DECLARE FRenderableSampler : public FInstance
{
   MO_CLASS_DECLARE_INHERITS(FRenderableSampler, FInstance);
protected:
   TString _code;
   TString _packCode;
   TInt _slot;
   // ͼԪ����
   GGraphicInstancePtr _graphicsObject;
public:
   FRenderableSampler();
   MO_ABSTRACT ~FRenderableSampler();
public:
   //------------------------------------------------------------
   // <T>�ж��Ƿ�ָ�����롣</T>
   MO_INLINE TBool IsCode(TCharC* pCode){
      return _code.Equals(pCode);
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
   // <T>�ж��Ƿ�ָ��������롣</T>
   MO_INLINE TBool IsPackCode(TCharC* pPackCode){
      return _packCode.Equals(pPackCode);
   }
   //------------------------------------------------------------
   // <T>��ô�����롣</T>
   MO_INLINE TCharC* PackCode(){
      return _packCode;
   }
   //------------------------------------------------------------
   // <T>���ô�����롣</T>
   MO_INLINE void SetPackCode(TCharC* pPackCode){
      _packCode = pPackCode;
   }
   //------------------------------------------------------------
   // <T>��ò�ۡ�</T>
   MO_INLINE TInt Slot(){
      return _slot;
   }
   //------------------------------------------------------------
   // <T>���ò�ۡ�</T>
   MO_INLINE void SetSlot(TInt slot){
      _slot = slot;
   }
   //------------------------------------------------------------
   // <T>���ͼԪ����</T>
   MO_INLINE FGraphicInstance* GraphicsObject(){
      return _graphicsObject;
   }
   //------------------------------------------------------------
   // <T>���ͼԪ����</T>
   template <class T>
   MO_INLINE T* GraphicsObject(){
      return _graphicsObject->Convert<T>();
   }
   //------------------------------------------------------------
   // <T>����ͼԪ����</T>
   MO_INLINE void SetGraphicsObject(FGraphicInstance* pGraphicsObject){
      _graphicsObject = pGraphicsObject;
   }
};
//------------------------------------------------------------
typedef MO_FG_DECLARE GPtr<FRenderableSampler> GRenderableSamplerPtr;
typedef MO_FG_DECLARE GPtrs<FRenderableSampler> GRenderableSamplerPtrs;

//============================================================
// <T>��Ⱦ����Ч����</T>
//============================================================
struct MO_FG_DECLARE FRenderableEffect : FInstance
{
   MO_CLASS_DECLARE_INHERITS(FRenderableEffect, FInstance);
public:
   FEffect* _pEffect;
   FRenderLayout* _pLayout;
public:
   FRenderableEffect();
   MO_ABSTRACT ~FRenderableEffect();
public:
   //------------------------------------------------------------
   // <T>���Ч������</T>
   MO_INLINE FEffect* Effect(){
      return _pEffect;
   }
   //------------------------------------------------------------
   // <T>����Ч������</T>
   MO_INLINE void SetEffect(FEffect* pEffect){
      _pEffect = pEffect;
   }
   //------------------------------------------------------------
   // <T>��ò��֡�</T>
   MO_INLINE FRenderLayout* Layout(){
      return _pLayout;
   }
   //------------------------------------------------------------
   // <T>���ò��֡�</T>
   MO_INLINE void SetLayout(FRenderLayout* pLayout){
      _pLayout = pLayout;
   }
};
//------------------------------------------------------------
typedef MO_FG_DECLARE GPtrs<FRenderableEffect> GRenderableEffectPtrs;

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
   // ��Ⱦ��Ϣ
   FRenderableVisual* _pVisualInfo;
   // ����
   GMaterialPtr _material;
   // ���ò���
   GMaterialPtr _materialReference;
   // ����
   GRenderableGeometryPtr _geometry;
   // ȡ������
   GRenderableSamplerPtrs _samplers;
   // ����Ч����
   FRenderableEffect* _pActiveEffect;
   // Ч��������
   GRenderableEffectPtrs _effects;
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
   MO_OVERRIDE FRenderableVisual* VisualInfo(){
      return _pVisualInfo;
   }
   //------------------------------------------------------------
   // <T>���ÿɼ���Ϣ��</T>
   MO_INLINE void SetVisualInfo(FRenderableVisual* pVisualInfo){
      _pVisualInfo = pVisualInfo;
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
   // <T>��ü����塣</T>
   MO_INLINE FRenderableGeometry* Geometry(){
      return _geometry;
   }
   //------------------------------------------------------------
   // <T>���ü����塣</T>
   MO_INLINE void SetGeometry(FRenderableGeometry* pGeometry){
      return _geometry = pGeometry;
   }
   //------------------------------------------------------------
   // <T>������Լ��ϡ�</T>
   MO_INLINE GRenderableAttributePtrs& Attributes(){
      MO_ASSERT(_geometry);
      return _geometry->Attributes();
   }
   //------------------------------------------------------------
   // <T>�����������</T>
   MO_INLINE FRenderIndexBuffer* IndexBuffer(){
      MO_ASSERT(_geometry);
      return _geometry->IndexBuffer();
   }
   //------------------------------------------------------------
   // <T>������������</T>
   MO_INLINE void SetIndexBuffer(FRenderIndexBuffer* pIndexBuffer){
      MO_ASSERT(_geometry);
      _geometry->SetIndexBuffer(pIndexBuffer);
   }
   //------------------------------------------------------------
   // <T>���ȡ�����ϡ�</T>
   MO_INLINE GRenderableSamplerPtrs& Samplers(){
      return _samplers;
   }
   //------------------------------------------------------------
   // <T>��ü���Ч������</T>
   MO_OVERRIDE FRenderableEffect* ActiveEffect(){
      return _pActiveEffect;
   }
   //------------------------------------------------------------
   // <T>���ü���Ч������</T>
   MO_INLINE void SetActiveEffect(FRenderableEffect* pEffect){
      _pActiveEffect = pEffect;
   }
   //------------------------------------------------------------
   // <T>���Ч�������ϡ�</T>
   MO_OVERRIDE GRenderableEffectPtrs& Effects(){
      return _effects;
   }
public:
   TBool AttributeContains(TCharC* pCode);
   FRenderableAttribute* AttributeFind(TCharC* pCode);
   FRenderableAttribute* AttributeGet(TCharC* pCode);
   TBool SamplerContains(TCharC* pCode);
   FRenderableSampler* SamplerFind(TCharC* pCode);
   FRenderableSampler* SamplerGet(TCharC* pCode);
   FRenderableSampler* SamplerPackFind(TCharC* pPackCode);
   FRenderableSampler* SamplerPackGet(TCharC* pPackCode);
   TResult SamplerPush(FRenderableSampler* pSampler);
   TResult SamplerRemove(FRenderableSampler* pSampler);
   FRenderableEffect* EffectFind(TCharC* pName);
   FRenderableEffect* EffectBind(FEffect* pEffect);
public:
   MO_ABSTRACT TResult CalculateModelMatrix(SFloatMatrix3d& matrix);
   MO_ABSTRACT TInt CalculateBoneMatrix(SFloatMatrix3d* pMatrix, TInt offset = 0, TInt capacity = 0);
public:
   MO_ABSTRACT TResult Update(TAny* pParameter = NULL);
   MO_ABSTRACT TResult ProcessBefore(TAny* pParameter = NULL);
   MO_ABSTRACT TResult ProcessAfter(TAny* pParameter = NULL);
   MO_ABSTRACT TResult Free();
public:
   MO_OVERRIDE TResult Suspend();
   MO_OVERRIDE TResult Resume();
   MO_OVERRIDE TResult Dispose();
   MO_ABSTRACT TResult Track();
};
//------------------------------------------------------------
typedef MO_FG_DECLARE FObjects<FRenderable*> FRenderableCollection;
typedef MO_FG_DECLARE GPtrs<FRenderable> GRenderablePtrs;

MO_NAMESPACE_END

//************************************************************
#endif // __MO_FG_BASE_H__
