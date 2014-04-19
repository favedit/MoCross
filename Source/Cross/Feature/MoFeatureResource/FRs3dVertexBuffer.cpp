#include "MoFrContent3dModel.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FRs3dVertexBuffer, FInstance);

//============================================================
// <T>������Դ3D���㻺�塣</T>
//============================================================
FRs3dVertexBuffer::FRs3dVertexBuffer(){
   _count = 0;
   _stride = 0;
   _pData = MO_CREATE(FBytes);
}

//============================================================
// <T>������Դ3D���㻺�塣</T>
//============================================================
FRs3dVertexBuffer::~FRs3dVertexBuffer(){
   MO_DELETE(_pData);
}

//============================================================
// <T>�������Ͳ��������ݡ�</T>
//
// @param bufferCd ��������
// @return ������
//============================================================
FRs3dVertexStream* FRs3dVertexBuffer::FindStream(EContent3dVertexBuffer bufferCd){
   TInt count = _streams.Count();
   for(TInt n = 0; n < count; n++){
      FRs3dVertexStream* pStream = _streams.Get(n);
      if(pStream->BufferCd() == bufferCd){
         return pStream;
      }
   }
   return NULL;
}

//============================================================
// <T>���������ﷴ���л���Ϣ���ݡ�</T>
//
// @param pInput ������
// @return ������
//============================================================
TResult FRs3dVertexBuffer::Unserialize(IDataInput* pInput){
   MO_CHECK(pInput, return ENull);
   // ��ȡ����������
   TInt streamCount = pInput->ReadInt8();
   for(TInt n = 0; n < streamCount; n++){
      FRs3dVertexStream* pStream = FRs3dVertexStream::InstanceCreate();
      pStream->SetBuffer(this);
      pStream->Unserialize(pInput);
      _streams.Push(pStream);
   }
   // ��ȡ�������
   _count = pInput->ReadInt32();
   _stride = pInput->ReadUint8();
   // ��ȡ����
   _pData->ForceLength(_stride * _count);
   pInput->Read(_pData->Memory(), _pData->Length());
   return ESuccess;
}

//============================================================
// <T>������ݡ�</T>
//============================================================
void FRs3dVertexBuffer::Clear(){
   _streams.Clear();
}

MO_NAMESPACE_END
