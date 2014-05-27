#include "MoFgRender.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FRenderObject, FGraphicInstance);

//============================================================
// <T>������Ⱦ����</T>
//============================================================
FRenderObject::FRenderObject(){
   _statusSetup = EFalse;
   MO_CLEAR(_pDevice);
}

//============================================================
// <T>������Ⱦ����</T>
//============================================================
FRenderObject::~FRenderObject(){
}

//============================================================
// <T>��ͣ����</T>
//
// @return ������
//============================================================
TResult FRenderObject::Suspend(){
   return ESuccess;
}

//============================================================
// <T>��������</T>
//
// @return ������
//============================================================
TResult FRenderObject::Resume(){
   return ESuccess;
}

MO_NAMESPACE_END
