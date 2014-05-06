#include "MoPd11Render.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FPd11RenderIndexBuffer, FRenderVertexBuffer);

//============================================================
// <T>������Ⱦ�������塣</T>
//============================================================
FPd11RenderIndexBuffer::FPd11RenderIndexBuffer(){
   MO_CLEAR(_piBuffer);
}

//============================================================
// <T>������Ⱦ�������塣</T>
//============================================================
FPd11RenderIndexBuffer::~FPd11RenderIndexBuffer(){
   MO_RELEASE(_piBuffer);
}

//============================================================
// <T>���ô���</T>
//
// @return ������
//============================================================
TResult FPd11RenderIndexBuffer::OnSetup(){
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
TResult FPd11RenderIndexBuffer::Upload(TByteC* pData, TInt length){
   // ������
   MO_CHECK(pData, return ENull);
   MO_CHECK(length > 0, return EFailure);
   TResult resultCd = ESuccess;
   MO_CHECK(_pDevice, return ENull);
   FPd11RenderDevice* pRenderDevice = _pDevice->Convert<FPd11RenderDevice>();
   MO_RELEASE(_piBuffer);
   //............................................................
   // ��������
   D3D11_BUFFER_DESC descriptor = {0};
   descriptor.ByteWidth = _dataLength;
   descriptor.Usage = D3D11_USAGE_DEFAULT;
   descriptor.BindFlags = D3D11_BIND_INDEX_BUFFER;
   descriptor.CPUAccessFlags = 0;
   descriptor.MiscFlags = 0;
   descriptor.StructureByteStride = 0;
   // ��������
   D3D11_SUBRESOURCE_DATA data = {0};
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
TResult FPd11RenderIndexBuffer::Suspend(){
   return ESuccess;
}

//============================================================
// <T>��������</T>
//
// @return ������
//============================================================
TResult FPd11RenderIndexBuffer::Resume(){
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
TResult FPd11RenderIndexBuffer::Dispose(){
   MO_RELEASE(_piBuffer);
   return ESuccess;
}

MO_NAMESPACE_END
