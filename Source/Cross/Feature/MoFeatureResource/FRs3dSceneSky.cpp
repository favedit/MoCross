#include "MoFrContent3dScene.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FRs3dSceneSky, FInstance);

//============================================================
// <T>������Դ����������</T>
//============================================================
FRs3dSceneSky::FRs3dSceneSky(){
}

//============================================================
// <T>������Դ����������</T>
//============================================================
FRs3dSceneSky::~FRs3dSceneSky(){
}

//============================================================
// <T>���������ﷴ���л���Ϣ����</T>
//
// @param pInput ������
// @return ������
//============================================================
TResult FRs3dSceneSky::Unserialize(IDataInput* pInput){
   // ��ȡ����
   _name.UnserializeAutomatic(pInput);
   _typeName.UnserializeAutomatic(pInput);
   // ��ȡ��ʾ����
   TInt displayCount = pInput->ReadInt32();
   for(TInt n = 0; n < displayCount; n++){
      FRs3dSceneDisplay* pDisplay = FRs3dSceneDisplay::InstanceCreate();
      pDisplay->Unserialize(pInput);
      _displays.Push(pDisplay);
   }
   return ESuccess;
}

MO_NAMESPACE_END
