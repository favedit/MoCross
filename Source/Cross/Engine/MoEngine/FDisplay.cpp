#include "MoEgDisplay.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FDisplay, FDrawable);

//============================================================
// <T>������ʾ����</T>
//============================================================
FDisplay::FDisplay(){
}

//============================================================
// <T>������ʾ����</T>
//============================================================
FDisplay::~FDisplay(){
}

//============================================================
// <T>����һ������Ⱦ����</T>
//
// @param pRenderable ����Ⱦ����
// @return ������
//============================================================
TResult FDisplay::RenderablePush(FRenderable* pRenderable){
   MO_ASSERT(pRenderable);
   // ����Ƿ��Ѿ�����
#ifdef _MO_DEBUG
   if(_renderables.Contains(pRenderable)){
      MO_FATAL("Child renderable has already. (renderable=0x%08X)", pRenderable);
      return EFailure;
   }
#endif // _MO_DEBUG
   // �Ӹ����������
   // pDisplay->RemoveFromParent();
   // �������������
   //pRenderable->SetParent(this);
   _renderables.Push(pRenderable);
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
#ifdef _MO_DEBUG
   if(!_renderables.Contains(pRenderable)){
      MO_DEBUG_WARN("Children not contains this child. (renderable=0x%08X)", pRenderable);
      return EFailure;
   }
#endif // _MO_DEBUG
   _renderables.Remove(pRenderable);
   return ESuccess;
}

//============================================================
// <T>�������Ⱦ����</T>
//
// @return ������
//============================================================
TResult FDisplay::RenderableClear(){
   _renderables.Clear();
   return ESuccess;
}

//============================================================
// <T>����һ������ʾ����</T>
//
// @param pDisplay ����ʾ����
// @return ������
//============================================================
TResult FDisplay::DisplayPush(FDisplay* pDisplay){
   MO_ASSERT(pDisplay);
   // ����Ƿ��Ѿ�����
#ifdef _MO_DEBUG
   if(_displays.Contains(pDisplay)){
      MO_FATAL("Child display has already. (renderable=0x%08X)", pDisplay);
      return EFailure;
   }
#endif // _MO_DEBUG
   // �Ӹ����������
   // pDisplay->RemoveFromParent();
   // �������������
   pDisplay->SetParent(this);
   _displays.Push(pDisplay);
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
#ifdef _MO_DEBUG
   if(!_displays.Contains(pDisplay)){
      MO_DEBUG_WARN("Children not contains this child. (display=0x%08X)", pDisplay);
      return EFailure;
   }
#endif // _MO_DEBUG
   _displays.Remove(pDisplay);
   return ESuccess;
}

//============================================================
// <T>�������ʾ����</T>
//
// @return ������
//============================================================
TResult FDisplay::DisplayClear(){
   _displays.Clear();
   return ESuccess;
}

//============================================================
// <T>���һ���ű�����</T>
//
// @return ������
//============================================================
TResult FDisplay::ScriptablePush(FScriptable* pScriptable){
   MO_CHECK(pScriptable, return ENull);
   // ����Ƿ��Ѿ�����
#ifdef _MO_DEBUG
   if(_scriptables.Contains(pScriptable)){
      MO_FATAL("Child scriptable has already. (renderable=0x%08X)", pScriptable);
      return EFailure;
   }
#endif // _MO_DEBUG
   _scriptables.Push(pScriptable);
   return ESuccess;
}

//============================================================
// <T>�Ƴ�һ���ű�����</T>
//
// @return ������
//============================================================
TResult FDisplay::ScriptableRemove(FScriptable* pScriptable){
   MO_CHECK(pScriptable, return ENull);
   _scriptables.Remove(pScriptable);
   return ESuccess;
}

//============================================================
// <T>��սű����󼯺ϡ�</T>
//
// @return ������
//============================================================
TResult FDisplay::ScriptableClear(){
   _scriptables.Clear();
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
   // ���׼����
   if(!TestReady()){
      return EContinue;
   }
   // ���ɼ�״̬
   if(!_statusVisible){
      return EContinue;
   }
   //............................................................
   // ���������ӽڵ�
   if(!_renderables.IsEmpty()){
      TInt count = _renderables.Count();
      FRenderableCollection* pRenderables = pRegion->Renderables();
      for(TInt n = 0; n < count; n++){
         FRenderable* pRenderable = _renderables.Get(n);
         pRenderables->Push(pRenderable);
      }
   }
   //............................................................
   // ������������ʾ����
   if(!_displays.IsEmpty()){
      TInt count = _displays.Count();
      for(TInt n = 0; n < count; n++){
         FDisplay* pDisplay = _displays.Get(n);
         pDisplay->FilterRegion(pRegion);
      }
   }
   return ESuccess;
}

//============================================================
// <T>���µ�ǰ���б任����</T>
//============================================================
TResult FDisplay::UpdateAllMatrix(SDrawableContext* pContext){
   // �����Ծ���
   UpdateSelftMatrix(pContext);
   // ��������ʾ����
   if(!_renderables.IsEmpty()){
      TInt count = _renderables.Count();
      for(TInt n = 0; n < count; n++){
         FRenderable* pRenderable = _renderables.Get(n);
         pRenderable->Matrix().Assign(_matrix);
      }
   }
   // ��������ʾ����
   if(!_displays.IsEmpty()){
      TInt count = _displays.Count();
      for(TInt n = 0; n < count; n++){
         FDisplay* pDisplay = _displays.Get(n);
         pDisplay->UpdateAllMatrix(pContext);
      }
   }
   return ESuccess;
}

//============================================================
// <T>���´���</T>
//
// @return ������
//============================================================
TResult FDisplay::Update(SProcessContext* pContext){
   // �߼�ǰ�ô���
   TResult resultCd = FDrawable::Update(pContext);
   // ���������ӽڵ�
   if(!_renderables.IsEmpty()){
      TInt count = _renderables.Count();
      for(TInt n = 0; n < count; n++){
         FRenderable* pRenderable = _renderables.Get(n);
         pRenderable->Update(pContext);
      }
   }
   // ���������ӽڵ�
   if(!_displays.IsEmpty()){
      TInt count = _displays.Count();
      for(TInt n = 0; n < count; n++){
         FDisplay* pDisplay = _displays.Get(n);
         pDisplay->Update(pContext);
      }
   }
   return resultCd;
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
   if(!_renderables.IsEmpty()){
      TInt count = _renderables.Count();
      for(TInt n = 0; n < count; n++){
         FRenderable* pRenderable = _renderables.Get(n);
         pRenderable->ProcessBefore(pContext);
      }
   }
   // ���������ӽڵ�
   if(!_displays.IsEmpty()){
      TInt count = _displays.Count();
      for(TInt n = 0; n < count; n++){
         FDisplay* pDisplay = _displays.Get(n);
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
   if(!_renderables.IsEmpty()){
      TInt count = _renderables.Count();
      for(TInt n = 0; n < count; n++){
         FRenderable* pRenderable = _renderables.Get(n);
         pRenderable->ProcessAfter(pContext);
      }
   }
   // ���������ӽڵ�
   if(!_displays.IsEmpty()){
      TInt count = _displays.Count();
      for(TInt n = 0; n < count; n++){
         FDisplay* pDisplay = _displays.Get(n);
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
   if(!_displays.IsEmpty()){
      TInt count = _displays.Count();
      for(TInt n = 0; n < count; n++){
         FDisplay* pDisplay = _displays.Get(n);
         pDisplay->Suspend();
      }
   }
   // ���������ӽڵ�
   if(!_renderables.IsEmpty()){
      TInt count = _renderables.Count();
      for(TInt n = 0; n < count; n++){
         FRenderable* pRenderable = _renderables.Get(n);
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
   if(!_displays.IsEmpty()){
      TInt count = _displays.Count();
      for(TInt n = 0; n < count; n++){
         FDisplay* pDisplay = _displays.Get(n);
         pDisplay->Resume();
      }
   }
   // ���������ӽڵ�
   if(!_renderables.IsEmpty()){
      TInt count = _renderables.Count();
      for(TInt n = 0; n < count; n++){
         FRenderable* pRenderable = _renderables.Get(n);
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
