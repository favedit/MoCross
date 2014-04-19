#include "MoFrContent3dScene.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FRs3dSceneMap, FInstance);

//============================================================
// <T>���쳡����ͼ��Դ��</T>
//============================================================
FRs3dSceneMap::FRs3dSceneMap(){
}

//============================================================
// <T>����������ͼ��Դ��</T>
//============================================================
FRs3dSceneMap::~FRs3dSceneMap(){
}

//============================================================
// <T>���������ﷴ���л���Ϣ����</T>
//
// @param pInput ������
// @return ������
//============================================================
TResult FRs3dSceneMap::Unserialize(IDataInput* pInput){
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
