#include "MoFgRender.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FRenderProgramLayoutElement, FRenderInstance);

//============================================================
// <T>������Ⱦ����Ԫ�ء�</T>
//============================================================
FRenderProgramLayoutElement::FRenderProgramLayoutElement(){
   MO_CLEAR(_pAttribute);
   MO_CLEAR(_pStream);
}

//============================================================
// <T>������Ⱦ����Ԫ�ء�</T>
//============================================================
FRenderProgramLayoutElement::~FRenderProgramLayoutElement(){
}

MO_NAMESPACE_END
