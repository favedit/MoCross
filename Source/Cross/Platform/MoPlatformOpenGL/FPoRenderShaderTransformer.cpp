#include <hlsl2glsl.h>
#include "MoPoRender.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FPoRenderShaderTransformer, FRenderShaderTransformer);

//============================================================
// <T>������Ⱦ�ű��任����</T>
//============================================================
FPoRenderShaderTransformer::FPoRenderShaderTransformer(){
}

//============================================================
// <T>������Ⱦ�ű��任����</T>
//============================================================
FPoRenderShaderTransformer::~FPoRenderShaderTransformer(){
}

//============================================================
// <T>ת���ű���</T>
//
// @param pOutputScript ����ű�
// @param pInputScript ����ű�
// @return ������
//============================================================
TResult FPoRenderShaderTransformer::Convert(MString* pOutputScript, MString* pInputScript){
   Hlsl2Glsl_Initialize();
   ShHandle parser = Hlsl2Glsl_ConstructCompiler(EShLangVertex);
   TInt parseOk = Hlsl2Glsl_Parse(parser, pInputScript->MemoryC(), ETargetGLSL_120, ETranslateOpIntermediate);
	TCharC* pInfo = Hlsl2Glsl_GetInfoLog(parser);
   if(parseOk){
   	TInt translateOk = Hlsl2Glsl_Translate(parser, "main", ETargetGLSL_120, ETranslateOpIntermediate);
		TCharC* infoLog = Hlsl2Glsl_GetInfoLog( parser );
		if(translateOk){
      	TCharC* txt = Hlsl2Glsl_GetShader(parser);
         MO_INFO(txt);
      }
   }
   Hlsl2Glsl_DestructCompiler(parser);
	Hlsl2Glsl_Shutdown();
   return ESuccess;
}

MO_NAMESPACE_END
