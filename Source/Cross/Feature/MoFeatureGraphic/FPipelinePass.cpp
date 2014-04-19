#include "MoFgRender.h"
#include "MoFgTechnique.h"
#include "MoFgPipeline.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FPipelinePass, FInstance);

//============================================================
// <T>������Ⱦ�ܵ����̡�</T>
//============================================================
FPipelinePass::FPipelinePass(){
   MO_CLEAR(_pPipeline);
   _lastSortTick = 0;
}

//============================================================
// <T>������Ⱦ�ܵ����̡�</T>
//============================================================
FPipelinePass::~FPipelinePass(){
}

//============================================================
// <T>���ô���</T>
//
// @return ������
//============================================================
TResult FPipelinePass::Setup(){
   // ע��ͳ����
   _renderableActiveStatistics = RStatisticsManager::Instance().SyncByName("pipeline.pass.renderable.active");
   _renderableSortStatistics = RStatisticsManager::Instance().SyncByName("pipeline.pass.renderable.sort");
   _renderableDrawStatistics = RStatisticsManager::Instance().SyncByName("pipeline.pass.renderable.draw");
   return ESuccess;
}

//============================================================
// <T>�����С��</T>
//
// @return ������
//============================================================
TResult FPipelinePass::Resize(TInt width, TInt height){
   return ESuccess;
}

//============================================================
// <T>���ƿ�ʼ����</T>
//
// @param pRegion ��Ⱦ����
// @return ������
//============================================================
TResult FPipelinePass::DrawBegin(FRenderRegion* pRegion){
   MO_CHECK(pRegion, return ENull);
   return ESuccess;
}

//============================================================
// <T>����������</T>
//
// @return ������
//============================================================
TResult FPipelinePass::DrawRegion(FRenderRegion* pRegion){
   MO_CHECK(pRegion, return ENull);
   // �����Ⱦ����
   FRenderableCollection* pRenderables = pRegion->Renderables();
   //............................................................
   TFsName spaceName;
   spaceName.AppendFormat("%s.%s.", _pPipeline->Name(), (TCharC*)_name);
   //............................................................
   // �����Ⱦ�������Ⱦ��
   _renderableActiveStatistics->Begin();
   TInt count = pRenderables->Count();
   for(TInt n = 0; n < count; n++){
      FRenderable* pRenderable = pRenderables->Get(n);
      FMaterial* pMaterial = pRenderable->Material();
      //pRenderable->UpdateMatrix();
      // �����ȾЧ��
      TFsName effectName = spaceName.MemoryC();
      effectName.Append(pMaterial->EffectName());
      FEffect* pEffect = pRenderable->EffectFind(effectName);
      if(pEffect == NULL){
         pEffect = REffectManager::Instance().Find(effectName, pRenderable);
         pRenderable->EffectBind(pEffect);
      }
      pRenderable->SetActiveEffect(pEffect);
   }
   _renderableActiveStatistics->Finish();
   //............................................................
   // ����Ѿ�����õĿɼ���Ⱦ���󼯺�
   FRenderableCollection* pVisibleRenderables = pRegion->VisibleRenderables();
   FVisualRegion* pVisualRegion = pRegion->VisualRegion();
   pVisualRegion->FetchVisuals(pVisibleRenderables);
   pVisualRegion->PushVisuals(pRenderables);
   //............................................................
   // ����Ч�����ͽ��з���
   _renderableDrawStatistics->Begin();
   TInt visibleCount = pVisibleRenderables->Count();
   for(TInt n = 0; n < visibleCount; ){
      // ��÷���
      TInt groupBegin = n;
      TInt groupEnd = visibleCount;
      FRenderable* pGroupRenderable = pVisibleRenderables->Get(groupBegin);
      FEffect* pGroupEffect = pGroupRenderable->ActiveEffect();
      for(TInt i = n; i < visibleCount; i++){
         FRenderable* pRenderable = (FRenderable*)pVisibleRenderables->Get(i);
         FEffect* pEffect = pRenderable->ActiveEffect();
         if(pGroupEffect != pEffect){
            groupEnd = i;
            break;
         }
         n++;
      }
      // ���Ƶ�ǰ��Ⱦ��
      pGroupEffect->DrawGroup(pRegion, groupBegin, groupEnd - groupBegin);
   }
   _renderableDrawStatistics->Finish();
   return ESuccess;
}

//============================================================
// <T>���ƽ�������</T>
//
// @param pRegion ��Ⱦ����
// @return ������
//============================================================
TResult FPipelinePass::DrawEnd(FRenderRegion* pRegion){
   MO_CHECK(pRegion, return ENull);
   return ESuccess;
}

MO_NAMESPACE_END
