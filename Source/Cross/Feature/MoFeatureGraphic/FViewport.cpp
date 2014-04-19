#include "MoFgViewport.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FViewport, FInstance);

//============================================================
// <T>�����ӽǡ�</T>
//============================================================
FViewport::FViewport(){
}

//============================================================
// <T>�����ӽǡ�</T>
//============================================================
FViewport::~FViewport(){
}

//============================================================
// <T>������Ϣ��</T>
//
// @param left ���
// @param top �ϱ�
// @param width ���
// @param height �߶�
//============================================================
void FViewport::Set(TInt left, TInt top, TInt width, TInt height){
   _position.Set(left, top);
   _size.Set(width, height);
}

MO_NAMESPACE_END
