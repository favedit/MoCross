#include <ft2build.h>
#include FT_FREETYPE_H 
#include <MoEngine.h>
#include <MoEngineFace.h>
#include <MoPlatformOpenGLES2.h>
//#include <MoEngineWindows.h>
#include "MoTestLogic.h"

MO_NAMESPACE_BEGIN

FPictureResource* g_pPictureResource = NULL;
FPictureResource* g_pLightResource = NULL;

//============================================================
// <T>����¼�����</T>
//============================================================
TResult DoParticle(TFloat x, TFloat y){
   //FSimpleStage* pStage = (FSimpleStage*)RStageManager::Instance().ActiveStage();
   //for(TInt n = 0; n < 360; n += 30){
   //   // ��������
   //   FPicture* pLightPicture = (FPicture*)RDisplay2dManager::Instance().DisplayAlloc(EDisplayType_Picture);
   //   pLightPicture->Size().Set(64, 64);
   //   pLightPicture->GravityCenter().Set(32, 32);
   //   pLightPicture->GroundColor().Set(1.0f, 1.0f, 1.0f, 0.05f);
   //   pLightPicture->SetResource(g_pLightResource);
   //   pLightPicture->SetOptionTail(ETrue);
   //   pLightPicture->TailController()->SetLimit(40);
   //   pLightPicture->TailController()->SetInterval(20000);
   //   pStage->GroundLayer()->DisplayPush(pLightPicture);
   //   // ����ͼƬ
   //   FPicture* pPicture = (FPicture*)RDisplay2dManager::Instance().DisplayAlloc(EDisplayType_Picture);
   //   pPicture->Size().Set(32, 32);
   //   pPicture->GravityCenter().Set(16, 16);
   //   pPicture->GroundColor().Set(1.0f, 1.0f, 1.0f, 1.0f);
   //   pPicture->SetResource(g_pPictureResource);
   //   pStage->SpriteLayer()->DisplayPush(pPicture);
   //   // ��������
   //   FParticleMove* pParticle = (FParticleMove*)RParticleManager::Instance().ParticleAlloc(EParticleType_Move);
   //   pParticle->StartLocation().Set(x, y);
   //   pParticle->SetRotation((TFloat)n);
   //   pParticle->SetSpeed(0.0001f);
   //   pParticle->SetAcceleration(0.0001f);
   //   pParticle->LinkerPush(pLightPicture);
   //   pParticle->LinkerPush(pPicture);
   //   pParticle->Setup();
   //   pStage->GroundLayer()->ParticleController()->Push(pParticle);
   //}
   return ESuccess;
}

MO_NAMESPACE_END
