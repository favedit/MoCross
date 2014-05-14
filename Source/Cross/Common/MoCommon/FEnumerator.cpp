#include "MoCmEnumerator.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FEnumerator, FInstance);

//============================================================
// <T>����ö������</T>
//============================================================
FEnumerator::FEnumerator(){
}

//============================================================
// <T>����ö������</T>
//============================================================
FEnumerator::~FEnumerator(){
}

//============================================================
// <T>���ô���</T>
//
// @return ������
//============================================================
TResult FEnumerator::Setup(){
   return ESuccess;
}

//============================================================
// <T>���ݴ���Ų���ö����Ŀ��</T>
//
// @param code ����
// @return ������
//============================================================
FEnumeratorItem* FEnumerator::FindByCode(TInt code){
   GEnumeratorItemPtrs::TIterator iterator = _items.Iterator();
   while(iterator.Next()){
      FEnumeratorItem* pItem = *iterator;
      if(pItem->Code() == code){
         return pItem;
      }
   }
   return NULL;
}

//============================================================
// <T>�������Ʋ���ö����Ŀ��</T>
//
// @param pName ����
// @return ������
//============================================================
FEnumeratorItem* FEnumerator::FindByName(TCharC* pName){
   GEnumeratorItemPtrs::TIterator iterator = _items.Iterator();
   while(iterator.Next()){
      FEnumeratorItem* pItem = *iterator;
      if(pItem->IsName(pName)){
         return pItem;
      }
   }
   return NULL;
}

//============================================================
// <T>��������Ϊ���롣</T>
//
// @param pName ����
// @return ����
//============================================================
TInt FEnumerator::Parse(TCharC* pName){
   MO_CHECK(pName, return -1);
   FEnumeratorItem* pItem = FindByName(pName);
   MO_FATAL_CHECK(pItem, return -1, "Parse enum code failure. (enum=%s, name=%s)", (TCharC*)_name, pName);
   TInt code = pItem->Code();
   return code;
}

//============================================================
// <T>��ʽ����Ϊ���ơ�</T>
//
// @param code ����
// @return ����
//============================================================
TCharC* FEnumerator::Format(TInt code){
   MO_CHECK(code >= 0, return NULL);
   FEnumeratorItem* pItem = FindByCode(code);
   MO_FATAL_CHECK(pItem, return NULL, "Parse enum name failure. (enum=%s, code=%d)", (TCharC*)_name, code);
   TCharC* pName = pItem->Name();
   return pName;
}

//============================================================
// <T>ע��һ��ö����Ŀ��</T>
//
// @param pItem ö����Ŀ
// @return ������
//============================================================
TResult FEnumerator::Register(FEnumeratorItem* pItem){
   MO_CHECK(pItem, return ENull);
   // ����ظ�
   if(_items.Contains(pItem)){
      MO_FATAL("Duplicate item in enumerator. (enum=%s, name=%s)", (TCharC*)_name, pItem->Name());
      return EDuplicate;
   }
   // ��������
   _items.Push(pItem);
   return ESuccess;
}

//============================================================
// <T>ע��һ��ö����Ŀ��</T>
//
// @param pItem ö����Ŀ
// @return ������
//============================================================
TResult FEnumerator::Unrgister(FEnumeratorItem* pItem){
   MO_CHECK(pItem, return ENull);
   // ��������
   if(!_items.Contains(pItem)){
      MO_FATAL("Not exists item in enumerator. (enum=%s, name=%s)", (TCharC*)_name, pItem->Name());
      return ENotExists;
   }
   // ��������
   _items.Remove(pItem);
   return ESuccess;
}

//============================================================
// <T>���������Ϣ��</T>
//
// @param pDump ��Ϣ
// @return ������
//============================================================
TResult FEnumerator::Dump(MString* pDump){
   pDump->AppendLine(_name);
   GEnumeratorItemPtrs::TIterator iterator = _items.Iterator();
   while(iterator.Next()){
      FEnumeratorItem* pItem = *iterator;
      pDump->Append(MO_DUMP_INDENT);
      pItem->Dump(pDump);
      pDump->AppendLine();
   }
   return ESuccess;
}

MO_NAMESPACE_END
