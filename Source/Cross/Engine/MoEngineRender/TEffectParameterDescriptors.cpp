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
// @param pLinker ������Ϣ
//============================================================
void TEffectParameterDescriptors::Register(TCharC* pLinker){
   // ��������
   EEffectParameter parameterCd = EEffectParameter_Unknown;
   ERenderShader shaderCd = ERenderShader_Unknown;
   ERenderShaderParameterFormat formatCd = ERenderShaderParameterFormat_Unknown;
   REffectParameter::Parse(pLinker, parameterCd, shaderCd, formatCd);
   // ���ò���
   SEffectParameterDescriptor& descriptor = _memory[parameterCd];
   descriptor.shaderCd = shaderCd;
   descriptor.code = parameterCd;
   descriptor.namePtr = pLinker;
   descriptor.bindId = -1;
}

MO_NAMESPACE_END
