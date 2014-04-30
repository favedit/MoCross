#include <sys/types.h>
#include <sys/stat.h>
#ifdef _MO_LINUX
#include <dirent.h>
#endif // _MO_LINUX
#include "MoFlFile.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>������־����������</T>
//
// @return ��־д���������ָ�롣
//============================================================
 FBufferedLoggerWriter::FBufferedLoggerWriter(){
   _code  = 0;
   _fileCount = 0;
   _length = 0;
   _capacity = 0;
   _pBuffer = MO_CREATE(FBytes);
   _pBuffer->EnsureSize(1024 * 1024 * 4);
   _pStream = MO_CREATE(FFileStream);
   _today = RDateTime::Current() / (TDateTime)MO_DATA_DAY_US;
   _forceToFlush = EFalse;
   _flushLength = 0;
   _flushTimeout = 10000000;
   _lastFlushDate = 0;
}

//============================================================
// <T>������־����������</T>
//============================================================
FBufferedLoggerWriter::~FBufferedLoggerWriter(){
   MO_DELETE(_pBuffer);
   MO_DELETE(_pStream);
}

//============================================================
// <T>������־д�����ı�š�</T>
//
// @param TInt code Ҫ���õı�š�
//============================================================
void FBufferedLoggerWriter::SetCode(TInt code){
   _code = code;
}

//============================================================
// <T>������־д�����Ķ�Ӧ�ļ�����</T>
//
// @param TCharC* pName д����־���ļ�����
//============================================================
void FBufferedLoggerWriter::SetName(TCharC* pName){
   _name = pName;
}

//============================================================
// <T>������־�ļ�Ŀ¼��</T>
//
// @param TCharC* pPath ��־�ļ���ŵ�Ŀ¼��
//============================================================
void FBufferedLoggerWriter::SetPath(TCharC* pPath){
   _path = pPath;
}

//============================================================
// <T>������־�ļ�������С��</T>
//
// @param TSize capacity �ļ��Ĵ�С��
//============================================================
void FBufferedLoggerWriter::SetCapacity(TSize capacity){
   _capacity = capacity;
}

//============================================================
// <T>�Ƿ�ǿ��ˢ�µ��ļ���</T>
//
// @param TBool isForceFlush �Ƿ�ǿ��ˢ�¡�
//============================================================
void FBufferedLoggerWriter::SetForceToFlush(TBool isForceFlush){
   _forceToFlush = isForceFlush;
}

//============================================================
// <T>�����ļ�����������</T>
//
// @param fileName �ļ�����
// @return ������
//============================================================
TBool FBufferedLoggerWriter::MakeFilePattern(TFsFileName& fileName){
   // ��ʽ������
   TFsName datetime;
   RDateTime::ToString(datetime.Memory(), datetime.Size(), RDateTime::Current(), "%y%m%d");
   datetime.Fix();
   // �����ļ�����
   fileName.Append(_path);
   fileName.Append("/");
   fileName.Append(_name);
   fileName.Append("_");
   fileName.Append(datetime);
   fileName.Append("_");
   return ETrue;
}

//============================================================
// <T>�Ƿ�ǿ��ˢ�µ��ļ���</T>
//
// @param TBool isForceFlush �Ƿ�ǿ��ˢ�¡�
//============================================================
TInt FBufferedLoggerWriter::CalculateCount(TCharC* pFilePattern, TInt baseCount){
   TFsFileName fileName;
   TInt count = baseCount;
   for(; count < 9999; count++){
      fileName.Assign(pFilePattern);
      fileName.AppendFormat("%04d.log", count);
      if(RFile::ExistFile(fileName)){
         TInt fileLength = RFile::FileSize(fileName);
         if((fileLength >= 0) && (fileLength <= _capacity)){
            return count;
         }
      }else{
         break;
      }
   }
   return count;
}

//============================================================
// <T>����־д������</T>
//
// @return �շ�򿪳ɹ���
//============================================================
TResult FBufferedLoggerWriter::Open(){
   TResult result = ESuccess;
   // �����ļ�Ŀ¼
   if(!RFile::ExistPath(_path)){
      RFile::CreateFullDirectory((TCharC*)_path);
   }
#ifdef _MO_LINUX
   // ����ļ�����
   TFsFileName fileName;
   MakeFilePattern(fileName);
   _fileCount = CalculateCount(fileName, 1);
   fileName.AppendFormat("%04d.log", _fileCount);
   // ����ļ��Ƿ����
   if(RFile::ExistFile(fileName)){
      result = _pStream->OpenAppend(fileName);
      _length = _pStream->Length();
   }else{
      result = _pStream->Create(fileName);
      _length = 0;
   }
#endif
   return result;
}

//============================================================
// <T>����һ���µ���־�ļ���</T>
//
// @return �Ƿ񴴽��ɹ���
//============================================================
TResult FBufferedLoggerWriter::Create(){
   TResult result = ESuccess;
   // �ر��ϸ��ļ�
   _pStream->Close();
   // ����ļ�����
   TFsFileName fileName;
   MakeFilePattern(fileName);
   _fileCount = CalculateCount(fileName, _fileCount);
   fileName.AppendFormat("%04d.log", _fileCount);
   // ����ļ��Ƿ����
   if(RFile::ExistFile(fileName)){
      result = _pStream->OpenAppend(fileName);
   }else{
      result = _pStream->Create(fileName);
   }
   _length = 0;
   return result;
}

//============================================================
// <T>�����־д�����ı�š�</T>
//
// @return ��־д�����ı�š�
//============================================================
TInt FBufferedLoggerWriter::Code(){
   return _code;
}

//============================================================
// <T>��һ����Ϣ��¼����־�С�</T>
//
// @param TCharC* pMessage ��Ϣ�����ݡ�
// @param TSize length ��Ϣ�ĳ��ȡ�
// @return �Ƿ��¼�ɹ���
//============================================================
TResult FBufferedLoggerWriter::Write(TDateTime time, TCharC* pMessage, TInt length){
   _section.Enter();
   _pBuffer->Append((TByteC*)pMessage, sizeof(TChar) * length);
   _pBuffer->Append((TByteC*)"\n", sizeof(TChar));
   _section.Leave();
   return ESuccess;
}

//============================================================
// <T>�ر���־д������</T>
//
// @return �ر��Ƿ�ɹ���
//============================================================
TResult FBufferedLoggerWriter::Close(){
   TResult result = ESuccess;
   _section.Enter();
   result = _pStream->Close();
   _section.Leave();
   return result;
}

//============================================================
// <T>�ر���־д������</T>
//
// @return �ر��Ƿ�ɹ���
//============================================================
TResult FBufferedLoggerWriter::Refresh(){
   TResult result = ESuccess;
   TDateTime current = RDateTime::Current();
   // д������
   _section.Enter();
   TInt length = _pBuffer->Length();
   if(length > 0){
      TInt lengthWrite = _pStream->Write(_pBuffer->MemoryC(), length);
      if(lengthWrite == length){
         _flushLength += length;
         result = ETrue;
      }
      _pBuffer->Clear();
   }
   //............................................................
   // �Ƿ�Ҫǿ��ˢ��
   if(result && _forceToFlush){
      _pStream->Flush();
   }
   // �Ƿ�ʱˢ��
   TTimeSpan flushSpan = current - _lastFlushDate;
   if((_flushLength > 0) && (flushSpan > _flushTimeout)){
      _pStream->Flush();
      _flushLength = 0;
      _flushTimeout = current;
   }
   //............................................................
   // ����ļ��Ƿ���Ҫ�л�
   TDateTime today = current / (TDateTime)MO_DATA_DAY_US;
   _length += length;
   if((_length > _capacity) || (_today != today)){
      _pStream->Flush();
      Create();
   }
   _section.Leave();
   return result;
}

//============================================================
// <T>ˢ�����ݡ�</T>
//
// @return ������
//============================================================
TResult FBufferedLoggerWriter::Flush(){
   TResult result = Refresh();
   _section.Enter();
   result = _pStream->Flush();
   _section.Leave();
   return result;
}

MO_NAMESPACE_END
