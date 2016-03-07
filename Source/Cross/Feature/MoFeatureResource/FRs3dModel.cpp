#include "MoFrContent3dModel.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FRs3dModel, FResource3d);

//============================================================
// <T>������Դ3Dģ�͡�</T>
//============================================================
FRs3dModel::FRs3dModel(){
   _pSkeleton = MO_CREATE(FRs3dSkeleton);
   _pAnimation = MO_CREATE(FRs3dAnimation);
   _pAnimation->SetModel(this);
}

//============================================================
// <T>������Դ3Dģ�͡�</T>
//============================================================
FRs3dModel::~FRs3dModel(){
   MO_DELETE(_pSkeleton);
   MO_DELETE(_pAnimation);
}

//============================================================
// <T>���������ﷴ���л���Ϣ����</T>
//
// @param pInput ������
// @return ������
//============================================================
TResult FRs3dModel::Unserialize(IDataInput* pInput){
   MO_CHECK(pInput, return ENull);
   // ��ȡ����Ϣ
   FResource3d::Unserialize(pInput);
   // ��ȡ�����弯��
   TInt geometryCount = pInput->ReadInt16();
   for(TInt n = 0; n < geometryCount; n++){
      FRs3dGeometry* pGeometry = MO_CREATE(FRs3dGeometry);
      pGeometry->Unserialize(pInput);
      _geometrys.Push(pGeometry);
   }
   // ��ȡ����
   _pSkeleton->Unserialize(pInput);
   // ��ȡ����
   _pAnimation->Unserialize(pInput);
   // ������ͷ�͸���
   GRs3dTrackPtrs& tracks = _pAnimation->Tracks();
   TInt trackCount = tracks.Count();
   for(TInt n = 0; n < trackCount; n++){
      FRs3dTrack* pTrack = tracks.Get(n);
      TInt boneId = pTrack->BoneId();
      FRs3dBone* pBone = _pSkeleton->Find(boneId);
      pBone->SetTrack(pTrack);
   }
   MO_DEBUG(TC("Unserialize model success. (code=%d, geometry_count=%d, track_count=%d)"),
         _code, geometryCount, trackCount);
   return ESuccess;
}

//============================================================
// <T>�򿪴���</T>
//
// @return ������
//============================================================
TResult FRs3dModel::OnOpen(){
   TResult result = FResource3d::OnOpen();
   // �����м�����
   TInt count = _geometrys.Count();
   for(TInt n = 0; n < count; n++){
      FRs3dGeometry* pGeometry = _geometrys.Get(n);
      //pGeometry->Open();
   }
   return result;
}

//============================================================
// <T>�رմ���</T>
//
// @return ������
//============================================================
TResult FRs3dModel::OnClose(){
   TResult result = FResource3d::OnClose();
   // �ر����м�����
   TInt count = _geometrys.Count();
   for(TInt n = 0; n < count; n++){
      FRs3dGeometry* pGeometry = _geometrys.Get(n);
      //pGeometry->Close();
   }
   return result;
}

MO_NAMESPACE_END
