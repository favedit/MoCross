#include "MoFgBase.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FRenderableEffect, FInstance);

//============================================================
// <T>������ȾЧ����Ϣ��</T>
//============================================================
FRenderableEffect::FRenderableEffect(){
   MO_CLEAR(_pEffect);
   MO_CLEAR(_pLayout);
}

//============================================================
// <T>������ȾЧ����Ϣ��</T>
//============================================================
FRenderableEffect::~FRenderableEffect(){
}

MO_NAMESPACE_END
