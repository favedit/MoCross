#include "MoEgDevice.h"
#include "MoEgFocus.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>���콹�����̨��</T>
//============================================================
FFocusConsole::FFocusConsole(){
   MO_CLEAR(_pHoverDrawable);
   MO_CLEAR(_pFocusDrawable);
   MO_CLEAR(_pDragDrawable);
   _pFocusDrawables = MO_CREATE(FDrawableCollection);
   _pTester = MO_CREATE(FFocusTester);
}

//============================================================
// <T>�����������̨��</T>
//============================================================
FFocusConsole::~FFocusConsole(){
   MO_DELETE(_pFocusDrawables);
   MO_DELETE(_pTester);
}

//============================================================
// <T>����λ�ò��Դ���</T>
//
// @param x ������
// @param y ������
// @return ������
//============================================================
FFocusTester* FFocusConsole::TestPosition(TInt x, TInt y){
   // ������
   FStage* pStage = RStageManager::Instance().ActiveStage();
   if(pStage == NULL){
      return NULL;
   }
   // ��������
   _pTester->Clear();
   _pTester->Location().Set(x, y);
   //pStage->FocusTest(_pTester);
   return _pTester;
}

//============================================================
// <T>������´���</T>
//
// @param pEvent �¼�����
// @return ������
//============================================================
TResult FFocusConsole::OnMouseDown(SMouseEvent* pEvent){
   // ��⽹����Ϣ
   TInt x = pEvent->position.x;
   TInt y = pEvent->position.y;
   FFocusTester* pTester = FFocusConsole::TestPosition(x, y);
   if(pTester == NULL){
      return ESuccess;
   }
   //............................................................
   // ��������
   _startLocation.Set(x, y);
   //............................................................
   // ��������¼�
   FDrawable* pDrawable = pTester->ActiveDrawable();
   if(pDrawable != NULL){
      //IMouseable* pMouseable = (IMouseable*)pDrawable->Convert(EComponent_Mouseable);
      //if(pMouseable != NULL){
      //   pMouseable->MouseDown(pEvent);
      //}
   }
   return ESuccess;
}

//============================================================
// <T>����ƶ�����</T>
//
// @param pEvent �¼�����
// @return ������
//============================================================
TResult FFocusConsole::OnMouseMove(SMouseEvent* pEvent){
   // ��⽹����Ϣ
   TInt x = pEvent->position.x;
   TInt y = pEvent->position.y;
   FFocusTester* pTester = FFocusConsole::TestPosition(x, y);
   if(pTester == NULL){
      return ESuccess;
   }
   //............................................................
   // ��������¼�
   FDrawable* pDrawable = pTester->ActiveDrawable();
   if(pDrawable != NULL){
      //IMouseable* pMouseable = (IMouseable*)pDrawable->Convert(EComponent_Mouseable);
      //if(pMouseable != NULL){
      //   pMouseable->MouseMove(pEvent);
      //}
   }
   // �ȵ�ѡ����
   HoverDrawable(pDrawable);
   //............................................................
   // ��ק����
   if(_pDragDrawable != NULL){
      TInt cx = x - _startLocation.x;
      TInt cy = y - _startLocation.y;
      _pDragDrawable->Location().x = (TFloat)(_dragDrawableLocation.x + cx);
      _pDragDrawable->Location().y = (TFloat)(_dragDrawableLocation.y + cy);
   }
   return ESuccess;
}

//============================================================
// <T>���̧����</T>
//
// @param pEvent �¼�����
// @return ������
//============================================================
TResult FFocusConsole::OnMouseUp(SMouseEvent* pEvent){
   // ��⽹����Ϣ
   TInt x = pEvent->position.x;
   TInt y = pEvent->position.y;
   FFocusTester* pTester = FFocusConsole::TestPosition(x, y);
   if(pTester == NULL){
      return ESuccess;
   }
   //............................................................
   // ���̧���¼�
   FDrawable* pDrawable = pTester->ActiveDrawable();
   if(pDrawable != NULL){
      //IMouseable* pMouseable = (IMouseable*)pDrawable->Convert(EComponent_Mouseable);
      //if(pMouseable != NULL){
      //   pMouseable->MouseUp(pEvent);
      //}
   }
   //............................................................
   // ֹͣ��ק����
   MO_CLEAR(_pDragDrawable);
   return ESuccess;
}

//============================================================
// <T>���ô���</T>
//
// @return ������
//============================================================
TResult FFocusConsole::Setup(){
   FMouseDevice* pMouseDevice = RDeviceManager::Instance().Find<FMouseDevice>();
   pMouseDevice->ListenersMouseDown().Register<FFocusConsole>(this, &FFocusConsole::OnMouseDown);
   pMouseDevice->ListenersMouseMove().Register<FFocusConsole>(this, &FFocusConsole::OnMouseMove);
   pMouseDevice->ListenersMouseUp().Register<FFocusConsole>(this, &FFocusConsole::OnMouseUp);
   return ESuccess;
}

//============================================================
// <T>һ���ɻ��ƶ������ȵ㡣</T>
//
// @return ������
//============================================================
TResult FFocusConsole::HoverDrawable(FDrawable* pDrawable){
   // ���ı�
   if(_pHoverDrawable == pDrawable){
      return ESuccess;
   }
   // ȡ���ϸ��ȵ���󼤻�
   if(_pHoverDrawable != NULL){
      //IHoverable* pHoverable = (IHoverable*)_pHoverDrawable->Convert(EComponent_Hoverable);
      //if(pHoverable != NULL){
      //   pHoverable->HoverLeave();
      //}
      //_pHoverDrawable = NULL;
   }
   // ���ǰ�ȵ����
   if(pDrawable != NULL){
      //IHoverable* pHoverable = (IHoverable*)pDrawable->Convert(EComponent_Hoverable);
      //if(pHoverable != NULL){
      //   pHoverable->HoverEnter();
      //   _pHoverDrawable = pDrawable;
      //}
   }
   return ESuccess;
}

//============================================================
// <T>һ���ɻ��ƶ����ý��㡣</T>
//
// @return ������
//============================================================
TResult FFocusConsole::FocusDrawable(FDrawable* pDrawable){
   MO_CHECK(pDrawable, return ENull);
   return ESuccess;
}

//============================================================
TResult FFocusConsole::DragDrawable(FDrawable* pDrawable, TInt x, TInt y){
   MO_CHECK(pDrawable, return ENull);
   if(_pDragDrawable == pDrawable){
      return EContinue;
   }
   _pDragDrawable = pDrawable;
   _dragLocation.Set(x, y);
   _dragDrawableLocation.Set((TInt)_pDragDrawable->Location().x, (TInt)_pDragDrawable->Location().y);
   return ESuccess;
}

//============================================================
// <T>�߼�����</T>
//
// @return ������
//============================================================
TResult FFocusConsole::Process(EMouseButton buttonCd, TInt x, TInt y){
   return ESuccess;
}

MO_NAMESPACE_END
