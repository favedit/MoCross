#include "MoPd10Render.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FPd10RenderIndexBuffer, FRenderVertexBuffer);

//============================================================
// <T>������Ⱦ�������塣</T>
//============================================================
FPd10RenderIndexBuffer::FPd10RenderIndexBuffer(){
   MO_CLEAR(_piBuffer);
}

//============================================================
// <T>������Ⱦ�������塣</T>
//============================================================
FPd10RenderIndexBuffer::~FPd10RenderIndexBuffer(){
   MO_RELEASE(_piBuffer);
}

//============================================================
// <T>���ô���</T>
//
// @return ������
//============================================================
TResult FPd10RenderIndexBuffer::OnSetup(){
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
TResult FPd10RenderIndexBuffer::Upload(TByteC* pData, TInt length){
   // ������
   MO_CHECK(pData, return ENull);
   MO_CHECK(length > 0, return EFailure);
   TResult resultCd = ESuccess;
   MO_CHECK(_pDevice, return ENull);
   FPd10RenderDevice* pRenderDevice = _pDevice->Convert<FPd10RenderDevice>();
   MO_RELEASE(_piBuffer);
   //............................................................
   // ��������
   D3D10_BUFFER_DESC descriptor = {0};
   descriptor.ByteWidth = _dataLength;
   descriptor.Usage = D3D10_USAGE_DEFAULT;
   descriptor.BindFlags = D3D10_BIND_INDEX_BUFFER;
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
TResult FPd10RenderIndexBuffer::Suspend(){
   return ESuccess;
}

//============================================================
// <T>��������</T>
//
// @return ������
//============================================================
TResult FPd10RenderIndexBuffer::Resume(){
   return ESuccess;
}

//============================================================
// <T>��������</T>
//
// @return ������
//============================================================
TResult FPd10RenderIndexBuffer::Dispose(){
   MO_RELEASE(_piBuffer);
   return ESuccess;
}

MO_NAMESPACE_END
