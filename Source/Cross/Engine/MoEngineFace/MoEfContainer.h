#ifndef __MO_EF_CONTAINER_H__
#define __MO_EF_CONTAINER_H__
//************************************************************

#ifndef __MO_EF_COMMON_H__
#include "MoEfCommon.h"
#endif // __MO_EF_COMMON_H__

#ifndef __MO_EF_CORE_H__
#include "MoEfCore.h"
#endif // __MO_EF_CORE_H__

MO_NAMESPACE_BEGIN

//============================================================
// <T>���ֿؼ���</T>
//============================================================
class MO_EF_DECLARE FUiPanel : public FUiControlContainer{
protected:
public:
   FUiPanel();
   MO_ABSTRACT ~FUiPanel();
};
//------------------------------------------------------------
MO_DEF_CONTROL_POOL(MO_EF_DECLARE, FUiPanelPool, FUiPanel, EControlType_Panel, NULL);

//============================================================
// <T>ҳ�ؼ���</T>
//============================================================
class MO_EF_DECLARE FUiPage : public FUiControlContainer{
protected:
   TBool _optionDefault;
public:
   FUiPage();
   MO_ABSTRACT ~FUiPage();
public:
   //------------------------------------------------------------
   // <T>�������Ĭ�ϡ�</T>
   MO_INLINE TBool OptionDefault(){
      return _optionDefault;
   }
   //------------------------------------------------------------
   // <T>��������Ĭ�ϡ�</T>
   MO_INLINE void SetOptionDefault(TBool optionDefault){
      _optionDefault = optionDefault;
   }
public:
   MO_OVERRIDE TResult OnUnserialize(IDataInput* pInput);
};
//------------------------------------------------------------
MO_DEF_CONTROL_POOL(MO_EF_DECLARE, FUiPagePool, FUiPage, EControlType_Page, NULL);

//============================================================
// <T>��ҳ�ؼ���</T>
//============================================================
class MO_EF_DECLARE FUiPageControl : public FUiControlContainer{
protected:
   FUiPage* _pActivePage;
public:
   FUiPageControl();
   MO_ABSTRACT ~FUiPageControl();
public:
   //------------------------------------------------------------
   // <T>��ü����ҳ�档</T>
   MO_INLINE FUiPage* ActivePage(){
      return _pActivePage;
   }
public:
   MO_OVERRIDE TResult OnSetupAfter();
   MO_OVERRIDE TResult OnUnserialize(IDataInput* pInput);
   MO_OVERRIDE TResult OnFocusTest(FFocusTester* pTester);
   MO_ABSTRACT TResult OnSelectPage(FUiPage* pPage);
public:
   TResult SelectPage(FUiPage* pPage);
};
//------------------------------------------------------------
MO_DEF_CONTROL_POOL(MO_EF_DECLARE, FUiPageControlPool, FUiPageControl, EControlType_PageControl, NULL);

MO_NAMESPACE_END

//************************************************************
#endif // __MO_EF_CONTAINER_H__
