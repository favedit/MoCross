#include "MoFgRender.h"

MO_NAMESPACE_BEGIN

MO_CLASS_ABSTRACT_IMPLEMENT_INHERITS(FRenderVertexShader, FRenderShader);

//============================================================
// <T>������̨����</T>
//============================================================
FRenderVertexShader::FRenderVertexShader(){
   _shaderCd = ERenderShader_Vertex;
}

//============================================================
// <T>������̨����</T>
//============================================================
FRenderVertexShader::~FRenderVertexShader(){
}

MO_NAMESPACE_END
