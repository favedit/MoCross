#include "MoFgRender.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FRenderView, FInstance);

//============================================================
// <T>������Ⱦ�����</T>
//============================================================
FRenderView::FRenderView(){
   _pRenderables = MO_CREATE(FRenderableCollection);
   _pRenderTargets = MO_CREATE(FRenderTargetCollection);
}

//============================================================
// <T>������Ⱦ�����</T>
//============================================================
FRenderView::~FRenderView(){
   MO_DELETE(_pRenderables);
   MO_DELETE(_pRenderTargets);
}

MO_NAMESPACE_END
