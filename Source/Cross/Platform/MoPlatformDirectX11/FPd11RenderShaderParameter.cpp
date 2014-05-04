#include "MoPd11Render.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FPd11RenderShaderParameter, FRenderShaderParameter);

//============================================================
// <T>������Ⱦ��������</T>
//============================================================
FPd11RenderShaderParameter::FPd11RenderShaderParameter(){
   MO_CLEAR(_piVariable);
}

//============================================================
// <T>������Ⱦ��������</T>
//============================================================
FPd11RenderShaderParameter::~FPd11RenderShaderParameter(){
}

//============================================================
// <T>����������Ϣ��</T>
//
// @param piVariable �����ӿ�
// @return ������
//============================================================
TResult FPd11RenderShaderParameter::LinkNative(ID3D11ShaderReflectionVariable* piVariable){
   // �������
   D3D11_SHADER_VARIABLE_DESC descriptor;
   HRESULT dxResult = piVariable->GetDesc(&descriptor);
   if(FAILED(dxResult)){
      MO_FATAL("Get variable description failure.");
      return EFailure;
   }
   // ��������
   _name = descriptor.Name;
   // �ж��Ƿ��Ǳ�ʹ��
   if((descriptor.uFlags & D3D_SVF_USED) == D3D_SVF_USED){
      _statusUsed = ETrue;
   }
   return ESuccess;
}

//============================================================
// <T>����������ݡ�</T>
//
// @param pData ����
// @param capacity ����
// @return ������
//============================================================
TResult FPd11RenderShaderParameter::Get(TAny* pData, TInt capacity){
   return ESuccess;
}

//============================================================
// <T>�����������ݡ�</T>
//
// @param pData ����
// @param length ����
// @return ������
//============================================================
TResult FPd11RenderShaderParameter::Set(TAny* pData, TInt length){
   ID3D11ShaderReflectionConstantBuffer* piBuffer = _piVariable->GetBuffer();
   return ESuccess;
}

MO_NAMESPACE_END
