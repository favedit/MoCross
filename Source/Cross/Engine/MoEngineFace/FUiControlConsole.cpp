#include "MoFmCore.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>����ؼ��������̨��</T>
//============================================================
FUiControlConsole::FUiControlConsole(){
   _pPools = MO_CREATE(FUiControlPoolCollection);
}

//============================================================
// <T>������ʾ�������̨��</T>
//============================================================
FUiControlConsole::~FUiControlConsole(){
   MO_DELETE(_pPools);
}

//============================================================
// <T>���ô���</T>
//
// @return ������
//============================================================
TResult FUiControlConsole::Setup(){
   return ESuccess;
}

//============================================================
// <T>��û����</T>
//
// @param typecCd ����
// @param pClassName ������
// @return �����
//============================================================
FUiControlPool* FUiControlConsole::PoolFind(EControlType typeCd, TCharC* pClassName){
   TInt count = _pPools->Count();
   for(TInt n = 0; n < count; n++){
      FUiControlPool* pPool = _pPools->Get(n);
      if(pPool->TypeCd() != typeCd){
         continue;
      }
      if(pClassName != NULL){
         if(!RString::Equals(pPool->ClassName(), pClassName)){
            continue;
         }
      }
      return pPool;
   }
   return NULL;
}

//============================================================
// <T>ע�Ỻ��ء�</T>
//
// @param pPool �����
// @return ������
//============================================================
TResult FUiControlConsole::PoolRegister(FUiControlPool* pPool){
   _pPools->Push(pPool);
   return ESuccess;
}

//============================================================
// <T>ע������ء�</T>
//
// @param pPool �����
// @return ������
//============================================================
TResult FUiControlConsole::PoolUnregister(FUiControlPool* pPool){
   _pPools->Remove(pPool);
   return ESuccess;
}

//============================================================
// <T>�ռ�һ��ָ�����͵����Ӷ���</T>
//
// @param typeCd ����
// @param pClassName ������
// @return ���Ӷ���
//============================================================
FUiControl* FUiControlConsole::Alloc(EControlType typeCd, TCharC* pClassName){
   FUiControlPool* pPool = PoolFind(typeCd, pClassName);
   MO_FATAL_CHECK(pPool, return NULL,
         "Alloc control failure. (type_cd=%d, class_name=%s)", typeCd, pClassName);
   FUiControl* pControl = pPool->Alloc();
   MO_CHECK(pControl, return NULL);
   return pControl;
}

//============================================================
// <T>�ͷ�һ��ָ�����͵����Ӷ���</T>
//
// @return ���Ӷ���
//============================================================
TResult FUiControlConsole::Free(FUiControl* pControl){
   MO_CHECK(pControl, return ENull);
   // �������
   EControlType controlCd = pControl->ControlCd();
   TCharC* pClassName = pControl->ClassName();
   //pControl->Cla
   FUiControlPool* pPool = PoolFind(controlCd, pClassName);
   MO_FATAL_CHECK(pPool, return ENull,
         "Alloc control failure. (type_cd=%d, class_name=%s)", controlCd, pClassName);
   pPool->Free(pControl);
   return ESuccess;
}

//============================================================
// <T>�ͷŴ���</T>
//
// @return ������
//============================================================
TResult FUiControlConsole::Dispose(){
   return ESuccess;
}

MO_NAMESPACE_END
