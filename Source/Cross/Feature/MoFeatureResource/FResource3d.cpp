#include "MoFrContent3dBase.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FResource3d, FContent);

//============================================================
// <T>������Դ��</T>
//============================================================
FResource3d::FResource3d(){
   _typeCd = EResource3d_Unknown;
   _code = 0;
   _timeout = 0;
   _statusOpen = EFalse;
   _statusReady = EFalse;
}

//============================================================
// <T>������Դ��</T>
//============================================================
FResource3d::~FResource3d(){
   MO_DEBUG_INFO(TC("Release resource. (code=%d)"), _code);
}

//============================================================
// <T>�����Ƿ�׼���á�</T>
//
// @return �Ƿ�׼���á�</T>
//============================================================
TBool FResource3d::TestReady(){
   return EFalse;
}

//============================================================
// <T>�����Ƿ���Ч��</T>
//
// @return �Ƿ���Ч
//============================================================
TBool FResource3d::TestValid(){
   return ETrue;
}

//============================================================
// <T>�򿪴���</T>
//
// @return ������
//============================================================
TResult FResource3d::OnOpen(){
   return ESuccess;
}

//============================================================
// <T>�رմ���</T>
//
// @return ������
//============================================================
TResult FResource3d::OnClose(){
   return ESuccess;
}

//============================================================
// <T>���������ﷴ���л���Ϣ����</T>
//
// @param pInput ������
// @return ������
//============================================================
TResult FResource3d::Unserialize(IDataInput* pInput){
   MO_CHECK(pInput, return ENull);
   _name.UnserializeAutomatic(pInput);
   // _code = pInput->ReadInt32();
   // _timeout = pInput->ReadInt32();
   return ESuccess;
}

//============================================================
// <T>�򿪴���</T>
//
// @return ������
//============================================================
TResult FResource3d::Open(){
   TResult result = ESuccess;
   if(!_statusOpen){
      result = OnOpen();
      _statusOpen = ETrue;
   }
   return result;
}

//============================================================
// <T>�رմ���</T>
//
// @return ������
//============================================================
TResult FResource3d::Close(){
   TResult result = ESuccess;
   if(_statusOpen){
      result = OnClose();
      _statusOpen = EFalse;
   }
   return result;
}

MO_NAMESPACE_END
