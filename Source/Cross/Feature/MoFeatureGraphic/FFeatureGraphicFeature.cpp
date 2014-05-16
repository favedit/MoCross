#include "MoFeatureGraphic.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FFeatureGraphicFeature, FFeature);

//============================================================
// <T>����ͼ�ι��ܡ�</T>
//============================================================
FFeatureGraphicFeature::FFeatureGraphicFeature(){
   _name = "Feature Graphic";
}

//============================================================
// <T>����ͼ�ι��ܡ�</T>
//============================================================
FFeatureGraphicFeature::~FFeatureGraphicFeature(){
}

//============================================================
// <T>���������</T>
//
// @return ������
//============================================================
TResult FFeatureGraphicFeature::Construct(){
   TResult resultCd = FFeature::Construct();
   // ��ʼ���ɼ�������
   RVisualManager::Create();
   // ��ʼ������������
   RTechniqueManager::Create();
   // ö�ٴ���
   RRenderAttribute::Create();
   RRenderSampler::Create();
   // ע��ö����Ϣ
   return resultCd;
}

//============================================================
// <T>��������</T>
//
// @return ������
//============================================================
TResult FFeatureGraphicFeature::Startup(){
   TResult resultCd = FFeature::Startup();
   // �����ɼ�������
   RVisualManager::Instance().Startup();
   return resultCd;
}

//============================================================
// <T>������</T>
//
// @return ������
//============================================================
TResult FFeatureGraphicFeature::Suspend(){
   TResult resultCd = FFeature::Suspend();
   return resultCd;
}

//============================================================
// <T>��������</T>
//
// @return ������
//============================================================
TResult FFeatureGraphicFeature::Resume(){
   TResult resultCd = FFeature::Resume();
   return resultCd;
}

//============================================================
// <T>ֹͣ����</T>
//
// @return ������
//============================================================
TResult FFeatureGraphicFeature::Shutdown(){
   TResult resultCd = FFeature::Shutdown();
   // ֹͣ�ɼ�������
   RVisualManager::Instance().Shutdown();
   return resultCd;
}

//============================================================
// <T>�ͷ������</T>
//
// @return ������
//============================================================
TResult FFeatureGraphicFeature::Dispose(){
   TResult resultCd = FFeature::Dispose();
   // �ͷż���������
   RTechniqueManager::Destroy();
   // �ͷſɼ�������
   RVisualManager::Destroy();
   return resultCd;
}

MO_NAMESPACE_END
