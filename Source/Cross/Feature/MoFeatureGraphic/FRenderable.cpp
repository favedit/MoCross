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
   _pTextures = MO_CREATE(FRenderTextureCollection);
   _pVertexStreams = MO_CREATE(FRenderVertexStreams);
   MO_CLEAR(_pIndexBuffer);
   MO_CLEAR(_pActiveEffect);
}

//============================================================
// <T>�����ɻ��ƶ���</T>
//============================================================
FRenderable::~FRenderable(){
   MO_DELETE(_pVisualInfo);
   MO_DELETE(_pTextures);
   MO_DELETE(_pVertexStreams);
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
   // ���ù�ͷ����
   _descriptor.vertexCount = _pVertexStreams->VertexCount();
   // �������Լ���
   FRenderVertexStreamCollection* pStreams = _pVertexStreams->Streams();
   TInt count = pStreams->Count();
   for(TInt n = 0; n < count; n++){
      FRenderVertexStream* pStream = pStreams->Get(n);
      TCharC* pCode = pStream->Code();
      TInt bufferCd = RRenderAttribute::Parse(pCode);
      _descriptor.vertexBuffers[bufferCd] = ETrue;
   }
   return ESuccess;
}

//============================================================
// <T>���ݲ�ֵ�����Ͳ�����Ⱦ����</T>
//
// @param samplerCode ��ֵ������
// @return ��Ⱦ����
//============================================================
FRenderTexture* FRenderable::FindTexture(TInt samplerCode){
   TInt count = _pTextures->Count();
   for(TInt n = 0; n < count; n++){
      FRenderTexture* pTexture = _pTextures->Get(n);
      if(pTexture->SamplerCd() == samplerCode){
         return pTexture;
      }
   }
   return NULL;
}

//============================================================
// <T>���ݲ�ֵ�����ͻ����Ⱦ����</T>
//
// @param samplerCode ��ֵ������
// @return ��Ⱦ����
//============================================================
FRenderTexture* FRenderable::GetTexture(TInt samplerCode){
   FRenderTexture* pTexture = FindTexture(samplerCode);
   MO_CHECK(pTexture, return NULL);
   return pTexture;
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

MO_NAMESPACE_END
