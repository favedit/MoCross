#include "MoFgRender.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>���㵱ǰ�豸֧�ֺϲ��������</T>
//
// @return �����
//============================================================
TInt RRenderUtil::CalculateMergeLimit(){
   FRenderDevice* pRenderDevice = RDeviceManager::Instance().Find<FRenderDevice>();
   // ���㳣����������
   TInt vertexConstLimit = pRenderDevice->Capability()->VertexConstLimit();
   TInt constLimit = (vertexConstLimit - MO_EG_CONST_RESERVE) / 4;
   return constLimit;
}

//============================================================
// <T>���㵱ǰ�豸֧��ʵ������������</T>
//
// @param vertexCount ��������
// @param boneCount ��ͷ����
//============================================================
TInt RRenderUtil::CalculateInstanceCount(TInt vertexCount, TInt boneCount){
   FRenderDevice* pRenderDevice = RDeviceManager::Instance().Find<FRenderDevice>();
   // ���㳣����������
   TInt vertexConstLimit = pRenderDevice->Capability()->VertexConstLimit();
   TInt constRequire = (3 * boneCount) + 4;
   TInt constLimit = (vertexConstLimit - MO_EG_CONST_RESERVE) / constRequire;
   TInt instanceCount = constLimit;
   // ���㶥������
   if(vertexCount > 0){
      TInt vertexCountLimit = pRenderDevice->Capability()->VertexCountLimit();
      TInt vertexLimit = vertexCountLimit / vertexCount;
      instanceCount = MO_LIB_MIN(instanceCount, vertexLimit);
   }
   // ������������
   instanceCount = MO_LIB_MIN(instanceCount, MO_EG_CONST_INSTANCE_MAX);
   return instanceCount;
}

MO_NAMESPACE_END
