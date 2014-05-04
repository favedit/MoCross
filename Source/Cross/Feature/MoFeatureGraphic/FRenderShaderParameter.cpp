#include "MoFgRender.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FRenderShaderParameter, FRenderObject);

//============================================================
// <T>������Ⱦ��������</T>
//============================================================
FRenderShaderParameter::FRenderShaderParameter(){
   _shaderCd = ERenderShader_Unknown;
   _formatCd = ERenderShaderParameterFormat_Unknown;
   _statusUsed = EFalse;
   MO_CLEAR(_pShader);
}

//============================================================
// <T>������Ⱦ��������</T>
//============================================================
FRenderShaderParameter::~FRenderShaderParameter(){
}

//============================================================
// <T>����������ݡ�</T>
//
// @param pData ����
// @param capacity ����
// @return ������
//============================================================
TResult FRenderShaderParameter::Get(TAny* pData, TInt capacity){
   MO_FATAL_UNSUPPORT();
   return EUnsupport;
}

//============================================================
// <T>�����������ݡ�</T>
//
// @param pData ����
// @param length ����
// @return ������
//============================================================
TResult FRenderShaderParameter::Set(TAny* pData, TInt length){
   MO_FATAL_UNSUPPORT();
   return EUnsupport;
}

//============================================================
// <T>�������á�</T>
//
// @param pConfig ���ýڵ�
// @return ������
//============================================================
TResult FRenderShaderParameter::LoadConfig(FXmlNode* pConfig){
   MO_CHECK(pConfig, return ENull);
   // ��������
   _name = pConfig->Get("name");
   // ���ù���
   _linker = pConfig->Get("linker");
   // ���ø�ʽ
   TCharC* pShader = pConfig->Get("shader");
   _shaderCd = RRenderShader::Parse(pShader);
   // ���ø�ʽ
   TCharC* pFormat = pConfig->Get("format");
   _formatCd = RRenderShaderParameterFormat::Parse(pFormat);
   return ESuccess;
}

MO_NAMESPACE_END
