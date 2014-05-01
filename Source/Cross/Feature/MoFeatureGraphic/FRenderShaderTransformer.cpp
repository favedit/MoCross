#include "MoFgRender.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FRenderShaderTransformer, FInstance);

//============================================================
// <T>������Ⱦ�ű��任����</T>
//============================================================
FRenderShaderTransformer::FRenderShaderTransformer(){
}

//============================================================
// <T>������Ⱦ�ű��任����</T>
//============================================================
FRenderShaderTransformer::~FRenderShaderTransformer(){
}

//============================================================
// <T>ת���ű���</T>
//
// @param pOutputScript ����ű�
// @param pInputScript ����ű�
// @return ������
//============================================================
TResult FRenderShaderTransformer::Convert(MString* pOutputScript, MString* pInputScript){
   pOutputScript->AssignPointer(pInputScript);
   return ESuccess;
}

MO_NAMESPACE_END
