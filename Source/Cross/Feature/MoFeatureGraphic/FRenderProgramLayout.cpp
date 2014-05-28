#include "MoFgRender.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FRenderProgramLayout, FRenderInstance);

//============================================================
// <T>������Ⱦ���֡�</T>
//============================================================
FRenderProgramLayout::FRenderProgramLayout(){
   MO_CLEAR(_pProgram);
   MO_CLEAR(_pRenderable);
}

//============================================================
// <T>������Ⱦ���֡�</T>
//============================================================
FRenderProgramLayout::~FRenderProgramLayout(){
}

//============================================================
// <T>����һ��Ԫ�ء�</T>
//============================================================
TResult FRenderProgramLayout::Push(FRenderProgramLayoutElement* pElement){
   MO_CHECK(pElement, return ENull);
   _elements.Push(pElement);
   return ESuccess;
}

MO_NAMESPACE_END
