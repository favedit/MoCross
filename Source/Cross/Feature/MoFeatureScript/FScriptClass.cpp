#include "MoScript.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FScriptClass, FScriptObject);

//============================================================
// <T>����ű������</T>
//============================================================
FScriptClass::FScriptClass(){
   MO_CLEAR(_pScriptLibrary);
}

//============================================================
// <T>�����ű������</T>
//============================================================
FScriptClass::~FScriptClass(){
}

//============================================================
// <T>��ýű���������</T>
//
// @return �ű�������
//============================================================
FScriptMachine* FScriptClass::ScriptMachine(){
   MO_CHECK(_pScriptLibrary, return NULL);
   return _pScriptLibrary->ScriptMachine();
}

//============================================================
// <T>�������ơ�</T>
//
// @param pName ��������
//============================================================
void FScriptClass::SetName(TCharC* pName){
   _name = pName;
   // �ָ�����
   TInt splitter = _name.LastIndexOf(TC('.'));
   if(splitter != ENotFound){
      _spaceName = _name.LeftStrC(splitter);
      _className = _name.MidStrC(splitter + 1);
   }else{
      _spaceName.Clear();
      _className = _name;
   }
}

//============================================================
// <T>�������Ʋ����ֶΡ�</T>
//
// @param pName ����
// @return �ֶ�
//============================================================
FScriptField* FScriptClass::FindField(TCharC* pName){
   MO_CHECK(_pScriptLibrary, return NULL);
   // �����ֶζ���
   FScriptField* pField = _fields.Find(pName);
   if(pField != NULL){
      return pField;
   }
   // �����ֶζ���
   pField = _pScriptLibrary->ScriptMachine()->ClassFactory()->Create<FScriptField>(MO_SCRIPT_FIELD);
   pField->SetScriptClass(this);
   pField->SetName(pName);
   pField->Open();
   _fields.Set(pName, pField);
   return pField;
}

//============================================================
// <T>�������Ʋ������ԡ�</T>
//
// @param pName ����
// @return ����
//============================================================
FScriptProperty* FScriptClass::FindProperty(TCharC* pName){
   MO_CHECK(_pScriptLibrary, return NULL);
   // ���������
   FScriptProperty* pProperty = _properties.Find(pName);
   if(pProperty != NULL){
      return pProperty;
   }
   // ���������
   pProperty = _pScriptLibrary->ScriptMachine()->ClassFactory()->Create<FScriptProperty>(MO_SCRIPT_PROPERTY);
   pProperty->SetScriptClass(this);
   pProperty->SetName(pName);
   pProperty->Open();
   _properties.Set(pName, pProperty);
   return pProperty;
}

//============================================================
// <T>�����������Һ�����</T>
//
// @param pDescriptor ����
// @return ����
//============================================================
FScriptMethod* FScriptClass::FindMethod(TCharC* pDescriptor){
   MO_CHECK(_pScriptLibrary, return NULL);
   // ���������
   FScriptMethod* pMethod = _methods.Find(pDescriptor);
   if(pMethod != NULL){
      return pMethod;
   }
   // ���������
   pMethod = _pScriptLibrary->ScriptMachine()->ClassFactory()->Create<FScriptMethod>(MO_SCRIPT_METHOD);
   pMethod->SetScriptClass(this);
   pMethod->SetDescriptor(pDescriptor);
   pMethod->Open();
   _methods.Set(pDescriptor, pMethod);
   return pMethod;
}

//============================================================
// <T>����ʵ������</T>
//
// @return ʵ������
//============================================================
FScriptInstance* FScriptClass::CreateInstance(){
   MO_FATAL_UNSUPPORT();
   return NULL;
}

MO_NAMESPACE_END
