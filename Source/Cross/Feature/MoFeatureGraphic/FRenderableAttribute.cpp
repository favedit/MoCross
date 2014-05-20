#include "MoFgBase.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FRenderableAttribute, FInstance);

//============================================================
// <T>������Ⱦ�������ԡ�</T>
//============================================================
FRenderableAttribute::FRenderableAttribute(){
   _valid = EFalse;
   _offset = -1;
   MO_CLEAR(_pVertexBuffer);
   //_slot = -1;
   //_formatCd = ERenderAttributeFormat_Unknown;
}

//============================================================
// <T>������Ⱦ�������ԡ�</T>
//============================================================
FRenderableAttribute::~FRenderableAttribute(){
}

//============================================================
// <T>����Ƿ���Ч��</T>
//
// @return �Ƿ���Ч
//============================================================
TBool FRenderableAttribute::CheckValid(){
   if(_valid){
      return ETrue;
   }
   // ������
   if(_code.IsEmpty()){
      return EFalse;
   }
   // ���ƫ��
   if(_offset < 0){
      return EFalse;
   }
   // ��黺��
   if(_pVertexBuffer == NULL){
      return EFalse;
   }
   // ��Ч����
   _valid = ETrue;
   return _valid;
}

MO_NAMESPACE_END
