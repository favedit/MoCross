#include "MoE3Scene.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FScene3dMovieRotation, FInstance);

//============================================================
// <T>���춯����</T>
//============================================================
FScene3dMovieRotation::FScene3dMovieRotation(){
   _lastTick = 0;
}

//============================================================
// <T>����������</T>
//============================================================
FScene3dMovieRotation::~FScene3dMovieRotation(){
}

//============================================================
// <T>������Դ��</T>
//
// @param pResource ��Դ����
// @return ������
//============================================================
TResult FScene3dMovieRotation::LoadResource(FRs3dSceneMovie* pResource){
   TResult resultCd = FScene3dMovie::LoadResource(pResource);
   _rotation.x = pResource->Rotation().x * MO_PI_FLOAT / 180.0f;
   _rotation.y = pResource->Rotation().y * MO_PI_FLOAT / 180.0f;
   _rotation.z = pResource->Rotation().z * MO_PI_FLOAT / 180.0f;
   return resultCd;
}

//============================================================
// <T>��������</T>
//
// @param matrix ����
// @return ������
//============================================================
TResult FScene3dMovieRotation::Process(SFloatMatrix3d& matrix){
   FTimerDevice* pTimerDevice = RDeviceManager::Instance().Find<FTimerDevice>();
   if(_lastTick == 0){
      _lastTick = pTimerDevice->CurrentTick();
   }
   TTimeTick currentTick = pTimerDevice->CurrentTick();
   TTimeSpan span = currentTick - _lastTick;
   if(span > _interval){
      // ���ݴ���
      SFloatMatrix3d rotationMatrix;
      rotationMatrix.SetRotation(_rotation);
      rotationMatrix.UpdateForce();
      matrix.Append(rotationMatrix);
      _lastTick = currentTick;
   }
   return ESuccess;
}

MO_NAMESPACE_END
