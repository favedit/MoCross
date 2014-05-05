#include "MoFgRender.h"

MO_NAMESPACE_BEGIN

MO_CLASS_ABSTRACT_IMPLEMENT_INHERITS(FRenderShader, FRenderInstance);

//============================================================
// <T>������Ⱦ����</T>
//============================================================
FRenderShader::FRenderShader(){
   _shaderCd = ERenderShader_Unknown;
   MO_CLEAR(_pProgram);
   _pSource = MO_CREATE(FRenderSource);
   _pCompileSource = MO_CREATE(FRenderSource);
}

//============================================================
// <T>������Ⱦ����</T>
//============================================================
FRenderShader::~FRenderShader(){
   MO_DELETE(_pSource);
   MO_DELETE(_pCompileSource);
}

//============================================================
// <T>�������롣</T>
//
// @param pSource ��Դ
// @return ������
//============================================================
TResult FRenderShader::Build(TCharC* pSource){
   MO_CHECK(_pDevice, return ENull);
   TResult resultCd = ESuccess;
   // ��������
   _pSource->Assign(pSource);
   // �任�ű�
   FRenderShaderTransformer* pTransformer = _pDevice->ShaderTransformer();
   if(pTransformer != NULL){
      pTransformer->Convert(_pCompileSource, _pSource);
   }
   // �Ż��ű�
   FRenderShaderOptimizer* pOptimizer = _pDevice->ShaderOptimizer();
   if(pOptimizer != NULL){
      pOptimizer->Convert(_pCompileSource, _pCompileSource);
   }
   // ����ű�
   if(_pCompileSource->IsEmpty()){
      Compile(_pSource->MemoryC());
   }else{
      Compile(_pCompileSource->MemoryC());
   }
   return ESuccess;
}

MO_NAMESPACE_END
