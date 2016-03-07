#include "MoFrContent3dModel.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>������Դ3D������</T>
//============================================================
FRs3dSkeleton::FRs3dSkeleton(){
   _pRootBones = MO_CREATE(FRs3dBoneVector);
   _pBones = MO_CREATE(FRs3dBoneSet);
}

//============================================================
// <T>������Դ3D������</T>
//============================================================
FRs3dSkeleton::~FRs3dSkeleton(){
   MO_DELETE(_pRootBones);
   MO_DELETE(_pBones);
}

//============================================================
// <T>���ݹ�ͷ��Ų��ҹ�ͷ����</T>
//
// @param boneId ��ͷ���
// @return ��ͷ����
//============================================================
FRs3dBone* FRs3dSkeleton::Find(TInt boneId){
   return _pBones->Find((TBoneId)boneId);
}

//============================================================
// <T>����һ����ͷ��</T>
//
// @param pBone ��ͷ
//============================================================
void FRs3dSkeleton::PushBone(FRs3dBone* pBone){
   TBoneId boneId = (TBoneId)pBone->Id();
   _pBones->Set(boneId, pBone);
}

//============================================================
// <T>���������ﷴ���л���Ϣ����</T>
//
// @param pInput ������
// @return ������
//============================================================
TResult FRs3dSkeleton::Unserialize(IDataInput* pInput){
   MO_CHECK(pInput, return ENull);
   // ��ȡ�����ӽڵ�
   TInt count = pInput->ReadInt8();
   for(TInt n = 0; n < count; n++){
      FRs3dBone* pBone = MO_CREATE(FRs3dBone);
      pBone->SetSkeleton(this);
      pBone->Unserialize(pInput);
      _pRootBones->Push(pBone);
   }
   return ESuccess;
}

//============================================================
// <T>������ݡ�</T>
//============================================================
void FRs3dSkeleton::Clear(){
}

MO_NAMESPACE_END
