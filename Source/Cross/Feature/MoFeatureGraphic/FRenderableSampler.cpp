#include "MoFgBase.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FRenderableSampler, FInstance);

//============================================================
// <T>������Ⱦ����ȡ������</T>
//============================================================
FRenderableSampler::FRenderableSampler(){
   _slot = -1;
   MO_CLEAR(_pTexture);
}

//============================================================
// <T>������Ⱦ����ȡ������</T>
//============================================================
FRenderableSampler::~FRenderableSampler(){
}

MO_NAMESPACE_END
