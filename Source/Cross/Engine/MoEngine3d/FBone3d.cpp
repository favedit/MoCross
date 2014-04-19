#include "MoE3Display.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>����ʵ��3D��ͷ��</T>
//============================================================
FBone3d::FBone3d(){
   MO_CLEAR(_pAnimation);
   _modelId = 0;
   _boneId = 0;
   MO_CLEAR(_pBoneResource);
   MO_CLEAR(_pTrackResource);
}

//============================================================
// <T>����ʵ��3D��ͷ��</T>
//============================================================
FBone3d::~FBone3d(){
}

//============================================================
// <T>������Դ��</T>
//
// @param pResource ��Դ����
//============================================================
TResult FBone3d::LoadResource(FRs3dBone* pResource){
   MO_CHECK(pResource, return ENull);
   _boneId = pResource->Id();
   _pBoneResource = pResource;
   _pTrackResource = pResource->Track();
   return ESuccess;
}

//============================================================
// <T>���´���</T>
//
// @param tick ʱ��
// @return ������
//============================================================
TResult FBone3d::Update(TTimeTick tick){
   MO_ERROR_CHECK(_pTrackResource, return EFailure,
         "Bone track is null. (tick=%d, track=0x%08X)", tick, _pTrackResource);
   // ����֡��Ϣ
   SRs3dFrameInfo info;
   _pTrackResource->CalculateFrameInfo(info, tick);
   info.Update();
   // �������
   _matrix.Assign(_pTrackResource->MatrixInvert());
   _matrix.Append(info.matrix);
   return ESuccess;
}

MO_NAMESPACE_END
