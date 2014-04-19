#include "MoEaAsset.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FEaAsset, FAsset);

//============================================================
// <T>������Դ��</T>
//============================================================
FEaAsset::FEaAsset(){
   MO_CLEAR(_pNative);
}

//============================================================
// <T>������Դ��</T>
//============================================================
FEaAsset::~FEaAsset(){
   Close();
}

//============================================================
// <T>��ó��ȡ�</T>
//============================================================
TInt FEaAsset::Length(){
   TInt length = -1;
   if(_pNative != NULL){
      length = AAsset_getLength(_pNative);
   }
   return length;
}

//============================================================
// <T>��λ����</T>
//============================================================
TResult FEaAsset::Seek(TInt position){
   if(_pNative != NULL){
      AAsset_seek(_pNative, position, 0);
   }
   return ESuccess;
}

//============================================================
// <T>��ȡָ�����ȵ����ݡ�</T>
//
// @param pData ����ָ��
// @param length ���ݳ���
// @return ������
//============================================================
TResult FEaAsset::Read(TAny* pData, TInt length){
   if(_pNative != NULL){
      AAsset_read(_pNative, pData, length);
   }
   return ESuccess;
}

//============================================================
// <T>�رմ���</T>
//============================================================
TResult FEaAsset::Close(){
   if(_pNative != NULL){
      AAsset_close(_pNative);
      MO_CLEAR(_pNative);
   }
   return ESuccess;
}

MO_NAMESPACE_END
