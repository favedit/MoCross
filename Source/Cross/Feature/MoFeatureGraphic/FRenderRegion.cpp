#include "MoFgRender.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FRenderRegion, FInstance);

//============================================================
// <T>��������</T>
//============================================================
FRenderRegion::FRenderRegion(){
   _optionRenderTarget = EFalse;
   _pViews = MO_CREATE(FRenderViewCollection);
   _pLights = MO_CREATE(FLightCollection);
   _pRenderables = MO_CREATE(FRenderableCollection);
   _pVisibleRenderables = MO_CREATE(FRenderableCollection);
   _pTextures = MO_CREATE(FRenderTextureCollection);
}

//============================================================
// <T>��������</T>
//============================================================
FRenderRegion::~FRenderRegion(){
   MO_DELETE(_pViews);
   MO_DELETE(_pLights);
   //MO_DELETE(_pVisibleRenderables);
   MO_DELETE(_pRenderables);
   MO_DELETE(_pTextures);
}

//============================================================
// <T>�����Ƿ���Ի��ơ�</T>
//
// @return �Ƿ���Ի���
//============================================================
TBool FRenderRegion::TestRenderable(){
   if(_pRenderables->IsEmpty()){
      return EFalse;
   }
   return ETrue;
}

MO_NAMESPACE_END
