#include "MoFrContent3dModel.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FRs3dAnimation, FInstance);

//============================================================
// <T>������Դ3D������</T>
//============================================================
FRs3dAnimation::FRs3dAnimation(){
   MO_CLEAR(_pModel);
   _frameTotal = 0;
   _frameTick = 0;
   _frameTotal = 0;
}

//============================================================
// <T>������Դ3D������</T>
//============================================================
FRs3dAnimation::~FRs3dAnimation(){
}

//============================================================
// <T>���������ﷴ���л���Ϣ����</T>
//
// @param pInput ������
// @return ������
//============================================================
TResult FRs3dAnimation::Unserialize(IDataInput* pInput){
   MO_CHECK(pInput, return ENull);
   // ��ȡ��������
   _frameCount = pInput->ReadInt16();
   _frameTick = pInput->ReadInt16();
   _frameTotal = pInput->ReadInt32();
   // ��ȡ�����б�
   TInt trackCount = pInput->ReadInt16();
   for(TInt n = 0; n < trackCount; n++){
      FRs3dTrack* pTrack = FRs3dTrack::InstanceCreate();
      pTrack->SetAnimation(this);
      pTrack->Unserialize(pInput);
      _tracks.Push(pTrack);
   }
   // ��ȡ�����б�
   TInt movieCount = pInput->ReadInt16();
   for(TInt n = 0; n < movieCount; n++){
      FRs3dMovie* pMovie = FRs3dMovie::InstanceCreate();
      pMovie->Unserialize(pInput);
      _movies.Push(pMovie);
   }
   return ESuccess;
}

//============================================================
// <T>��ո��ټ��ϡ�</T>
//============================================================
void FRs3dAnimation::TrackClear(){
   _tracks.Clear();
}

//============================================================
// <T>��ն������ϡ�</T>
//============================================================
void FRs3dAnimation::MovieClear(){
   _movies.Clear();
}

MO_NAMESPACE_END
