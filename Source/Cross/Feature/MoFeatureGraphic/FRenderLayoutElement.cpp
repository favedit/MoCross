#include "MoFgRender.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FRenderLayoutElement, FRenderObject);

//============================================================
// <T>������Ⱦ����Ԫ�ء�</T>
//============================================================
FRenderLayoutElement::FRenderLayoutElement(){
   MO_CLEAR(_pAttribute);
   MO_CLEAR(_pStream);
}

//============================================================
// <T>������Ⱦ����Ԫ�ء�</T>
//============================================================
FRenderLayoutElement::~FRenderLayoutElement(){
}

MO_NAMESPACE_END
