#include "MoPd9Render.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FPd9RenderShaderParameter, FRenderShaderParameter);

//============================================================
// <T>������Ⱦ��������</T>
//============================================================
FPd9RenderShaderParameter::FPd9RenderShaderParameter(){
   //MO_CLEAR(_piVariable);
}

//============================================================
// <T>������Ⱦ��������</T>
//============================================================
FPd9RenderShaderParameter::~FPd9RenderShaderParameter(){
}

//============================================================
// <T>����������Ϣ��</T>
//
// @param piVariable �����ӿ�
// @return ������
//============================================================
//TResult FPd9RenderShaderParameter::LinkNative(ID3D9ShaderReflectionVariable* piVariable){
//   // �������
//   D3D9_SHADER_VARIABLE_DESC descriptor;
//   HRESULT dxResult = piVariable->GetDesc(&descriptor);
//   if(FAILED(dxResult)){
//      MO_FATAL("Get variable description failure.");
//      return EFailure;
//   }
//   // ��������
//   _name = descriptor.Name;
//   // �ж��Ƿ��Ǳ�ʹ��
//   if((descriptor.uFlags & D3D_SVF_USED) == D3D_SVF_USED){
//      _statusUsed = ETrue;
//   }
//   // ��������
//   _slot = descriptor.StartOffset;
//   _size = descriptor.Size;
//   return ESuccess;
//}

MO_NAMESPACE_END
