#include "MoEgDevice.h"
#include "MoEgEntity.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>���쾫��ʵ�塣</T>
//============================================================
FSpriteEntity::FSpriteEntity(){
   _speed = 0.0f;
   _lastTick = 0;
}

//============================================================
// <T>��������ʵ�塣</T>
//============================================================
FSpriteEntity::~FSpriteEntity(){
}

//============================================================
// <T>���ô���</T>
//
// @return ������
//============================================================
TResult FSpriteEntity::Setup(){
   return ESuccess;
}

//============================================================
// <T>�ƶ���Ŀ�괦��</T>
//
// @return ������
//============================================================
TResult FSpriteEntity::MoveTarget(TFloat x, TFloat y, TFloat z){
   _targetSpace.location.Set(x, y, z);
   _direction.Set(_space.location, _targetSpace.location, ETrue);
   return ESuccess;
}

//============================================================
// <T>���Ӵ���</T>
//
// @param data ��������
// @return ������
//============================================================
TResult FSpriteEntity::DoParticle(SParticleData& data){
   if(data.actionCd == EParticleAction_Move){
      _space.location.Assign(data.location);
   }
   return ESuccess;
}

//============================================================
// <T>���´���</T>
//
// @return ������
//============================================================
TResult FSpriteEntity::Update(){
   TResult result = FEntity::Update();
   return result;
}

//============================================================
// <T>�߼�����</T>
//
// @return ������
//============================================================
TResult FSpriteEntity::Process(){
   TResult result = FEntity::Process();
   // �����ƶ�
   FTimerDevice* pTimer = RDeviceManager::Instance().Find<FTimerDevice>();
   TTimeTick currentTick = pTimer->CurrentTick();
   if(_lastTick != 0){
      if(_space.location != _targetSpace.location){
         TFloat distance = _space.location.Distance(_targetSpace.location);
         TFloat spanDistance = RTimeSpan::CalculateFloatSecond(_lastTick, currentTick) * _speed;
         if(spanDistance > distance){
            _space.location.Assign(_targetSpace.location);
         }else{
            SFloatVector3 distanceDirection = _direction.MulToVector3(spanDistance);
            _space.location.Add(distanceDirection.x, distanceDirection.y, distanceDirection.z);
         }
      }
   }
   _lastTick = currentTick;
   return result;
}

//============================================================
// <T>�ͷŴ���</T>
//
// @return ������
//============================================================
TResult FSpriteEntity::Dispose(){
   return ESuccess;
}

MO_NAMESPACE_END
