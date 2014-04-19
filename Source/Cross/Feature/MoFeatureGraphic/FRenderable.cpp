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
   MO_CLEAR(_pEffects);
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
FEffect* FRenderable::EffectFind(TCharC* pName){
   FEffect* pEffect = NULL;
   if(_pEffects != NULL){
      TInt count = _pEffects->Count();
      for(TInt n = 0; n < count; n++){
         FEffect* pFind = _pEffects->Get(n);
         if(pFind->IsName(pName)){
            pEffect = pFind;
            break;
         }
      }
   }
   return pEffect;
}

//============================================================
// <T>��ָ�����Ƶ�Ч������</T>
//
// @param pEffect Ч����
// @return ������
//============================================================
TResult FRenderable::EffectBind(FEffect* pEffect){
   if(_pEffects == NULL){
      _pEffects = MO_CREATE(FEffectCollection);
   }
   _pEffects->Push(pEffect);
   return ESuccess;
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
      ERenderVertexBuffer bufferCd = (ERenderVertexBuffer)pStream->BufferCd();
      _descriptor.vertexBuffers[bufferCd] = ETrue;
   }
   return ESuccess;
}

//============================================================
// <T>���ݲ�ֵ�����Ͳ�����Ⱦ����</T>
//
// @param samplerCd ��ֵ������
// @return ��Ⱦ����
//============================================================
FRenderTexture* FRenderable::FindTexture(ERenderSampler samplerCd){
   TInt count = _pTextures->Count();
   for(TInt n = 0; n < count; n++){
      FRenderTexture* pTexture = _pTextures->Get(n);
      if(pTexture->SamplerCd() == samplerCd){
         return pTexture;
      }
   }
   return NULL;
}

//============================================================
// <T>���ݲ�ֵ�����ͻ����Ⱦ����</T>
//
// @param samplerCd ��ֵ������
// @return ��Ⱦ����
//============================================================
FRenderTexture* FRenderable::GetTexture(ERenderSampler samplerCd){
   FRenderTexture* pTexture = FindTexture(samplerCd);
   MO_CHECK(pTexture, return NULL);
   return pTexture;
}

//============================================================
// <T>����ǰ�ô���</T>
//
// @return ������
//============================================================
TResult FRenderable::ProcessBefore(TAny* pParameter){
   return ESuccess;
}

//============================================================
// <T>���ܺ��ô���</T>
//
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
   if(_pEffects != NULL){
      _pEffects->Clear();
   }
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
