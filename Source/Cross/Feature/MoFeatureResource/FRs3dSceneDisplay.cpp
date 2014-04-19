#include "MoFrContent3dScene.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FRs3dSceneDisplay, FInstance);

//============================================================
// <T>������Դ����������</T>
//============================================================
FRs3dSceneDisplay::FRs3dSceneDisplay(){
}

//============================================================
// <T>������Դ����������</T>
//============================================================
FRs3dSceneDisplay::~FRs3dSceneDisplay(){
}

//============================================================
// <T>���������ﷴ���л���Ϣ����</T>
//
// @param pInput ������
// @return ������
//============================================================
TResult FRs3dSceneDisplay::Unserialize(IDataInput* pInput){
   // ��ȡ��Դ
   _source.UnserializeAutomatic(pInput);
   _optionMergeVertex = RGeomFlag::ToBoolean(pInput->ReadInt8());
   _optionMergeMaterial = RGeomFlag::ToBoolean(pInput->ReadInt8());
   // ��ȡ����
   _matrix.Unserialize(pInput);
   // ��ȡ��������
   TInt movieCount = pInput->ReadInt32();
   for(TInt n = 0; n < movieCount; n++){
      FRs3dSceneMovie* pMovie = FRs3dSceneMovie::InstanceCreate();
      pMovie->Unserialize(pInput);
      _movies.Push(pMovie);
   }
   // ��ȡ���ʼ���
   TInt materialCount = pInput->ReadInt32();
   for(TInt n = 0; n < materialCount; n++){
      FRs3dSceneMaterial* pMaterial = FRs3dSceneMaterial::InstanceCreate();
      pMaterial->Unserialize(pInput);
      _materials.Push(pMaterial);
   }
   // ��ȡ��Ⱦ����
   TInt renderableCount = pInput->ReadInt32();
   for(TInt n = 0; n < renderableCount; n++){
      FRs3dSceneRenderable* pRenderable = FRs3dSceneRenderable::InstanceCreate();
      pRenderable->Unserialize(pInput);
      _renderables.Push(pRenderable);
   }
   return ESuccess;
}

MO_NAMESPACE_END
