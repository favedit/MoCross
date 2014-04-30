#include <sys/types.h>
#include <sys/stat.h>
#ifdef _MO_LINUX
#include <dirent.h>
#endif // _MO_LINUX
#include "MoFlNet.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FNetLoggerWriter, FInstance);

//============================================================
// <T>������־����������</T>
//
// @return ��־д���������ָ�롣
//============================================================
FNetLoggerWriter::FNetLoggerWriter(){
   _code  = 0;
   _pBuffer = MO_CREATE(FByteStream);
   _pBuffer->EnsureSize(1024 * 1024);
   _pData = MO_CREATE(FBytes);
   _pSocket = MO_CREATE(FNetClientSocket);
}

//============================================================
// <T>������־����������</T>
//============================================================
FNetLoggerWriter::~FNetLoggerWriter(){
   MO_DELETE(_pBuffer);
   MO_DELETE(_pData);
   MO_DELETE(_pSocket);
}

//============================================================
// <T>����־д������</T>
//
// @return �շ�򿪳ɹ���
//============================================================
TResult FNetLoggerWriter::Open(){
   _pSocket->Connect();
   return ESuccess;
}

//============================================================
// <T>����һ���µ���־�ļ���</T>
//
// @return �Ƿ񴴽��ɹ���
//============================================================
TResult FNetLoggerWriter::Create(){
   return ESuccess;
}

//============================================================
// <T>�����־д�����ı�š�</T>
//
// @return ��־д�����ı�š�
//============================================================
TInt FNetLoggerWriter::Code(){
   return _code;
}

//============================================================
// <T>��һ����Ϣ��¼����־�С�</T>
//
// @param TCharC* pMessage ��Ϣ�����ݡ�
// @param TSize length ��Ϣ�ĳ��ȡ�
// @return �Ƿ��¼�ɹ���
//============================================================
TResult FNetLoggerWriter::Write(TDateTime time, TCharC* pMessage, TInt length){
   // ������Ϣͷ
   SNetLoggerInfo info;
   info.length = sizeof(SNetLoggerInfo) + sizeof(TChar) * length;
   info.type = 0;
   info.level = 0;
   info.tick = time;
   // �������
   _section.Enter();
   _pBuffer->Write(&info, sizeof(SNetLoggerInfo));
   _pBuffer->Write(pMessage, sizeof(TChar) * length);
   // ������Ϣ
   TInt sended = _pSocket->Send(_pBuffer->Memory(), _pBuffer->Length());
   if(sended > 0){
      _pBuffer->DeleteSegment(0, sended);
      _pBuffer->Skip(-sended);
   }
   _section.Leave();
   return ESuccess;
}

//============================================================
// <T>�ر���־д������</T>
//
// @return �ر��Ƿ�ɹ���
//============================================================
TResult FNetLoggerWriter::Close(){
   TResult result = ESuccess;
   _section.Enter();
   _section.Leave();
   return result;
}

//============================================================
// <T>�ر���־д������</T>
//
// @return �ر��Ƿ�ɹ���
//============================================================
TResult FNetLoggerWriter::Refresh(){
   TResult resultCd = ESuccess;
   //TDateTime current = RDateTime::Current();
   //// д������
   //_section.Enter();
   //TInt length = _pBuffer->Length();
   //if(length > 0){
   //   TInt lengthWrite = _pStream->Write(_pBuffer->MemoryC(), length);
   //   if(lengthWrite == length){
   //      _flushLength += length;
   //      result = ETrue;
   //   }
   //   _pBuffer->Clear();
   //}
   ////............................................................
   //// �Ƿ�Ҫǿ��ˢ��
   //if(result && _forceToFlush){
   //   _pStream->Flush();
   //}
   //// �Ƿ�ʱˢ��
   //TTimeSpan flushSpan = current - _lastFlushDate;
   //if((_flushLength > 0) && (flushSpan > _flushTimeout)){
   //   _pStream->Flush();
   //   _flushLength = 0;
   //   _flushTimeout = current;
   //}
   ////............................................................
   //// ����ļ��Ƿ���Ҫ�л�
   //TDateTime today = current / (TDateTime)MO_DATA_DAY_US;
   //_length += length;
   //if((_length > _capacity) || (_today != today)){
   //   _pStream->Flush();
   //   Create();
   //}
   //_section.Leave();
   return resultCd;
}

//============================================================
// <T>ˢ�����ݡ�</T>
//
// @return ������
//============================================================
TResult FNetLoggerWriter::Flush(){
   TResult resultCd = Refresh();
   //_section.Enter();
   //result = _pStream->Flush();
   //_section.Leave();
   return resultCd;
}

MO_NAMESPACE_END
