#include "MoFgRender.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FRenderProgramBuffer, FRenderInstance);

//============================================================
// <T>������Ⱦ�����塣</T>
//============================================================
FRenderProgramBuffer::FRenderProgramBuffer(){
   _groupCd = ERenderShaderBuffer_Unknown;
   _bufferCd = ERenderShaderBuffer_Unknown;
   _dataLength = 0;
   _statusUsed = EFalse;
   _statusChanged = EFalse;
   _pData = MO_CREATE(FBytes);
   _shaderCd = ERenderShader_Unknown;
   _slot = -1;
}

//============================================================
// <T>������Ⱦ�����塣</T>
//============================================================
FRenderProgramBuffer::~FRenderProgramBuffer(){
   MO_DELETE(_pData);
}

//============================================================
// <T>�������á�</T>
//
// @param pConfig ���ýڵ�
// @return ������
//============================================================
TResult FRenderProgramBuffer::LoadConfig(FXmlNode* pConfig){
   MO_CHECK(pConfig, return ENull);
   // ��������
   _name = pConfig->Get("name");
   // ���ù���
   _linker = pConfig->Get("linker");
   // ������Ϣ
   _bufferCd = RRenderShaderBuffer::Parse(_linker);
   _groupCd = RRenderShaderBuffer::ParseGroup(_bufferCd);
   _slot = RRenderShaderBuffer::ParseSlot(_bufferCd);
   return ESuccess;
}

//============================================================
// <T>���ô���</T>
//
// @return ������
//============================================================
TResult FRenderProgramBuffer::OnSetup(){
   MO_CHECK(_pDevice, return ENull);
   if(_dataLength == 0){
      return ESuccess;
   }
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
TResult FRenderProgramBuffer::Set(TInt slot, TAnyC* pData, TInt length){
   // ����Ƿ�ʹ��
   if(!_statusUsed){
      return EContinue;
   }
   // ������
   MO_CHECK(slot >= 0, return EOutRange);
   MO_CHECK(pData, return ENull);
   MO_CHECK(length >= 0, return EOutRange);
   MO_CHECK(slot + length <= _dataLength, return EOutRange);
   // ������ݱ��
   TByte* pMemory = _pData->Memory() + slot;
   if(!_statusChanged){
      if(MO_LIB_MEMORY_COMPARE(pMemory, pData, length) == 0){
         return EContinue;
      }
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
TResult FRenderProgramBuffer::Commit(){
   MO_FATAL_UNSUPPORT();
   return ESuccess;
}

//============================================================
// <T>���´���</T>
//
// @return ������
//============================================================
TResult FRenderProgramBuffer::Update(){
   // ����Ƿ�ʹ��
   if(!_statusUsed){
      return EContinue;
   }
   // ��������
   MO_CHECK(_pDevice, return ENull);
   TResult resultCd = ESuccess;
   // �ύ����
   if(_statusChanged){
      Commit();
      _statusChanged = EFalse;
   }
   return ESuccess;
}

//============================================================
// <T>�󶨴���</T>
//
// @return ������
//============================================================
TResult FRenderProgramBuffer::Bind(){
   return ESuccess;
}

//============================================================
// <T>����ڲ�������Ϣ��</T>
//
// @param pDump �������
// @return ������
//============================================================
TResult FRenderProgramBuffer::Dump(MString* pDump, TBool detail){
   MO_CHECK(pDump, return ENull);
   pDump->AppendFormat("Buffer: name=%s, linker=%s, slot=%d", (TCharC*)_name, (TCharC*)_linker, _slot);
   return ESuccess;
}

MO_NAMESPACE_END
