#include "MoPoe3Render.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FPoe3RenderDevice, FEoRenderDevice);

//============================================================
// <T>������̨����</T>
//============================================================
FPoe3RenderDevice::FPoe3RenderDevice(){
   _pCapability->SetCode("opengles3");
}

//============================================================
// <T>������̨����</T>
//============================================================
FPoe3RenderDevice::~FPoe3RenderDevice(){
}

MO_NAMESPACE_END