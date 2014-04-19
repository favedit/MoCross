#include "MoFgVisual.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>����ɼ��ӽǡ�</T>
//============================================================
FVisualView::FVisualView(){
   _pVisuals = MO_CREATE(FVisualCollection);
}

//============================================================
// <T>�����ɼ��ӽǡ�</T>
//============================================================
FVisualView::~FVisualView(){
   MO_DELETE(_pVisuals);
}

//============================================================
// <T>����һ�����Ӷ���</T>
//============================================================
TResult FVisualView::Push(FVisualNode* pVisual){
   _pVisuals->Push(pVisual);
   return ESuccess;
}

MO_NAMESPACE_END
