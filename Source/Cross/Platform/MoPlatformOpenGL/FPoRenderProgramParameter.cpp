#include "MoPoRender.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FPoRenderProgramParameter, FRenderProgramParameter);

//============================================================
// <T>������Ⱦ��������</T>
//============================================================
FPoRenderProgramParameter::FPoRenderProgramParameter(){
}

//============================================================
// <T>������Ⱦ��������</T>
//============================================================
FPoRenderProgramParameter::~FPoRenderProgramParameter(){
}

//============================================================
// <T>����������ݡ�</T>
//
// @param pData ����
// @param capacity ����
// @return ������
//============================================================
TResult FPoRenderProgramParameter::Get(TAny* pData, TInt capacity){
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
TResult FPoRenderProgramParameter::Set(TAny* pData, TInt length){
   _pDevice->BindConst(_shaderCd, _slot, _formatCd, pData, length);
   return EUnsupport;
}

MO_NAMESPACE_END
