#include "MoFgRender.h"

MO_NAMESPACE_BEGIN

MO_CLASS_ABSTRACT_IMPLEMENT_INHERITS(FRenderFragmentShader, FRenderShader);

//============================================================
// <T>������̨����</T>
//============================================================
FRenderFragmentShader::FRenderFragmentShader(){
   _shaderCd = ERenderShader_Fragment;
}

//============================================================
// <T>������̨����</T>
//============================================================
FRenderFragmentShader::~FRenderFragmentShader(){
}

MO_NAMESPACE_END
