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
   // ��������
   _slot = descriptor.StartOffset;
   _size = descriptor.Size;
   return ESuccess;
}

MO_NAMESPACE_END
