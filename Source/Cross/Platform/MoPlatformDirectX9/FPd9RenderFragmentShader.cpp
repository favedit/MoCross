#include "MoPd9Render.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FPd9RenderFragmentShader, FRenderFragmentShader);

//============================================================
// <T>������Ⱦ����</T>
//============================================================
FPd9RenderFragmentShader::FPd9RenderFragmentShader(){
   _pBuffer = MO_CREATE(FPd9RenderShaderBuffer);
   _pBuffer->SetName("FragmentBuffer");
   MO_CLEAR(_piData);
   MO_CLEAR(_piShader);
   MO_CLEAR(_piTable);
}

//============================================================
// <T>������Ⱦ����</T>
//============================================================
FPd9RenderFragmentShader::~FPd9RenderFragmentShader(){
   MO_DELETE(_pBuffer);
   MO_RELEASE(_piData);
   MO_RELEASE(_piShader);
   MO_RELEASE(_piTable);
}

//============================================================
// <T>���ô���</T>
//
// @return ������
//============================================================
TResult FPd9RenderFragmentShader::Setup(){
   return ESuccess;
}

//============================================================
// <T>���봦��</T>
//
// @param pSource �����ַ���
// @return ������
//============================================================
TResult FPd9RenderFragmentShader::Compile(TCharC* pSource){
   // ����豸��Ϣ
   MO_CHECK(_pDevice, return ENull);
   FPd9RenderDevice* pRenderDevice = _pDevice->Convert<FPd9RenderDevice>();
   FRenderCapability* pCapability = pRenderDevice->Capability();
   TCharC* pShaderVersion = pCapability->ShaderFragmentVersion();
   // ���ñ�־
   //TUint32 shaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
   TUint32 shaderFlags = 0;
#ifdef _MO_DEBUG
    shaderFlags |= D3DCOMPILE_DEBUG;
#endif // _MO_DEBUG
    // �ϴ�����
   TInt length = RString::Length(pSource);
   ID3DXBuffer* piError = NULL;
   HRESULT dxResult = D3DXCompileShader(pSource, length, NULL, NULL, "main", pShaderVersion, shaderFlags, &_piData, &piError, &_piTable);
   if(FAILED(dxResult)){
      TCharC* pBuffer = (TCharC*)piError->GetBufferPointer();
      MO_ERROR("Compile from memory failure.\n%s", pBuffer);
      MO_RELEASE(piError);
      MO_FATAL("Compile failure.");
      return EFailure;
   }
   // ������Ⱦ��
   TAny* pData = _piData->GetBufferPointer();
   TInt dataSize = _piData->GetBufferSize();
   dxResult = pRenderDevice->NativeDevice()->CreatePixelShader((const DWORD*)pData, &_piShader);
   if(FAILED(dxResult)){
      MO_FATAL("Create vertex shader failure.");
      return EFailure;
   }
   MO_INFO("Create fragment shader success. (status=%d)\n%s", dxResult, pSource);
   return ESuccess;
}

//============================================================
// <T>������</T>
//
// @return ������
//============================================================
TResult FPd9RenderFragmentShader::Suspend(){
   return ESuccess;
}

//============================================================
// <T>��������</T>
//
// @return ������
//============================================================
TResult FPd9RenderFragmentShader::Resume(){
   return ESuccess;
}

//============================================================
// <T>��������</T>
//
// @return ������
//============================================================
TResult FPd9RenderFragmentShader::Dispose(){
   return ESuccess;
}

MO_NAMESPACE_END
