#include "MoFgBase.h"
#include "MoFgVisual.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FVisualRegion, FInstance);

//============================================================
// <T>����ɼ�����</T>
//============================================================
FVisualRegion::FVisualRegion(){
   _pInputVisuals = MO_CREATE(FVisualCollection);
   _pVisuals = MO_CREATE(FVisualCollection);
   _pOutputVisuals = MO_CREATE(FVisualCollection);
   _pAlphaMaterial = MO_CREATE(FVisualMaterial);
   _pMaterials = MO_CREATE(FVisualMaterialCollection);
}

//============================================================
// <T>�����ɼ�����</T>
//============================================================
FVisualRegion::~FVisualRegion(){
   MO_DELETE(_pInputVisuals);
   MO_DELETE(_pVisuals);
   MO_DELETE(_pOutputVisuals);
   MO_DELETE(_pAlphaMaterial);
   MO_DELETE(_pMaterials);
}

//============================================================
// <T>���ҿɼ����ʡ�</T>
//
// @param pMaterial ����
// @return �ɼ�����
//============================================================
FVisualMaterial* FVisualRegion::FindMaterial(FMaterial* pMaterial){
   TInt count = _pMaterials->Count();
   for(TInt n = 0 ; n < count; n++){
      FVisualMaterial* pVisualMaterial = _pMaterials->Get(n);
      if(pVisualMaterial->Material() == pMaterial){
         return pVisualMaterial;
      }
   }
   return NULL;
}

//============================================================
// <T>��ȡ�ɼ����󼯺ϡ�</T>
//
// @param pRenderables ��Ⱦ����
// @param capacity ����
// @return ��ø���
//============================================================
TResult FVisualRegion::FetchVisuals(FRenderableCollection* pRenderables){
   MO_CHECK(pRenderables, return ENull);
   pRenderables->Clear();
   _outputLocker.Enter();
   TInt count = _pOutputVisuals->Count();
   for(TInt n = 0; n < count; n++){
      FVisualNode* pVisual = _pOutputVisuals->Get(n);
      FRenderable* pRenderable = pVisual->Renderable();
      pRenderables->Push(pRenderable);
   }
   _outputLocker.Leave();
   return ESuccess;
}

//============================================================
// <T>���ӿɼ����󼯺ϡ�</T>
//
// @param pRenderables ��Ⱦ����
// @param count ����
// @return ��ø���
//============================================================
TResult FVisualRegion::PushVisuals(FRenderableCollection* pRenderables){
   MO_CHECK(pRenderables, return ENull);
   _inputLocker.Enter();
   _pInputVisuals->Clear();
   TInt count = pRenderables->Count();
   for(TInt n = 0; n < count; n++){
      FRenderable* pRenderable = pRenderables->Get(n);
      FVisualNode* pVisual = (FVisualNode*)pRenderable->VisualInfo();
      _pInputVisuals->Push(pVisual);
   }
   _inputLocker.Leave();
   return ESuccess;
}

//============================================================
// <T>��Ⱦ�����������</T>
//
// @param pSource ��Դ����
// @param pTarget Ŀ�����
// @param pCondition ����
// @return �ȽϽ��
//============================================================
static TInt VisualRegionMaterialComparer(FVisualMaterial* pSource, FVisualMaterial* pTarget, TAny* pCondition){
   //FMaterial* pSourceMaterial = pSource->Material();
   //FMaterial* pTargetMaterial = pTarget->Material();
   //if(pSourceMaterial->OptionAlpha() && pTargetMaterial->OptionAlpha()){
   //}else if(!pSourceMaterial->OptionAlpha() && pTargetMaterial->OptionAlpha()){
   //   return 1;
   //}else if(pSourceMaterial->OptionAlpha() && !pTargetMaterial->OptionAlpha()){
   //   return 1;
   //}else{
   //   return 0;
   //}
   //FEffect* pSourceEffect = pSource->ActiveEffect();
   //MO_CHECK(pSourceEffect, return 0);
   //FEffect* pTargetEffect = pTarget->ActiveEffect();
   //MO_CHECK(pTargetEffect, return 0);
   //return pSourceEffect - pTargetEffect;
   return 0;
}

//============================================================
// <T>�߼�����</T>
//
// @return ������
//============================================================
TResult FVisualRegion::Process(){
   // ��ȡ����
   _inputLocker.Enter();
   if(!_pInputVisuals->IsEmpty()){
      _pVisuals->Assign(_pInputVisuals);
   }
   _inputLocker.Leave();
   //............................................................
   TInt visualCount = _pVisuals->Count();
   if(visualCount == 0){
      return EContinue;
   }
   //............................................................
   // ��ղ���
   _pAlphaMaterial->Reset();
   TInt materialCount = _pMaterials->Count();
   for(TInt n = 0 ; n < materialCount; n++){
      FVisualMaterial* pVisualMaterial = _pMaterials->Get(n);
      pVisualMaterial->Reset();
   }
   // �������
   for(TInt n = 0; n < visualCount; n++){
      FVisualNode* pVisual = _pVisuals->Get(n);
      FRenderable* pRenderable =  pVisual->Renderable();
      if(pRenderable->ActiveEffect() == NULL){
         continue;
      }
      FMaterial* pMaterial = pRenderable->MaterialReference();
      MO_CHECK(pMaterial, continue);
      if(pMaterial->OptionAlpha()){
         _pAlphaMaterial->Push(pVisual);
      }else{
         FVisualMaterial* pVisualMaterial = FindMaterial(pMaterial);
         if(pVisualMaterial == NULL){
            pVisualMaterial = FVisualMaterial::InstanceCreate();
            pVisualMaterial->SetMaterial(pMaterial);
            _pMaterials->Push(pVisualMaterial);
         }
         pVisualMaterial->Push(pVisual);
      }
   }
   //............................................................
   // ��������
   _pMaterials->SortValue(&VisualRegionMaterialComparer);
   // �����ڴ���
   _pVisuals->Clear();
   for(TInt n = 0 ; n < materialCount; n++){
      FVisualMaterial* pVisualMaterial = _pMaterials->Get(n);
      if(!pVisualMaterial->Visuals()->IsEmpty()){
         pVisualMaterial->Process();
         _pVisuals->AppendPointer(pVisualMaterial->Visuals());
      }
   }
   if(!_pAlphaMaterial->Visuals()->IsEmpty()){
      _pAlphaMaterial->Process();
      _pVisuals->AppendPointer(_pAlphaMaterial->Visuals());
   }
   //............................................................
   // ������
   _outputLocker.Enter();
   if(!_pVisuals->IsEmpty()){
      _pOutputVisuals->Assign(_pVisuals);
   }
   _outputLocker.Leave();
   return ESuccess;
}

MO_NAMESPACE_END
