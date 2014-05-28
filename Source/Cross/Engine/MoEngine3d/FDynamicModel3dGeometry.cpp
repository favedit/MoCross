#include "MoE3Material.h"
#include "MoE3Model.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FDynamicModel3dGeometry, FRenderable3d);

//============================================================
// <T>����ʵ��3D�����塣</T>
//============================================================
FDynamicModel3dGeometry::FDynamicModel3dGeometry(){
   MO_CLEAR(_pModel);
   MO_CLEAR(_pResource);
   MO_CLEAR(_pMaterialResource);
   _material = MO_CREATE(FMaterial3d);
   _pModelRenderables = MO_CREATE(FModel3dRenderableCollection);
}

//============================================================
// <T>����ʵ��3D�����塣</T>
//============================================================
FDynamicModel3dGeometry::~FDynamicModel3dGeometry(){
   MO_DELETE(_pModelRenderables);
}

//============================================================
// <T>������Դ��</T>
//
// @param pResource ��Դ����
//============================================================
TResult FDynamicModel3dGeometry::Merge(){
   // ������Ⱦ����
   FDynamicRenderable* pDynamicRenderable = FDynamicRenderable::InstanceCreate();
   _dynamicRenderables.Push(pDynamicRenderable);
   TInt count = _pModelRenderables->Count();
   for(TInt n = 0; n < count; n++){
      FModel3dRenderable* pRenderable = _pModelRenderables->Get(n);
      TBool mergeable = pDynamicRenderable->TestMergeable(pRenderable);
      if(!mergeable){
         pDynamicRenderable = FDynamicRenderable::InstanceCreate();
         _dynamicRenderables.Push(pDynamicRenderable);
         mergeable = pDynamicRenderable->TestMergeable(pRenderable);
         MO_CHECK(mergeable, return EFailure);
      }
      pDynamicRenderable->Push(pRenderable);
   }
   // �ϲ���Ⱦ����
   TInt dynamicCount = _dynamicRenderables.Count();
   for(TInt n = 0; n < dynamicCount; n++){
      FDynamicRenderable* pDynamicRenderable = _dynamicRenderables.Get(n);
      pDynamicRenderable->Setup();
      _material->Convert<FMaterial3d>()->BuildDescriptor(pDynamicRenderable->Descriptor());
   }
   return ESuccess;
}

MO_NAMESPACE_END
