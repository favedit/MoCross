#include "MoPoe2Render.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FPoe2RenderDevice, FPoRenderDevice);

//============================================================
// <T>������̨����</T>
//============================================================
FPoe2RenderDevice::FPoe2RenderDevice(){
   _pCapability->SetCode("gles2");
   _pCapability->SetLabel("OpenGL ES 2.0");
}

//============================================================
// <T>������̨����</T>
//============================================================
FPoe2RenderDevice::~FPoe2RenderDevice(){
}

MO_NAMESPACE_END
