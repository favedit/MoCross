#include "MoFgRender.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FRenderLayout, FInstance);

//============================================================
// <T>������Ⱦ���֡�</T>
//============================================================
FRenderLayout::FRenderLayout(){
   MO_CLEAR(_pProgram);
   MO_CLEAR(_pRenderable);
}

//============================================================
// <T>������Ⱦ���֡�</T>
//============================================================
FRenderLayout::~FRenderLayout(){
}

MO_NAMESPACE_END
