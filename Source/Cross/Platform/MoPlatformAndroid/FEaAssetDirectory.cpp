#include "MoEaAsset.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FEaAssetDirectory, FAssetDirectory);

//============================================================
// <T>������ԴĿ¼��</T>
//============================================================
FEaAssetDirectory::FEaAssetDirectory(){
   MO_CLEAR(_pFileName);
   MO_CLEAR(_pNative);
}

//============================================================
// <T>������ԴĿ¼��</T>
//============================================================
FEaAssetDirectory::~FEaAssetDirectory(){
   Close();
}

//============================================================
// <T>�����һ�����ݡ�</T>
//
// @return �Ƿ���
//============================================================
TBool FEaAssetDirectory::Next(){
   if(_pNative != NULL){
      _pFileName = AAssetDir_getNextFileName(_pNative);
      if(_pFileName != NULL){
         return ETrue;
      }
   }
   return EFalse;
}

//============================================================
// <T>��õ�ǰ���ݡ�</T>
//
// @return ��ǰ����
//============================================================
TCharC* FEaAssetDirectory::Current(){
   return _pFileName;
}

//============================================================
// <T>�رմ���</T>
//
// @return ������
//============================================================
TResult FEaAssetDirectory::Close(){
   AAssetDir_close(_pNative);
   return ESuccess;
}

MO_NAMESPACE_END
