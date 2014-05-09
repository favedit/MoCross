#include "MoPd9Render.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FPd9RenderIndexBuffer, FRenderVertexBuffer);

//============================================================
// <T>������Ⱦ�������塣</T>
//============================================================
FPd9RenderIndexBuffer::FPd9RenderIndexBuffer(){
   MO_CLEAR(_piBuffer);
}

//============================================================
// <T>������Ⱦ�������塣</T>
//============================================================
FPd9RenderIndexBuffer::~FPd9RenderIndexBuffer(){
   MO_RELEASE(_piBuffer);
}

//============================================================
// <T>���ô���</T>
//
// @return ������
//============================================================
TResult FPd9RenderIndexBuffer::OnSetup(){
   TResult resultCd = FRenderIndexBuffer::OnSetup();
   return resultCd;
}

//============================================================
// <T>�ϴ����ݡ�</T>
//
// @param pData ����ָ��
// @param length ���ݳ���
// @return ������
//============================================================
TResult FPd9RenderIndexBuffer::Upload(TByteC* pData, TInt length){
   // ������
   MO_CHECK(pData, return ENull);
   MO_CHECK(length > 0, return EFailure);
   TResult resultCd = ESuccess;
   MO_CHECK(_pDevice, return ENull);
   FPd9RenderDevice* pRenderDevice = _pDevice->Convert<FPd9RenderDevice>();
   MO_RELEASE(_piBuffer);
   //............................................................
   // ��������
   HRESULT dxResult = pRenderDevice->NativeDevice()->CreateIndexBuffer(_dataLength, 0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &_piBuffer, NULL);
   if(FAILED(dxResult)){
      MO_FATAL("Create buffer failure.");
      return EFailure;
   }
   // �ϴ�����
   TByte* pUpload = NULL;
   dxResult = _piBuffer->Lock( 0, 0, (TAny**)&pUpload, 0);
   if(FAILED(dxResult)){
      MO_FATAL("Lock buffer failure.");
      return EFailure;
   }
   MO_LIB_MEMORY_COPY(pUpload, _dataLength, pData, _dataLength);
   _piBuffer->Unlock();
   return ESuccess;
}

//============================================================
// <T>������</T>
//
// @return ������
//============================================================
TResult FPd9RenderIndexBuffer::Suspend(){
   return ESuccess;
}

//============================================================
// <T>��������</T>
//
// @return ������
//============================================================
TResult FPd9RenderIndexBuffer::Resume(){
   return ESuccess;
}

//============================================================
// <T>��������</T>
//
// @return ������
//============================================================
TResult FPd9RenderIndexBuffer::Dispose(){
   //MO_RELEASE(_piBuffer);
   return ESuccess;
}

MO_NAMESPACE_END
