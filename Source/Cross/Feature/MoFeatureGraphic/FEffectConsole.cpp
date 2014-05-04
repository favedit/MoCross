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
   GPtr<FTemplateContext> context = FTemplateContext::InstanceCreate();
   context->SetSpace("shader");
   context->SetTrimBeginLine(ETrue);
   context->SetTrimEmptyLine(ETrue);
   context->SetTrimEndLine(ETrue);
   context->SetTrimCommentLine(ETrue);
#ifdef _MO_ANDROID
   context->DefineBool("os.android", ETrue);
#endif // _MO_ANDROID
   //............................................................
   // ����Ч����
   FEffect* pEffect = _pFactory->Create<FEffect>(pName);
   pEffect->SetRenderDevice(pRenderDevice);
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
   pEffect->LoadConfig(pTemplate->Config());
   //pEffect->LoadConfig(context->MergeConfig());
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
   FRenderProgram* pProgram = pEffect->Program();
   // ����������Ϣ
   FXmlNode* pConfig = pTemplate->Config();
   TXmlNodeIteratorC iterator = pConfig->NodeIteratorC();
   while(iterator.Next()){
      FXmlNode* pNode = *iterator;
      //............................................................
      // �����������弯��
      if(pNode->IsName("Parameter")){
         FRenderShaderParameter* pParameter = pRenderDevice->ClassFactory()->Create<FRenderShaderParameter>(MO_RENDEROBJECT_SHADERPARAMETER);
         pParameter->LoadConfig(pNode);
         pProgram->ParameterPush(pParameter);
         continue;
      }
      //............................................................
      // �������Զ��弯��
      if(pNode->IsName("Attribute")){
         FRenderShaderAttribute* pAttribute = pRenderDevice->ClassFactory()->Create<FRenderShaderAttribute>(MO_RENDEROBJECT_SHADERATTRIBUTE);
         pAttribute->LoadConfig(pNode);
         pProgram->AttributePush(pAttribute);
         continue;
      }
      //............................................................
      // ����ȡ�������弯��
      if(pNode->IsName("Sampler")){
         FRenderShaderSampler* pSampler = pRenderDevice->ClassFactory()->Create<FRenderShaderSampler>(MO_RENDEROBJECT_SHADERSAMPLER);
         pSampler->LoadConfig(pNode);
         pProgram->SamplerPush(pSampler);
         continue;
      }
   }
   //............................................................
   // ���ô���
   pEffect->SetName(pName);
   pEffect->Setup();
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
