#include "MoFgDisplay.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FInstanceRenderable, FRenderable);

//============================================================
// <T>����ʵ����Ⱦ����</T>
//============================================================
FInstanceRenderable::FInstanceRenderable(){
}

//============================================================
// <T>����ʵ����Ⱦ����</T>
//============================================================
FInstanceRenderable::~FInstanceRenderable(){
}

//============================================================
// <T>���ô���</T>
//
// @return ������
//============================================================
TResult FInstanceRenderable::Setup(){
   MO_ASSERT(_renderable);
   FRenderDevice* pRenderDevice = RDeviceManager::Instance().Find<FRenderDevice>();
   //............................................................
   // �������ʵ�����
   TInt vertexCount = _renderable->VertexStreams()->VertexCount();
   TInt boneCount = _renderable->CalculateBoneMatrix(NULL, 0, 0);
   if(_instanceCount <= 0){
      _instanceCount = RRenderUtil::CalculateInstanceCount(vertexCount, boneCount);
   }
   MO_ASSERT(_instanceCount > 0);
   //............................................................
   // ������������
   TInt vertexTotal = vertexCount * _instanceCount;
   _pVertexStreams->SetVertexCount(vertexTotal);
   _pVertexStreams->SetInstanceSize(vertexCount);
   _pVertexStreams->SetInstanceCount(_instanceCount);
   // ����ʵ����Ż���
   FRenderVertexBuffer* pInstanceIndexBuffer = pRenderDevice->CreateVertexBuffer();
   pInstanceIndexBuffer->SetCount(vertexTotal);
   pInstanceIndexBuffer->SetStride(sizeof(TFloat));
   pInstanceIndexBuffer->Setup();
   pInstanceIndexBuffer->BuildData();
   TFloat* pInstanceIdWriter = pInstanceIndexBuffer->DataMemory<TFloat>();
   for(TInt n = 0; n < _instanceCount; n++){
      RFloats::Fill(pInstanceIdWriter, vertexCount, (TFloat)n);
      pInstanceIdWriter += vertexCount;
   }
   pInstanceIndexBuffer->UploadData();
   // ����ʵ�������
   FRenderVertexStream* pInstanceIdStream = FRenderVertexStream::InstanceCreate();
   pInstanceIdStream->SetCode("Instance");
   pInstanceIdStream->SetFormatCd(ERenderAttributeFormat_Float1);
   pInstanceIdStream->SetVertexBuffer(pInstanceIndexBuffer);
   _pVertexStreams->PushStream(pInstanceIdStream);
   // ��������������
   FRenderVertexStreams* pVertexStreams = _renderable->VertexStreams();
   FRenderVertexBufferCollection::TIteratorC bufferIterator = pVertexStreams->Buffers()->IteratorC();
   while(bufferIterator.Next()){
      // ��ö��㻺��
      FRenderVertexBuffer* pVertexBuffer = *bufferIterator;
      TInt stride = pVertexBuffer->Stride();
      TByte* pVertexData = pVertexBuffer->DataMemory<TByte>();
      TInt vertexDataLength = pVertexBuffer->DataLength();
      // �������㻺��
      FRenderVertexBuffer* pInstanceVertexBuffer = pRenderDevice->CreateVertexBuffer();
      pInstanceVertexBuffer->SetCount(vertexTotal);
      pInstanceVertexBuffer->SetStride(stride);
      pInstanceVertexBuffer->Setup();
      pInstanceVertexBuffer->BuildData();
      TByte* pInstanceVertexWriter = pInstanceVertexBuffer->DataMemory<TByte>();
      for(TInt n = 0; n < _instanceCount; n++){
         RBytes::Copy(pInstanceVertexWriter, pVertexData, vertexDataLength);
         pInstanceVertexWriter += vertexDataLength;
      }
      // ����������
      FRenderVertexStreamCollection::TIteratorC iterator = pVertexStreams->Streams()->IteratorC();
      while(iterator.Next()){
         // ��ö�������Ϣ
         FRenderVertexStream* pVertexStream = *iterator;
         if(pVertexStream->VertexBuffer() != pVertexBuffer){
            continue;
         }
         TCharC* pBufferCode = pVertexStream->Code();
         ERenderAttributeFormat formatCd = pVertexStream->FormatCd();
         TInt offset = pVertexStream->Offset();
         // ������Ⱦ��
         FRenderVertexStream* pInstanceVertexStream = FRenderVertexStream::InstanceCreate();
         pInstanceVertexStream->SetCode(pBufferCode);
         pInstanceVertexStream->SetFormatCd(formatCd);
         pInstanceVertexStream->SetOffset(offset);
         pInstanceVertexStream->SetVertexBuffer(pInstanceVertexBuffer);
         _pVertexStreams->PushStream(pInstanceVertexStream);
         //// �������㻺��
         //if(bufferCd == ERenderAttribute_BoneIndex){
         //   // ���¼����ͷ����λ��
         //   pInstanceVertexBuffer->SetStride(sizeof(TFloat) * 4);
         //   pInstanceVertexBuffer->Setup();
         //   pInstanceVertexBuffer->SetupData();
         //   TFloat boneIndex = 0.0f;
         //   TInt vertexUnitTotal = 4 * vertexCount;
         //   TFloat* pInstanceVertexWriter = pInstanceVertexBuffer->DataMemory<TFloat>();
         //   for(TInt n = 0; n < _instanceCount; n++){
         //      for(TInt i = 0; i < vertexUnitTotal; i++){
         //         *pInstanceVertexWriter++ = (TFloat)pVertexData[i] + boneIndex;
         //      }
         //      boneIndex += (TFloat)(boneCount);
         //   }
         //   formatCd = ERenderVertexFormat_Float4;
         //}else{
         //   // ��������
         //   pInstanceVertexBuffer->SetStride(stride);
         //   pInstanceVertexBuffer->Setup();
         //   pInstanceVertexBuffer->SetupData();
         //   TByte* pInstanceVertexWriter = pInstanceVertexBuffer->DataMemory<TByte>();
         //   for(TInt n = 0; n < _instanceCount; n++){
         //      for(TInt i = 0; i < vertexCount; i++){
         //      }
         //      RBytes::Copy(pInstanceVertexWriter, pVertexData, vertexDataLength);
         //      pInstanceVertexWriter += vertexDataLength;
         //   }
         //}
      }
      pInstanceVertexBuffer->UploadData();
   }
   //............................................................
   // �����Ⱦ���󶥵�����
   FRenderIndexBuffer* pIndexBuffer = _renderable->IndexBuffer();
   TInt indexCount = pIndexBuffer->Count();
   ERenderIndexStride indexStrideCd = pIndexBuffer->StrideCd();
   TUint16* pIndexData = pIndexBuffer->DataMemory<TUint16>();
   // ����ʵ������Ĵ���
   TInt indexTotal = indexCount * _instanceCount;
   _pIndexBuffer = pRenderDevice->CreateIndexBuffer();
   _pIndexBuffer->SetCount(indexTotal);
   _pIndexBuffer->SetStrideCd(indexStrideCd);
   _pIndexBuffer->SetInstanceStride(indexCount);
   _pIndexBuffer->SetInstanceCount(_instanceCount);
   _pIndexBuffer->Setup();
   // �������
   _pIndexBuffer->BuildData();
   TUint16 indexPosition = 0;
   TUint16* pInstanceIndexWriter = _pIndexBuffer->DataMemory<TUint16>();
   for(TInt n = 0; n < _instanceCount; n++){
      for(TInt i = 0; i < indexCount; i++){
         *pInstanceIndexWriter++ = indexPosition + pIndexData[i];
      }
      indexPosition += vertexCount;
   }
   _pIndexBuffer->UploadData();
   //............................................................
   // ���ò���
   _material = _renderable->Material();
   _pTextures->Assign(_renderable->Textures());
   MO_INFO("Build instance renderable. (type_name=%s, vertex_count=%d, index_count=%d, instance=%d)",
         (TCharC*)_typeName, vertexCount, indexCount, _instanceCount);
   return ESuccess;
}

MO_NAMESPACE_END
