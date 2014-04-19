#include "MoGeDisplay.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FGameScene, FScene3d);

//============================================================
// <T>����ʵ��3Dģ�͡�</T>
//============================================================
FGameScene::FGameScene(){
}

//============================================================
// <T>����ʵ��3Dģ�͡�</T>
//============================================================
FGameScene::~FGameScene(){
}

//============================================================
// <T>���ô���</T>
//
// @return ������
//============================================================
TResult FGameScene::Setup(){
   TResult resultCd = FScene3d::Setup();
   return resultCd;
}

//============================================================
// <T>���ô���</T>
//
// @return ������
//============================================================
TResult FGameScene::ProcessInput(){
   // ��鼤���ӽ�
   if(!_activeView){
      return EContinue;
   }
   FCamera* pCamera = _activeView->Camera();
   MO_CHECK(pCamera, return ENull);
   // �����豸
   FKeyboardDevice* pKeyboardDevice = RDeviceManager::Instance().Find<FKeyboardDevice>();
   TFloat rateMove = 1.0f;
   TFloat angleRate = 0.015f;
   // Forward
   if(pKeyboardDevice->TestKeyDown(EKeyCode_W)){
      pCamera->DoWalk(rateMove);
   }
   // Back
   if(pKeyboardDevice->TestKeyDown(EKeyCode_S)){
      pCamera->DoWalk(-rateMove);
   }
   // Rotation Left
   if(pKeyboardDevice->TestKeyDown(EKeyCode_A)){
      pCamera->DoYaw(angleRate);
   }
   // Rotation Right
   if(pKeyboardDevice->TestKeyDown(EKeyCode_D)){
      pCamera->DoYaw(-angleRate);
   }
   // Down
   if(pKeyboardDevice->TestKeyDown(EKeyCode_Q)){
      pCamera->DoFly(-rateMove);
   }
   // Up
   if(pKeyboardDevice->TestKeyDown(EKeyCode_E)){
      pCamera->DoFly(rateMove);
   }
   // Rotation Down
   if(pKeyboardDevice->TestKeyDown(EKeyCode_Z)){
      pCamera->DoPitch(-rateMove);
   }
   // Rotation Up
   if(pKeyboardDevice->TestKeyDown(EKeyCode_W)){
      pCamera->DoPitch(rateMove);
   }
   pCamera->Update();
   return ESuccess;
}

MO_NAMESPACE_END
