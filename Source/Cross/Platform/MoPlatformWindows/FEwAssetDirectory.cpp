#include "MoEwAsset.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FEwAssetDirectory, FAssetDirectory);

//============================================================
// <T>������ԴĿ¼��</T>
//============================================================
FEwAssetDirectory::FEwAssetDirectory(){
   //MO_CLEAR(_pFileName);
   //MO_CLEAR(_pNative);
}

//============================================================
// <T>������ԴĿ¼��</T>
//============================================================
FEwAssetDirectory::~FEwAssetDirectory(){
   Close();
}

//============================================================
// <T>�����һ�����ݡ�</T>
//
// @return �Ƿ���
//============================================================
TBool FEwAssetDirectory::Next(){
   //if(_pNative != NULL){
   //   _pFileName = AAssetDir_getNextFileName(_pNative);
   //   if(_pFileName != NULL){
   //      return ETrue;
   //   }
   //}
   return EFalse;
}

//============================================================
// <T>��õ�ǰ���ݡ�</T>
//
// @return ��ǰ����
//============================================================
TCharC* FEwAssetDirectory::Current(){
   return _pFileName;
}

//============================================================
// <T>�رմ���</T>
//
// @return ������
//============================================================
TResult FEwAssetDirectory::Close(){
//   AAssetDir_close(_pNative);
   return ESuccess;
}

MO_NAMESPACE_END
