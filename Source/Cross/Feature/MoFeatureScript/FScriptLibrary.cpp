#include "MoScript.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FScriptLibrary, FScriptObject);

//============================================================
// <T>����ű��⡣</T>
//============================================================
FScriptLibrary::FScriptLibrary(){
   MO_CLEAR(_pScriptMachine);
}

//============================================================
// <T>�����ű��⡣</T>
//============================================================
FScriptLibrary::~FScriptLibrary(){
}

//============================================================
// <T>���ݿռ����ƺ��������������</T>
//
// @param pSpaceName �ռ�����
// @param pClassName ������
// @return �����
//============================================================
FScriptClass* FScriptLibrary::FindClass(TCharC* pSpaceName, TCharC* pClassName){
   // ��������
   TFsName name;
   name.Append(pSpaceName);
   name.Append(TC("."));
   name.Append(pClassName);
   // ���������
   FScriptClass* pClass = FindClass(name);
   return pClass;
}

//============================================================
// <T>�������Ʋ��������</T>
//
// @param pName ����
// @return �����
//============================================================
FScriptClass* FScriptLibrary::FindClass(TCharC* pName){
   MO_CHECK(_pScriptMachine, return NULL);
   // ���������
   FScriptClass* pClass = _classes.Find(pName);
   if(pClass != NULL){
      return pClass;
   }
   // ���������
   pClass = _pScriptMachine->ClassFactory()->Create<FScriptClass>(MO_SCRIPT_CLASS);
   pClass->SetScriptLibrary(this);
   pClass->SetName(pName);
   pClass->Open();
   _classes.Set(pName, pClass);
   return pClass;
}

MO_NAMESPACE_END
