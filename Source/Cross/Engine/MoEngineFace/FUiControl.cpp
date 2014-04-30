#include "MoEfDisplay.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>����ؼ�����</T>
//============================================================
FUiControl::FUiControl(){
   _controlCd = EControlType_Unknown;
   _flags = 0;
   _optionEnable = ETrue;
   _optionVisible = ETrue;
   _dockCd = EControlDock_None;
   // �����Ⱦ��Ϣ
   MO_CLEAR(_pCanvas);
   MO_CLEAR(_pMaterial);
}

//============================================================
// <T>�����ؼ�����</T>
//============================================================
FUiControl::~FUiControl(){
   MO_DELETE(_pMaterial);
   MO_DELETE(_pCanvas);
}

//============================================================
// <T>���ݿؼ����������ͻ�ÿؼ�����</T>
//
// @param index �ؼ�����
// @param controlCd �ؼ�����
// @return ����
//============================================================
FUiControl* FUiControl::ControlGet(TInt index, EControlType controlCd){
   //if(_pChildren != NULL){
   //   FComponent* pComponent = _pChildren->Get(index);
   //   if(pComponent->IsObject(EComponent_Control)){
   //      FUiControl* pControl = (FUiControl*)pComponent;
   //      if(pControl->ControlCd() == controlCd){
   //         return pControl;
   //      }
   //   }
   //}
   return NULL;
}

//============================================================
// <T>�������������л��������ݡ�</T>
//
// @param pInput ������
//============================================================
TResult FUiControl::OnUnserialize(IDataInput* pInput){
   MO_CHECK(pInput, return ENull);
   // ��ȡ����
   _flags = pInput->ReadInt32();
   _name.Unserialize(pInput);
   _label.UnserializeAutomatic(pInput);
   // ��ȡλ��
   _optionEnable = TestFlag(EControlFlag_Enable);
   _optionVisible = TestFlag(EControlFlag_Visible);
   _dockCd = (EControlDock)pInput->ReadUint8();
   _location.x = pInput->ReadInt16();
   _location.y = pInput->ReadInt16();
   _size.width = pInput->ReadUint16();
   _size.height = pInput->ReadUint16();
   // ��ȡ�߾�
   if(TestFlag(EControlFlag_Margin)){
      _margin.Unserialize8(pInput);
   }
   if(TestFlag(EControlFlag_Padding)){
      _padding.Unserialize8(pInput);
   }
   // ��ȡ�߿�
   if(TestFlag(EControlFlag_BorderOuter)){
      _borderOuter.Unserialize(pInput);
   }
   if(TestFlag(EControlFlag_BorderInner)){
      _borderInner.Unserialize(pInput);
   }         
   // ��ȡǰ��
   _foreColor = pInput->ReadInt32();
   if(TestFlag(EControlFlag_LayerFore)){
      _forePicture.Unserialize(pInput);
   }
   // ��ȡ��
   _backColor = pInput->ReadInt32();
   if(TestFlag(EControlFlag_LayerBack)){
      _backPicture.Unserialize(pInput);
   }
   return ESuccess;
}

//============================================================
// <T>������Դ���</T>
//
// @param pTester ������Ϣ
// @return ������
//============================================================
TResult FUiControl::OnFocusTest(FFocusTester* pTester){
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
// <T>�������������л��������ݡ�</T>
//
// @param pInput ������
//============================================================
TResult FUiControl::Unserialize(IDataInput* pInput){
   MO_CHECK(pInput, return ENull);
   // ��ȡ����
   TResult result = OnUnserialize(pInput);
   // ��ȡ�ӿؼ�
   TInt count = pInput->ReadInt16();
   for(TInt n = 0; n < count; n++){
      EControlType controlCd = (EControlType)pInput->ReadInt16();
      _className.Unserialize(pInput);
      FUiControl* pControl = RFaceManager::Instance().ControlConsole()->Alloc(controlCd, (TCharC*)_className);
      pControl->Unserialize(pInput);
      //ChildPush(pControl);
   }
   return result;
}

//============================================================
// <T>��ò��ʡ�</T>
//
// @return ����
//============================================================
FMaterial* FUiControl::Material(){
   return _pMaterial;
}

//============================================================
// <T>���㷶Χ��</T>
//
// @param pRectangle ��Χ
// @return ������
//============================================================
TResult FUiControl::CalculateRectangle(SIntRectangle* pRectangle){
   TResult result = FDrawable::CalculateRectangle(pRectangle);
   // �洢λ��
   if(result == ESuccess){
      _statusRectangle.Assign(*pRectangle);
   }
   return result;
}

//============================================================
// <T>��ÿͻ�����Χ��</T>
//
// @param pRectangle ��Χ
// @return ������
//============================================================
TResult FUiControl::CalculateClientRectangle(SIntRectangle* pRectangle){
   pRectangle->SetLocation(0, 0);
   pRectangle->SetSize((TInt)_size.width, (TInt)_size.height);
   _clientRectangle.Assign(*pRectangle);
   return ESuccess;
}

//============================================================
// <T>������Ⱦ��Ϣ��</T>
//
// @param renderable ��Ⱦ��Ϣ
// @return ������
//============================================================
TResult FUiControl::CalculateRenderable(SRenderable& renderable){
   SRenderableItem& item = renderable.Alloc();
   // ��������λ��
   TInt level = 0;
   FComponent* pFind = this;
   item.location.Reset();
   while(pFind != NULL){
      //if(pFind->IsObject(EComponent_Drawable)){
      //   FDrawable* pDrawable = (FDrawable*)pFind;
      //   item.location.Add(pDrawable->Location());
      //}
      pFind = pFind->Parent();
      //level++;
   }
   // ��������
   item.size.Assign(_size);
   item.rotation.Assign(_rotation);
   item.coord.Assign(_coord);
   item.groundColor.Assign(_groundColor);
   // ���ò㼶
   if(_pMaterial != NULL){
      //_pMaterial->SetLevel(level);
   }
   return ESuccess;
}

//============================================================
// <T>��û��塣</T>
//
// @return ����
//============================================================
FUiCanvas* FUiControl::Canvas(){
   // ������
   if(_pCanvas != NULL){
      return _pCanvas;
   }
   // ��������
   _pCanvas = MO_CREATE(FUiCanvas);
   _pCanvas->Setup();
   _pCanvas->Resize((TInt)_size.width, (TInt)_size.height);
   // ��������
   //_pMaterial = MO_CREATE(FMaterial);
   //_pMaterial->SetEffectCd(ERenderEffect_2dTexture);
   //_pMaterial->SetOptionDepth(EFalse);
   //_pMaterial->SetOptionAlpha(ETrue);
   //_pMaterial->SetBlendSourceMode(ERenderBlendMode_SourceAlpha);
   //_pMaterial->SetBlendTargetMode(ERenderBlendMode_OneMinusSourceAlpha);
   //_pMaterial->TextureSet(_pCanvas->RenderTexture());
   //// ������������
   //SIntSize2& canvasSize = _pCanvas->Size();
   //_coord.x2 = _size.width / (TFloat)canvasSize.width;
   //_coord.y2 = _size.height / (TFloat)canvasSize.height;
   return _pCanvas;
}

//============================================================
// <T>�ͷ����ݡ�</T>
//
// @return ������
//============================================================
TResult FUiControl::Free(){
   return ESuccess;
}

MO_NAMESPACE_END
