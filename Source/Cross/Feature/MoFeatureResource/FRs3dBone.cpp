#include "MoFrContent3dModel.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FRs3dBone, FInstance);

//============================================================
// <T>������Դ3D��ͷ��</T>
//============================================================
FRs3dBone::FRs3dBone(){
   MO_CLEAR(_pSkeleton);
   _id = -1;
   MO_CLEAR(_pParent);
   MO_CLEAR(_pTrack);
   MO_CLEAR(_pBones);
}

//============================================================
// <T>������Դ3D��ͷ��</T>
//============================================================
FRs3dBone::~FRs3dBone(){
   Clear();
   MO_DELETE(_pBones);
}

//============================================================
// <T>����һ���ӹ�ͷ��</T>
//
// @param pBone �ӹ�ͷ
//============================================================
void FRs3dBone::Push(FRs3dBone* pBone){
   if(_pBones == NULL){
      _pBones = MO_CREATE(FRs3dBoneVector);
   }
   _pBones->Push(pBone);
}

//============================================================
// <T>���������ﷴ���л���Ϣ����</T>
//
// @param pInput ������
// @return ������
//============================================================
TResult FRs3dBone::Unserialize(IDataInput* pInput){
   MO_CHECK(pInput, return ENull);
   // ��ȡ����
   _id = pInput->ReadInt8();
   // ��ȡ�����ӽڵ�
   TInt count = pInput->ReadInt8();
   for(TInt n = 0; n < count; n++){
      FRs3dBone* pBone = MO_CREATE(FRs3dBone);
      pBone->SetSkeleton(_pSkeleton);
      pBone->SetParent(this);
      pBone->Unserialize(pInput);
      Push(pBone);
   }
   // ���Ӷ���
   _pSkeleton->PushBone(this);
   return ESuccess;
}

//============================================================
// <T>������ݡ�</T>
//============================================================
void FRs3dBone::Clear(){
   if(_pBones != NULL){
      TInt count = _pBones->Count();
      for(TInt n = 0; n < count; n++){
         FRs3dBone* pBone = _pBones->Get(n);
         MO_DELETE(pBone);
      }
      _pBones->Clear();
   }
}

MO_NAMESPACE_END
