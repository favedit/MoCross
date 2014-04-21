#include "MoEwAsset.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FEwAssetConsole, FAssetConsole);

//============================================================
// <T>������Դ����̨��</T>
//============================================================
FEwAssetConsole::FEwAssetConsole(){
}

//============================================================
// <T>������Դ����̨��</T>
//============================================================
FEwAssetConsole::~FEwAssetConsole(){
}

//============================================================
// <T>���ô���</T>
//
// @return ������
//============================================================
TResult FEwAssetConsole::Setup(){
   // ��ò���
   TCharC* pHomePath = RApplication::Instance().Parameters()->FindValue("-home");
   SetDirectory(pHomePath);
   // ע��·��
   TFsPath path;
   path.AssignFormat("%s/Asset", pHomePath);
   path.Replace('\\', '/');
   RegisterSpace("asset", path);
   // ע��·��
   path.AssignFormat("%s/Script", pHomePath);
   path.Replace('\\', '/');
   RegisterSpace("script", path);
   return ESuccess;
}

//============================================================
// <T>��һ����ԴĿ¼��</T>
//
// @param pDirectory Ŀ¼����
// @return ��ԴĿ¼
//============================================================
FAssetDirectory* FEwAssetConsole::OpenDirectory(TCharC* pDirectory){
   return NULL;
}

//============================================================
// <T>��һ����Դ��</T>
//
// @param pName ����
// @return ��Դ
//============================================================
FAsset* FEwAssetConsole::OpenAsset(TCharC* pName){
   return NULL;
}

//============================================================
// <T>��һ���ı����ݡ�</T>
//
// @param pSource �ı�����
// @param pName ����
// @return ������
//============================================================
TResult FEwAssetConsole::OpenAssetString(MString* pSource, TCharC* pName){
   // ������
   MO_CHECK(pSource, return ENull);
   MO_CHECK(pName, return ENull);
   // �������
   TFsFileName fileName;
   TResult result = ParsePath(&fileName, pName);
   if(result != ESuccess){
      MO_FATAL("Parse file name failure. (pName=%s)", pName);
      return result;
   }
   // �����ļ��Ƿ����
   if(!RFile::ExistFile(fileName)){
      MO_FATAL("Asset file is not exists. (file_name=%s)", (TCharC*)fileName);
      return EFailure;
   }
   // ���ļ�
   FFileString* pFile = MO_CREATE(FFileString);
   pFile->LoadFile(fileName);
   TInt length = pFile->Length();
   // ��������
   pSource->ForceLength(length + 1);
   pSource->Assign((TCharC*)pFile->MemoryC(), length);
   // �ͷ��ļ�
   MO_DELETE(pFile);
   MO_INFO("Load asset string success. (name=%s, length=%d)", pName, length);
   return ESuccess;
}

//============================================================
// <T>��һ����Դ���ݡ�</T>
//
// @param pData ����
// @param pName ����
// @return ��Դ��
//============================================================
TResult FEwAssetConsole::OpenData(FBytes* pData, TCharC* pName){
   // ������
   MO_CHECK(pData, return ENull);
   MO_CHECK(pName, return ENull);
   // �������
   TFsFileName fileName;
   TResult result = ParsePath(&fileName, pName);
   if(result != ESuccess){
      MO_FATAL("Parse file name failure. (pName=%s)", pName);
      return result;
   }
   // �����ļ��Ƿ����
   if(!RFile::ExistFile(fileName)){
      MO_FATAL("Asset file is not exists. (file_name=%s)", (TCharC*)fileName);
      return EFailure;
   }
   // ���ļ�
   FByteFile* pFile = MO_CREATE(FByteFile);
   pFile->LoadFile(fileName);
   TInt length = pFile->Length();
   // ��������
   pData->Assign(pFile->MemoryC(), length);
   // �ͷ��ļ�
   MO_DELETE(pFile);
   MO_INFO("Load asset stream success. (name=%s, length=%d)", pName, length);
   return result;
}

MO_NAMESPACE_END
