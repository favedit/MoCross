#include "MoFgCommon.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FGraphicObject, FInstance);

//============================================================
// <T>����ͼ�ζ���</T>
//============================================================
FGraphicObject::FGraphicObject(){
   MO_CLEAR(_pOwner);
   _statusSetup = EFalse;
}

//============================================================
// <T>����ͼ�ζ���</T>
//============================================================
FGraphicObject::~FGraphicObject(){
}

//============================================================
// <T>���ô���</T>
//
// @return ������
//============================================================
TResult FGraphicObject::OnSetup(){
   return ESuccess;
}

//============================================================
// <T>���ô���</T>
//
// @return ������
//============================================================
TResult FGraphicObject::Setup(){
   TResult result = EContinue;
   if(!_statusSetup){
      result = OnSetup();
      if(result){
         MO_WARN("Setup result is not success. (result=%d)", result);
      }
      _statusSetup = ETrue;
   }
   return result;
}

MO_NAMESPACE_END
