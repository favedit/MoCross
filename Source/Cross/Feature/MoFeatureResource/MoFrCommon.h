#ifndef __MO_FR_COMMON_H__
#define __MO_FR_COMMON_H__
//************************************************************

#ifndef __MO_FR_PUBLIC_H__
#include "MoFrPublic.h"
#endif // __MO_FR_PUBLIC_H__

#ifndef __MO_FR_COMPRESS_H__
#include "MoFrCompress.h"
#endif // __MO_FR_COMPRESS_H__

MO_NAMESPACE_BEGIN

//============================================================
// <T>��Դ�����</T>
//============================================================
struct SResourceHandle{
public:
   TResourceId id;
   TCharC* namePtr;
   FInstance* instancePtr;
public:
   //------------------------------------------------------------
   // <T>������Դ�����</T>
   MO_INLINE SResourceHandle(){
      id = 0;
      MO_CLEAR(namePtr);
      MO_CLEAR(instancePtr);
   }
public:
   //------------------------------------------------------------
   // <T>ת��Ϊ��š�</T>
   operator TResourceId(){
      return id;
   }
   //------------------------------------------------------------
   // <T>ת��Ϊ��š�</T>
   operator TCharC*(){
      return namePtr;
   }
public:
   //------------------------------------------------------------
   // <T>�������ݡ�</T>
   void Set(TResourceId resourceId = 0, TCharC* pName = NULL, FInstance* pInstance = NULL){
      id = resourceId;
      namePtr = pName;
      instancePtr = pInstance;
   }
};
//------------------------------------------------------------
typedef SResourceHandle TResourceHandle;

//============================================================
// <T>���α�־��</T>
//============================================================
enum EGeomFlag{
   // �̳�
   Inherit = 0,
   // ��
   No = 1,
   // ��
   Yes = 2,
};

//============================================================
// <T>���α�־���ߡ�</T>
//============================================================
struct MO_FR_DECLARE RGeomFlag{
public:
   //============================================================
   // <T>���������</T>
   //============================================================
   static TInt ToInteger(TBool value){
      return value ? Yes : Inherit;
   }

   //============================================================
   // <T>��ò���ֵ��</T>
   //
   // @param pv:value ����
   // @param pd:default Ĭ��
   //============================================================
   static TBool ToBoolean(TInt value, TBool defaultValue = EFalse){
      if(value == 0){
         return defaultValue;
      }
      return (Yes == value);
   }
};

MO_NAMESPACE_END
      
//************************************************************
#endif // __MO_FR_COMMON_H__
