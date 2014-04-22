#include "MoEgDisplay.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FDrawable, FComponent);

//============================================================
// <T>����ɻ��ƶ���</T>
//============================================================
FDrawable::FDrawable(){
   _statusReady = ETrue;
   _statusVisible = ETrue;
   _statusDirty = ETrue;
   _groundColor.Set(1.0f, 1.0f, 1.0f, 1.0f);
   _coord.Set(0.0f, 0.0f, 1.0f, 1.0f);
}

//============================================================
// <T>�����ɻ��ƶ���</T>
//============================================================
FDrawable::~FDrawable(){
}

//============================================================
// <T>����׼���á�</T>
//
// @return �Ƿ�׼����
//============================================================
TBool FDrawable::TestReady(){
   return _statusReady;
}

//============================================================
// <T>�����Ƿ���Ի��ơ�</T>
//
// @return �Ƿ���Ի���
//============================================================
TBool FDrawable::TestDrawable(){
   return ETrue;
}

//============================================================
// <T>���ƴ���</T>
//
// @return ������
//============================================================
TResult FDrawable::OnPaint(){
   return ESuccess;
}

//============================================================
// <T>������Դ���</T>
//
// @param pTester ������Ϣ
// @return ������
//============================================================
TResult FDrawable::OnFocusTest(FFocusTester* pTester){
   //SIntRectangle rectangle;
   //CalculateRectangle(&rectangle);
   //SIntPoint2& location = pTester->Location();
   //if(rectangle.TestInRange(location.x, location.y)){
   //   pTester->SetStatusInRange(ETrue);
   //   //pTester->SetStatusChildren(_pChildren != NULL);
   //}
   return ESuccess;
}

//============================================================
// <T>���㷶Χ��</T>
//
// @param pRectangle ��Χ
// @return ������
//============================================================
TResult FDrawable::CalculateRectangle(SIntRectangle* pRectangle){
   MO_CHECK(pRectangle, return ENull);
   // ��������λ��
   FComponent* pFind = this;
   pRectangle->Reset();
   //while(pFind != NULL){
   //   if(pFind->IsObject(EComponent_Drawable)){
   //      FDrawable* pDrawable = (FDrawable*)pFind;
   //      SFloatPoint3& position = pDrawable->Location();
   //      pRectangle->left += (TInt)position.x;
   //      pRectangle->top += (TInt)position.y;
   //   }
   //   pFind = pFind->Parent();
   //}
   pRectangle->SetSize((TInt)_size.width, (TInt)_size.height);
   return ESuccess;
}

//============================================================
// <T>������Ⱦ����</T>
//
// @param pRegion ��Ⱦ����
// @return ������
//============================================================
TResult FDrawable::FilterRegion(FRenderRegion* pRegion){
   MO_CHECK(pRegion, return ENull);
   return ESuccess;
}

//============================================================
// <T>�����Լ��任����</T>
//============================================================
TResult FDrawable::UpdateSelftMatrix(SDrawableContext* pContext){
   // ׷�ӱ任����
   _matrix.Assign(_matrixTransform);
   // ׷��ģ�;���
   _matrix.Append(_matrixModel);
   // ׷�Ӹ�����
   if(_pParent != NULL){
      FDrawable* pDrawable = (FDrawable*)_pParent;
      _matrix.Append(pDrawable->Matrix());
   }
   return ESuccess;
}

//============================================================
// <T>���¸����任����</T>
//============================================================
TResult FDrawable::UpdateParentMatrix(){
   if(_pParent != NULL){
      FDrawable* pParent = ParentDrawable();
      while(pParent != NULL){
         _matrix.Append(pParent->Matrix());
         pParent = pParent->ParentDrawable();
      }
   }
   return ESuccess;
}

//============================================================
// <T>���µ�ǰ�任����</T>
//============================================================
TResult FDrawable::UpdateMatrix(){
   // ׷���Լ���Ϣ
   _matrix.Assign(_matrixModel);
   // ׷�Ӹ���Ϣ
   FDrawable* pParent = ParentDrawable();
   while(pParent != NULL){
      _matrix.Append(pParent->Matrix());
      pParent = pParent->ParentDrawable();
   }
   return ESuccess;
}

//============================================================
// <T>���µ�ǰ���б任����</T>
//============================================================
TResult FDrawable::UpdateAllMatrix(SDrawableContext* pContext){
   // �����Ծ���
   UpdateSelftMatrix(pContext);
   return ESuccess;
}
      
//============================================================
// <T>����´���</T>
//
// @param p:context ����
//============================================================
TResult FDrawable::UpdateDirty(SDrawableContext* pContext){
   //dirty = false;
   // _logger.debug("updateDirty", "Update dirty. (name={1})", name);
   return ESuccess;
}

//============================================================
// <T>���ÿɼ��ԡ�</T>
//
// @param visible �ɼ���
// @return ������
//============================================================
TResult FDrawable::SetVisible(TBool visible){
   _statusVisible = visible;
   return ESuccess;
}

//============================================================
// <T>������Դ���</T>
//
// @param pTester ������Ϣ
// @return ������
//============================================================
TResult FDrawable::FocusTest(FFocusTester* pTester){
   MO_CHECK(pTester, return ENull);
   //// ���ɼ�״̬
   //if(!_statusVisible){
   //   return EFalse;
   //}
   //// ���Դ���
   //pTester->TestReset();
   //TResult result = OnFocusTest(pTester);
   //TBool inRange = pTester->StatusInRange();
   //TBool children = pTester->StatusChildren();
   //// �������������
   //if(children){
   //   //TInt childCount = ChildCount();
   //   //for(TInt n = 0; n < childCount; n++){
   //   //   FComponent* pComponent = _pChildren->Get(n);
   //   //   if(pComponent->IsObject(EComponent_Drawable)){
   //   //      FRenderable* pDrawable = (FRenderable*)pComponent;
   //   //      pDrawable->FocusTest(pTester);
   //   //   }
   //   //}
   //}
   //// ���ӵ�������
   //if(inRange){
   //   pTester->Push(this);
   //}
   return ESuccess;
}

//============================================================
// <T>�ദ��</T>
//
// @return ������
//============================================================
TResult FDrawable::Dirty(TBool force){
   _statusDirty = ETrue;
   return ESuccess;
}

//============================================================
// <T>���ƴ���</T>
//
// @return ������
//============================================================
TResult FDrawable::Paint(){
   TResult result = ESuccess;
   if(_statusVisible){
      if(_statusDirty){
         result = OnPaint();
         _statusDirty = EFalse;
      }
   }
   return result;
}

//============================================================
// <T>���´���</T>
//
// @param pContext ������
// @return ������
//============================================================
TResult FDrawable::Update(SProcessContext* pContext){
   TResult result = FComponent::Update(pContext);
   // ������������һ��
   if(_statusDirty){
      Paint();
   }
   return result;
}


//============================================================
// <T>����ǰ�ô���</T>
//
// @param pContext ������
// @return ������
//============================================================
TResult FDrawable::ProcessBefore(SProcessContext* pContext){
   TResult result = FComponent::ProcessBefore(pContext);
   if(_statusDirty){
      result = Paint();
   }
   return result;
}

//============================================================
// <T>�߼����ô���</T>
//
// @param pContext ������
// @return ������
//============================================================
TResult FDrawable::ProcessAfter(SProcessContext* pContext){
   TResult result = FComponent::ProcessAfter(pContext);
   return result;
}

//============================================================
// <T>������</T>
//
// @return ������
//============================================================
TResult FDrawable::Suspend(){
   return ESuccess;
}

//============================================================
// <T>��������</T>
//
// @return ������
//============================================================
TResult FDrawable::Resume(){
   return ESuccess;
}

//============================================================
// <T>��������</T>
//
// @return ������
//============================================================
TResult FDrawable::Dispose(){
   return ESuccess;
}

MO_NAMESPACE_END
