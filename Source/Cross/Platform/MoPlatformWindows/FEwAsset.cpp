#include "MoEwAsset.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FEwAsset, FAsset);

//============================================================
// <T>������Դ��</T>
//============================================================
FEwAsset::FEwAsset(){
   //MO_CLEAR(_pNative);
}

//============================================================
// <T>������Դ��</T>
//============================================================
FEwAsset::~FEwAsset(){
   Close();
}

//============================================================
// <T>��ó��ȡ�</T>
//============================================================
TInt FEwAsset::Length(){
   TInt length = -1;
   //if(_pNative != NULL){
   //   length = AAsset_getLength(_pNative);
   //}
   return length;
}

//============================================================
// <T>��λ����</T>
//============================================================
TResult FEwAsset::Seek(TInt position){
   //if(_pNative != NULL){
   //   AAsset_seek(_pNative, position, 0);
   //}
   return ESuccess;
}

//============================================================
// <T>��ȡָ�����ȵ����ݡ�</T>
//
// @param pData ����ָ��
// @param length ���ݳ���
// @return ������
//============================================================
TResult FEwAsset::Read(TAny* pData, TInt length){
   //if(_pNative != NULL){
   //   AAsset_read(_pNative, pData, length);
   //}
   return ESuccess;
}

//============================================================
// <T>�رմ���</T>
//============================================================
TResult FEwAsset::Close(){
   //if(_pNative != NULL){
   //   AAsset_close(_pNative);
   //   MO_CLEAR(_pNative);
   //}
   return ESuccess;
}

MO_NAMESPACE_END
