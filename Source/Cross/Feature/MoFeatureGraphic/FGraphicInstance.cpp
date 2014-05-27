#include "MoFgCommon.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FGraphicInstance, FInstance);

//============================================================
// <T>����ͼ��ʵ����</T>
//============================================================
FGraphicInstance::FGraphicInstance(){
   MO_CLEAR(_pOwner);
   _statusSetup = EFalse;
}

//============================================================
// <T>����ͼ��ʵ����</T>
//============================================================
FGraphicInstance::~FGraphicInstance(){
}

//============================================================
// <T>���ô���</T>
//
// @return ������
//============================================================
TResult FGraphicInstance::OnSetup(){
   return ESuccess;
}

//============================================================
// <T>���ô���</T>
//
// @return ������
//============================================================
TResult FGraphicInstance::Setup(){
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
