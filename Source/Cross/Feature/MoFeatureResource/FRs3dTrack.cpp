#include "MoFrContent3dModel.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FRs3dTrack, FInstance);

//============================================================
// <T>������Դ3D���١�</T>
//============================================================
FRs3dTrack::FRs3dTrack(){
   MO_CLEAR(_pAnimation);
   _optionBoneScale = EFalse;
   _boneId = 0;
   _frameTick = 0;
}

//============================================================
// <T>������Դ3D���١�</T>
//============================================================
FRs3dTrack::~FRs3dTrack(){
}

//============================================================
// <T>���������ﷴ���л���Ϣ����</T>
//
// @param pInput ������
// @return ������
//============================================================
TResult FRs3dTrack::Unserialize(IDataInput* pInput){
   MO_CHECK(pInput, return ENull);
   // ��ȡ������Ϣ
   _optionBoneScale = pInput->ReadBool();
   _boneId = pInput->ReadInt8();
   _frameTick = pInput->ReadInt16();
   // ��ȡת������
   _matrix.Unserialize(pInput);
   _matrixInvert.Assign(_matrix);
   _matrixInvert.Invert();
   //............................................................
   // ��ȡ����֡�б�
   TInt frameCount = pInput->ReadInt16();
   for(TInt n = 0; n < frameCount; n++){
      FRs3dFrame* pFrame = FRs3dFrame::InstanceCreate();
      pFrame->SetIndex(n);
      pFrame->Unserialize(pInput);
      _frames.Push(pFrame);
   }
   return ESuccess;
}

//============================================================
// <T>���������ﷴ���л���Ϣ����</T>
//
// @param pInput ������
// @return ������
//============================================================
TResult FRs3dTrack::CalculateFrameInfo(SRs3dFrameInfo& info, TTimeTick tick){
   TInt frameCount = _frames.Count();
   if(frameCount == 0){
      return EFailure;
   }
   // ȥ������
   if(tick < 0){
      tick = -tick;
   }
   // ������
   TInt span = (TInt)((TFloat)(TInt)tick * info.playRate);
   TInt index = (span / _frameTick) % frameCount;
   // ��õ�ǰ֡����һ֡
   FRs3dFrame* pCurrentFrame = _frames.Get(index);
   FRs3dFrame* pNextFrame = NULL;
   if(index < frameCount -1){
      pNextFrame = _frames.Get(index + 1);
   }else{
      pNextFrame = _frames.Get(0);
   }
   // ���ý��
   info.tick = tick;
   info.rate = (TFloat)(span % _frameTick) / (TFloat)_frameTick;
   info.currentPtr = pCurrentFrame;
   info.nextPtr = pNextFrame;
   return true;
}

//============================================================
// <T>������ݡ�</T>
//============================================================
void FRs3dTrack::Clear(){
   _frames.Clear();
}

MO_NAMESPACE_END
