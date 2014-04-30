#include "MoPd10Render.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FPd10RenderVertexBuffer, FRenderVertexBuffer);

//============================================================
// <T>������Ⱦ���㻺�塣</T>
//============================================================
FPd10RenderVertexBuffer::FPd10RenderVertexBuffer(){
   MO_CLEAR(_piBuffer);
}

//============================================================
// <T>������Ⱦ���㻺�塣</T>
//============================================================
FPd10RenderVertexBuffer::~FPd10RenderVertexBuffer(){
   MO_RELEASE(_piBuffer);
}

//============================================================
// <T>���ô���</T>
//
// @return ������
//============================================================
TResult FPd10RenderVertexBuffer::OnSetup(){
   TResult resultCd = ESuccess;
   MO_CHECK(_pDevice, return ENull);
   FPd10RenderDevice* pRenderDevice = _pDevice->Convert<FPd10RenderDevice>();
   //............................................................
   if(_dataLength == 0){
      return EContinue;
   }
   //............................................................
   // ��������
   D3D10_BUFFER_DESC description;
   RType<D3D10_BUFFER_DESC>::Clear(&description);
   description.BindFlags = D3D10_BIND_VERTEX_BUFFER;
   description.ByteWidth = _dataLength;
   description.CPUAccessFlags = 0;
   description.MiscFlags = 0;
   description.Usage = D3D10_USAGE_STAGING;
   HRESULT dxResult = pRenderDevice->NativeDevice()->CreateBuffer(&description, NULL, &_piBuffer);
   if(FAILED(dxResult)){
      MO_FATAL("Create buffer failure.");
      return EFailure;
   }
   return resultCd;
}

//============================================================
// <T>�ϴ����ݡ�</T>
//
// @param pData ����ָ��
// @param length ���ݳ���
// @return ������
//============================================================
TResult FPd10RenderVertexBuffer::Upload(TByteC* pData, TInt length){
   // ������
   MO_CHECK(pData, return ENull);
   MO_CHECK(length > 0, return EFailure);
   TResult resultCd = ESuccess;
   MO_CHECK(_pDevice, return ENull);
   FPd10RenderDevice* pRenderDevice = _pDevice->Convert<FPd10RenderDevice>();
   MO_RELEASE(_piBuffer);
   //............................................................
   // ��������
   D3D10_BUFFER_DESC description;
   RType<D3D10_BUFFER_DESC>::Clear(&description);
   description.BindFlags = D3D10_BIND_VERTEX_BUFFER;
   description.ByteWidth = _dataLength;
   description.CPUAccessFlags = 0;
   description.MiscFlags = 0;
   description.Usage = D3D10_USAGE_DEFAULT;
   D3D10_SUBRESOURCE_DATA data;
   RType<D3D10_SUBRESOURCE_DATA>::Clear(&data);
   data.pSysMem = pData;
   HRESULT dxResult = pRenderDevice->NativeDevice()->CreateBuffer(&description, &data, &_piBuffer);
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
TResult FPd10RenderVertexBuffer::Suspend(){
   return ESuccess;
}

//============================================================
// <T>��������</T>
//
// @return ������
//============================================================
TResult FPd10RenderVertexBuffer::Resume(){
   //// ���ɱ��
   //glGenBuffers(1, &_bufferId);
   //MO_FATAL_CHECK(_bufferId != 0, return EFailure,
   //      "Generate vertex buffer id failure. (buffer_id=%d)", _bufferId);
   //// �󶨱��
   //glBindBuffer(GL_ARRAY_BUFFER, _bufferId);
   //_pDevice->CheckError("glBindBuffer", "Bind array buffer. (buffer_id=%d)", _bufferId);
   //// �ϴ�����
   //TInt length = _pDataStream->Length();
   //TByteC* pData = _pDataStream->MemoryC();
   //glBufferData(GL_ARRAY_BUFFER, length, pData, GL_STATIC_DRAW);
   //_pDevice->CheckError("glBufferData", "Upload array buffer data. (buffer_id=%d, length=%d, data=0x%08X)", _bufferId, length, pData);
   return ESuccess;
}

//============================================================
// <T>��������</T>
//
// @return ������
//============================================================
TResult FPd10RenderVertexBuffer::Dispose(){
   //if(_bufferId != 0){
   //   TInt size = _stride * _count;
   //   glDeleteBuffers(size, &_bufferId);
   //   _bufferId = 0;
   //}
   return ESuccess;
}

MO_NAMESPACE_END
