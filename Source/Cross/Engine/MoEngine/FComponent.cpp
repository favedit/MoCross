#include "MoEgDevice.h"
#include "MoEgDisplay.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FComponent, FInstance);

//============================================================
// <T>�����������</T>
//============================================================
FComponent::FComponent(){
   _optionFlag = 0;
   _statusFlag = 0;
   MO_CLEAR(_pParent);
   _lastUpdate = 0;
}

//============================================================
// <T>�����������</T>
//============================================================
FComponent::~FComponent(){
}

//============================================================
// <T>�����������</T>
//
// @return �������
//============================================================
FComponent* FComponent::TopComponent(){
   FComponent* pComponent = this;
   while(pComponent != NULL){
      FComponent* pParent = pComponent->Parent();
      if(pParent == NULL){
         break;
      }
      pComponent = pParent;
   }
   return pComponent;
}

//============================================================
// <T>���촦��</T>
//
// @return ������
//============================================================
TResult FComponent::OnConstruct(){
   return ESuccess;
}

//============================================================
// <T>���л��������ݵ��������</T>
//
// @param pOutput �����
// @return ������
//============================================================
TResult FComponent::OnSerialize(IDataOutput* pOutput){
   return ESuccess;
}

//============================================================
// <T>�������������л��������ݡ�</T>
//
// @param pInput ������
// @return ������
//============================================================
TResult FComponent::OnUnserialize(IDataInput* pInput){
   return ESuccess;
}

//============================================================
// <T>����ǰ�ô���</T>
//
// @return ������
//============================================================
TResult FComponent::OnSetupBefore(){
   return ESuccess;
}

//============================================================
// <T>���ú��ô���</T>
//
// @return ������
//============================================================
TResult FComponent::OnSetupAfter(){
   return ESuccess;
}

//============================================================
// <T>�ͷŴ���</T>
//
// @return ������
//============================================================
TResult FComponent::OnDispose(){
   return ESuccess;
}

//============================================================
// <T>���촦��</T>
//
// @return ������
//============================================================
TResult FComponent::Construct(){
   // ���״̬
   if(!IsStatus(EComponentStatus_Construct)){
      // ���촦��
      OnConstruct();
      // ����״̬
      SetStatus(EComponentStatus_Construct, ETrue);
   }
   return ESuccess;
}

//============================================================
// <T>���л��������ݵ��������</T>
//
// @param pOutput �����
//============================================================
TResult FComponent::Serialize(IDataOutput* pOutput){
   TResult resultCd = OnSerialize(pOutput);
   return resultCd;
}

//============================================================
// <T>�������������л��������ݡ�</T>
//
// @param pInput ������
//============================================================
TResult FComponent::Unserialize(IDataInput* pInput){
   TResult resultCd = OnUnserialize(pInput);
   return resultCd;
}

//============================================================
// <T>���ô���</T>
//
// @return ������
//============================================================
TResult FComponent::Setup(){
   // ���״̬
   if(!IsStatus(EComponentStatus_Setup)){
      // ����ǰ�ô���
      OnSetupBefore();
      // ���ú��ô���
      OnSetupAfter();
      // ����״̬
      SetStatus(EComponentStatus_Setup, ETrue);
   }
   return ESuccess;
}

//============================================================
// <T>���´���</T>
// <P>ֻҪ����̨�ڶ���ȫ�����봦�������Ƿ���Ч���Ƿ���ʾ��</P>
//
// @param pContext ������
// @return ������
//============================================================
TResult FComponent::Update(SProcessContext* pContext){
   MO_CHECK(pContext, return ENull);
   _lastUpdate = pContext->currentTick;
   return ESuccess;
}

//============================================================
// <T>����ǰ�ô���</T>
//
// @param pContext ������
// @return ������
//============================================================
TResult FComponent::ProcessBefore(SProcessContext* pContext){
   return ESuccess;
}

//============================================================
// <T>���ܺ��ô���</T>
//
// @param pContext ������
// @return ������
//============================================================
TResult FComponent::ProcessAfter(SProcessContext* pContext){
   return ESuccess;
}

//============================================================
// <T>�ͷŴ���</T>
//
// @return ������
//============================================================
TResult FComponent::Dispose(){
   TResult resultCd = OnDispose();
   return resultCd;
}

MO_NAMESPACE_END
