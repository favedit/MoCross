#include "MoFgRender.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FRenderShaderBuffer, FRenderObject);

//============================================================
// <T>������Ⱦ�����塣</T>
//============================================================
FRenderShaderBuffer::FRenderShaderBuffer(){
   _dataLength = 0;
   _statusChanged = EFalse;
   _pData = MO_CREATE(FBytes);
   _shaderCd = ERenderShader_Unknown;
   _slot = -1;
}

//============================================================
// <T>������Ⱦ�����塣</T>
//============================================================
FRenderShaderBuffer::~FRenderShaderBuffer(){
   MO_DELETE(_pData);
}

//============================================================
// <T>���ô���</T>
//
// @return ������
//============================================================
TResult FRenderShaderBuffer::Setup(){
   MO_CHECK(_pDevice, return ENull);
   MO_CHECK(_dataLength > 0, return EOutRange);
   // ���û���
   if(_pData->Length() != _dataLength){
      _pData->SetLength(_dataLength);
      RBytes::Clear(_pData->Memory(), _dataLength);
   }
   return ESuccess;
}

//============================================================
// <T>�����������ݡ�</T>
//
// @param slot ���
// @param pData ����
// @param length ����
// @return ������
//============================================================
TResult FRenderShaderBuffer::Set(TInt slot, TAnyC* pData, TInt length){
   // ������
   MO_CHECK(slot >= 0, return EOutRange);
   MO_CHECK(pData, return ENull);
   MO_CHECK(length >= 0, return EOutRange);
   MO_CHECK(slot + length <= _dataLength, return EOutRange);
   // ������ݱ��
   TByte* pMemory = _pData->Memory() + slot;
   if(!_statusChanged){
      //if(MO_LIB_MEMORY_COMPARE(pMemory, pData, length) == 0){
      //   return EContinue;
      //}
      _statusChanged = ETrue;
   }
   // �����ڴ�
   MO_LIB_MEMORY_COPY(pMemory, length, pData, length);
   return ESuccess;
}

//============================================================
// <T>�ύ����</T>
//
// @return ������
//============================================================
TResult FRenderShaderBuffer::Commit(){
   MO_FATAL_UNSUPPORT();
   return ESuccess;
}

//============================================================
// <T>���´���</T>
//
// @return ������
//============================================================
TResult FRenderShaderBuffer::Update(){
   MO_CHECK(_pDevice, return ENull);
   TResult resultCd = ESuccess;
   // �ύ����
   //if(_statusChanged){
   //   Commit();
   //   _statusChanged = EFalse;
   //}
   Commit();
   return ESuccess;
}

MO_NAMESPACE_END
