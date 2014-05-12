#include "MoBgCore.h"
      
MO_NAMESPACE_BEGIN

//============================================================
// <T>�����Žӿ���̨��</T>
//============================================================
FBridgeConsole::FBridgeConsole(){
   _pClassFactory = MO_CREATE(FClassFactory);
}

//============================================================
// <T>�����Žӿ���̨��</T>
//============================================================
FBridgeConsole::~FBridgeConsole(){
   MO_DELETE(_pClassFactory);
}

//============================================================
// <T>��������</T>
//============================================================
TInt FBridgeConsole::CreateObject(SBridgeLinker* pLinker, TCharC* pClassName){
   FInstance* pInstance = _pClassFactory->Create(pClassName);
   pInstance->ReferIncrease();
   pLinker->instanceId = (TUint32)pInstance;
   return ESuccess;
}

MO_NAMESPACE_END

