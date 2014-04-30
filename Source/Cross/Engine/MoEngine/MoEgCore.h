#ifndef __MO_EG_CORE_H__
#define __MO_EG_CORE_H__
//************************************************************

#ifndef __MO_EG_PROCESSOR_H__
#include "MoEgProcessor.h"
#endif // __MO_EG_PROCESSOR_H__

MO_NAMESPACE_BEGIN

//============================================================
// <T>����ӿڡ�</T>
//============================================================
class MO_EG_DECLARE ICanvas{
public:
   //------------------------------------------------------------
   // <T>��������ӿڡ�</T>
   MO_ABSTRACT ~ICanvas(){
   }
public:
   MO_VIRTUAL TResult Update() = 0;
};

//============================================================
// <T>�ɻ�����ӿڡ�</T>
//============================================================
class MO_EG_DECLARE IMouseable{
public:
   //------------------------------------------------------------
   // <T>�����ɻ�����ӿڡ�</T>
   MO_ABSTRACT ~IMouseable(){
   }
public:
   MO_VIRTUAL TResult MouseDown(SMouseEvent* pEvent) = 0;
   MO_VIRTUAL TResult MouseMove(SMouseEvent* pEvent) = 0;
   MO_VIRTUAL TResult MouseUp(SMouseEvent* pEvent) = 0;
};

//============================================================
// <T>�ɻ�ý���ӿڡ�</T>
//============================================================
class MO_EG_DECLARE IFocusable{
public:
   //------------------------------------------------------------
   // <T>�����ɻ�ý���ӿڡ�</T>
   MO_ABSTRACT ~IFocusable(){
   }
public:
   MO_VIRTUAL TResult FocusEnter() = 0;
   MO_VIRTUAL TResult FocusLeave() = 0;
};

//============================================================
// <T>�ɻ���ȵ�ӿڡ�</T>
//============================================================
class MO_EG_DECLARE IHoverable{
public:
   //------------------------------------------------------------
   // <T>�����ɻ���ȵ�ӿڡ�</T>
   MO_ABSTRACT ~IHoverable(){
   }
public:
   MO_VIRTUAL TResult HoverEnter() = 0;
   MO_VIRTUAL TResult HoverLeave() = 0;
};

//============================================================
// <T>����ק�ӿڡ�</T>
//============================================================
class MO_EG_DECLARE IDragable{
public:
   //------------------------------------------------------------
   // <T>��������ק�ӿڡ�</T>
   MO_ABSTRACT ~IDragable(){
   }
public:
   MO_VIRTUAL TResult DragBegin() = 0;
   MO_VIRTUAL TResult DragMove() = 0;
   MO_VIRTUAL TResult DragEnd() = 0;
};

//============================================================
// <T>��ʾ�����������͡�</T>
//============================================================
enum EMovieAction{
   EMovieAction_Play,
   EMovieAction_Visible,
   EMovieAction_Dispose,
};

//============================================================
// <T>��ʾ�������</T>
//============================================================
struct MO_EG_DECLARE SMovieAction{
public:
   // ��������
   EMovieAction actionCd;
   // �ɼ���
   TBool visible;
   // ����
   TInt directionCd;
   // ѭ������
   TInt loop;
   // ����
   TFloat rate;
public:
   //------------------------------------------------------------
   // <T>������ʾ�������</T>
   SMovieAction(){
   }
};
//------------------------------------------------------------
typedef MO_EG_DECLARE TList<SMovieAction> TMovieActionList;

MO_NAMESPACE_END
      
//************************************************************
#endif // __MO_EG_CORE_H__
