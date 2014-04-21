#include "MoEgDisplay.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FDisplay, FDrawable);

//============================================================
// <T>������ʾ����</T>
//============================================================
FDisplay::FDisplay(){
   MO_CLEAR(_pDisplays);
   MO_CLEAR(_pRenderables);
}

//============================================================
// <T>������ʾ����</T>
//============================================================
FDisplay::~FDisplay(){
}

//============================================================
// <T>����һ������ʾ����</T>
//
// @param pDisplay ����ʾ����
// @return ������
//============================================================
TResult FDisplay::DisplayPush(FDisplay* pDisplay){
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
TResult FDisplay::DisplayRemove(FDisplay* pDisplay){
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
TResult FDisplay::DisplayClear(){
   if(_pDisplays != NULL){
      _pDisplays->Clear();
   }
   return ESuccess;
}

//============================================================
// <T>����һ������Ⱦ����</T>
//
// @param pRenderable ����Ⱦ����
// @return ������
//============================================================
TResult FDisplay::RenderablePush(FRenderable* pRenderable){
   MO_ASSERT(pRenderable);
   // �����ʾ����
   if(_pRenderables == NULL){
      _pRenderables = MO_CREATE(FRenderableCollection);
   }
   // ����Ƿ��Ѿ�����
   if(_pRenderables->Contains(pRenderable)){
      // ��鸸����Ƿ�Ϊ�Լ�
      //FComponent* pParent = pRenderable->Parent();
      //if(pParent != NULL){
      //   MO_DEBUG_WARN("Child has already, but parent is null. (renderable=0x%08X)", pRenderable);
      //}else if(pParent != this){
      //   MO_DEBUG_WARN("Child has already, but parent is not this. (renderable=0x%08X, parent=0x%08X)", pRenderable, pParent);
      //}else{
      //   MO_DEBUG_WARN("Child has already. (renderable=0x%08X)", pRenderable);
      //}
      return EFailure;
   }
   // �Ӹ����������
   // pDisplay->RemoveFromParent();
   // �������������
   //pRenderable->SetParent(this);
   _pRenderables->Push(pRenderable);
   return ESuccess;
}

//============================================================
// <T>�Ƴ�һ������Ⱦ����</T>
//
// @param pRenderable ����Ⱦ����
// @return ������
//============================================================
TResult FDisplay::RenderableRemove(FRenderable* pRenderable){
   MO_ASSERT(pRenderable);
   if(_pRenderables == NULL){
      MO_DEBUG_WARN("Children is empty, can't remove any child. (renderable=0x%08X)", pRenderable);
      return EFailure;
   }
#ifdef _MO_DEBUG
   if(!_pRenderables->Contains(pRenderable)){
      MO_DEBUG_WARN("Children not contains this child. (renderable=0x%08X)", pRenderable);
      return EFailure;
   }
#endif // _MO_DEBUG
   _pRenderables->Remove(pRenderable);
   return ESuccess;
}

//============================================================
// <T>�������Ⱦ����</T>
//
// @return ������
//============================================================
TResult FDisplay::RenderableClear(){
   if(_pRenderables != NULL){
      _pRenderables->Clear();
   }
   return ESuccess;
}

//============================================================
// <T>������Ⱦ����</T>
//
// @param pRegion ��Ⱦ����
// @return ������
//============================================================
TResult FDisplay::FilterRegion(FRenderRegion* pRegion){
   MO_CHECK(pRegion, return ENull);
   // ���ɼ�״̬
   if(!_statusVisible){
      return EFalse;
   }
   //............................................................
   // ���������ӽڵ�
   if(_pRenderables != NULL){
      TInt count = _pRenderables->Count();
      if(count > 0){
         FRenderableCollection* pRenderables = pRegion->Renderables();
         for(TInt n = 0; n < count; n++){
            FRenderable* pRenderable = _pRenderables->Get(n);
            pRenderables->Push(pRenderable);
         }
      }
   }
   //............................................................
   // ������������ʾ����
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
void FDisplay::UpdateAllMatrix(SDrawableContext* pContext){
   // �����Ծ���
   UpdateSelftMatrix(pContext);
   // ��������ʾ����
   if(_pRenderables != NULL){
      TInt count = _pRenderables->Count();
      for(TInt n = 0; n < count; n++){
         FRenderable* pRenderable = (FRenderable*)_pRenderables->Get(n);
         pRenderable->Matrix().Assign(_matrix);
      }
   }
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
TResult FDisplay::ProcessBefore(SProcessContext* pContext){
   // �߼�ǰ�ô���
   FDrawable::ProcessBefore(pContext);
   // ���������ӽڵ�
   if(_pRenderables != NULL){
      TInt count = _pRenderables->Count();
      for(TInt n = 0; n < count; n++){
         FRenderable* pRenderable = (FRenderable*)_pRenderables->Get(n);
         pRenderable->ProcessBefore(pContext);
      }
   }
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
TResult FDisplay::ProcessAfter(SProcessContext* pContext){
   // �߼�ǰ�ô���
   FDrawable::ProcessAfter(pContext);
   // ���������ӽڵ�
   if(_pRenderables != NULL){
      TInt count = _pRenderables->Count();
      for(TInt n = 0; n < count; n++){
         FRenderable* pRenderable = (FRenderable*)_pRenderables->Get(n);
         pRenderable->ProcessAfter(pContext);
      }
   }
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
TResult FDisplay::Free(){
   // ���븸���
   // RemoveFromParent();
   return ESuccess;
}

//============================================================
// <T>������</T>
//
// @return ������
//============================================================
TResult FDisplay::Suspend(){
   // ���������ӽڵ�
   if(_pDisplays != NULL){
      TInt count = _pDisplays->Count();
      for(TInt n = 0; n < count; n++){
         FDisplay* pDisplay = _pDisplays->Get(n);
         pDisplay->Suspend();
      }
   }
   // ���������ӽڵ�
   if(_pRenderables != NULL){
      TInt count = _pRenderables->Count();
      for(TInt n = 0; n < count; n++){
         FRenderable* pRenderable = (FRenderable*)_pRenderables->Get(n);
         pRenderable->Suspend();
      }
   }
   return ESuccess;
}

//============================================================
// <T>��������</T>
//
// @return ������
//============================================================
TResult FDisplay::Resume(){
   // ���������ӽڵ�
   if(_pDisplays != NULL){
      TInt count = _pDisplays->Count();
      for(TInt n = 0; n < count; n++){
         FDisplay* pDisplay = _pDisplays->Get(n);
         pDisplay->Resume();
      }
   }
   // ���������ӽڵ�
   if(_pRenderables != NULL){
      TInt count = _pRenderables->Count();
      for(TInt n = 0; n < count; n++){
         FRenderable* pRenderable = (FRenderable*)_pRenderables->Get(n);
         pRenderable->Resume();
      }
   }
   return ESuccess;
}

//============================================================
// <T>��������</T>
//
// @return ������
//============================================================
TResult FDisplay::Dispose(){
   return ESuccess;
}

MO_NAMESPACE_END
