#include "MoFgRender.h"
#include "MoFgTechnique.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FEffect, FInstance);

//============================================================
// <T>������ȾЧ����</T>
//============================================================
FEffect::FEffect(){
}

//============================================================
// <T>������ȾЧ����</T>
//============================================================
FEffect::~FEffect(){
}

//============================================================
// <T>����ģ����Ϣ��</T>
//
// @param renderableDescriptor ��Ⱦ����
// @param pCode ����
// @param pTemplateContext ģ�廷��
// @return ������
//============================================================
TResult FEffect::BuildTemplate(SRenderableDescriptor& renderableDescriptor, MString* pCode, FTemplateContext* pTemplateContext){
   return ESuccess;
}

//============================================================
// <T>������Ⱦ�����佨��Ч����������</T>
//
// @param renderableDescriptor ��Ⱦ������
// @return Ч��������
//============================================================
TResult FEffect::BuildDescripter(SRenderableDescriptor& renderableDescriptor){
   return ESuccess;
}

//============================================================
// <T>���ô���</T>
//
// @return ������
//============================================================
TResult FEffect::Setup(){
   // ��������
   _program = _renderDevice->CreateProgrom();
   _program->Setup();
   return ESuccess;
}

//============================================================
// <T>����������Ϣ��</T>
//
// @param pConfig ���ô���
// @return ������
//============================================================
TResult FEffect::LoadConfig(FXmlNode* pConfig){
   // ������������Ϣ
   _descriptor.LoadConfig(pConfig);
   //............................................................
   // ����������Ϣ
   TXmlNodeIteratorC iterator = pConfig->NodeIteratorC();
   while(iterator.Next()){
      FXmlNode* pNode = *iterator;
      //............................................................
      // �����������弯��
      if(pNode->IsName("Parameter")){
         FRenderShaderParameter* pParameter = _renderDevice->CreateObject<FRenderShaderParameter>(MO_RENDEROBJECT_SHADERPARAMETER);
         pParameter->LoadConfig(pNode);
         _program->ParameterPush(pParameter);
         continue;
      }
      //............................................................
      // �������Զ��弯��
      if(pNode->IsName("Attribute")){
         FRenderShaderAttribute* pAttribute = _renderDevice->CreateObject<FRenderShaderAttribute>(MO_RENDEROBJECT_SHADERATTRIBUTE);
         pAttribute->LoadConfig(pNode);
         _program->AttributePush(pAttribute);
         continue;
      }
      //............................................................
      // ����ȡ�������弯��
      if(pNode->IsName("Sampler")){
         FRenderShaderSampler* pSampler = _renderDevice->CreateObject<FRenderShaderSampler>(MO_RENDEROBJECT_SHADERSAMPLER);
         pSampler->LoadConfig(pNode);
         _program->SamplerPush(pSampler);
         continue;
      }
   }
   return ESuccess;
}

//============================================================
// <T>��������</T>
//
// @return ������
//============================================================
TResult FEffect::Build(){
   // �������
   _program->VertexShader()->Build(_vertexSource);
   _program->FragmentShader()->Build(_fragmentSource);
   // ��������
   _program->Build();
   _program->Link();
   return ESuccess;
}

//============================================================
// <T>�����С��</T>
//
// @return ������
//============================================================
TResult FEffect::Resize(TInt width, TInt height){
   return ESuccess;
}

//============================================================
// <T>���ƴ���</T>
//
// @return ������
//============================================================
TResult FEffect::DrawRenderable(FRenderRegion* pRegion, FRenderable* pRenderable){
   return ESuccess;
}

//============================================================
// <T>���ƴ���</T>
//
// @return ������
//============================================================
TResult FEffect::DrawGroup(FRenderRegion* pRegion, TInt offset, TInt count){
   MO_CHECK(pRegion, return ENull);
   FRenderableCollection* pRenderables = pRegion->VisibleRenderables();
   for(TInt n = 0; n < count; n++){
      FRenderable* pRenderable = pRenderables->Get(offset + n);
      DrawRenderable(pRegion, pRenderable);
   }
   return ESuccess;
}

MO_NAMESPACE_END
