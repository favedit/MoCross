#include "MoEaAsset.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FEaAssetConsole, FAssetConsole);

//============================================================
// <T>������Դ����̨��</T>
//============================================================
FEaAssetConsole::FEaAssetConsole(){
   MO_CLEAR(_pManager);
}

//============================================================
// <T>������Դ����̨��</T>
//============================================================
FEaAssetConsole::~FEaAssetConsole(){
}

//============================================================
// <T>��������</T>
//
// @param pEnvironment ����
// @param assetManager �ʲ�������
//============================================================
void FEaAssetConsole::Link(JNIEnv* pEnvironment, jobject assetManager){
   _pManager = AAssetManager_fromJava(pEnvironment, assetManager);
}

//============================================================
// <T>���ô���</T>
//
// @return ������
//============================================================
TResult FEaAssetConsole::Setup(){
   RegisterSpace("asset", "Asset");
   return ESuccess;
}

//============================================================
// <T>��һ����ԴĿ¼��</T>
//
// @param pDirectory Ŀ¼����
// @return ��ԴĿ¼
//============================================================
FAssetDirectory* FEaAssetConsole::OpenDirectory(TCharC* pDirectory){
   MO_CHECK(pDirectory, return NULL);
   // �������
   TFsFileName directory;
   TResult result = ParsePath(&directory, pDirectory);
   if(result != ESuccess){
      MO_FATAL("Parse file name failure. (directory=%s)", pDirectory);
      return NULL;
   }
   // ���ļ�
   AAssetDir* pNative = AAssetManager_openDir(_pManager, pDirectory);
   MO_ERROR_CHECK(pNative, return NULL,
         "Open asset directory failure. (directory=%s)", (TCharC*)directory);
   // ������Դ
   FEaAssetDirectory* pAssetDirectory = MO_CREATE(FEaAssetDirectory);
   pAssetDirectory->SetNative(pNative);
   return pAssetDirectory;
}

//============================================================
// <T>��һ����Դ��</T>
//
// @param pFileName �ļ�����
// @return ��Դ
//============================================================
FAsset* FEaAssetConsole::OpenAsset(TCharC* pName){
   MO_CHECK(pName, return NULL);
   // �������
   TFsFileName fileName;
   TResult result = ParsePath(&fileName, pName);
   if(result != ESuccess){
      MO_FATAL("Parse file name failure. (pName=%s)", pName);
      return NULL;
   }
   // ���ļ�
   AAsset* pNative = AAssetManager_open(_pManager, fileName, AASSET_MODE_UNKNOWN);
   MO_ERROR_CHECK(pNative, return NULL,
         "Open asset stream failure. (file_name=%s)", (TCharC*)fileName);
   // ������Դ
   FEaAsset* pAssert = MO_CREATE(FEaAsset);
   pAssert->SetNative(pNative);
   return pAssert;
}

//============================================================
// <T>��һ���ı����ݡ�</T>
//
// @param pSource �ı�����
// @param pName ����
// @return ������
//============================================================
TResult FEaAssetConsole::OpenAssetString(MString* pSource, TCharC* pName){
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
   // ���ļ�
   AAsset* pNative = AAssetManager_open(_pManager, fileName, AASSET_MODE_UNKNOWN);
   MO_ERROR_CHECK(pNative, return EFailure,
         "Open asset stream failure. (file_name=%s)", (TCharC*)fileName);
   // ��ô�С
   TInt length = AAsset_getLength(pNative);
   if(length == 0){
      AAsset_close(pNative);
      MO_ERROR("Open asset length is zero. (file_name=%s, length=%d)", (TCharC*)fileName, length);
      return EFailure;
   }
   // ��������
   pSource->ForceLength(length + 1);
   TChar* pMemory = pSource->Memory();
   TInt readLength = AAsset_read(pNative, pMemory, length);
   if(readLength <= 0 ){
      MO_ERROR("Read asset failure. (file_name=%s, read_length=%d)", (TCharC*)fileName, readLength);
      AAsset_close(pNative);
      return EFailure;
   }
   pSource->SetLength(length);
   // �ر�����
   AAsset_close(pNative);
   MO_INFO("Load data success. (file_name=%s, length=%d)", (TCharC*)fileName, length);
   return ESuccess;
}

//============================================================
// <T>����һ�����ݡ�</T>
//
// @param pData ����
// @param pFileName �ļ�����
// @return ������
//============================================================
TResult FEaAssetConsole::OpenData(FBytes* pData, TCharC* pName){
   MO_CHECK(pData, return ENull);
   MO_CHECK(pName, return ENull);
   // �������
   TFsFileName fileName;
   TResult result = ParsePath(&fileName, pName);
   if(result != ESuccess){
      MO_FATAL("Parse file name failure. (pName=%s)", pName);
      return result;
   }
   // ���ļ�
   AAsset* pNative = AAssetManager_open(_pManager, fileName, AASSET_MODE_UNKNOWN);
   MO_ERROR_CHECK(pNative, return EFailure,
         "Open asset stream failure. (file_name=%s)", (TCharC*)fileName);
   // ��ô�С
   TInt length = AAsset_getLength(pNative);
   if(length == 0){
      AAsset_close(pNative);
      MO_ERROR("Open asset length is zero. (file_name=%s, length=%d)", (TCharC*)fileName, length);
      return EFailure;
   }
   // ��������
   pData->ForceLength(length);
   TInt readLength = AAsset_read(pNative, pData->Memory(), length);
   if(readLength <= 0 ){
      MO_ERROR("Read asset failure. (file_name=%s, read_length=%d)", (TCharC*)fileName, readLength);
      AAsset_close(pNative);
      return EFailure;
   }
   // �ر�����
   AAsset_close(pNative);
   MO_INFO("Load data success. (file_name=%s, length=%d)", (TCharC*)fileName, length);
   return ESuccess;
}

MO_NAMESPACE_END
