#ifndef __MO_FG_TECHNIQUE_H__
#define __MO_FG_TECHNIQUE_H__
//************************************************************

#ifndef __MO_FG_COMMON_H__
#include "MoFgCommon.h"
#endif // __MO_FG_COMMON_H__

#ifndef __MO_FG_BASE_H__
#include "MoFgBase.h"
#endif // __MO_FG_BASE_H__

#ifndef __MO_FG_RENDER_H__
#include "MoFgRender.h"
#endif // __MO_FG_RENDER_H__

#define MO_EG_EFFECT_CONST_MAXCNT     64
#define MO_EG_EFFECT_ATTRIBUTE_MAXCNT 32
#define MO_EG_EFFECT_SAMPLER_MAXCNT   16

MO_NAMESPACE_BEGIN

//============================================================
// <T>��Ⱦ������Ϣ��</T>
//============================================================
class MO_FG_DECLARE SEffectDescriptor{
public:
   // ����
   TCharC* namePtr;
public:
   ERenderFillMode fillModeCd;
   TBool optionCullMode;
   ERenderCullMode cullModeCd;
   TBool optionDepthTest;
   ERenderDepthMode depthModeCd;
   TBool optionDepthWrite;
   TBool optionBlendMode;
   ERenderBlendMode blendSourceMode;
   ERenderBlendMode blendTargetMode;
   TBool optionAlphaTest;
public:
   // ֧��ʵ������
   TBool supportInstance;
   // ֧�ֶ�����ɫ
   TBool supportVertexColor;
   // ֧�ֶ�������
   TBool supportVertexCoord;
   // ֧�ַ���
   TBool supportVertexNormal;
   // ֧��ȫ����
   TBool supportVertexNormalFull;
   // ֧�ֹ�������
   TBool supportSkeleton;
public:
   // ֧��͸������
   TBool supportAlpha;
   // ֧�ְ�͹����
   TBool supportBump;
   // ֧�ֻ���ɫ����
   TBool supportAmbient;
   // ֧��ɢ�似��
   TBool supportDiffuse;
   // ֧�ֻ���ɢ�似��
   TBool supportDiffuseView;
   // ֧�ָ߹���ɫ����
   TBool supportSpecularColor;
   // ֧�ָ߹⼶����
   TBool supportSpecularLevel;
   // ֧�ָ߹��������
   TBool supportSpecularView;
   // ֧�ֻ�������
   TBool supportEnvironment;
   // ֧���չ⼼��
   TBool supportLight;
   // ֧�ַ��似��
   TBool supportReflect;
   // ֧�����似��
   TBool supportRefract;
   // ֧�ַ��⼼��
   TBool supportEmissive;
   // ֧�ָ߶ȼ���
   TBool supportHeight;
public:
   SEffectDescriptor();
public:
   TResult LoadConfig(FXmlNode* pConfig);
};

//============================================================
// <T>��ȾЧ��������</T>
//============================================================
class MO_FG_DECLARE FEffectContext : public FObject{
public:
   FEffectContext();
   MO_ABSTRACT ~FEffectContext();
};

//============================================================
// <T>��ȾЧ����</T>
//============================================================
class MO_FG_DECLARE FEffect : public FInstance
{
   MO_CLASS_DECLARE_INHERITS(FEffect, FInstance);
protected:
   TString _name;
   TString _flag;
   TString _vertexSource;
   TString _fragmentSource;
   SEffectDescriptor _descriptor;
   GPtr<FRenderProgram> _program;
   GPtr<FRenderDevice> _renderDevice;
public:
   FEffect();
   MO_ABSTRACT ~FEffect();
public:
   //------------------------------------------------------------
   // <T>�ж��Ƿ�ָ�����ơ�</T>
   MO_INLINE TBool IsName(TCharC* pName){
      return _name.Equals(pName);
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
   // <T>��ñ�־��</T>
   MO_INLINE TCharC* Flag(){
      return _flag;
   }
   //------------------------------------------------------------
   // <T>���ñ�־��</T>
   MO_INLINE void SetFlag(TCharC* pFlag){
      _flag = pFlag;
   }
   //------------------------------------------------------------
   // <T>��ö�����롣</T>
   MO_INLINE TCharC* VertexSource(){
      return _vertexSource;
   }
   //------------------------------------------------------------
   // <T>���ö�����롣</T>
   MO_INLINE void SetVertexSource(TCharC* pSource){
      _vertexSource = pSource;
   }
   //------------------------------------------------------------
   // <T>������ش��롣</T>
   MO_INLINE TCharC* FragmentSource(){
      return _fragmentSource;
   }
   //------------------------------------------------------------
   // <T>�������ش��롣</T>
   MO_INLINE void SetFragmentSource(TCharC* pSource){
      _fragmentSource = pSource;
   }
   //------------------------------------------------------------
   // <T>�����Ⱦ������</T>
   MO_INLINE SEffectDescriptor& Descriptor(){
      return _descriptor;
   }
   //------------------------------------------------------------
   // <T>��ó���</T>
   MO_INLINE FRenderProgram* Program(){
      return _program;
   }
   //------------------------------------------------------------
   // <T>�����Ⱦ�豸��</T>
   MO_INLINE FRenderDevice* RenderDevice(){
      return _renderDevice;
   }
   //------------------------------------------------------------
   // <T>������Ⱦ�豸��</T>
   MO_INLINE void SetRenderDevice(FRenderDevice* pRenderDevice){
      _renderDevice = pRenderDevice;
   }
public:
   MO_ABSTRACT TResult Setup();
   MO_ABSTRACT TResult Build();
public:
   MO_ABSTRACT TResult LoadConfig(FXmlNode* pConfig);
   MO_ABSTRACT TResult BuildDescripter(SRenderableDescriptor& renderableDescriptor);
   MO_ABSTRACT TResult BuildTemplate(SRenderableDescriptor& renderableDescriptor, MString* pCode, FTemplateContext* pTemplateContext);
public:
   MO_ABSTRACT TResult Resize(TInt width, TInt height);
   MO_ABSTRACT TResult UpdateBegin();
   MO_ABSTRACT TResult WriteRenderable(FRenderable* pRenderable);
   MO_ABSTRACT TResult UpdateEnd();
   MO_ABSTRACT TResult DrawRenderable(FRenderRegion* pRegion, FRenderable* pRenderable);
   MO_ABSTRACT TResult DrawGroup(FRenderRegion* pRegion, TInt offset, TInt count);
};
//------------------------------------------------------------
typedef MO_FG_DECLARE FDictionary<FEffect*> FEffectDictionary;
typedef MO_FG_DECLARE GPtrDictionary<FEffect> GEffectPtrDictionary;

//============================================================
// <T>������Ⱦ����</T>
//============================================================
class MO_FG_DECLARE FStageEffect : public FEffect
{
   MO_CLASS_DECLARE_INHERITS(FStageEffect, FEffect);
public:
   FStageEffect();
   MO_ABSTRACT ~FStageEffect();
public:
   MO_OVERRIDE TResult OnSetup();
public:
   MO_OVERRIDE TResult Resize(TInt width, TInt height);
   MO_OVERRIDE TResult Draw(FRenderable* pRenderable);
};

//============================================================
// <T>��ȾЧ������̨��</T>
//============================================================
class MO_FG_DECLARE FEffectConsole : public FConsole{
protected:
   FClassFactory* _pFactory;
   GEffectPtrDictionary _effects;
   GEffectPtrDictionary _templateEffects;
public:
   FEffectConsole();
   MO_ABSTRACT ~FEffectConsole();
public:
   //------------------------------------------------------------
   // <T>����๤����</T>
   MO_INLINE FClassFactory* Factory(){
      return _pFactory;
   }
   //------------------------------------------------------------
   // <T>���Ч���ֵ䡣</T>
   MO_INLINE GEffectPtrDictionary& Effects(){
      return _effects;
   }
protected:
public:
   FEffect* Build(TCharC* pName, FRenderable* pRenderable = NULL);
   FEffect* FindTemplate(TCharC* pName);
   FEffect* Find(TCharC* pName, FRenderable* pRenderable = NULL);
public:
   //------------------------------------------------------------
   // <T>�������ƺ���Ⱦ��Ϣ���һ��Ч������</T>
   template <class T>
   T* Find(TCharC* pName, FRenderable* pRenderable = NULL){
      FEffect* pEffect = Find(pName, pRenderable);
      return pEffect->Convert<T>();
   }
public:
   MO_OVERRIDE TResult Suspend();
   MO_OVERRIDE TResult Resume();
};

//============================================================
// <T>��ȾЧ����������</T>
//============================================================
class MO_FG_DECLARE REffectManager : public RSingleton<FEffectConsole>{
};

//============================================================
// <T>��Ⱦ�������̡�</T>
//============================================================
class MO_FG_DECLARE FTechniquePass : public FObject{
public:
   FTechniquePass();
   MO_ABSTRACT ~FTechniquePass();
};

//============================================================
// <T>��Ⱦ����������</T>
//============================================================
class MO_FG_DECLARE FTechniqueContext : public FObject{
public:
   FTechniqueContext();
   MO_ABSTRACT ~FTechniqueContext();
};

//============================================================
// <T>��Ⱦ������</T>
//============================================================
class MO_FG_DECLARE FTechnique : public FObject{
protected:
   TString _name;
   FEffectCollection* _pEffects;
   FRenderProgram* _pProgram;
public:
   FTechnique();
   MO_ABSTRACT ~FTechnique();
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
   // <T>��ó���</T>
   MO_INLINE FRenderProgram* Program(){
      return _pProgram;
   }
public:
   //MO_ABSTRACT FEffect* FindFEffect(ERenderEffect typeCd);
public:
   MO_ABSTRACT TResult Setup();
public:
   MO_ABSTRACT TResult Resize(TInt width, TInt height);
   MO_ABSTRACT TResult Draw(FRenderRegion* pRegion, TInt offset, TInt count);
};
//------------------------------------------------------------
typedef MO_FG_DECLARE FObjects<FTechnique*> FTechniqueCollection;
typedef MO_FG_DECLARE FList<FTechnique*> FTechniqueList;

//============================================================
// <T>��Ⱦ����������</T>
//============================================================
struct STechniqueCapability{
public:
   TBool optionInstance;
   TBool optionMerge;
public:
   //------------------------------------------------------------
   // <T>������Ⱦ����������</T>
   STechniqueCapability(){
      optionInstance = EFalse;
      optionMerge = EFalse;
   }
};

//============================================================
// <T>��Ⱦ��������̨��</T>
//============================================================
class MO_FG_DECLARE FTechniqueConsole : public FConsole{
protected:
   STechniqueCapability _capability;
   FTechniqueCollection* _pTechniques;
public:
   FTechniqueConsole();
   MO_ABSTRACT ~FTechniqueConsole();
public:
   //------------------------------------------------------------
   // <T>�����Ⱦ����������</T>
   MO_INLINE STechniqueCapability& Capability(){
      return _capability;
   }
   //------------------------------------------------------------
   // <T>��ü������ϡ�</T>
   MO_INLINE FTechniqueCollection* Techniques(){
      return _pTechniques;
   }
public:
   MO_ABSTRACT void Setup();
};

//============================================================
// <T>��Ⱦ������������</T>
//============================================================
class MO_FG_DECLARE RTechniqueManager : public RSingleton<FTechniqueConsole>{
};

MO_NAMESPACE_END

//************************************************************
#endif // __MO_FG_TECHNIQUE_H__
