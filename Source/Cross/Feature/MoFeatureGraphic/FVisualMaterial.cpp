#include "MoFgBase.h"
#include "MoFgVisual.h"
#include "MoFgTechnique.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FVisualMaterial, FInstance);

//============================================================
// <T>����ɼ�����</T>
//============================================================
FVisualMaterial::FVisualMaterial(){
   MO_CLEAR(_pMaterial);
   _pVisuals = MO_CREATE(FVisualCollection);
}

//============================================================
// <T>�����ɼ�����</T>
//============================================================
FVisualMaterial::~FVisualMaterial(){
   MO_DELETE(_pVisuals);
}

//============================================================
// <T>����һ�����Ӷ���</T>
//
// @param pVisual �ɼ��ڵ�
// @return ������
//============================================================
TResult FVisualMaterial::Push(FVisualNode* pVisual){
   _pVisuals->Push(pVisual);
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
static TInt VisualMaterialRenderableComparer(FVisualNode* pSource, FVisualNode* pTarget, TAny* pCondition){
   // �������
   FRenderable* pSourceRenderable = pSource->Renderable();
   FRenderable* pTargetRenderable = pTarget->Renderable();
   // �Ƚ�Ч����
   FEffect* pSourceEffect = pSourceRenderable->ActiveEffect();
   MO_CHECK(pSourceEffect, return 0);
   FEffect* pTargetEffect = pTargetRenderable->ActiveEffect();
   MO_CHECK(pTargetEffect, return 0);
   if(pSourceEffect != pTargetEffect){
      return pSourceEffect - pTargetEffect;
   }
   // �Ƚ�����ʹ��������飩
   FRenderIndexBuffer* pSourceIndexBuffer = pSourceRenderable->IndexBuffer();
   MO_CHECK(pSourceIndexBuffer, return 0);
   FRenderIndexBuffer* pTargetIndexBuffer = pTargetRenderable->IndexBuffer();
   MO_CHECK(pTargetIndexBuffer, return 0);
   if(pSourceIndexBuffer != pTargetIndexBuffer){
      return pSourceIndexBuffer - pTargetIndexBuffer;
   }
   return 0;
}

//============================================================
TResult FVisualMaterial::Process(){
   _pVisuals->SortValue(&VisualMaterialRenderableComparer);
   return ESuccess;
}

//============================================================
// <T>�������ݡ�</T>
//
// @return ������
//============================================================
TResult FVisualMaterial::Reset(){
   _pVisuals->Clear();
   return ESuccess;
}

MO_NAMESPACE_END
