#include "MoFgRender.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FRenderLayout, FRenderObject);

//============================================================
// <T>������Ⱦ���֡�</T>
//============================================================
FRenderLayout::FRenderLayout(){
   MO_CLEAR(_pProgram);
}

//============================================================
// <T>������Ⱦ���֡�</T>
//============================================================
FRenderLayout::~FRenderLayout(){
}

//============================================================
// <T>����һ��Ԫ�ء�</T>
//============================================================
TResult FRenderLayout::Push(FRenderLayoutElement* pElement){
   MO_CHECK(pElement, return ENull);
   _elements.Push(pElement);
   return ESuccess;
}

MO_NAMESPACE_END
