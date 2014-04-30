#include "MoE2Display.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>������ʾ������</T>
//============================================================
FMovie::FMovie(){
   //_objectCd |= EComponent_Renderable;
   _typeCd = EDisplayType_Movie;
   _pMaterial = MO_CREATE(FMaterial);
   //_pMaterial->SetEffectCd(ERenderEffect_2dTexture);
   MO_CLEAR(_pResource);
   _rate = 1.0f;
   _startTick = 0;
   _lastTick = 0;
   MO_CLEAR(_pActiveClip);
   MO_CLEAR(_pActiveFrame);
   _hasActiveAction = EFalse;
}

//============================================================
// <T>������ʾ������</T>
//============================================================
FMovie::~FMovie(){
   MO_DELETE(_pMaterial);
}

//============================================================
// <T>���㲢�����Ⱦ���ݡ�</T>
//
// @param renderable ��Ⱦ����
//============================================================
TResult FMovie::CalculateRenderable(SRenderable& renderable){
   FDisplay2d::CalculateRenderable(renderable);
   if(_pActiveFrame != NULL){
      SRenderableItem& item = renderable.items.Get(0);
      SIntPoint2& baryCenter = _pActiveFrame->ValidBarycenter();
      item.location.x -= baryCenter.x;
      item.location.y -= baryCenter.y;
   }
   return ESuccess;
}

//============================================================
// <T>������Դ��</T>
//
// @param pResource ��Դ
//============================================================
void FMovie::LoadResource(FAnimationResource* pResource){
   _pResource = pResource;
   //_pMaterial->TextureSet(pResource->Bitmap()->RenderTexture());
}

//============================================================
// <T>����б�</T>
//
// @return ������
//============================================================
TResult FMovie::PlayClear(){
   _startTick = 0;
   MO_CLEAR(_pActiveClip);
   MO_CLEAR(_pActiveFrame);
   _hasActiveAction = EFalse;
   _actions.Clear();
   return ESuccess;
}

//============================================================
// <T>���Ŷ�����</T>
//
// @param pAction ����
// @return ������
//============================================================
TResult FMovie::Play(SMovieAction* pAction){
   MO_ASSERT(pAction);
   _actions.Push(*pAction);
   return ESuccess;
}

//============================================================
// <T>���Ŵ���</T>
//
// @return ������
//============================================================
TResult FMovie::ProcessPlay(){
   // ����ʱ����
   //TTimeTick current = RDeviceManager::Instance().TimerDevice()->CurrentTick();
   //TInt span = (TInt)((current - _startTick) / 1000);
   //if(_rate != 1.0f){
   //   span = (TInt)((TFloat)span * _rate);
   //}
   // ��ü������
   _pActiveClip = _pResource->FindClipByDirection(_activeAction.directionCd);
   // ��ü���֡
   //TInt frameIndex = _pResource->CalculateFrameIndex(span);
   //_pActiveFrame = _pActiveClip->Frame(frameIndex);
   //_size.Set((TFloat)_pActiveFrame->ValidSize().width, (TFloat)_pActiveFrame->ValidSize().height);
   //_coord.Assign(_pActiveFrame->Coord());
   return ESuccess;
}

//============================================================
// <T>�߼�����</T>
//
// @return ������
//============================================================
TResult FMovie::Process(){
   // �����Դ
   if(_pResource == NULL){
      return EContinue;
   }
   // ��ü��������
   if(!_hasActiveAction){
      if(!_actions.IsEmpty()){
         _activeAction = _actions.Shift();
         _hasActiveAction = ETrue;
         //_startTick = RDeviceManager::Instance().TimerDevice()->CurrentTick();
      }
   }
   // ����Ƿ��м�������
   if(!_hasActiveAction){
      return EContinue;
   }
   // ��������
   switch(_activeAction.actionCd){
      case EMovieAction_Play:
         ProcessPlay();
         break;
   }
   return ESuccess;
}

MO_NAMESPACE_END
