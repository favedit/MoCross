#include "MoBfRender.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FBfRenderVertexBuffer, FRenderVertexBuffer);

//============================================================
// <T>������Ⱦ���㻺�塣</T>
//============================================================
FBfRenderVertexBuffer::FBfRenderVertexBuffer(){
   MO_CLEAR(_piBuffer);
}

//============================================================
// <T>������Ⱦ���㻺�塣</T>
//============================================================
FBfRenderVertexBuffer::~FBfRenderVertexBuffer(){
   MO_RELEASE(_piBuffer);
}

//============================================================
// <T>���ô���</T>
//
// @return ������
//============================================================
TResult FBfRenderVertexBuffer::OnSetup(){
   TResult resultCd = ESuccess;
   MO_CHECK(_pDevice, return ENull);
   FBfRenderDevice* pRenderDevice = _pDevice->Convert<FBfRenderDevice>();
   //............................................................
   _dataLength = _stride * _count;
   //if(_dataLength == 0){
   //   return EContinue;
   //}
   //............................................................
   //// ��������
   //D3D10_BUFFER_DESC description;
   //RType<D3D10_BUFFER_DESC>::Clear(&description);
   //description.BindFlags = D3D10_BIND_VERTEX_BUFFER;
   //description.ByteWidth = _dataLength;
   //description.CPUAccessFlags = 0;
   //description.MiscFlags = 0;
   //description.Usage = D3D10_USAGE_STAGING;
   //HRESULT dxResult = pRenderDevice->NativeDevice()->CreateBuffer(&description, NULL, &_piBuffer);
   //if(FAILED(dxResult)){
   //   MO_FATAL("Create buffer failure.");
   //   return EFailure;
   //}
   return resultCd;
}

//============================================================
// <T>�ϴ����ݡ�</T>
//
// @param pData ����ָ��
// @param length ���ݳ���
// @return ������
//============================================================
TResult FBfRenderVertexBuffer::Upload(TByteC* pData, TInt length){
   // ������
   MO_CHECK(pData, return ENull);
   MO_CHECK(length > 0, return EFailure);
   TResult resultCd = ESuccess;
   MO_CHECK(_pDevice, return ENull);
   FBfRenderDevice* pRenderDevice = _pDevice->Convert<FBfRenderDevice>();
   MO_RELEASE(_piBuffer);
   //............................................................
   // ��������
   D3D10_BUFFER_DESC descriptor = {0};
   descriptor.ByteWidth = _dataLength;
   descriptor.Usage = D3D10_USAGE_DEFAULT;
   descriptor.BindFlags = D3D10_BIND_VERTEX_BUFFER;
   descriptor.CPUAccessFlags = 0;
   descriptor.MiscFlags = 0;
   // ��������
   D3D10_SUBRESOURCE_DATA data = {0};
   data.pSysMem = pData;
   data.SysMemPitch = 0;
   data.SysMemSlicePitch = 0;
   // ��������
   HRESULT dxResult = pRenderDevice->NativeDevice()->CreateBuffer(&descriptor, &data, &_piBuffer);
   if(FAILED(dxResult)){
      MO_FATAL("Create buffer failure.");
      return EFailure;
   }
   return ESuccess;
}

//============================================================
// <T>������</T>
//
// @return ������
//============================================================
TResult FBfRenderVertexBuffer::Suspend(){
   return ESuccess;
}

//============================================================
// <T>��������</T>
//
// @return ������
//============================================================
TResult FBfRenderVertexBuffer::Resume(){
   return ESuccess;
}

//============================================================
// <T>��������</T>
//
// @return ������
//============================================================
TResult FBfRenderVertexBuffer::Dispose(){
   return ESuccess;
}

MO_NAMESPACE_END
