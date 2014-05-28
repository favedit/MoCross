#include "MoFgBase.h"
#include "MoFgVisual.h"
#include "MoFgRender.h"
#include "MoFgTechnique.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FRenderable, FInstance);

//============================================================
// <T>����ɻ��ƶ���</T>
//============================================================
FRenderable::FRenderable(){
   _pVisualInfo = MO_CREATE(FVisualNode);
   _pVisualInfo->SetRenderable(this);
   MO_CLEAR(_pActiveEffect);
}

//============================================================
// <T>�����ɻ��ƶ���</T>
//============================================================
FRenderable::~FRenderable(){
   MO_DELETE(_pVisualInfo);
}

//============================================================
// <T>�����Ƿ���ָ����������ԡ�</T>
//
// @param pCode ����
// @return �Ƿ���
//============================================================
TBool FRenderable::AttributeContains(TCharC* pCode){
   FRenderableAttribute* pAttribute = _geometry->AttributeFind(pCode);
   return (pAttribute != NULL);
}

//============================================================
// <T>����ָ����������ԡ�</T>
//
// @param pCode ����
// @return ����
//============================================================
FRenderableAttribute* FRenderable::AttributeFind(TCharC* pCode){
   return _geometry->AttributeFind(pCode);
}

//============================================================
// <T>���ָ����������ԡ�</T>
//
// @param pCode ����
// @return ����
//============================================================
FRenderableAttribute* FRenderable::AttributeGet(TCharC* pCode){
   return _geometry->AttributeGet(pCode);
}

//============================================================
// <T>�����Ƿ���ָ�������ȡ������</T>
//
// @param pCode ����
// @return �Ƿ���
//============================================================
TBool FRenderable::SamplerContains(TCharC* pCode){
   FRenderableSampler* pSampler = SamplerFind(pCode);
   return (pSampler != NULL);
}

//============================================================
// <T>����ָ�������ȡ������</T>
//
// @param pCode ����
// @return ȡ����
//============================================================
FRenderableSampler* FRenderable::SamplerFind(TCharC* pCode){
   TInt count = _samplers.Count();
   for(TInt n = 0; n < count; n++){
      FRenderableSampler* pRenderableSampler = _samplers.Get(n);
      if(pRenderableSampler->IsCode(pCode)){
         return pRenderableSampler;
      }
   }
   return NULL;
}

//============================================================
// <T>���ָ�������ȡ������</T>
//
// @param pCode ����
// @return ȡ����
//============================================================
FRenderableSampler* FRenderable::SamplerGet(TCharC* pCode){
   FRenderableSampler* pRenderableSampler = SamplerFind(pCode);
   if(pRenderableSampler == NULL){
      MO_FATAL("Can't find renderable sampler. (code=%s)", pCode);
   }
   return pRenderableSampler;
}

//============================================================
// <T>����ָ����������ȡ������</T>
//
// @param pPackCode �������
// @return ȡ����
//============================================================
FRenderableSampler* FRenderable::SamplerPackFind(TCharC* pPackCode){
   TInt count = _samplers.Count();
   for(TInt n = 0; n < count; n++){
      FRenderableSampler* pRenderableSampler = _samplers.Get(n);
      if(pRenderableSampler->IsPackCode(pPackCode)){
         return pRenderableSampler;
      }
   }
   return NULL;
}

//============================================================
// <T>���ָ����������ȡ������</T>
//
// @param pPackCode �������
// @return ȡ����
//============================================================
FRenderableSampler* FRenderable::SamplerPackGet(TCharC* pPackCode){
   FRenderableSampler* pRenderableSampler = SamplerFind(pPackCode);
   if(pRenderableSampler == NULL){
      MO_FATAL("Can't find renderable sampler. (pack_code=%s)", pPackCode);
   }
   return pRenderableSampler;
}

//============================================================
// <T>����һ��ȡ����</T>
//
// @param pSampler ȡ��
// @return ������
//============================================================
TResult FRenderable::SamplerPush(FRenderableSampler* pSampler){
   MO_CHECK(pSampler, return ENull);
   // �����Ƿ����
   TCharC* pCode = pSampler->Code();
   MO_CHECK(pCode, return ENull);
   FRenderableSampler* pFind = SamplerFind(pCode);
   if(pFind != NULL){
      MO_FATAL("Sampler is already exists. (code=%s)", pCode);
      return EDuplicate;
   }
   // �������
   _samplers.Push(pSampler);
   return ESuccess;
}

//============================================================
// <T>�Ƴ�һ��ȡ����</T>
//
// @param pSampler ȡ��
// @return ������
//============================================================
TResult FRenderable::SamplerRemove(FRenderableSampler* pSampler){
   MO_CHECK(pSampler, return ENull);
   // �����Ƿ����
   if(!_samplers.Contains(pSampler)){
      MO_FATAL("Sampler is not exists. (code=%s)", pSampler->Code());
      return ENotExists;
   }
   // �������
   _samplers.Push(pSampler);
   return ESuccess;
}

//============================================================
// <T>����ָ�����Ƶ�Ч������</T>
//
// @param pName ����
// @return Ч����
//============================================================
FRenderableEffect* FRenderable::EffectFind(TCharC* pName){
   TInt count = _effects.Count();
   for(TInt n = 0; n < count; n++){
      FRenderableEffect* pRenderableEffect = _effects.Get(n);
      if(pRenderableEffect != NULL){
         FEffect* pEffect = pRenderableEffect->Effect();
         MO_CHECK(pEffect, continue);
         if(pEffect->IsName(pName)){
            return pRenderableEffect;
         }
      }
   }
   return NULL;
}

//============================================================
// <T>��ָ�����Ƶ�Ч������</T>
//
// @param pEffect Ч����
// @return ������
//============================================================
FRenderableEffect* FRenderable::EffectBind(FEffect* pEffect){
   FRenderableEffect* pRenderableEffect = FRenderableEffect::InstanceCreate();
   pRenderableEffect->SetEffect(pEffect);
   _effects.Push(pRenderableEffect);
   return pRenderableEffect;
}

//============================================================
// <T>����ģ�;���</T>
//
// @param matrix ģ�;���
// @return ������
//============================================================
TResult FRenderable::CalculateModelMatrix(SFloatMatrix3d& matrix){
   return ESuccess;
}

//============================================================
// <T>����ģ�;���</T>
//
// @param pMatrix ���󼯺�
// @param offset λ��
// @param count ����
// @return �������
//============================================================
TInt FRenderable::CalculateBoneMatrix(SFloatMatrix3d* pMatrix, TInt offset, TInt capacity){
   return 0;
}

//============================================================
// <T>������־���ϡ�</T>
//============================================================
TResult FRenderable::BuildDescriptor(){
   //// ���ù�ͷ����
   //_descriptor.vertexCount = _pVertexStreams->VertexCount();
   //// �������Լ���
   //FRenderVertexStreamCollection* pStreams = _pVertexStreams->Streams();
   //TInt count = pStreams->Count();
   //for(TInt n = 0; n < count; n++){
   //   FRenderVertexStream* pStream = pStreams->Get(n);
   //   TCharC* pCode = pStream->Code();
   //   TInt bufferCd = RRenderAttribute::Parse(pCode);
   //   _descriptor.vertexBuffers[bufferCd] = ETrue;
   //}
   return ESuccess;
}

//============================================================
// <T>���´���</T>
//
// @param pContext ����
// @return ������
//============================================================
TResult FRenderable::Update(TAny* pContext){
   return ESuccess;
}

//============================================================
// <T>����ǰ�ô���</T>
//
// @param pContext ����
// @return ������
//============================================================
TResult FRenderable::ProcessBefore(TAny* pParameter){
   return ESuccess;
}

//============================================================
// <T>���ܺ��ô���</T>
//
// @param pContext ����
// @return ������
//============================================================
TResult FRenderable::ProcessAfter(TAny* pParameter){
   return ESuccess;
}

//============================================================
// <T>�ͷ����ݡ�</T>
//============================================================
TResult FRenderable::Free(){
   return ESuccess;
}

//============================================================
// <T>������</T>
//
// @return ������
//============================================================
TResult FRenderable::Suspend(){
   _pActiveEffect = NULL;
   _effects.Clear();
   return ESuccess;
}

//============================================================
// <T>��������</T>
//
// @return ������
//============================================================
TResult FRenderable::Resume(){
   return ESuccess;
}

//============================================================
// <T>��������</T>
//
// @return ������
//============================================================
TResult FRenderable::Dispose(){
   return ESuccess;
}

//============================================================
// <T>���ٴ���</T>
//
// @return ������
//============================================================
TResult FRenderable::Track(){
   TString dump;
   dump.Append("Renderable\n");
   //............................................................
   // ȡ������Ϣ
   TInt attributeCount = _geometry->Attributes().Count();
   dump.AppendFormat("Attribute (count=%d)\n", attributeCount);
   for(TInt n = 0; n < attributeCount; n++){
      FRenderableAttribute * pAttribute = _geometry->Attributes().Get(n);
      dump.AppendFormat("   %s = 0x%08X\n", pAttribute->Code(), pAttribute->GraphicsObject());
   }
   //............................................................
   // ȡ������Ϣ
   TInt samplerCount = _samplers.Count();
   dump.AppendFormat("Sampler (count=%d)\n", samplerCount);
   for(TInt n = 0; n < samplerCount; n++){
      FRenderableSampler* pSampler = _samplers.Get(n);
      dump.AppendFormat("   %s = 0x%08X\n", pSampler->Code(), pSampler->GraphicsObject());
   }
   MO_INFO(dump);
   return ESuccess;
}

MO_NAMESPACE_END
