#include "MoEgDisplay.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>����ռ��塣</T>
//============================================================
FSpatial::FSpatial(){
   _objectCd |= EComponent_Spatial;
   MO_CLEAR(_pDisplays);
}

//============================================================
// <T>�����ռ��塣</T>
//============================================================
FSpatial::~FSpatial(){
   MO_DELETE(_pDisplays);
}

//============================================================
// <T>����һ������ʾ����</T>
//
// @param pDisplay ����ʾ����
// @return ������
//============================================================
TResult FSpatial::DisplayPush(FDisplay* pDisplay){
   MO_ASSERT(pDisplay);
   // �����ʾ����
   if(_pDisplays == NULL){
      _pDisplays = MO_CREATE(FDisplayCollection);
   }
   // ����Ƿ��Ѿ�����
   if(_pDisplays->Contains(pDisplay)){
      // ��鸸����Ƿ�Ϊ�Լ�
      FComponent* pParent = pDisplay->Parent();
      if(pParent != NULL){
         MO_DEBUG_WARN("Child has already, but parent is null. (display=0x%08X)", pDisplay);
      }else if(pParent != this){
         MO_DEBUG_WARN("Child has already, but parent is not this. (display=0x%08X, parent=0x%08X)", pDisplay, pParent);
      }else{
         MO_DEBUG_WARN("Child has already. (display=0x%08X)", pDisplay);
      }
      return EFailure;
   }
   // �Ӹ����������
   // pDisplay->RemoveFromParent();
   // �������������
   pDisplay->SetParent(this);
   _pDisplays->Push(pDisplay);
   return ESuccess;
}

//============================================================
// <T>�Ƴ�һ������ʾ����</T>
//
// @param pDisplay ����ʾ����
// @return ������
//============================================================
TResult FSpatial::DisplayRemove(FDisplay* pDisplay){
   MO_ASSERT(pDisplay);
   if(_pDisplays == NULL){
      MO_DEBUG_WARN("Children is empty, can't remove any child. (display=0x%08X)", pDisplay);
      return EFailure;
   }
#ifdef _MO_DEBUG
   if(!_pDisplays->Contains(pDisplay)){
      MO_DEBUG_WARN("Children not contains this child. (display=0x%08X)", pDisplay);
      return EFailure;
   }
#endif // _MO_DEBUG
   _pDisplays->Remove(pDisplay);
   return ESuccess;
}

//============================================================
// <T>�������ʾ����</T>
//
// @return ������
//============================================================
TResult FSpatial::DisplayClear(){
   if(_pDisplays != NULL){
      _pDisplays->Clear();
   }
   return ESuccess;
}

//============================================================
// <T>������Ⱦ����</T>
//
// @param pRegion ��Ⱦ����
// @return ������
//============================================================
TResult FSpatial::FilterRegion(FRenderRegion* pRegion){
   MO_CHECK(pRegion, return ENull);
   // ���ɼ�״̬
   if(!_statusVisible){
      return EFalse;
   }
   // �ж��Ƿ���Ա�����
   //if(TestDrawable()){
   //   FRenderable* pRenderable = (FRenderable*)Convert(EComponent_Renderable);
   //   if(pRenderable != NULL){
   //      if(pRenderable->Material() != NULL){
   //         pRenderables->Push(pRenderable);
   //      }
   //   }
   //}
   // ���������ӽڵ�
   if(_pDisplays != NULL){
      TInt count = _pDisplays->Count();
      for(TInt n = 0; n < count; n++){
         FDisplay* pDisplay = _pDisplays->Get(n);
         pDisplay->FilterRegion(pRegion);
      }
   }
   return ESuccess;
}

//============================================================
// <T>���µ�ǰ���б任����</T>
//============================================================
void FSpatial::UpdateAllMatrix(SDrawableContext* pContext){
   // �����Ծ���
   UpdateSelftMatrix(pContext);
   // ��������ʾ����
   if(_pDisplays != NULL){
      TInt count = _pDisplays->Count();
      for(TInt n = 0; n < count; n++){
         FDisplay* pDisplay = _pDisplays->Get(n);
         pDisplay->UpdateAllMatrix(pContext);
      }
   }
}

//============================================================
// <T>����ǰ�ô���</T>
//
// @return ������
//============================================================
TResult FSpatial::ProcessBefore(SProcessContext* pContext){
   // �߼�ǰ�ô���
   FDrawable::ProcessBefore(pContext);
   // ���������ӽڵ�
   if(_pDisplays != NULL){
      TInt count = _pDisplays->Count();
      for(TInt n = 0; n < count; n++){
         FDisplay* pDisplay = _pDisplays->Get(n);
         pDisplay->ProcessBefore(pContext);
      }
   }
   return ESuccess;
}

//============================================================
// <T>���ܺ��ô���</T>
//
// @return ������
//============================================================
TResult FSpatial::ProcessAfter(SProcessContext* pContext){
   // �߼�ǰ�ô���
   FDrawable::ProcessAfter(pContext);
   // ���������ӽڵ�
   if(_pDisplays != NULL){
      TInt count = _pDisplays->Count();
      for(TInt n = 0; n < count; n++){
         FDisplay* pDisplay = _pDisplays->Get(n);
         pDisplay->ProcessAfter(pContext);
      }
   }
   return ESuccess;
}

//============================================================
// <T>�ͷŴ���</T>
//============================================================
TResult FSpatial::Free(){
   // ���븸���
   // RemoveFromParent();
   return ESuccess;
}

MO_NAMESPACE_END
