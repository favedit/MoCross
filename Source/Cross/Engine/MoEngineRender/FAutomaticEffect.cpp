#include "MoErTechnique.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FAutomaticEffect, FEffect);

//============================================================
// <T>������ȾЧ����</T>
//============================================================
FAutomaticEffect::FAutomaticEffect(){
   // ���ù���
   _descriptor.supportVertexColor = ETrue;
   _descriptor.supportVertexCoord = ETrue;
   _descriptor.supportVertexNormal = ETrue;
   _descriptor.supportVertexNormalFull = ETrue;
   _descriptor.supportAlpha = ETrue;
   _descriptor.supportBump = ETrue;
   _descriptor.supportAmbient = ETrue;
   _descriptor.supportDiffuse = ETrue;
   _descriptor.supportDiffuseView = ETrue;
   _descriptor.supportSpecularColor = ETrue;
   _descriptor.supportSpecularLevel = ETrue;
   _descriptor.supportSpecularView = ETrue;
   _descriptor.supportEnvironment = ETrue;
   _descriptor.supportLight = ETrue;
   _descriptor.supportReflect = ETrue;
   _descriptor.supportRefract = ETrue;
   _descriptor.supportEmissive = ETrue;
   _descriptor.supportHeight = ETrue;
   // ���û���
   _pParameters = MO_CREATE(FRenderProgramParameterCollection);
   _pAttributes = MO_CREATE(FRenderProgramAttributeCollection);
   _pSamplers = MO_CREATE(FRenderProgramSamplerCollection);
}

//============================================================
// <T>������ȾЧ����</T>
//============================================================
FAutomaticEffect::~FAutomaticEffect(){
   MO_DELETE(_pParameters);
   MO_DELETE(_pAttributes);
   MO_DELETE(_pSamplers);
}

//============================================================
// <T>ע��һ��������</T>
//
// @param pLinker ������
// @param code ����
// @retrun ������
//============================================================
TResult FAutomaticEffect::RegisterParameter(TCharC* pLinker, TInt code){
   // ������
   MO_CHECK(pLinker, return ENull);
   MO_CHECK(code >= 0, return EOutRange);
   // ��ó������
   FRenderProgramParameter* pParameter = _program->ParameterFindByLinker(pLinker);
   //MO_CHECK(pParameter, return ENull);
   if(pParameter == NULL){
      MO_WARN("Register parameter is not exists. (linker=%s)", pLinker);
      return ENotExists;
   }
   // ����λ��
   _pParameters->ExtendSet(code, pParameter);
   return ESuccess;
}

//============================================================
// <T>ע��һ��ȡ������</T>
//
// @param pLinker ������
// @param code ����
// @retrun ������
//============================================================
TResult FAutomaticEffect::RegisterSampler(TCharC* pLinker, TInt code){
   // ������
   MO_CHECK(pLinker, return ENull);
   MO_CHECK(code >= 0, return EOutRange);
   // ��ó������
   FRenderProgramSampler* pSampler = _program->SamplerFindByLinker(pLinker);
   MO_CHECK(pSampler, return ENull);
   // ����λ��
   _pSamplers->ExtendSet(code, pSampler);
   return ESuccess;
}

//============================================================
// <T>����������Ϣ��</T>
//
// @param pConfig ���ô���
// @return ������
//============================================================
TResult FAutomaticEffect::LoadConfig(FXmlNode* pConfig){
   FEffect::LoadConfig(pConfig);
   _config = pConfig;
   return ESuccess;
}

//============================================================
// <T>�����������ϡ�</T>
//
// @return ������
//============================================================
TResult FAutomaticEffect::BindDescriptors(){
   TResult resultCd = ESuccess;
   MO_CHECK(_program, return ENull);
   //............................................................
   // ��������������
   GRenderShaderParameterPtrs& parameters = _program->Parameters();
   if(!parameters.IsEmpty()){
      TInt count = parameters.Count();
      for(TInt n = 0; n < count; n++){
         FRenderProgramParameter* pParameter = parameters.Get(n);
         TCharC* pLinker = pParameter->Linker();
         // ��������
         EEffectParameter parameterCd = EEffectParameter_Unknown;
         ERenderShader shaderCd = ERenderShader_Unknown;
         ERenderParameterFormat formatCd = ERenderParameterFormat_Unknown;
         REffectParameter::Parse(pLinker, parameterCd, shaderCd, formatCd);
         pParameter->SetShaderCd(shaderCd);
         pParameter->SetFormatCd(formatCd);
         // ���ò���
         if(pParameter->IsStatusUsed()){
            //_pParameters->ExtendSet(parameterCd, pParameter);
            MO_DEBUG("Build shader parameter. (code=%d, name=%s, format=%d)", parameterCd, pParameter->Name(), pParameter->FormatCd());
         }
      }
   }
   //............................................................
   // ��������������
   GRenderShaderAttributePtrs& attributes = _program->Attributes();
   if(!attributes.IsEmpty()){
      TInt count = attributes.Count();
      for(TInt n = 0; n < count; n++){
         FRenderProgramAttribute* pAttribute = attributes.Get(n);;
         if(pAttribute->IsStatusUsed()){
            // ��������
            TCharC* pLinker = pAttribute->Linker();
            EEffectAttribute attributeCd = EEffectAttribute_Unknown;
            ERenderAttributeFormat formatCd = ERenderAttributeFormat_Unknown;
            REffectAttribute::Parse(pLinker, attributeCd, formatCd);
            // ���ò���
            pAttribute->SetFormatCd(formatCd);
         }
      }
   }
   //............................................................
   // ��������������
   GRenderProgramSamplerPtrs& samplers = _program->Samplers();
   if(!samplers.IsEmpty()){
      TInt count = samplers.Count();
      for(TInt n = 0; n < count; n++){
         FRenderProgramSampler* pSampler = samplers.Get(n);
         if(pSampler->IsStatusUsed()){
            TCharC* pLinker = pSampler->Linker();
            // ��������
            //TInt samplerCd = RRenderSampler::Parse(pLinker);
            //TInt packCd = RRenderSampler::ParsePack(samplerCd);
            // ���ò���
            //pSampler->SetCode(samplerCd);
            //_pSamplers->Set(samplerCd, pSampler);
            //_pSamplers->Set(packCd, pSampler);
         }
      }
   }
   return resultCd;
}

//============================================================
// <T>���ô���</T>
//
// @return ������
//============================================================
TResult FAutomaticEffect::Setup(){
   TResult resultCd = FEffect::Setup();
   return resultCd;
}

//============================================================
// <T>����ģ�廷����</T>
//
// @param pContext ����
// @return ������
//============================================================
TResult FAutomaticEffect::BuildContext(SEffectContext* pContext){
   // ��ò���
   MO_CHECK(pContext, return ENull);
   TFsCode& code = pContext->code;
   FRenderable* pRenderable = pContext->renderablePtr;
   MO_CHECK(pRenderable, return ENull);
   FTemplateContext* pTemplateContext = pContext->contextPtr;
   STechniqueCapability& capability = RTechniqueManager::Instance().Capability();
   SRenderableDescriptor& renderableDescriptor = pRenderable->Descriptor();
   //............................................................
   // ֧�ֶ�����ɫ
   TBool attributeColor = pRenderable->AttributeContains(MO_ER_ATTRIBUTE_COLOR);
   _dynamicDescriptor.supportVertexColor = (_descriptor.supportVertexColor && attributeColor);
   if(_dynamicDescriptor.supportVertexColor){
      code.Append("|AC");
      if(pTemplateContext){
         pTemplateContext->DefineBool("vertex.attribute.color", ETrue);
      }
   }
   // ֧�ֶ�������
   TBool attributeCoord = pRenderable->AttributeContains(MO_ER_ATTRIBUTE_COORD);
   _dynamicDescriptor.supportVertexCoord = (_descriptor.supportVertexCoord && attributeCoord);
   if(_dynamicDescriptor.supportVertexCoord){
      code.Append("|AD");
      if(pTemplateContext){
         pTemplateContext->DefineBool("vertex.attribute.coord", ETrue);
      }
   }
   // ֧�ַ���
   TBool attributeNormal = pRenderable->AttributeContains(MO_ER_ATTRIBUTE_NORMAL);
   _dynamicDescriptor.supportVertexNormal = (_dynamicDescriptor.supportVertexCoord && attributeNormal);
   if(_dynamicDescriptor.supportVertexNormal){
      code.Append("|AN");
      if(pTemplateContext){
         pTemplateContext->DefineBool("vertex.attribute.normal", ETrue);
      }
   }
   // ֧��ȫ����
   TBool attributeBinormal = pRenderable->AttributeContains(MO_ER_ATTRIBUTE_BINORMAL);
   TBool attributeTangent = pRenderable->AttributeContains(MO_ER_ATTRIBUTE_TANGENT);
   TBool attributeNormalFull = (attributeNormal && attributeBinormal && attributeTangent);
   _dynamicDescriptor.supportVertexNormalFull = (_dynamicDescriptor.supportVertexCoord && attributeNormalFull);
   if(_dynamicDescriptor.supportVertexNormalFull){
      code.Append("|AF");
      if(pTemplateContext){
         pTemplateContext->DefineBool("vertex.attribute.normal.full", ETrue);
      }
   }
   //............................................................
   // ֧��ʵ������
   _dynamicDescriptor.supportInstance = (_descriptor.supportInstance && capability.optionInstance);
   if(_dynamicDescriptor.supportInstance){
      code.Append("|SI");
      if(pTemplateContext){
         pTemplateContext->DefineBool("support.instance", ETrue);
      }
   }
   // ֧�ֹ�������
   _dynamicDescriptor.supportSkeleton = _descriptor.supportSkeleton;
   if(_dynamicDescriptor.supportSkeleton){
      code.Append("|SS");
      if(pTemplateContext){
         pTemplateContext->DefineBool("support.skeleton", ETrue);
      }
   }
   //............................................................
   // ֧��͸������
   TBool samplerDiffuse  = pRenderable->SamplerContains(MO_ER_SAMPLER_DIFFUSE);
   TBool samplerAlpha  = pRenderable->SamplerContains(MO_ER_SAMPLER_ALPHA);
   _dynamicDescriptor.supportAlpha = (_descriptor.supportAlpha && samplerAlpha);
   if(_dynamicDescriptor.supportAlpha){
      code.Append("|RA");
      if(pTemplateContext){
         pTemplateContext->DefineBool("support.alpha", ETrue);
      }
      _descriptor.optionBlendMode = ETrue;
   }else{
      _descriptor.optionBlendMode = EFalse;
   }
   // ֧�ֻ���ɫ����
   _dynamicDescriptor.supportAmbient = _descriptor.supportAmbient;
   if(_dynamicDescriptor.supportAmbient){
      code.Append("|TA");
      if(pTemplateContext){
         pTemplateContext->DefineBool("support.ambient", ETrue);
      }
      if(samplerDiffuse){
         code.Append("|TAS");
         if(pTemplateContext){
            pTemplateContext->DefineBool("support.ambient.sampler", ETrue);
         }
      }
   }
   //............................................................
   // ֧��ɢ�似��
   TBool samplerNormal = pRenderable->SamplerContains(MO_ER_SAMPLER_NORMAL);
   _dynamicDescriptor.supportDiffuse = _descriptor.supportDiffuse && (_dynamicDescriptor.supportVertexNormal || samplerNormal);
   if(_descriptor.supportDiffuse){
      if(pTemplateContext){
         pTemplateContext->DefineBool("support.diffuse", ETrue);
      }
      if(samplerNormal){
         code.Append("|TDD");
         if(pTemplateContext){
            pTemplateContext->DefineBool("support.diffuse.dump", ETrue);
         }
      }else if(_dynamicDescriptor.supportVertexNormal){
         code.Append("|TDN");
         if(pTemplateContext){
            pTemplateContext->DefineBool("support.diffuse.normal", ETrue);
         }
      }
   }
   // ֧���ӽ�ɢ�似��
   _dynamicDescriptor.supportDiffuseView = (_descriptor.supportDiffuseView && (_dynamicDescriptor.supportVertexNormal || samplerNormal));
   if(_descriptor.supportDiffuseView){
      if(pTemplateContext){
         pTemplateContext->DefineBool("support.diffuse.view", ETrue);
      }
      if(samplerNormal){
         code.Append("|TDVD");
         if(pTemplateContext){
            pTemplateContext->DefineBool("support.diffuse.view.dump", ETrue);
         }
      }else if(_dynamicDescriptor.supportVertexNormal){
         code.Append("|TDVN");
         if(pTemplateContext){
            pTemplateContext->DefineBool("support.diffuse.view.normal", ETrue);
         }
      }
   }
   //............................................................
   // ֧�ָ߹⼼��
   TBool samplerSpecularColor = pRenderable->SamplerContains(MO_ER_SAMPLER_SPECULAR_COLOR);
   TBool samplerSpecularLevel = pRenderable->SamplerContains(MO_ER_SAMPLER_SPECULAR_LEVEL);
   _dynamicDescriptor.supportSpecularColor = (_descriptor.supportSpecularColor && samplerSpecularColor);
   _dynamicDescriptor.supportSpecularLevel = (_descriptor.supportSpecularLevel && samplerSpecularLevel);
   if((_dynamicDescriptor.supportSpecularColor || _dynamicDescriptor.supportSpecularLevel) && _dynamicDescriptor.supportVertexNormal){
      code.Append("|TS");
      if(pTemplateContext){
         pTemplateContext->DefineBool("support.specular", ETrue);
      }
      // ֧�ָ߹���ɫ����
      if(_dynamicDescriptor.supportSpecularColor){
         code.Append("|TSC");
         if(pTemplateContext){
            pTemplateContext->DefineBool("support.specular.color", ETrue);
         }
      }
      // ֧�ָ߹⼶����
      if(_dynamicDescriptor.supportSpecularLevel){
         code.Append("|TSL");
         if(pTemplateContext){
            pTemplateContext->DefineBool("support.specular.level", ETrue);
         }
      }else{
         code.Append("|NSL");
         if(pTemplateContext){
            pTemplateContext->DefineBool("support.specular.normal", ETrue);
         }
      }
   }
   // ֧���ӽǸ߹⼼��
   _dynamicDescriptor.supportSpecularView = _descriptor.supportSpecularView;
   if(_dynamicDescriptor.supportSpecularView && _dynamicDescriptor.supportVertexNormal){
      code.Append("|TSV");
      if(pTemplateContext){
         pTemplateContext->DefineBool("support.specular.view", ETrue);
      }
      // ֧�ָ߹���ɫ����
      if(_dynamicDescriptor.supportSpecularColor){
         code.Append("|TSVC");
         if(pTemplateContext){
            pTemplateContext->DefineBool("support.specular.view.color", ETrue);
         }
      }
      // ֧�ָ߹⼶����
      if(_dynamicDescriptor.supportSpecularLevel){
         code.Append("|TSVL");
         if(pTemplateContext){
            pTemplateContext->DefineBool("support.specular.view.level", ETrue);
         }
      }else{
         code.Append("|NSVL");
         if(pTemplateContext){
            pTemplateContext->DefineBool("support.specular.view.normal", ETrue);
         }
      }
   }
   //............................................................
   // ֧���չ⼼��
   TBool samplerLight = pRenderable->SamplerContains(MO_ER_SAMPLER_LIGHT);
   _dynamicDescriptor.supportLight = (_descriptor.supportLight && samplerLight);
   if(_dynamicDescriptor.supportLight){
      code.Append("|TL");
      if(pTemplateContext){
         pTemplateContext->DefineBool("support.light", ETrue);
      }
   }
   // ֧�ַ��似��
   TBool samplerReflect = pRenderable->SamplerContains(MO_ER_SAMPLER_REFLECT);
   _dynamicDescriptor.supportReflect = (_descriptor.supportReflect && samplerReflect);
   if(_dynamicDescriptor.supportReflect){
      code.Append("|TRL");
      if(pTemplateContext){
         pTemplateContext->DefineBool("support.reflect", ETrue);
      }
   }
   // ֧�����似��
   TBool samplerRefract = pRenderable->SamplerContains(MO_ER_SAMPLER_REFRACT);
   _dynamicDescriptor.supportRefract = (_descriptor.supportRefract && samplerRefract);
   if(_dynamicDescriptor.supportRefract){
      code.Append("|TRF");
      if(pTemplateContext){
         pTemplateContext->DefineBool("support.refract", ETrue);
      }
   }
   // ֧�ַ��⼼��
   TBool samplerEmissive = pRenderable->SamplerContains(MO_ER_SAMPLER_EMISSIVE);
   _dynamicDescriptor.supportEmissive = (_descriptor.supportEmissive && samplerEmissive);
   if(_dynamicDescriptor.supportEmissive){
      code.Append("|TLE");
      if(pTemplateContext){
         pTemplateContext->DefineBool("support.emissive", ETrue);
      }
   }
   //............................................................
   // ֧�ָ߶ȼ���
   TBool samplerHeight = pRenderable->SamplerContains(MO_ER_SAMPLER_HEIGHT);
   _dynamicDescriptor.supportHeight = (_descriptor.supportHeight && samplerHeight);
   if(_dynamicDescriptor.supportHeight){
      code.Append("|TH");
      if(pTemplateContext){
         pTemplateContext->DefineBool("support.height", ETrue);
      }
   }
   //............................................................
   // ֧�ֻ�������
   TBool samplerEnvironment = pRenderable->SamplerContains(MO_ER_SAMPLER_ENVIRONMENT);
   _dynamicDescriptor.supportEnvironment = (_descriptor.supportEnvironment && samplerEnvironment);
   if(_dynamicDescriptor.supportEnvironment){
      code.Append("|TE");
      if(pTemplateContext){
         pTemplateContext->DefineBool("support.environment", ETrue);
      }
   }
   //............................................................
   // �������ʵ������
   FRenderDevice* pRenderDevice = RDeviceManager::Instance().Find<FRenderDevice>();
   TInt instanceCount = RRenderUtil::CalculateInstanceCount(renderableDescriptor.vertexCount, renderableDescriptor.boneCount);
   if(_dynamicDescriptor.supportInstance && pTemplateContext){
      pTemplateContext->DefineInt("instance.count", instanceCount);
   }
   // �����ͷʵ������
   if(_dynamicDescriptor.supportSkeleton && pTemplateContext){
      pTemplateContext->DefineBool("support.bone.weight.1", ETrue);
      pTemplateContext->DefineBool("support.bone.weight.2", ETrue);
      pTemplateContext->DefineBool("support.bone.weight.3", ETrue);
      pTemplateContext->DefineBool("support.bone.weight.4", ETrue);
   }
   return ESuccess;
}

//============================================================
// <T>���ô���</T>
//
// @return ������
//============================================================
TResult FAutomaticEffect::Build(){
   //............................................................
   // ���붥�����
   _program->VertexShader()->Compile(_vertexSource);
   // �������س���
   _program->FragmentShader()->Compile(_fragmentSource);
   //............................................................
   // ��������
   _program->Build();
   BindDescriptors();
   //............................................................
   // ��������
   _program->Link();
   //............................................................
   // �ı��С
   FScreenDevice* pScreenDevice = RDeviceManager::Instance().Find<FScreenDevice>();
   SIntSize2& screenSize = pScreenDevice->Size();
   Resize(screenSize.width, screenSize.height);
   return ESuccess;
}

//============================================================
// <T>�󶨳�����ά���ꡣ</T>
//
// @param shaderCd ��Ⱦ����
// @param bindCd ������
// @param point ��ά����
//============================================================
TResult FAutomaticEffect::BindConstPosition3(TInt bindCd, SFloatPoint3& point){
   FRenderProgramParameter* pParameter = _pParameters->Get(bindCd);
   if(pParameter != NULL){
      if(pParameter->IsStatusUsed()){
         pParameter->SetFloat3(point.x, point.y, point.z);
      }
   }
   return ESuccess;
}

//============================================================
// <T>�󶨳�����ά����</T>
//
// @param shaderCd ��Ⱦ����
// @param bindCd ������
// @param vector ��ά����
//============================================================
TResult FAutomaticEffect::BindConstVector3(TInt bindCd, SFloatVector3& vector){
   FRenderProgramParameter* pParameter = _pParameters->Get(bindCd);
   if(pParameter != NULL){
      if(pParameter->IsStatusUsed()){
         pParameter->SetFloat3(vector.x, vector.y, vector.z);
      }
   }
   return ESuccess;
}

//============================================================
// <T>�󶨳�����ά��������</T>
//
// @param bindCd �󶨴���
// @param x ������X
// @param y ������Y
// @param z ������Z
// @param w ������W
//============================================================
TResult FAutomaticEffect::BindConstFloat4(TInt bindCd, TFloat x, TFloat y, TFloat z, TFloat w){
   FRenderProgramParameter* pParameter = _pParameters->Get(bindCd);
   if(pParameter != NULL){
      if(pParameter->IsStatusUsed()){
         pParameter->SetFloat4(x, y, z, w);
      }
   }
   return ESuccess;
}

//============================================================
// <T>�󶨳�����ά��������</T>
//
// @param bindCd �󶨴���
// @param x ������X
// @param y ������Y
// @param z ������Z
// @param w ������W
//============================================================
TResult FAutomaticEffect::BindConstColor4(TInt bindCd, const SFloatColor4& color){
   FRenderProgramParameter* pParameter = _pParameters->Get(bindCd);
   if(pParameter != NULL){
      if(pParameter->IsStatusUsed()){
         pParameter->SetFloat4(color.red, color.green, color.blue, color.alpha);
      }
   }
   return ESuccess;
}

//============================================================
// <T>�󶨳���4X4����</T>
//
// @param shaderCd ��Ⱦ����
// @param bindCd ������
// @param matrix 4X4����
//============================================================
TResult FAutomaticEffect::BindConstMatrix3x3(TInt bindCd, SFloatMatrix3d* pMatrix, TInt count){
   FRenderProgramParameter* pParameter = _pParameters->Get(bindCd);
   if((pParameter != NULL) && (count > 0)){
      if(pParameter->IsStatusUsed()){
         pParameter->SetMatrix3x3(pMatrix, count, ETrue);
      }
   }
   return ESuccess;
}

//============================================================
// <T>�󶨳���4X4����</T>
//
// @param shaderCd ��Ⱦ����
// @param bindCd ������
// @param matrix 4X4����
//============================================================
TResult FAutomaticEffect::BindConstMatrix4x3(TInt bindCd, SFloatMatrix3d* pMatrix, TInt count){
   FRenderProgramParameter* pParameter = _pParameters->Get(bindCd);
   if((pParameter != NULL) && (count > 0)){
      if(pParameter->IsStatusUsed()){
         pParameter->SetMatrix4x3(pMatrix, count, ETrue);
      }
   }
   return ESuccess;
}

//============================================================
// <T>�󶨳���4X4����</T>
//
// @param shaderCd ��Ⱦ����
// @param bindCd ������
// @param matrix 4X4����
//============================================================
TResult FAutomaticEffect::BindConstMatrix4x4(TInt bindCd, SFloatMatrix3d* pMatrix, TInt count){
   FRenderProgramParameter* pParameter = _pParameters->Get(bindCd);
   if((pParameter != NULL) && (count > 0)){
      if(pParameter->IsStatusUsed()){
         pParameter->SetMatrix4x4(pMatrix, count, ETrue);
      }
   }
   return ESuccess;
}

//============================================================
// <T>���������������ϡ�</T>
//
// @param pRenderable ��Ⱦ����
// @return ������
//============================================================
TResult FAutomaticEffect::BindAttributeDescriptors(FRenderable* pRenderable){
   MO_CHECK(pRenderable, return ENull);
   //............................................................
   // ��ò���
   FRenderableEffect* pRenderableEffect = pRenderable->ActiveEffect();
   FRenderLayout* pLayout = pRenderableEffect->Layout();
   if(pLayout == NULL){
      // ��������
      pLayout = _renderDevice->CreateObject<FRenderLayout>(MO_RENDEROBJECT_LAYOUT);
      pLayout->SetProgram(_program);
      pLayout->SetRenderable(pRenderable);
      pLayout->Setup();
      pRenderableEffect->SetLayout(pLayout);
   }
   //............................................................
   // ���ò���
   _renderDevice->SetLayout(pLayout);
   return ESuccess;
}

//============================================================
// <T>���������������ϡ�</T>
//
// @param pRenderable ��Ⱦ����
// @return ������
//============================================================
TResult FAutomaticEffect::UnbindAttributeDescriptors(FRenderable* pRenderable){
   // ����豸
   FRenderDevice* pRenderDevice = RDeviceManager::Instance().Find<FRenderDevice>();
   MO_CHECK(pRenderDevice, return ENull);
   //............................................................
   //// �������
   //FRenderVertexStreams* pVertexStreams = pRenderable->VertexStreams();
   //MO_CHECK(pVertexStreams, return ENull);
   ////............................................................
   //// �������Լ���
   //TEffectAttributeDescriptors::TIterator attributeIterator = _attributeDescriptors.Iterator();
   //while(attributeIterator.Next()){
   //   SEffectAttributeDescriptor& descriptor = *attributeIterator;
   //   if(descriptor.bindId != -1){
   //      pRenderDevice->BindVertexStream(descriptor.bindId, NULL);
   //   }
   //}
   return ESuccess;
}

//============================================================
// <T>��ȡ�������������ϡ�</T>
//
// @param pRenderable ��Ⱦ����
// @return ������
//============================================================
TResult FAutomaticEffect::BindSampler(TInt bindCd, FRenderTexture* pTexture){
   // ����豸
   FRenderDevice* pRenderDevice = RDeviceManager::Instance().Find<FRenderDevice>();
   MO_CHECK(pRenderDevice, return ENull);
   //............................................................
   // �������Լ���
   FRenderProgramSampler* pSampler = _pSamplers->Get(bindCd);
   if(pSampler != NULL){
      pRenderDevice->BindTexture(pSampler->Slot(), pSampler->Index(), pTexture);
   }
   return ESuccess;
}

//============================================================
// <T>��ȡ�������������ϡ�</T>
//
// @param pRenderable ��Ⱦ����
// @return ������
//============================================================
TResult FAutomaticEffect::BindSamplerDescriptors(FRenderable* pRenderable){
   // ����豸
   FRenderDevice* pRenderDevice = RDeviceManager::Instance().Find<FRenderDevice>();
   MO_CHECK(pRenderDevice, return ENull);
   //............................................................
   // �������Լ���
   GRenderProgramSamplerPtrs& samplers = _program->Samplers();
   TInt count = samplers.Count();
   for(TInt n = 0; n < count; n++){
      FRenderProgramSampler* pSampler = samplers.Get(n);
      if(pSampler->IsStatusUsed()){
         TCharC* pLinker = pSampler->Linker();
         FRenderableSampler* pRenderableSampler = pRenderable->SamplerPackFind(pLinker);
         if(pRenderableSampler != NULL){
            FRenderTexture* pTexture = pRenderableSampler->GraphicsObject<FRenderTexture>();
            pRenderDevice->BindTexture(pSampler->Slot(), pSampler->Index(), pTexture);
         }
      }
   }
   return ESuccess;
}

//============================================================
// <T>���ò���ѡ�</T>
//
// @param pMaterial ����
// @return ������
//============================================================
TResult FAutomaticEffect::SetMaterialOption(FMaterial* pMaterial){
   // ����͸��
   TBool optionAlpha = pMaterial->OptionAlpha();
   if(optionAlpha){
      _renderDevice->SetBlendFactors(_descriptor.optionBlendMode, _descriptor.blendSourceMode, _descriptor.blendTargetMode);
   }else{
      _renderDevice->SetBlendFactors(EFalse);
   }
   // ����˫��
   TBool optionDouble = pMaterial->OptionDouble();
   if(optionDouble){
      _renderDevice->SetCullingMode(EFalse);
   }else{
      _renderDevice->SetCullingMode(_descriptor.optionCullMode, _descriptor.cullModeCd);
   }
   return ESuccess;
}

//============================================================
// <T>��������������Ⱦ���ϴ���</T>
//============================================================
TResult FAutomaticEffect::DrawRenderable(FRenderRegion* pRegion, FRenderable* pRenderable){
   return ESuccess;
}

//============================================================
// <T>ʵ������������Ⱦ���ϴ���</T>
//============================================================
TResult FAutomaticEffect::DrawInstanceRenderable(FRenderRegion* pRegion, FInstanceRenderable* pInstanceRenderable, TInt offset, TInt count){
   return ESuccess;
}

//============================================================
// <T>����һ����Ⱦ���ϴ���</T>
//
// @param pRegion ����
// @param offset λ��
// @param count ����
//============================================================
TResult FAutomaticEffect::DrawGroup(FRenderRegion* pRegion, TInt offset, TInt count){
   MO_CHECK(pRegion, return ENull);
   // �����豸״̬
   _renderDevice->SetFillMode(_descriptor.fillModeCd);
   _renderDevice->SetDepthMode(_descriptor.optionDepthTest, _descriptor.depthModeCd);
   //............................................................
   FRenderableCollection* pRenderables = pRegion->VisibleRenderables();
   TBool instanceDraw = EFalse;
   if(_dynamicDescriptor.supportInstance && (count > 1)){
      for(TInt n = 0; n < count; ){
         // ����������з���
         TInt groupBegin = n;
         TInt groupEnd = count;
         FRenderable* pGroupRenderable = pRenderables->Get(offset + n);
         FRenderIndexBuffer* pGroupIndexBuffer = pGroupRenderable->IndexBuffer();
         for(TInt i = n; i < count; i++){
            FRenderable* pRenderable = pRenderables->Get(offset + i);
            FRenderIndexBuffer* pIndexBuffer = pRenderable->IndexBuffer();
            if(pGroupIndexBuffer != pIndexBuffer){
               groupEnd = i;
               break;
            }
            n++;
         }
         // ����ѡ��
         SetMaterialOption(pGroupRenderable->Material());
         // ���Ƶ�ǰ��Ⱦ��
         TInt instanceCount = groupEnd - groupBegin;
         if(instanceCount > 1){
            FInstanceRenderable* pInstanceRenderable = RInstance3dManager::Instance().ModelConsole()->LoadInstance(pGroupRenderable);
            DrawInstanceRenderable(pRegion, pInstanceRenderable, groupBegin, groupEnd - groupBegin);
         }else{
            DrawRenderable(pRegion, pGroupRenderable);
         }
      }
      instanceDraw = ETrue;
   }
   //............................................................
   // ����������Ⱦ����
   if(!instanceDraw){
      for(TInt n = 0; n < count; n++){
         FRenderable* pRenderable = pRenderables->Get(offset + n);
         SetMaterialOption(pRenderable->Material());
         DrawRenderable(pRegion, pRenderable);
      }
   }
   return ESuccess;
}

MO_NAMESPACE_END
