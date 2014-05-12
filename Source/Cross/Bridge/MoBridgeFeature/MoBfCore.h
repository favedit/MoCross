#ifndef __MO_BF_CORE_H__
#define __MO_BF_CORE_H__
//************************************************************

#ifndef __MO_BF_COMMON_H__
#include "MoBfCommon.h"
#endif // __MO_BF_COMMON_H__

MO_NAMESPACE_BEGIN

#define MO_INPUT_ELEMENT_MAXCNT 64

//============================================================
// <T>�豸���ߡ�</T>
//============================================================
template <class T>
class MO_BF_DECLARE FBridgeObject : public FInstance
{
   T* _pInstance;
   FScriptInstance* _pScriptInstance;
public:
   //------------------------------------------------------------
   // <T>�����ŽӶ���</T>
   FBridgeObject(){
      MO_CLEAR(_pDevice);
      MO_CLEAR(_pScriptInstance);
   }
   //------------------------------------------------------------
   // <T>�����ŽӶ���</T>
   MO_ABSTRACT ~FBridgeObject(){
   }
public:
   //------------------------------------------------------------
   // <T>���ʵ����</T>
   MO_INLINE T* operator(){
      return _pInstance;
   }
public:
   //------------------------------------------------------------
   // <T>���ʵ����</T>
   MO_INLINE T* Instance(){
      return _pInstance;
   }
   //------------------------------------------------------------
   // <T>����ʵ����</T>
   MO_INLINE void SetInstance(T* pInstance){
      _pInstance = pInstance;
   }
   //------------------------------------------------------------
   // <T>��ýű�ʵ����</T>
   MO_INLINE FScriptInstance* ScriptInstance(){
      return _pScriptInstance;
   }
   //------------------------------------------------------------
   // <T>���ýű�ʵ����</T>
   MO_INLINE void SetScriptInstance(FScriptInstance* pScriptInstance){
      _pScriptInstance = pScriptInstance;
   }
public:
   //------------------------------------------------------------
   // <T>���ô���</T>
   TResult Invoke(){
      return ESuccess;
   }
};

MO_NAMESPACE_END

//************************************************************
#endif // __MO_BF_CORE_H__
