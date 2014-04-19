#include "MoFgCamera.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>�����ӽ���ƽ�����͡�</T>
//============================================================
SFrustumPlanes::SFrustumPlanes(){
}

//============================================================
// <T>�����Ƿ����ӽ����ڡ�</T>
//
// @param x ����X
// @param y ����Y
// @param z ����Z
//============================================================
TBool SFrustumPlanes::ContainsPoint(TFloat x, TFloat y, TFloat z){
   for(TInt n = 0; n < EFrustumPlane_Count; n++){
      if(planes[n].Dot(x, y, z) < 0){
         return EFalse;
      }
   }
   return ETrue;
}
      
//============================================================
// <T>����������Ƿ����ӽ����ڡ�</T>
//
// @param centerX ���ĵ�X����
// @param centerY ���ĵ�Y����
// @param centerZ ���ĵ�Z����
// @param size ��С
// @return �Ƿ����
//============================================================
TBool SFrustumPlanes::ContainsCube(TFloat centerX, TFloat centerY, TFloat centerZ, TFloat size){
   for(TInt n = 0; n < EFrustumPlane_Count; n++){
      if(planes[n].Dot(centerX - size, centerY - size, centerZ - size) >= 0){
         continue;
      }
      if(planes[n].Dot(centerX + size, centerY - size, centerZ - size) >= 0){
         continue;
      }
      if(planes[n].Dot(centerX - size, centerY + size, centerZ - size) >= 0){
         continue;
      }
      if(planes[n].Dot(centerX + size, centerY + size, centerZ - size) >= 0){
         continue;
      }
      if(planes[n].Dot(centerX - size, centerY - size, centerZ + size) >= 0){
         continue;
      }
      if(planes[n].Dot(centerX + size, centerY - size, centerZ + size) >= 0){
         continue;
      }
      if(planes[n].Dot(centerX - size, centerY + size, centerZ + size) >= 0){
         continue;
      }
      if(planes[n].Dot(centerX + size, centerY + size, centerZ + size) >= 0){
         continue;
      }
      return EFalse;
   }
   return ETrue;
}
      
//============================================================
// <T>��鳤�����Ƿ����ӽ����ڡ�</T>
//
// @param cx:centerX ���ĵ�X����
// @param cy:centerY ���ĵ�Y����
// @param cz:centerZ ���ĵ�Z����
// @param sx:sizeX X��С
// @param sy:sizeY Y��С
// @param sz:sizeZ Z��С
// @return �Ƿ����
//============================================================
TBool SFrustumPlanes::ContainsRectangle(TFloat cx, TFloat cy, TFloat cz, TFloat sx, TFloat sy, TFloat sz){
   for(TInt n = 0; n < EFrustumPlane_Count; n++){
      if(planes[n].Dot(cx - sx, cy - sy, cz - sz) >= 0){
         continue;
      }
      if(planes[n].Dot(cx + sx, cy - sy, cz - sz) >= 0){
         continue;
      }
      if(planes[n].Dot(cx - sx, cy + sy, cz - sz) >= 0){
         continue;
      }
      if(planes[n].Dot(cx + sx, cy + sy, cz - sz) >= 0){
         continue;
      }
      if(planes[n].Dot(cx - sx, cy - sy, cz + sz) >= 0){
         continue;
      }
      if(planes[n].Dot(cx + sx, cy - sy, cz + sz) >= 0){
         continue;
      }
      if(planes[n].Dot(cx - sx, cy + sy, cz + sz) >= 0){
         continue;
      }
      if(planes[n].Dot(cx + sx, cy + sy, cz + sz) >= 0){
         continue;
      }
      return EFalse;
   }
   return ETrue;
}
      
//============================================================
// <T>��鳤�����Ƿ����ӽ����ڡ�</T>
//
// @param p:corners ���㼯��
// @return �Ƿ����
//============================================================
TBool SFrustumPlanes::ContainsCorners(TFloat* pCorners){
   for(TInt n = 0; n < EFrustumPlane_Count; n++){
      if(planes[n].Dot(pCorners[ 0], pCorners[ 1], pCorners[ 2]) >= 0){
         continue;
      }
      if(planes[n].Dot(pCorners[ 3], pCorners[ 4], pCorners[ 5]) >= 0){
         continue;
      }
      if(planes[n].Dot(pCorners[ 6], pCorners[ 7], pCorners[ 8]) >= 0){
         continue;
      }
      if(planes[n].Dot(pCorners[ 9], pCorners[10], pCorners[11]) >= 0){
         continue;
      }
      if(planes[n].Dot(pCorners[12], pCorners[13], pCorners[14]) >= 0){
         continue;
      }
      if(planes[n].Dot(pCorners[15], pCorners[16], pCorners[17]) >= 0){
         continue;
      }
      if(planes[n].Dot(pCorners[18], pCorners[19], pCorners[20]) >= 0){
         continue;
      }
      if(planes[n].Dot(pCorners[21], pCorners[22], pCorners[23]) >= 0){
         continue;
      }
      return EFalse;
   }
   return ETrue;
}
      
//============================================================
// <T>��������Ƿ����ӽ����ڡ�</T>
//
// @param px:centerX ���ĵ�X����
// @param py:centerY ���ĵ�Y����
// @param pz:centerZ ���ĵ�Z����
// @param pr:radius �뾶
// @return �Ƿ����
//============================================================
TBool SFrustumPlanes::ContainsSphere(TFloat px, TFloat py, TFloat pz, TFloat pr){
   for(TInt n = 0; n < EFrustumPlane_Count; n++){
      if(planes[n].Dot(px, py, pz) < -pr){
         return EFalse;
      }
   }
   return ETrue;
}
      
//============================================================
// <T>���¿��ӷ�Χ��Ϣ��</T>
//
// @param p ��������
//============================================================
void SFrustumPlanes::UpdateVision(TFloat* pVision){
   // �����ӽ���Ľ�ƽ��
   SFloatPlane& nearPlane = planes[EFrustumPlane_Near];
   nearPlane.a = pVision[4 * 0 + 2];
   nearPlane.b = pVision[4 * 1 + 2];
   nearPlane.c = pVision[4 * 2 + 2];
   nearPlane.d = pVision[4 * 3 + 2];
   nearPlane.Normalize();
   // �����ӽ����Զƽ��
   SFloatPlane& farPlane = planes[EFrustumPlane_Far];
   farPlane.a = pVision[4 * 0 + 3] - pVision[4 * 0 + 2];
   farPlane.b = pVision[4 * 1 + 3] - pVision[4 * 1 + 2];
   farPlane.c = pVision[4 * 2 + 3] - pVision[4 * 2 + 2];
   farPlane.d = pVision[4 * 3 + 3] - pVision[4 * 3 + 2];
   farPlane.Normalize();
   // �����ӽ������ƽ��
   SFloatPlane& leftPlane = planes[EFrustumPlane_Left];
   leftPlane.a = pVision[4 * 0 + 3] + pVision[4 * 0 + 0];
   leftPlane.b = pVision[4 * 1 + 3] + pVision[4 * 1 + 0];
   leftPlane.c = pVision[4 * 2 + 3] + pVision[4 * 2 + 0];
   leftPlane.d = pVision[4 * 3 + 3] + pVision[4 * 3 + 0];
   leftPlane.Normalize();
   // �����ӽ������ƽ��
   SFloatPlane& rightPlane = planes[EFrustumPlane_Right];
   rightPlane.a = pVision[4 * 0 + 3] - pVision[4 * 0 + 0];
   rightPlane.b = pVision[4 * 1 + 3] - pVision[4 * 1 + 0];
   rightPlane.c = pVision[4 * 2 + 3] - pVision[4 * 2 + 0];
   rightPlane.d = pVision[4 * 3 + 3] - pVision[4 * 3 + 0];
   rightPlane.Normalize();
   // �����ӽ���Ķ�ƽ��
   SFloatPlane& topPlane = planes[EFrustumPlane_Top];
   topPlane.a = pVision[4 * 0 + 3] - pVision[4 * 0 + 1];
   topPlane.b = pVision[4 * 1 + 3] - pVision[4 * 1 + 1];
   topPlane.c = pVision[4 * 2 + 3] - pVision[4 * 2 + 1];
   topPlane.d = pVision[4 * 3 + 3] - pVision[4 * 3 + 1];
   topPlane.Normalize();
   // �����ӽ���ĵ�ƽ��
   SFloatPlane& bottomPlane = planes[EFrustumPlane_Bottom];
   bottomPlane.a = pVision[4 * 0 + 3] + pVision[4 * 0 + 1];
   bottomPlane.b = pVision[4 * 1 + 3] + pVision[4 * 1 + 1];
   bottomPlane.c = pVision[4 * 2 + 3] + pVision[4 * 2 + 1];
   bottomPlane.d = pVision[4 * 3 + 3] + pVision[4 * 3 + 1];
   bottomPlane.Normalize();
}

MO_NAMESPACE_END
