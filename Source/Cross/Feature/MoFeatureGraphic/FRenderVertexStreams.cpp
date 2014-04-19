#include "MoFgRender.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>������Ⱦ���㻺�塣</T>
//============================================================
FRenderVertexStreams::FRenderVertexStreams(){
   _vertexCount = 0;
   _instanceSize = 0;
   _instanceCount = 0;
   _pBuffers = MO_CREATE(FRenderVertexBufferCollection);
   _pStreams = MO_CREATE(FRenderVertexStreamCollection);
}

//============================================================
// <T>������Ⱦ���㻺�塣</T>
//============================================================
FRenderVertexStreams::~FRenderVertexStreams(){
   MO_DELETE(_pBuffers);
   MO_DELETE(_pStreams);
}

//============================================================
// <T>�ж�������Ϣ��ȡ�</T>
//
// @param pStream ������
// @return �Ƿ����
//============================================================
TBool FRenderVertexStreams::EqualsDescription(FRenderVertexStreams* pStreams){
   TInt count = _pStreams->Count();
   if(pStreams->Streams()->Count() != count){
      return EFalse;
   }
   for(TInt n = 0; n < count; n++){
      FRenderVertexStream* pSourceStream = pStreams->Streams()->Get(n);
      FRenderVertexStream* pStream = _pStreams->Get(n);
      if(pStream->BufferCd() != pSourceStream->BufferCd()){
         return EFalse;
      }
      if(pStream->FormatCd() != pSourceStream->FormatCd()){
         return EFalse;
      }
      if(pStream->Stride() != pSourceStream->Stride()){
         return EFalse;
      }
   }
   return ETrue;
}

//============================================================
// <T>�������Ͳ��������ݡ�</T>
//
// @param bufferCd ������
// @return ������
//============================================================
FRenderVertexStream* FRenderVertexStreams::FindStream(ERenderVertexBuffer bufferCd){
   TInt count = _pStreams->Count();
   for(TInt n = 0; n < count; n++){
      FRenderVertexStream* pStream = _pStreams->Get(n);
      if(pStream->BufferCd() == bufferCd){
         return pStream;
      }
   }
   return NULL;
}

//============================================================
// <T>�������ͻ�������ݡ�</T>
//
// @param bufferCd ������
// @return ������
//============================================================
FRenderVertexStream* FRenderVertexStreams::GetStream(ERenderVertexBuffer bufferCd){
   FRenderVertexStream* pStream = FindStream(bufferCd);
   MO_CHECK(pStream, return NULL);
   return pStream;
}

//============================================================
// <T>����һ����������</T>
//
// @param pStream ������
// @return ������
//============================================================
TResult FRenderVertexStreams::PushStream(FRenderVertexStream* pStream){
   // ���붥����
   MO_CHECK(pStream, return ENull);
   _pStreams->Push(pStream);
   // ���붥�㻺��
   FRenderVertexBuffer* pBuffer = pStream->VertexBuffer();
   MO_CHECK(pBuffer, return ENull);
   _pBuffers->PushUnique(pBuffer);
   return ESuccess;
}

//============================================================
// <T>���������ݼ��ϡ�</T>
//
// @param pStreams �����ͼ���
// @return ������
//============================================================
TResult FRenderVertexStreams::Assign(FRenderVertexStreams* pStreams){
   MO_CHECK(pStreams, return ENull);
   _vertexCount = pStreams->VertexCount();
   _instanceSize = pStreams->InstanceSize();
   _instanceCount = pStreams->InstanceCount();
   _pBuffers->Assign(pStreams->Buffers());
   _pStreams->Assign(pStreams->Streams());
   return ESuccess;
}

MO_NAMESPACE_END
