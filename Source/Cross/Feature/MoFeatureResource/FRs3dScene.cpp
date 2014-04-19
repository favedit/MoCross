#include "MoFrContent3dScene.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FRs3dScene, FResource3d);

//============================================================
// <T>������Դ3Dģ�塣</T>
//============================================================
FRs3dScene::FRs3dScene(){
   // ����
   _technique = FRs3dSceneTechnique::InstanceCreate();
   // ����
   _region = FRs3dSceneRegion::InstanceCreate();
   // ���
   _sky = FRs3dSceneSky::InstanceCreate();
   // ��ͼ
   _map = FRs3dSceneMap::InstanceCreate();
   // �ռ�
   _space = FRs3dSceneSpace::InstanceCreate();
}

//============================================================
// <T>������Դ3Dģ�塣</T>
//============================================================
FRs3dScene::~FRs3dScene(){
}

//============================================================
// <T>���������ﷴ���л���Ϣ����</T>
//
// @param pInput ������
// @return ������
//============================================================
TResult FRs3dScene::Unserialize(IDataInput* pInput){
   FResource3d::Unserialize(pInput);
   // ��ȡ����
   _themeCode.UnserializeAutomatic(pInput);
   //_theme = RGeResource.themeConsole.load(themeCode);
   // ��ȡ����
   _technique->Unserialize(pInput);
   _region->Unserialize(pInput);
   _sky->Unserialize(pInput);
   _map->Unserialize(pInput);
   _space->Unserialize(pInput);
   // dataReady = true;
   return ESuccess;
}

MO_NAMESPACE_END
