#include "MoFrContent3dScene.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FRs3dSceneTechnique, FInstance);

//============================================================
// <T>���쳡��������Դ��</T>
//============================================================
FRs3dSceneTechnique::FRs3dSceneTechnique(){
}

//============================================================
// <T>��������������Դ��</T>
//============================================================
FRs3dSceneTechnique::~FRs3dSceneTechnique(){
}

//============================================================
// <T>���������ﷴ���л���Ϣ����</T>
//
// @param pInput ������
// @return ������
//============================================================
TResult FRs3dSceneTechnique::Unserialize(IDataInput* pInput){
   _name.UnserializeAutomatic(pInput);
   // ��ȡ��Ⱦ���̼���
   TInt passCount = pInput->ReadInt32();
   for(TInt n = 0; n < passCount; n++){
      FRs3dScenePass* pPass = FRs3dScenePass::InstanceCreate();
      pPass->Unserialize(pInput);
      _passes.Push(pPass);
   }
   return ESuccess;
}

MO_NAMESPACE_END
