#include "MoErCore.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>����Ч�������������ϡ�</T>
//============================================================
TEffectParameterDescriptors::TEffectParameterDescriptors(){
   _count = _capacity;
}

//============================================================
// <T>ע��һ��������Ϣ��</T>
//
// @param pParameter ����
//============================================================
TResult TEffectParameterDescriptors::Link(FRenderShaderParameter* pParameter){
   MO_CHECK(pParameter, return ENull);
   TCharC* pLinker = pParameter->Linker();
   // ��������
   EEffectParameter parameterCd = EEffectParameter_Unknown;
   ERenderShader shaderCd = ERenderShader_Unknown;
   ERenderShaderParameterFormat formatCd = ERenderShaderParameterFormat_Unknown;
   REffectParameter::Parse(pLinker, parameterCd, shaderCd, formatCd);
   // ���ò���
   SEffectParameterDescriptor& descriptor = _memory[parameterCd];
   descriptor.parameterPtr = pParameter;
   descriptor.code = parameterCd;
   descriptor.namePtr = pLinker;
   descriptor.bindId = -1;
   descriptor.shaderCd = shaderCd;
   return ESuccess;
}

MO_NAMESPACE_END
