#include "MoE3Model.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FModel3d, FDisplay3d);

//============================================================
// <T>����ʵ��3Dģ�͡�</T>
//============================================================
FModel3d::FModel3d(){
   _pGeometrys = MO_CREATE(FModel3dGeometryCollection);
   _pAnimation = MO_CREATE(FAnimation3d);
}

//============================================================
// <T>����ʵ��3Dģ�͡�</T>
//============================================================
FModel3d::~FModel3d(){
   MO_DELETE(_pRenderables);
   MO_DELETE(_pAnimation);
}

//============================================================
// <T>������Դ��</T>
//
// @param pResource ��Դ����
// @return ������
//============================================================
TResult FModel3d::LoadResource(FRs3dModel* pResource){
   MO_ASSERT(pResource);
   _pResource = pResource;
   // ������Ⱦ���󼯺�
   GRs3dGeometryPtrs& geometrys = pResource->Geometrys();
   TInt count = geometrys.Count();
   for(TInt n = 0; n < count; n++){
      FRs3dGeometry* pRsGeometry = geometrys.Get(n);
      // �����Ⱦ����ģ��
      FModel3dGeometry* pGeometry = FModel3dGeometry::InstanceCreate();
      pGeometry->LoadResource(pRsGeometry);
      _pGeometrys->Push(pGeometry);
   }
   return ESuccess;
}

MO_NAMESPACE_END
