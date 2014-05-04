#include "MoPd11Render.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FPd11RenderShaderBuffer, FRenderObject);

//============================================================
// <T>������Ⱦ�����塣</T>
//============================================================
FPd11RenderShaderBuffer::FPd11RenderShaderBuffer(){
   _dataLength = 0;
   _pData = MO_CREATE(FBytes);
   _pCommit = MO_CREATE(FBytes);
   _commitLength = 0;
   _slot = -1;
   MO_CLEAR(_piBuffer);
}

//============================================================
// <T>������Ⱦ�����塣</T>
//============================================================
FPd11RenderShaderBuffer::~FPd11RenderShaderBuffer(){
   MO_DELETE(_pData);
   MO_DELETE(_pCommit);
   MO_RELEASE(_piBuffer);
}

//============================================================
// <T>���ô���</T>
//
// @return ������
//============================================================
TResult FPd11RenderShaderBuffer::Setup(){
   MO_CHECK(_pDevice, return ENull);
   MO_CHECK(_dataLength > 0, return EOutRange);
   FPd11RenderDevice* pRenderDevice = _pDevice->Convert<FPd11RenderDevice>();
   // ���û���
   _pData->SetLength(_dataLength);
   RBytes::Clear(_pData->Memory(), _dataLength);
   _pCommit->SetLength(_dataLength);
   RBytes::Clear(_pCommit->Memory(), _dataLength);
   // ��������
   D3D11_BUFFER_DESC descriptor;
   RType<D3D11_BUFFER_DESC>::Clear(&descriptor);
   descriptor.ByteWidth = _dataLength;
   descriptor.Usage = D3D11_USAGE_DEFAULT;
   descriptor.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
   // ��������
   D3D11_SUBRESOURCE_DATA data;
   RType<D3D11_SUBRESOURCE_DATA>::Clear(&data);
   data.pSysMem = _pData->Memory();
   // ��������
   HRESULT dxResult = pRenderDevice->NativeDevice()->CreateBuffer(&descriptor, &data, &_piBuffer);
   if(FAILED(dxResult)){
      MO_FATAL("Create buffer failure.");
      return EFailure;
   }
   return ESuccess;
}

//============================================================
// <T>���ó������������ݡ�</T>
//
// @param pName ����
// @param pData ����
// @param length ����
// @return ������
//============================================================
TResult FPd11RenderShaderBuffer::SetData(TInt index, TAnyC* pData, TInt length){
   // ������
   MO_CHECK(index >= 0, return EOutRange);
   MO_CHECK(pData, return ENull);
   MO_CHECK(length >= 0, return EOutRange);
   TInt endPosition = index + length;
   MO_CHECK(endPosition <= _dataLength, return EOutRange);
   // �����ύ��С
   if(endPosition > _commitLength){
      _commitLength = endPosition;
   }
   // �����ڴ�
   TByte* pMemory = _pData->Memory() + index;
   MO_LIB_MEMORY_COPY(pMemory, length, pData, length);
   return ESuccess;
}

//============================================================
// <T>���´���</T>
//
// @return ������
//============================================================
TResult FPd11RenderShaderBuffer::Update(){
   MO_CHECK(_pDevice, return ENull);
   TResult resultCd = ESuccess;
   FPd11RenderDevice* pRenderDevice = _pDevice->Convert<FPd11RenderDevice>();
   //............................................................
   TByte* pMemoryData = _pData->Memory();
   TByte* pCommitData = _pCommit->Memory();
   // ���ҿ�ʼ�����λ��
   TInt startPosition = 0;
   for(TInt n = startPosition; n < _commitLength; n++){
      if(pMemoryData[n] != pCommitData[n]){
         startPosition = n;
         break;
      }
   }
   // ���ҽ��������λ��
   TInt endPosition = _commitLength - 1;
   for(TInt n = endPosition; n >= startPosition; n--){
      if(pMemoryData[n] != pCommitData[n]){
         endPosition = n;
         break;
      }
   }
   // �ύ����
   if(startPosition != endPosition){
      TInt length = endPosition - startPosition;
      // д������
      D3D11_MAPPED_SUBRESOURCE resource;
      pRenderDevice->NativeContext()->Map(_piBuffer, 0, D3D11_MAP_READ_WRITE, 0, &resource);
      MO_LIB_MEMORY_COPY(resource.pData, length, pMemoryData + startPosition, length);
      pRenderDevice->NativeContext()->Unmap(_piBuffer, 0);
      // �����ύ����
      MO_LIB_MEMORY_COPY(pCommitData + startPosition, length, pMemoryData + startPosition, length);
   }
   _commitLength = 0;
   return ESuccess;
}

MO_NAMESPACE_END
