#include "MoFgRender.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FRenderInstance, FGraphicInstance);

//============================================================
// <T>������Ⱦ����</T>
//============================================================
FRenderInstance::FRenderInstance(){
   _statusSetup = EFalse;
   MO_CLEAR(_pDevice);
}

//============================================================
// <T>������Ⱦ����</T>
//============================================================
FRenderInstance::~FRenderInstance(){
}

//============================================================
// <T>��ͣ����</T>
//
// @return ������
//============================================================
TResult FRenderInstance::Suspend(){
   return ESuccess;
}

//============================================================
// <T>��������</T>
//
// @return ������
//============================================================
TResult FRenderInstance::Resume(){
   return ESuccess;
}

MO_NAMESPACE_END
