//============================================================
//   DYNAMIC LINK LIBRARY : Mo3DSExporter Project Overview
//------------------------------------------------------------
// ��3DS MAX�е���ģ�͵Ķ�̬���ӿ⡣
//------------------------------------------------------------
// Copyright From MAOCY
// 2010-05-02 (^o^)
//============================================================

#include <MoCommon.h>
#include "Mo3dsDefine.h"
#include "Mo3dsExporter.h"

MO_NAMESPACE_INCLUDE;

//============================================================
// <T>���ض�̬�⡣</T>
//
// @param hInstance ʵ�����
// @param reason ��������
// @param pReserved ������
// @return ����
//============================================================
TBool APIENTRY DllMain(HMODULE hModule, TUint32 reason, TAny* pReserved){
	switch (reason){
      case DLL_PROCESS_ATTACH:
	   case DLL_THREAD_ATTACH:
	   case DLL_THREAD_DETACH:
      case DLL_PROCESS_DETACH:
         break;
	}
	return ETrue;
}

//============================================================
// <T>����ģ�ͼ��ض�̬�⡣</T>
//
// @param hInstance ʵ���ӱ�
// @param reason ����ԭ��
// @param pReserved ����
// @return ����
//============================================================
MO_EXPORT TInt __DoExport(TCharC* pFileName, ExpInterface* piExpInterface, Interface* piInterface, TBool suppressPrompts, TUint32 options){
   MO_STATIC_INFO(TC("Export 3DS scene xml. (filename=%s)"), pFileName);
   // �������нڵ�
   M3dsExporter* pExporter = MO_CREATE(F3dsGameExporter, piExpInterface->theScene, piInterface->GetTime(), piInterface);
   try{
      pExporter->SetFileName(pFileName);
      pExporter->Convert();
      pExporter->SaveAs(pFileName, TC("GB2312"));
   }catch(TInt error){
      MO_STATIC_INFO(TC("Convert scene failure. (error=%d)"), error);
      MO_DELETE(pExporter);
      return IMPEXP_FAIL;
   }
   MO_DELETE(pExporter);
   return IMPEXP_SUCCESS;
}

//============================================================
// <T>���ض�̬�⡣</T>
//
// @param hInstance ʵ���ӱ�
// @param reason ����ԭ��
// @param pReserved ����
// @return ����
//============================================================
MO_EXPORT TInt DoExport(TCharC *pFileName, ExpInterface* piExpInterface, Interface* piInterface, TBool suppressPrompts, TUint32 options){
   TInt result = IMPEXP_SUCCESS;
   MO_STATIC_INFO(TC("Export scene start."));
   try{
      result = __DoExport(pFileName, piExpInterface, piInterface, suppressPrompts, options);
   }catch(TInt error){
      MO_STATIC_INFO(TC("Export scene failure. (filename=%s, error=%d)"), pFileName, error);
      result = IMPEXP_FAIL;
   }
   MO_STATIC_INFO(TC("Export scene success."));
   return result;
}
