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
   D3D10_BUFFER_DESC description;
   RType<D3D10_BUFFER_DESC>::Clear(&description);
   description.BindFlags = D3D10_BIND_INDEX_BUFFER;
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
TResult FPd10RenderIndexBuffer::Suspend(){
   return ESuccess;
}

//============================================================
// <T>��������</T>
//
// @return ������
//============================================================
TResult FPd10RenderIndexBuffer::Resume(){
   //// ���ɱ��
   //glGenBuffers(1, &_bufferId);
   //MO_FATAL_CHECK(_bufferId != 0, return EFailure,
   //      "Generate index buffer id failure. (buffer_id=%d)", _bufferId);
   //// �󶨱��
   //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _bufferId);
   //MO_FATAL_CHECK(_bufferId != 0, return EFailure,
   //      "Buffer id is invalid. (buffer_id=%d)", _bufferId);
   //// �ϴ�����
   //TInt length = _pDataStream->Length();
   //TByteC* pData = _pDataStream->MemoryC();
   //glBufferData(GL_ELEMENT_ARRAY_BUFFER, length, pData, GL_STATIC_DRAW);
   //_pDevice->CheckError("glBufferData", "Upload array buffer data. (buffer_id=%d, length=%d, data=0x%08X)", _bufferId, length, pData);
   return ESuccess;
}

//============================================================
// <T>��������</T>
//
// @return ������
//============================================================
TResult FPd10RenderIndexBuffer::Dispose(){
   //if(_bufferId != 0){
   //   glDeleteBuffers(_dataLength, &_bufferId);
   //   _count = 0;
   //   _dataLength = 0;
   //   _bufferId = 0;
   //}
   return ESuccess;
}

MO_NAMESPACE_END
