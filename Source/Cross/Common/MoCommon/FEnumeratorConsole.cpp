#include "MoCmEnumerator.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FEnumeratorConsole, FConsole);

//============================================================
// <T>����ö��������̨��</T>
//============================================================
FEnumeratorConsole::FEnumeratorConsole(){
}

//============================================================
// <T>����ö��������̨��</T>
//============================================================
FEnumeratorConsole::~FEnumeratorConsole(){
}

//============================================================
// <T>ע��һ��ö������</T>
//
// @param pEnumerator ö��
// @return ������
//============================================================
TResult FEnumeratorConsole::Register(FEnumerator* pEnumerator){
   MO_CHECK(pEnumerator, return ENull);
   TCharC* pName = pEnumerator->Name();
   MO_CHECK(pName, return ENull);
   // ����ظ�
   FEnumerator* pFind = _enumerators.Find(pName);
   if(pFind != NULL){
      MO_FATAL("Duplicate enumerator. (name=%s)", pName);
      return EDuplicate;
   }
   // ��������
   _enumerators.Set(pName, pEnumerator);
   return ESuccess;
}

//============================================================
// <T>ע��һ��ö������</T>
//
// @param pEnumerator ö��
// @return ������
//============================================================
TResult FEnumeratorConsole::Unrgister(FEnumerator* pEnumerator){
   MO_CHECK(pEnumerator, return ENull);
   TCharC* pName = pEnumerator->Name();
   MO_CHECK(pName, return ENull);
   // ��������
   FEnumerator* pFind = _enumerators.Find(pName);
   if(pFind == NULL){
      MO_FATAL("Not exists enumerator. (name=%s)", pName);
      return ENotExists;
   }
   // ��������
   _enumerators.Remove(pName);
   return ESuccess;
}

MO_NAMESPACE_END
