#include "MoFeatureTerrain.h"
      
MO_NAMESPACE_BEGIN

//============================================================
// <T>��ʼ�����ι��ܴ���</T>
//============================================================
void MoFeatureTerrainInitialize(){
   MO_STATIC_INFO("Feature terrain initialize.");
}

//============================================================
// <T>�������ι��ܴ���</T>
//============================================================
void MoFeatureTerrainStartup(){
   MO_STATIC_INFO("Feature terrain startup.");
}

//============================================================
// <T>�رյ��ι��ܴ���</T>
//============================================================
void MoFeatureTerrainShutdown(){
   MO_STATIC_INFO("Feature terrain shutdown.");
}

//============================================================
// <T>�ͷŵ��ι��ܴ���</T>
//============================================================
void MoFeatureTerrainRelease(){
   MO_STATIC_INFO("Feature terrain release.");
}

MO_NAMESPACE_END
