#include "MoFmContainer.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>�����ҳ�ؼ���</T>
//============================================================
FUiPageControl::FUiPageControl(){
   _controlCd = EControlType_PageControl;
   MO_CLEAR(_pActivePage);
}

//============================================================
// <T>������ҳ�ؼ���</T>
//============================================================
FUiPageControl::~FUiPageControl(){
}

//============================================================
// <T>���ú��ô���</T>
//
// @return ������
//============================================================
TResult FUiPageControl::OnSetupAfter(){
   // �����ú��ô���
   TResult result = FUiControlContainer::OnSetupAfter();
   // �ӽڵ㼯�ϴ���
   //TInt count = ChildCount();
   //for(TInt n = 0; n < count; n++){
   //   FUiPage* pPage = (FUiPage*)ControlGet(n, EControlType_Page);
   //   if(pPage != NULL){
   //      // Ĭ�������׸�ҳ��Ϊ����ҳ��
   //      if(_pActivePage == NULL){
   //         _pActivePage = pPage;
   //         continue;
   //      }
   //      // �����õ�ʱ��������Ĭ��Ϊ׼
   //      if(pPage->OptionDefault()){
   //         _pActivePage = pPage;
   //         break;
   //      }
   //   }
   //}
   // ѡ��ҳ��
   OnSelectPage(_pActivePage);
   return result;
}

//============================================================
// <T>�������������л��������ݡ�</T>
//
// @param pInput ������
// @return ������
//============================================================
TResult FUiPageControl::OnUnserialize(IDataInput* pInput){
   // ����Ϣ�����л�
   TResult result = FUiControlContainer::OnUnserialize(pInput);
   return result;
}

//============================================================
// <T>������Դ���</T>
//
// @param pTester ������Ϣ
// @return ������
//============================================================
TResult FUiPageControl::OnFocusTest(FFocusTester* pTester){
   SIntRectangle rectangle;
   CalculateRectangle(&rectangle);
   SIntPoint2& location = pTester->Location();
   if(rectangle.TestInRange(location.x, location.y)){
      pTester->SetStatusInRange(ETrue);
      pTester->SetStatusChildren(ETrue);
   }
   return ESuccess;
}

//============================================================
// <T>ѡ��ҳ�洦��</T>
//
// @param pPage ҳ��
// @return ������
//============================================================
TResult FUiPageControl::OnSelectPage(FUiPage* pPage){
   // ��������ҳ��
   //TInt count = ChildCount();
   //for(TInt n = 0; n < count; n++){
   //   FUiPage* pFindPage = (FUiPage*)ControlGet(n, EControlType_Page);
   //   if(pFindPage != NULL){
   //      pFindPage->SetVisible(pFindPage == pPage);
   //   }
   //}
   // ���ü���ҳ��
   _pActivePage = pPage;
   return ESuccess;
}

//============================================================
// <T>ѡ��ҳ�洦��</T>
//
// @param pPage ҳ��
// @return ������
//============================================================
TResult FUiPageControl::SelectPage(FUiPage* pPage){
   TResult result = ESuccess;
   if(_pActivePage != pPage){
      result = OnSelectPage(pPage);
   }
   return result;
}

MO_NAMESPACE_END
