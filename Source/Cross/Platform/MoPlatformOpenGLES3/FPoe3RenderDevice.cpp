#include "MoPoe3Render.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FPoe3RenderDevice, FEoRenderDevice);

//============================================================
// <T>������̨����</T>
//============================================================
FPoe3RenderDevice::FPoe3RenderDevice(){
   _pCapability->SetCode("gles3");
   _pCapability->SetLabel("OpenGL ES 3.0");
}

//============================================================
// <T>������̨����</T>
//============================================================
FPoe3RenderDevice::~FPoe3RenderDevice(){
}

MO_NAMESPACE_END
