#include "MoPoRender.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FPoRenderShaderOptimizer, FRenderShaderOptimizer);

//============================================================
// <T>������Ⱦ�ű��Ż�����</T>
//============================================================
FPoRenderShaderOptimizer::FPoRenderShaderOptimizer(){
}

//============================================================
// <T>������Ⱦ�ű��Ż�����</T>
//============================================================
FPoRenderShaderOptimizer::~FPoRenderShaderOptimizer(){
}

//============================================================
// <T>ת���ű���</T>
//
// @param pOutputScript ����ű�
// @param pInputScript ����ű�
// @return ������
//============================================================
TResult FPoRenderShaderOptimizer::Convert(MString* pOutputScript, MString* pInputScript){
   pOutputScript->AssignPointer(pInputScript);
   return ESuccess;
}

MO_NAMESPACE_END
