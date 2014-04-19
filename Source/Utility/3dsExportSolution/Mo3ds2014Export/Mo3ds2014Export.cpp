//============================================================
//   DYNAMIC LINK LIBRARY : Mo3DSExport Project Overview
//------------------------------------------------------------
// ��3DS MAX�е���ģ�͵Ķ�̬���ӿ⡣
// - �ڲ�û�е�������ֻ��һ���ſ⡣
// - Ŀ�����ڲ���Ҫ����3DS MAX���������£����¶�̬���ر�����Ķ�̬�⡣
//  ������������һ��DLL(Mo3DSExporter)�ṩ��
//------------------------------------------------------------
// Copyright From MAOCY
// 2010-05-02 (^o^)
//============================================================

#include "Mo3dsDefine.h"
#include "Mo3dsExport.h"

MO_NAMESPACE_INCLUDE;

//============================================================
// <T>���ض�̬�⡣</T>
//
// @param hInstance ʵ���ӱ�
// @param reason ����ԭ��
// @param pReserved ����
// @return ����
//============================================================
TBool WINAPI DllMain(TInstance hInstance, TUint32 reason, TAny* pReserved){
   switch(reason){
      // ���̿�ʼ����
      case DLL_PROCESS_ATTACH:{
         DisableThreadLibraryCalls(hInstance);
         MoInitialize();
         break;
      }
      // �߳̿�ʼ����
      case DLL_THREAD_ATTACH:
         break;
      // �߳̽�������
      case DLL_THREAD_DETACH:
         break;
      // ���̽�������
      case DLL_PROCESS_DETACH:{
         MoRelease();
         break;
      }
   }
   return ETrue;
}

//============================================================
// <T>��ÿ�������</T>
//
// @return ����
//============================================================
MO_3E_DECLARE TCharC* LibDescription(){
   return MO_3E_LIB_DESCRIPTION;
}

//============================================================
// <T>�������������������</T>
//
// @return ����
//============================================================
MO_3E_DECLARE TInt LibNumberClasses(){
   return 1;
}

//============================================================
// <T>���ָ������������������</T>
//
// @return ��������
//============================================================
MO_3E_DECLARE ClassDesc* LibClassDesc(TInt index){
   switch(index){
   case 0:
      return &g_classDesc; 
   }
   return NULL;
}

//============================================================
// <T>��ÿ�İ汾��</T>
//
// @return �汾
//============================================================
MO_EXPORT TUint32 LibVersion(){
   return VERSION_3DSMAX;
}

//============================================================
// <T>����Ƿ�����Զ��ӳ١�</T>
//
// @return �Զ��ӳ�
//============================================================
MO_EXPORT TUint32 CanAutoDefer(){
   return ETrue;
}
