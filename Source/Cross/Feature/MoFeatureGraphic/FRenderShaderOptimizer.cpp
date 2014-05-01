#include "MoFgRender.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FRenderShaderOptimizer, FInstance);

//============================================================
// <T>������Ⱦ�ű��Ż�����</T>
//============================================================
FRenderShaderOptimizer::FRenderShaderOptimizer(){
}

//============================================================
// <T>������Ⱦ�ű��Ż�����</T>
//============================================================
FRenderShaderOptimizer::~FRenderShaderOptimizer(){
}

//============================================================
// <T>ת���ű���</T>
//
// @param pOutputScript ����ű�
// @param pInputScript ����ű�
// @return ������
//============================================================
TResult FRenderShaderOptimizer::Convert(MString* pOutputScript, MString* pInputScript){
   pOutputScript->AssignPointer(pInputScript);
   return ESuccess;
}

MO_NAMESPACE_END
