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
   // ���ñ�־
   //TUint32 shaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
   TUint32 shaderFlags = 0;
#ifdef _MO_DEBUG
    shaderFlags |= D3DCOMPILE_DEBUG;
#endif // _MO_DEBUG
    // �ϴ�����
   TInt length = RString::Length(pSource);
   ID3D10Blob* piError = NULL;
   HRESULT shaderResult = S_OK;
   HRESULT dxResult = D3DX11CompileFromMemory(pSource, length, NULL, NULL, NULL, "main", pShaderVersion, shaderFlags, 0, NULL, &_piData, &piError, &shaderResult);
   if(FAILED(dxResult) || FAILED(shaderResult)){
      TCharC* pBuffer = (TCharC*)piError->GetBufferPointer();
      MO_ERROR("Compile from memory failure.\n%s", pBuffer);
      MO_RELEASE(piError);
      MO_FATAL("Compile failure.");
      return EFailure;
   }
   // ������Ⱦ��
   TAny* pData = _piData->GetBufferPointer();
   TInt dataSize = _piData->GetBufferSize();
   dxResult = pRenderDevice->NativeDevice()->CreateVertexShader(pData, dataSize, NULL, &_piShader);
   if(FAILED(dxResult)){
      MO_FATAL("Create vertex shader failure.");
      return EFailure;
   }
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
   return ESuccess;
}

MO_NAMESPACE_END
