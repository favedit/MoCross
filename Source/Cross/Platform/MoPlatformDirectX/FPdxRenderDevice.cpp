#include "MoPdxRender.h"

MO_NAMESPACE_BEGIN

MO_CLASS_ABSTRACT_IMPLEMENT_INHERITS(FPdxRenderDevice, FRenderDevice);

//============================================================
// <T>������Ⱦ�豸��</T>
//============================================================
FPdxRenderDevice::FPdxRenderDevice(){
   MO_CLEAR(_windowHandle);
}

//============================================================
// <T>������Ⱦ�豸��</T>
//============================================================
FPdxRenderDevice::~FPdxRenderDevice(){
}

MO_NAMESPACE_END
