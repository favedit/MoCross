#include "MoEfContainer.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>����ҳ�ؼ���</T>
//============================================================
FUiPage::FUiPage(){
   _controlCd = EControlType_Page;
   _optionDefault = EFalse;
}

//============================================================
// <T>����ҳ�ؼ���</T>
//============================================================
FUiPage::~FUiPage(){
}

//============================================================
// <T>�������������л��������ݡ�</T>
//
// @param pInput ������
// @return ������
//============================================================
TResult FUiPage::OnUnserialize(IDataInput* pInput){
   // ����Ϣ�����л�
   TResult result = FUiControlContainer::OnUnserialize(pInput);
   // ��ȡ����
   _optionDefault = pInput->ReadBool();
   return result;
}

MO_NAMESPACE_END
