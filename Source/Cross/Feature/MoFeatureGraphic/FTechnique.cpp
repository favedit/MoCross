#include "MoFgRender.h"
#include "MoFgTechnique.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>������Ⱦ������</T>
//============================================================
FTechnique::FTechnique(){
   _pEffects = MO_CREATE(FEffectCollection);
   MO_CLEAR(_pProgram);
}

//============================================================
// <T>������Ⱦ������</T>
//============================================================
FTechnique::~FTechnique(){
   MO_DELETE(_pEffects);
   MO_DELETE(_pProgram);
}

//============================================================
// <T>���ô���</T>
//
// @return ������
//============================================================
TResult FTechnique::Setup(){
   return ESuccess;
}

//============================================================
//FEffect* FTechnique::FindFEffect(ERenderEffect typeCd){
//   TInt count = _pEffects->Count();
//   for(TInt n = 0; n < count; n++){
//      FEffect* pEffect = _pEffects->Get(n);
//      if(pEffect->TypeCd() == typeCd){
//         return pEffect;
//      }
//   }
//   return NULL;
//}

//============================================================
// <T>�����С��</T>
//
// @return ������
//============================================================
TResult FTechnique::Resize(TInt width, TInt height){
   TInt count = _pEffects->Count();
   for(TInt n = 0; n < count; n++){
      FEffect* pEffect = _pEffects->Get(n);
      pEffect->Resize(width, height);
   }
   return ESuccess;
}

//============================================================
// <T>���ƴ���</T>
//
// @return ������
//============================================================
TResult FTechnique::Draw(FRenderRegion* pRegion, TInt offset, TInt count){
   //MO_CHECK(pRegion, return ENull);
   //FRenderableCollection* pRenderables = pRegion->Renderables();
   //TInt offsetEnd = offset + count;
   ////............................................................
   //// ����Ч����
   ////for(TInt n = offset; n < offsetEnd; ){
   ////   FRenderable* pRenderable = (FRenderable*)pRenderables->Get(n);
   ////   FEffect* pEffect = pRenderable->EffectFind(_name);
   ////   if(pEffect == NULL){
   ////      SEffectDescriptor descriptor;
   ////      // REffectManager::Instance().BuildAutomatic();
   ////   }
   ////}
   ////............................................................
   //// ������Ⱦ���ͽ��з���
   //for(TInt n = offset; n < offsetEnd; ){
   //   // ��÷���
   //   TInt groupBegin = n;
   //   TInt groupEnd = offsetEnd;
   //   FRenderable* pGroupRenderable = pRenderables->Get(groupBegin);
   //   FMaterial* pGroupMaterial = pGroupRenderable->Material();
   //   ERenderEffect effectCd = pGroupMaterial->EffectCd();
   //   for(TInt i = n; i < offsetEnd; i++){
   //      FRenderable* pRenderable = pRenderables->Get(i);
   //      FMaterial* pMaterial = pRenderable->Material();
   //      if(pGroupMaterial->Compare(pMaterial) != 0){
   //         groupEnd = i;
   //         break;
   //      }
   //      n++;
   //   }
   //   //............................................................
   //   // ���Ƶ�ǰ��
   //   FEffect* pEffect = FindFEffect(effectCd);
   //   pEffect->DrawGroup(pRegion, groupBegin, groupEnd - groupBegin);
   //}
   return ESuccess;
}

MO_NAMESPACE_END
