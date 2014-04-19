#include "MoE3Scene.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FScene3dFrame, FStageFrame);

//============================================================
// <T>����ʵ��3D����֡��</T>
//============================================================
FScene3dFrame::FScene3dFrame(){
   _name = "scene.frame";
}

//============================================================
// <T>����ʵ��3D����֡��</T>
//============================================================
FScene3dFrame::~FScene3dFrame(){
}

//============================================================
// <T>���ô���</T>
//
// @return ������
//============================================================
TResult FScene3dFrame::Setup(){
   TResult resultCd = FStageFrame::Setup();
   // ������ղ�
   _skyLayer = FDisplayLayer::InstanceCreate();
   _skyLayer->SetName("sky.layer");
   _skyLayer->Setup();
   _pLayers->Push(_skyLayer);
   // �����ر��
   _mapLayer = FDisplayLayer::InstanceCreate();
   _mapLayer->SetName("map.layer");
   _mapLayer->Setup();
   _pLayers->Push(_mapLayer);
   // �����ռ��
   _spaceLayer = FDisplayLayer::InstanceCreate();
   _spaceLayer->SetName("space.layer");
   _spaceLayer->Setup();
   _pLayers->Push(_spaceLayer);
   // ���������
   _faceLayer = FDisplayLayer::InstanceCreate();
   _faceLayer->SetName("face.layer");
   _faceLayer->Setup();
   _pLayers->Push(_faceLayer);
   return resultCd;
}

MO_NAMESPACE_END
