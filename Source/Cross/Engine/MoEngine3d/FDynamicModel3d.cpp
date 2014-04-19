#include "MoE3Model.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FDynamicModel3d, FDisplay3d);

//============================================================
// <T>����ʵ��3Dģ�͡�</T>
//============================================================
FDynamicModel3d::FDynamicModel3d(){
   _pModelRenderables = MO_CREATE(FModel3dRenderableCollection);
   _pGeometrys = MO_CREATE(FDynamicModel3dGeometryCollection);
}

//============================================================
// <T>����ʵ��3Dģ�͡�</T>
//============================================================
FDynamicModel3d::~FDynamicModel3d(){
   MO_DELETE(_pModelRenderables);
   MO_DELETE(_pRenderables);
}

//============================================================
// <T>���ݲ���ͬ��һ�������塣</T>
//============================================================
FDynamicModel3dGeometry* FDynamicModel3d::SyncGeometryByRenderable(FModel3dRenderable* pRenderable){
   FMaterial* pMaterial = pRenderable->MaterialReference();
   // ���Ҽ�����
   TInt count = _pGeometrys->Count();
   for(TInt n = 0; n < count; n++){
      FDynamicModel3dGeometry* pGeometry = _pGeometrys->Get(n);
      if(pGeometry->Material() == pMaterial){
         if(pGeometry->VertexStreams()->EqualsDescription(pRenderable->VertexStreams())){
            return pGeometry;
         }
      }
   }
   // �½�������
   FDynamicModel3dGeometry* pGeometry = FDynamicModel3dGeometry::InstanceCreate();
   pGeometry->SetMaterial(pMaterial);
   pGeometry->VertexStreams()->Assign(pRenderable->VertexStreams());
   _pGeometrys->Push(pGeometry);
   return pGeometry;
}

//============================================================
// <T>����һ����Ⱦ����</T>
//============================================================
TResult FDynamicModel3d::PushRenderable(FModel3dRenderable* pRenderable){
   // ���뼯��
   _pModelRenderables->Push(pRenderable);
   // ���뼯��
   FMaterial* pMaterial = pRenderable->MaterialReference();
   FDynamicModel3dGeometry* pGeometry = SyncGeometryByRenderable(pRenderable);
   pGeometry->ModelRenderables()->Push(pRenderable);
   return ESuccess;
}

//============================================================
// <T>������Դ��</T>
//
// @param pResource ��Դ����
// @return ������
//============================================================
TResult FDynamicModel3d::Merge(){
   TInt count = _pGeometrys->Count();
   for(TInt n = 0; n < count; n++){
      FDynamicModel3dGeometry* pGeometry = _pGeometrys->Get(n);
      pGeometry->Merge();
   }
   return ESuccess;
}

MO_NAMESPACE_END
