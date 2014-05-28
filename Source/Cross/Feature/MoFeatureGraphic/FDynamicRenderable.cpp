#include "MoFgDisplay.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FDynamicRenderable, FRenderable);

//============================================================
// <T>���춯̬��Ⱦ����</T>
//============================================================
FDynamicRenderable::FDynamicRenderable(){
   _vertexTotal = 0;
   _indexTotal = 0;
}

//============================================================
// <T>������̬��Ⱦ����</T>
//============================================================
FDynamicRenderable::~FDynamicRenderable(){
}

//============================================================
// <T>���ݶ��㻺����Ϣ���һ�����㻺�塣</T>
//
// @param pBuffer ���㻺��
// @return ���㻺��
//============================================================
FRenderVertexBuffer* FDynamicRenderable::SyncVertexBuffer(FRenderVertexBuffer* pBuffer){
   FRenderVertexBuffer* pMergeVertexBuffer = NULL;
   //if(!_pVertexStreams->Buffers()->IsEmpty()){
   //   pMergeVertexBuffer = _pVertexStreams->Buffers()->Get(0);
   //}
   //// ����������
   //if(pMergeVertexBuffer == NULL){
   //   FRenderDevice* pRenderDevice = RDeviceManager::Instance().Find<FRenderDevice>();
   //   TInt stride = pBuffer->Stride();
   //   // �������㻺��
   //   pMergeVertexBuffer = pRenderDevice->CreateVertexBuffer();
   //   pMergeVertexBuffer->SetStride(stride);
   //   pMergeVertexBuffer->SetCount(_vertexTotal);
   //   pMergeVertexBuffer->Setup();
   //   pMergeVertexBuffer->BuildData();
   //   _pVertexStreams->Buffers()->Push(pMergeVertexBuffer);
   //}
   return pMergeVertexBuffer;
}

//============================================================
// <T>���ݶ�������Ϣ���һ�����㻺�塣</T>
//
// @param pBuffer ������
// @return ������
//============================================================
FRenderVertexStream* FDynamicRenderable::SyncVertexStream(FRenderVertexStream* pStream){
   //TCharC* pCode = pStream->Code();
   //FRenderVertexStream* pMergeVertexStream = _pVertexStreams->FindStream(pCode);
   //// ����������
   //if(pMergeVertexStream == NULL){
   //   // ���Ҷ��㻺��
   //   FRenderVertexBuffer* pVertexBuffer = pStream->VertexBuffer();
   //   FRenderVertexBuffer* pMergeVertexBuffer = SyncVertexBuffer(pVertexBuffer);
   //   // ����������
   //   pMergeVertexStream = FRenderVertexStream::InstanceCreate();
   //   pMergeVertexStream->SetCode(pStream->Code());
   //   pMergeVertexStream->SetFormatCd(pStream->FormatCd());
   //   pMergeVertexStream->SetVertexBuffer(pMergeVertexBuffer);
   //   _pVertexStreams->PushStream(pMergeVertexStream);
   //}
   //return pMergeVertexStream;
   return NULL;
}

//============================================================
// <T>����ָ����Ⱦ�����Ƿ���Ա���ǰ��Ⱦ����ϲ���</T>
//
// @param pRenderable ��Ⱦ����
// @return �Ƿ���Ա��ϲ�
//============================================================
TBool FDynamicRenderable::TestMergeable(FRenderable* pRenderable){
   MO_CHECK(pRenderable, return ENull);
   // ���㳣����������
   FRenderDevice* pRenderDevice = RDeviceManager::Instance().Find<FRenderDevice>();
   TInt mergeLimit = RRenderUtil::CalculateMergeLimit();
   TInt renderableCount = _renderables.Count() + 1;
   if(renderableCount > mergeLimit){
      return EFalse;
   }
   // ���㶥��������
   TInt vertexCountLimit = pRenderDevice->Capability()->VertexCountLimit();
   //FRenderVertexStreams* pVertexStreams = pRenderable->VertexStreams();
   //TInt vertexCount = pVertexStreams->VertexCount();
   //TInt vertexTotal = _vertexTotal + vertexCount;
   //if(vertexTotal > vertexCountLimit){
   //   return EFalse;
   //}
   return ETrue;
}

//============================================================
// <T>����һ����Ⱦ����</T>
//
// @param pRenderable ��Ⱦ����
// @return ������
//============================================================
TResult FDynamicRenderable::Push(FRenderable* pRenderable){
   //MO_CHECK(pRenderable, return ENull);
   //// ����Ƿ���Ժϲ�
   //TBool mergeable = TestMergeable(pRenderable);
   //MO_CHECK(mergeable, return EFailure);
   //// ��������
   //FRenderVertexStreams* pVertexStreams = pRenderable->VertexStreams();
   //TInt vertexCount = pVertexStreams->VertexCount();
   //_vertexTotal += vertexCount;
   //TInt indexCount = pRenderable->IndexBuffer()->Count();
   //_indexTotal += indexCount;
   //// ������Ϣ
   //if(_renderables.IsEmpty()){
   //   _material = pRenderable->Material();
   //   _materialReference = pRenderable->MaterialReference();
   //   _pTextures->Assign(pRenderable->Textures());
   //}
   //// ����ϲ���
   //_renderables.Push(pRenderable);
   return ESuccess;
}

//============================================================
// <T>���ô���</T>
//
// @return ������
//============================================================
TResult FDynamicRenderable::Setup(){
   //FRenderDevice* pRenderDevice = RDeviceManager::Instance().Find<FRenderDevice>();
   //_pVertexStreams->SetVertexCount(_vertexTotal);
   ////............................................................
   //// ����ʵ������Ĵ���
   //_pIndexBuffer = pRenderDevice->CreateIndexBuffer();
   //_pIndexBuffer->SetCount(_indexTotal);
   //_pIndexBuffer->Setup();
   //_pIndexBuffer->BuildData();
   ////............................................................
   //TInt vertexTotal = 0;
   //TInt indexTotal = 0;
   //TInt renderableCount = _renderables.Count();
   //for(TInt n = 0; n < renderableCount; n++){
   //   FRenderable* pRenderable = _renderables.Get(n);
   //   FRenderVertexStreams* pVertexStreams = pRenderable->VertexStreams();
   //   TInt vertexCount = pVertexStreams->VertexCount();
   //   SFloatMatrix3d& renderableMatrix = pRenderable->Matrix();
   //   FRenderVertexBufferCollection::TIteratorC bufferIterator = pVertexStreams->Buffers()->IteratorC();
   //   //............................................................
   //   // ����任����
   //   SFloatMatrix3d modelMatrix;
   //   modelMatrix.Assign(renderableMatrix);
   //   while(bufferIterator.Next()){
   //      // ��ö�������
   //      FRenderVertexBuffer* pVertexBuffer = *bufferIterator;
   //      TInt vertexStride = pVertexBuffer->Stride();
   //      TInt vertexDataLength = pVertexBuffer->DataLength();
   //      TByte* pVertexData = pVertexBuffer->DataMemory<TByte>();
   //      // д�붥������
   //      FRenderVertexBuffer* pMergeVertexBuffer = SyncVertexBuffer(pVertexBuffer);
   //      MO_ASSERT(pMergeVertexBuffer->Stride() == vertexStride);
   //      TByte* pMergeVertexData = pMergeVertexBuffer->DataMemory<TByte>();
   //      pMergeVertexData += vertexStride * vertexTotal;
   //      RBytes::Copy(pMergeVertexData, pVertexData, vertexDataLength);
   //      // ���������
   //      FRenderVertexStreamCollection::TIteratorC streamIterator = pVertexStreams->Streams()->IteratorC();
   //      while(streamIterator.Next()){
   //         FRenderVertexStream* pVertexStream = *streamIterator;
   //         TCharC* pBufferCode = pVertexStream->Code();
   //         TInt vertexOffset = pVertexStream->Offset();
   //         FRenderVertexStream* pMergeVertexStream = SyncVertexStream(pVertexStream);
   //         FRenderVertexBuffer* pMergeVertexBuffer = pMergeVertexStream->VertexBuffer();
   //         if(RString::Equals(pBufferCode, "Position")){
   //            // ����λ��Ϊ����λ��
   //            for(TInt i = 0; i < vertexCount; i++){
   //               TFloat* pVertexDataReader = (TFloat*)(pVertexData + vertexStride * i + vertexOffset);
   //               TFloat* pMergePositionWriter = (TFloat*)(pMergeVertexData + vertexStride * i + vertexOffset);
   //               SFloatPoint3 modelPosition = modelMatrix.TransformPoint3(pVertexDataReader[0], pVertexDataReader[1], pVertexDataReader[2]);
   //               *pMergePositionWriter++ = modelPosition.x;
   //               *pMergePositionWriter++ = modelPosition.y;
   //               *pMergePositionWriter++ = modelPosition.z;
   //            }
   //         }
   //      }
   //   }
   //   //............................................................
   //   // �����Ⱦ������������
   //   FRenderIndexBuffer* pIndexBuffer = pRenderable->IndexBuffer();
   //   TInt indexCount = pIndexBuffer->Count();
   //   TUint16* pIndexData = pIndexBuffer->DataMemory<TUint16>();
   //   // �����������
   //   TUint16* pMergeIndexWriter = _pIndexBuffer->DataMemory<TUint16>();
   //   pMergeIndexWriter += indexTotal;
   //   for(TInt i = 0; i < indexCount; i++){
   //      *pMergeIndexWriter++ = vertexTotal + pIndexData[i];
   //   }
   //   //............................................................
   //   vertexTotal += vertexCount;
   //   indexTotal += indexCount;
   //}
   //FRenderVertexStreamCollection::TIteratorC streamIterator = _pVertexStreams->Streams()->IteratorC();
   //while(streamIterator.Next()){
   //   FRenderVertexStream* pVertexStream = *streamIterator;
   //   pVertexStream->VertexBuffer()->UploadData();
   //}
   //_pIndexBuffer->UploadData();
   ////............................................................
   //// ���ò���
   //MO_INFO("Build dynamic renderable. (count=%d, vertex_total=%d, index_total=%d)",
   //      _renderables.Count(), vertexTotal, indexTotal);
   return ESuccess;
}

MO_NAMESPACE_END
