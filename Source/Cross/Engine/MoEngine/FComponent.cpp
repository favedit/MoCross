#include "MoEgDevice.h"
#include "MoEgDisplay.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FComponent, FInstance);

//============================================================
// <T>�����������</T>
//============================================================
FComponent::FComponent(){
   _optionValid = ETrue;
   _objectCd = EComponent_Object | EComponent_Component;
   _flagCd = 0;
   MO_CLEAR(_pParent);
   //MO_CLEAR(_pChildren);
   MO_CLEAR(_pProperties);
   _statusConstruct = EFalse;
   _statusSetup = EFalse;
   _statusReady = EFalse;
   _lastUpdate = 0;
}

//============================================================
// <T>�����������</T>
//============================================================
FComponent::~FComponent(){
   //MO_DELETE(_pChildren);
   MO_DELETE(_pProperties);
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

////============================================================
//// <T>�Ӹ��������Ƴ��Լ���</T>
////
//// @return ������
////============================================================
//TResult FComponent::RemoveFromParent(){
//   if(_pParent != NULL){
//      _pParent->ChildRemove(this);
//      _pParent = NULL;
//   }
//   return ESuccess;
//}
//
////============================================================
//// <T>�������Ʋ����ӽڵ㡣</T>
////
//// @param pName ����
//// @return �ӽڵ�
////============================================================
//FComponent* FComponent::ChildGet(TCharC* pName){
//   FComponent* pComponent = ChildFind(pName);
//   MO_FATAL_CHECK(pComponent, return NULL,
//         "Child is not exists. (name=%s)", pName);
//   return pComponent;
//}
//
////============================================================
//// <T>�������Ʋ����ӽڵ㡣</T>
////
//// @param pName ����
//// @return �ӽڵ�
////============================================================
//FComponent* FComponent::ChildFind(TCharC* pName){
//   MO_CHECK(pName, return NULL);
//   // ���������ӽڵ�
//   TInt count = ChildCount();
//   for(TInt n = 0; n < count; n++){
//      FComponent* pComponent = _pChildren->Get(n);
//      if(pComponent->IsName(pName)){
//         return pComponent;
//      }
//   }
//   return NULL;
//}
//
////============================================================
//// <T>�������������ӽڵ㡣</T>
////
//// @param pName ����
//// @return �ӽڵ�
////============================================================
//FComponent* FComponent::ChildSearch(TCharC* pName){
//   MO_CHECK(pName, return NULL);
//   // ���������ӽڵ�
//   TInt count = ChildCount();
//   for(TInt n = 0; n < count; n++){
//      FComponent* pComponent = _pChildren->Get(n);
//      // �ж���ǰ�ڵ�
//      if(pComponent->IsName(pName)){
//         return pComponent;
//      }
//      // �����ӽڵ�
//      FComponent* pSearchComponent = pComponent->ChildSearch(pName);
//      if(pSearchComponent != NULL){
//         return pSearchComponent;
//      }
//   }
//   return NULL;
//}
//
////============================================================
//// <T>����һ���������</T>
////
//// @param pComponent �����
//// @return ������
////============================================================
//TResult FComponent::ChildPush(FComponent* pComponent){
//   MO_ASSERT(pComponent);
//   // ��������Ϊ���򴴽�
//   FComponentCollection* pChildren = Children();
//   // ����Ƿ��Ѿ�����
//   if(pChildren->Contains(pComponent)){
//      // ��鸸����Ƿ�Ϊ�Լ�
//      FComponent* pParent = pComponent->Parent();
//      if(pParent != NULL){
//         MO_DEBUG_WARN("Child has already, but parent is null. (component=0x%08X)", pComponent);
//      }else if(pParent != this){
//         MO_DEBUG_WARN("Child has already, but parent is not this. (component=0x%08X, parent=0x%08X)", pComponent, pParent);
//      }else{
//         MO_DEBUG_WARN("Child has already. (component=0x%08X)", pComponent);
//      }
//      return EFailure;
//   }
//   // �Ӹ����������
//   pComponent->RemoveFromParent();
//   pComponent->SetParent(this);
//   // �������������
//   pChildren->Push(pComponent);
//   return ESuccess;
//}
//
////============================================================
//// <T>����һ���������</T>
////
//// @param pComponent �����
//// @return ������
////============================================================
//TResult FComponent::ChildPushDirect(FComponent* pComponent){
//   MO_ASSERT(pComponent);
//   pComponent->SetParent(this);
//   FComponentCollection* pChildren = Children();
//   pChildren->Push(pComponent);
//   return ESuccess;
//}
//
////============================================================
//// <T>�Ƴ�һ���������</T>
////
//// @param pComponent �����
//// @return ������
////============================================================
//TResult FComponent::ChildRemove(FComponent* pComponent){
//   MO_ASSERT(pComponent);
//   if(_pChildren == NULL){
//      MO_DEBUG_WARN("Children is empty, can't remove any child. (component=0x%08X)", pComponent);
//      return EFailure;
//   }
//#ifdef _MO_DEBUG
//   if(!_pChildren->Contains(pComponent)){
//      MO_DEBUG_WARN("Children not contains this child. (component=0x%08X)", pComponent);
//      return EFailure;
//   }
//#endif // _MO_DEBUG
//   _pChildren->Remove(pComponent);
//   return ESuccess;
//}
//
////============================================================
//// <T>���������������λ�á�</T>
////
//// @param pSource ��Դ�����
//// @param pTarget Ŀ�������
//// @return ������
////============================================================
//TResult FComponent::ChildSwap(FComponent* pSource, FComponent* pTarget){
//   return ESuccess;
//}
//
////============================================================
//// <T>����ӽڵ㡣</T>
////
//// @return ������
////============================================================
//TResult FComponent::ChildClear(){
//   if(_pChildren != NULL){
//      _pChildren->Clear();
//   }
//   return ESuccess;
//}

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
   // ��鹹���
   if(_statusConstruct){
      return ESuccess;
   }
   // ���촦��
   OnConstruct();
   // �������������
   //TInt childCount = ChildCount();
   //for(TInt n = 0; n < childCount; n++){
   //   FComponent* pComponent = _pChildren->Get(n);
   //   pComponent->Construct();
   //}
   _statusConstruct = ETrue;
   return ESuccess;
}

//============================================================
// <T>���л��������ݵ��������</T>
//
// @param pOutput �����
//============================================================
TResult FComponent::Serialize(IDataOutput* pOutput){
   // ���л�����
   OnSerialize(pOutput);
   // ���л������
   //TInt childCount = ChildCount();
   //pOutput->WriteInt16(childCount);
   //for(TInt n = 0; n < childCount; n++){
   //   FComponent* pComponent = _pChildren->Get(n);
   //   pComponent->Serialize(pOutput);
   //}
   return ESuccess;
}

//============================================================
// <T>�������������л��������ݡ�</T>
//
// @param pInput ������
//============================================================
TResult FComponent::Unserialize(IDataInput* pInput){
   // ���л�����
   OnUnserialize(pInput);
   // ���л������
   TInt childCount = pInput->ReadInt16();
   for(TInt n = 0; n < childCount; n++){
      TInt componentCd = pInput->ReadInt8();
      // TODO: ��ʱ����
      FComponent* pComponent = MO_CREATE(FComponent);
      pComponent->Unserialize(pInput);
   }
   return ESuccess;
}

//============================================================
// <T>���ô���</T>
//
// @return ������
//============================================================
TResult FComponent::Setup(){
   // ������ù�
   if(_statusSetup){
      return ESuccess;
   }
   // ����ǰ�ô���
   OnSetupBefore();
   // �������������
   //TInt childCount = ChildCount();
   //for(TInt n = 0; n < childCount; n++){
   //   FComponent* pComponent = _pChildren->Get(n);
   //   pComponent->Setup();
   //}
   // ���ú��ô���
   OnSetupAfter();
   _statusSetup = ETrue;
   return ESuccess;
}

//============================================================
// <T>���´���</T>
//
// @return ������
//============================================================
TResult FComponent::Update(){
   FTimerDevice* pTimerDevice = RDeviceManager::Instance().Find<FTimerDevice>();
   _lastUpdate = pTimerDevice->CurrentTick();
   return ESuccess;
}

//============================================================
// <T>����ǰ�ô���</T>
//
// @return ������
//============================================================
TResult FComponent::ProcessBefore(SProcessContext* pContext){
   // �߼����������
   //TInt childCount = ChildCount();
   //for(TInt n = 0; n < childCount; n++){
   //   FComponent* pComponent = _pChildren->Get(n);
   //   pComponent->Process();
   //}
   return ESuccess;
}

//============================================================
// <T>���ܺ��ô���</T>
//
// @return ������
//============================================================
TResult FComponent::ProcessAfter(SProcessContext* pContext){
   // �߼����������
   //TInt childCount = ChildCount();
   //for(TInt n = 0; n < childCount; n++){
   //   FComponent* pComponent = _pChildren->Get(n);
   //   pComponent->Process();
   //}
   return ESuccess;
}

//============================================================
// <T>�ͷŴ���</T>
//
// @return ������
//============================================================
TResult FComponent::Dispose(){
   // �ͷ����������
   //TInt childCount = ChildCount();
   //for(TInt n = 0; n < childCount; n++){
   //   FComponent* pComponent = _pChildren->Get(n);
   //   pComponent->Dispose();
   //}
   // �ͷŴ���
   return OnDispose();
}

MO_NAMESPACE_END
