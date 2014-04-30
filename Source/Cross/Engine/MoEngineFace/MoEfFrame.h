#ifndef __MO_EF_FRAME_H__
#define __MO_EF_FRAME_H__
//************************************************************

#ifndef __MO_EF_COMMON_H__
#include "MoEfCommon.h"
#endif // __MO_EF_COMMON_H__

#ifndef __MO_EF_CORE_H__
#include "MoEfCore.h"
#endif // __MO_EF_CORE_H__

MO_NAMESPACE_BEGIN

//============================================================
// <T>����ͣ������</T>
//============================================================
class MO_EF_DECLARE FUiBar : public FUiFrame{
public:
   FUiBar();
   MO_ABSTRACT ~FUiBar();
};
//------------------------------------------------------------
MO_DEF_CONTROL_POOL(MO_EF_DECLARE, FUiBarPool, FUiBar, EControlType_Bar, NULL);

//============================================================
// <T>�������</T>
//============================================================
class MO_EF_DECLARE FUiForm : public FUiFrame{
public:
   FUiForm();
   MO_ABSTRACT ~FUiForm();
};
//------------------------------------------------------------
MO_DEF_CONTROL_POOL(MO_EF_DECLARE, FUiFormPool, FUiForm, EControlType_Form, NULL);

//============================================================
// <T>���㴰�ڡ�</T>
//============================================================
class MO_EF_DECLARE FUiWindow :
      public FUiFrame,
      public IMouseable,
      public IDragable{
protected:
   TInt _titleHeight;
public:
   FUiWindow();
   MO_ABSTRACT ~FUiWindow();
public:
   MO_OVERRIDE TResult OnPaint();
public:
   MO_OVERRIDE TResult PaintTitle(FUiCanvas* pCanvas, SIntRectangle* pRectangle);
   MO_OVERRIDE TResult PaintBody(FUiCanvas* pCanvas, SIntRectangle* pRectangle);
public:
   MO_OVERRIDE TResult MouseDown(SMouseEvent* pEvent);
   MO_OVERRIDE TResult MouseMove(SMouseEvent* pEvent);
   MO_OVERRIDE TResult MouseUp(SMouseEvent* pEvent);
public:
   MO_OVERRIDE TResult DragBegin();
   MO_OVERRIDE TResult DragMove();
   MO_OVERRIDE TResult DragEnd();
};
//------------------------------------------------------------
MO_DEF_CONTROL_POOL(MO_EF_DECLARE, FUiWindowPool, FUiWindow, EControlType_Window, NULL);

MO_NAMESPACE_END

//************************************************************
#endif // __MO_EF_FRAME_H__
