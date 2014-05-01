#include "MoPd9Render.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FPd9RenderIndexBuffer, FRenderVertexBuffer);

//============================================================
// <T>������Ⱦ�������塣</T>
//============================================================
FPd9RenderIndexBuffer::FPd9RenderIndexBuffer(){
   _bufferId = 0;
}

//============================================================
// <T>������Ⱦ�������塣</T>
//============================================================
FPd9RenderIndexBuffer::~FPd9RenderIndexBuffer(){
}

//============================================================
// <T>���ô���</T>
//
// @return ������
//============================================================
TResult FPd9RenderIndexBuffer::OnSetup(){
   TResult resultCd = FRenderIndexBuffer::OnSetup();
   glGenBuffers(1, &_bufferId);
   MO_FATAL_CHECK(_bufferId != 0, return EFailure,
         "Generate index buffer id failure. (buffer_id=%d)", _bufferId);
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _bufferId);
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
   // �����
   MO_FATAL_CHECK(_bufferId != 0, return EFailure,
         "Buffer id is invalid. (buffer_id=%d)", _bufferId);
   // �ϴ�����
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _bufferId);
   glBufferData(GL_ELEMENT_ARRAY_BUFFER, length, pData, GL_STATIC_DRAW);
   _pDevice->CheckError("glBufferData", "Upload array buffer data. (buffer_id=%d, length=%d, data=0x%08X)", _bufferId, length, pData);
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
   // ���ɱ��
   glGenBuffers(1, &_bufferId);
   MO_FATAL_CHECK(_bufferId != 0, return EFailure,
         "Generate index buffer id failure. (buffer_id=%d)", _bufferId);
   // �󶨱��
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _bufferId);
   MO_FATAL_CHECK(_bufferId != 0, return EFailure,
         "Buffer id is invalid. (buffer_id=%d)", _bufferId);
   // �ϴ�����
   TInt length = _pDataStream->Length();
   TByteC* pData = _pDataStream->MemoryC();
   glBufferData(GL_ELEMENT_ARRAY_BUFFER, length, pData, GL_STATIC_DRAW);
   _pDevice->CheckError("glBufferData", "Upload array buffer data. (buffer_id=%d, length=%d, data=0x%08X)", _bufferId, length, pData);
   return ESuccess;
}

//============================================================
// <T>��������</T>
//
// @return ������
//============================================================
TResult FPd9RenderIndexBuffer::Dispose(){
   if(_bufferId != 0){
      glDeleteBuffers(_dataLength, &_bufferId);
      _count = 0;
      _dataLength = 0;
      _bufferId = 0;
   }
   return ESuccess;
}

MO_NAMESPACE_END
