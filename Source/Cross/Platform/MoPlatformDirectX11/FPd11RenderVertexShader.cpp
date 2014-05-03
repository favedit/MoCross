#include "MoPd11Render.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FPd11RenderVertexShader, FRenderVertexShader);

//============================================================
// <T>������Ⱦ����</T>
//============================================================
FPd11RenderVertexShader::FPd11RenderVertexShader(){
   MO_CLEAR(_piData);
   MO_CLEAR(_piLinkage);
   MO_CLEAR(_piShader);
}

//============================================================
// <T>������Ⱦ����</T>
//============================================================
FPd11RenderVertexShader::~FPd11RenderVertexShader(){
   MO_RELEASE(_piData);
   MO_RELEASE(_piLinkage);
   MO_RELEASE(_piShader);
}

//============================================================
// <T>���ô���</T>
//
// @return ������
//============================================================
TResult FPd11RenderVertexShader::Setup(){
   //_renderId.uint32 = glCreateShader(GL_VERTEX_SHADER);
   //TResult resultCd = _pDevice->CheckError("glCreateShader", "Create vertex shader failure. (shader_id=%d)", _renderId.uint32);
   //return resultCd;
   return ESuccess;
}

//============================================================
// <T>���봦��</T>
//
// @param pSource �����ַ���
// @return ������
//============================================================
TResult FPd11RenderVertexShader::Compile(TCharC* pSource){
   // ����豸��Ϣ
   MO_CHECK(_pDevice, return ENull);
   FPd11RenderDevice* pRenderDevice = _pDevice->Convert<FPd11RenderDevice>();
   FRenderCapability* pCapability = pRenderDevice->Capability();
   TCharC* pShaderVersion = pCapability->ShaderVertexVersion();
   // �ϴ�����
   TInt length = RString::Length(pSource);
   ID3D10Blob* piError = NULL;
   HRESULT shaderResult = S_OK;
   HRESULT dxResult = D3DX11CompileFromMemory(pSource, length, NULL, NULL, NULL, "main", pShaderVersion, 0, 0, NULL, &_piData, &piError, &shaderResult);
   if(FAILED(dxResult) || FAILED(shaderResult)){
      TCharC* pBuffer = (TCharC*)piError->GetBufferPointer();
      MO_ERROR("Compile from memory failure.\n%s", pBuffer);
      MO_RELEASE(piError);
      MO_FATAL("Compile failure.");
      return EFailure;
   }
   // ����������
   dxResult = pRenderDevice->NativeDevice()->CreateClassLinkage(&_piLinkage);
   if(FAILED(dxResult)){
      MO_FATAL("Create class linkage failure.");
      return EFailure;
   }
   // ������Ⱦ��
   TAny* pData = _piData->GetBufferPointer();
   TInt dataSize = _piData->GetBufferSize();
   dxResult = pRenderDevice->NativeDevice()->CreateVertexShader(pData, dataSize, _piLinkage, &_piShader);
   if(FAILED(dxResult)){
      MO_FATAL("Create vertex shader failure.");
      return EFailure;
   }

   //TInt np = desc.InputParameters;
   //for(TInt n = 0; n < np; n++){
   //   D3D11_SIGNATURE_PARAMETER_DESC paramDesc;
   //   piReflection->GetInputParameterDesc(0, &paramDesc);
   //   n = n;
   //}
   //TInt rb = desc.BoundResources;
   //for(TInt n = 0; n < rb; n++){
   //   D3D11_SHADER_INPUT_BIND_DESC bdesc;
   //   piReflection->GetResourceBindingDesc(n, &bdesc);
   //   n = n;
   //}

   //ID3D11ShaderReflectionVariable* pVariable = piReflection->GetVariableByName("_matrix");
   //D3D11_SHADER_VARIABLE_DESC vDesc;
   //pVariable->GetDesc(&vDesc);
   //ID3D11ShaderReflectionType* piReflectionType = pVariable->GetType();
   //D3D11_SHADER_TYPE_DESC typeDesc;
   //piReflectionType->GetDesc(&typeDesc);


   ////ID3D11ShaderReflectionConstantBuffer* piConstantBuffer = piReflection->GetConstantBufferByName("_matrix2");
   ////ID3D11ShaderReflectionVariable* pAmbientLightingVar = piReflection->GetVariableByName("_matrix2");
   ////TInt slot = pAmbientLightingVar->GetInterfaceSlot(0);

   MO_INFO("Create vertex shader success. (status=%d)\n%s", dxResult, pSource);
   return ESuccess;
}

//============================================================
// <T>������</T>
//
// @return ������
//============================================================
TResult FPd11RenderVertexShader::Suspend(){
   return ESuccess;
}

//============================================================
// <T>��������</T>
//
// @return ������
//============================================================
TResult FPd11RenderVertexShader::Resume(){
   return ESuccess;
}

//============================================================
// <T>��������</T>
//
// @return ������
//============================================================
TResult FPd11RenderVertexShader::Dispose(){
   //TResult resultCd = ESuccess;
   //if(_renderId.uint32 != 0){
   //   glDeleteShader(_renderId.uint32);
   //   resultCd = _pDevice->CheckError("glCreateShader", "Delete vertex shader failure. (shader_id=%d)", _renderId.uint32);
   //   _renderId.uint32 = 0;
   //}
   //return resultCd;
   return ESuccess;
}

MO_NAMESPACE_END
