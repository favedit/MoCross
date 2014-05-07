#include "MoFgTechnique.h"
#include "MoFgRender.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>������ȾЧ������̨��</T>
//============================================================
FEffectConsole::FEffectConsole(){
   _pFactory = MO_CREATE(FClassFactory);
}

//============================================================
// <T>������ȾЧ������̨��</T>
//============================================================
FEffectConsole::~FEffectConsole(){
   MO_DELETE(_pFactory);
}

//============================================================
// <T>�������ƺ���Ⱦ��Ϣ������Ⱦ����</T>
//
// @param pName ����
// @param pRenderable ��Ⱦ��Ϣ
// @return Ч����
//============================================================
FEffect* FEffectConsole::Build(TCharC* pName, FRenderable* pRenderable){
   MO_ASSERT(pName);
   // ����豸
   FRenderDevice* pRenderDevice = RDeviceManager::Instance().Find<FRenderDevice>();
   TCharC* pDeviceCode = pRenderDevice->Capability()->Code();
   //............................................................
   // ���û���
   GPtr<FTemplateContext> context = FTemplateContext::InstanceCreate();
   context->SetSpace("shader");
   context->SetTrimBeginLine(ETrue);
   context->SetTrimEmptyLine(ETrue);
   context->SetTrimEndLine(ETrue);
   context->SetTrimCommentLine(ETrue);
#ifdef _MO_ANDROID
   context->DefineBool("os.android", ETrue);
#endif // _MO_ANDROID
   context->DefineString("device.render",                  pRenderDevice->Name());
   context->DefineInt("shader.buffer.global.static",       RRenderShaderBuffer::ParseSlot(ERenderShaderBuffer_GlobalStatic));
   context->DefineInt("shader.buffer.global.dynamic",      RRenderShaderBuffer::ParseSlot(ERenderShaderBuffer_GlobalDynamic));
   context->DefineInt("shader.buffer.technique.static",    RRenderShaderBuffer::ParseSlot(ERenderShaderBuffer_TechniqueStatic));
   context->DefineInt("shader.buffer.technique.dynamic",   RRenderShaderBuffer::ParseSlot(ERenderShaderBuffer_TechniqueDynamic));
   context->DefineInt("shader.buffer.effect.static",       RRenderShaderBuffer::ParseSlot(ERenderShaderBuffer_EffectStatic));
   context->DefineInt("shader.buffer.effect.dynamic",      RRenderShaderBuffer::ParseSlot(ERenderShaderBuffer_EffectDynamic));
   context->DefineInt("shader.buffer.renderable.dynamic",  RRenderShaderBuffer::ParseSlot(ERenderShaderBuffer_RenderableDynamic));
   context->DefineInt("shader.buffer.renderable.material", RRenderShaderBuffer::ParseSlot(ERenderShaderBuffer_RenderableMaterial));
   //............................................................
   // ����Ч����
   FEffect* pEffect = _pFactory->Create<FEffect>(pName);
   pEffect->SetName(pName);
   pEffect->SetRenderDevice(pRenderDevice);
   pEffect->Setup();
   //............................................................
   // ������Ⱦ��Ϣ
   if(pRenderable != NULL){
      TFsText templateName;
      SRenderableDescriptor& descriptor = pRenderable->Descriptor();
      pEffect->BuildTemplate(descriptor, &templateName, context);
   }
   //............................................................
   // ��ģ��
   TFsPath path;
   path.AssignFormat("asset:/shader/%s/%s.xml", pDeviceCode, pName);
   FTemplate* pTemplate = RTemplateManager::Instance().Load(context, path);
   FXmlNode* pTemplateConfig = pTemplate->Config();
   //pEffect->LoadConfig(context->MergeConfig());
   // ����������Ϣ
   pEffect->LoadConfig(pTemplateConfig);
   //............................................................
   // ����������Ⱦ����
   context->SourceReset();
   if(pTemplate->Parse(context, "vertex") == ESuccess){
      TCharC* pVertexCode = context->SourceMemory();
      pEffect->SetVertexSource(pVertexCode);
   }else{
      MO_FATAL("Build vertex souce failure.");
   }
   // ����������Ⱦ����
   context->SourceReset();
   if(pTemplate->Parse(context, "fragment") == ESuccess){
      TCharC* pFragmentCode = context->SourceMemory();
      pEffect->SetFragmentSource(pFragmentCode);
   }else{
      MO_FATAL("Build fragment souce failure.");
   }
   //............................................................
   // ��������
   pEffect->Build();
   return pEffect;
}

//============================================================
// <T>����һ��ģ����Ⱦ����</T>
//
// @param pName ����
// @return ��Ⱦ��
//============================================================
FEffect* FEffectConsole::FindTemplate(TCharC* pName){
   FEffect* pEffect = _templateEffects.Find(pName);
   if(pEffect == NULL){
      FRenderDevice* pRenderDevice = RDeviceManager::Instance().Find<FRenderDevice>();
      pEffect = _pFactory->Create<FEffect>(pName);
      MO_CHECK(pEffect, return NULL);
      pEffect->SetRenderDevice(pRenderDevice);
      pEffect->SetName(pName);
      _templateEffects.Set(pName, pEffect);
   }
   return pEffect;
}

//============================================================
// <T>�������ƺ���Ⱦ��Ϣ���һ��Ч������</T>
//
// @param pName ����
// @param pRenderable ��Ⱦ��Ϣ
// @return Ч����
//============================================================
FEffect* FEffectConsole::Find(TCharC* pName, FRenderable* pRenderable){
   // ������Ⱦʶ�����
   TFsCode flag;
   flag.Append(pName);
   if(pRenderable != NULL){
      SRenderableDescriptor& descriptor = pRenderable->Descriptor();
      if(!descriptor.setuped){
         pRenderable->BuildDescriptor();
         descriptor.Build();
      }
      FEffect* pTemplateEffect = FindTemplate(pName);
      pTemplateEffect->BuildTemplate(descriptor, &flag, NULL);
   }
   // ����Ч����
   FEffect* pEffect = _effects.Find(flag);
   if(pEffect == NULL){
      pEffect = Build(pName, pRenderable);
      pEffect->SetFlag(flag);
      _effects.Set(flag, pEffect);
   }
   return pEffect;
}

//============================================================
// <T>������</T>
//
// @return ������
//============================================================
TResult FEffectConsole::Suspend(){
   _effects.Clear();
   _templateEffects.Clear();
   return ESuccess;
}

//============================================================
// <T>��������</T>
//
// @return ������
//============================================================
TResult FEffectConsole::Resume(){
   return ESuccess;
}

MO_NAMESPACE_END
