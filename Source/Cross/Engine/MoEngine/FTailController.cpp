#include "MoEgDevice.h"
#include "MoEgDisplay.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>������ٿ�������</T>
//============================================================
FTailController::FTailController(){
   _limit = 16;
   _interval = 0;
   _lastTick = 0;
}

//============================================================
// <T>�������ٿ�������</T>
//============================================================
FTailController::~FTailController(){
}

//============================================================
// <T>����һ��������Ϣ��</T>
//
// @param info ������Ϣ
// @return ������
//============================================================
TResult FTailController::Push(STailInfo& info){
   // ���ʱ����
   FTimerDevice* pTimerDevice = RDeviceManager::Instance().Find<FTimerDevice>();
   TTimeTick currentTick = pTimerDevice->CurrentTick();
   if(_lastTick == 0){
      _lastTick = currentTick;
   }else{
      if(currentTick - _lastTick < _interval){
         return ESuccess;
      }
      _lastTick = currentTick;
   }
   // ����Ƿ��Ѿ����Ｋ��
   TInt count = _infos.Count();
   if(count > _limit){
      _infos.Pop();
   }
   // �ӿ�ʼλ�ò���
   _infos.Unshift(info);
   return ESuccess;
}

//============================================================
// <T>��ո��ټ��ϡ�</T>
//
// @return ������
//============================================================
TResult FTailController::Reset(){
   _lastTick = 0;
   _infos.Clear();
   return ESuccess;
}

MO_NAMESPACE_END
