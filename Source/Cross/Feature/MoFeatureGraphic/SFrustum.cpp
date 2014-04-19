#include "MoFgCamera.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>����ռ��ӽ��塣</T>
//============================================================
SFrustum::SFrustum(){
}

//============================================================
// <T>��������</T>
//============================================================
void SFrustum::UpdateCenter(){
   // ����ռ���λ��
   TInt n = 0;
   minX = minY = minZ = MO_TP_FLOAT_MAX;
   maxX = maxY = maxZ = MO_TP_FLOAT_MIN;
   while(n < 24){
      TFloat x = coners[n++];
      if(x < minX){
         minX = x;
      }
      if(x > maxX){
         maxX = x;
      }
      TFloat y = coners[n++];
      if(y < minY){
         minY = y;
      }
      if(y > maxY){
         maxY = y;
      }
      TFloat z = coners[n++];
      if(z < minZ){
         minZ = z;
      }
      if(z > maxZ){
         maxZ = z;
      }
   }
   // ��������λ��
   center.x = (minX + maxX) * 0.5f;
   center.y = (minY + maxY) * 0.5f;
   center.z = (minZ + maxZ) * 0.5f;
   radius = sqrt((minX - minY) * (minX - minY) + (minZ - maxX) * (minZ - maxX) + (maxY - maxZ) * (maxY - maxZ)) * 0.5f;
}

//============================================================
// <T>���´���</T>
//
// @param pva:viewportAngle �ӽǽǶ�
// @param pvw:viewportWidth �ӽǿ��
// @param pvh:viewportHeight �ӽǸ߶�
// @param pvn:viewportNear �ӽǽ�ƽ��
// @param pvf:viewportFar �ӽ�Զƽ��
// @param pfr:frontRate ǰƽ�����
// @param pbr:backRate ��ƽ�����
// @param matrix ����
//============================================================
void SFrustum::Update(TFloat pva, TFloat pvw, TFloat pvh, TFloat pvn, TFloat pvf, TFloat pfr, TFloat pbr, SFloatMatrix3d& matrix){
   // �����ӽ���Ϣ
   TFloat aspect = pvw / pvh;
   TFloat znear = -pvf * pbr;
   TFloat zfar = pvf * pfr;
   TFloat fov = tan(MO_GRAPHIC_DEGREE_RATE * pva * 0.5f);
   TFloat nearY = znear * fov;
   TFloat nearX = nearY * aspect;
   TFloat farY = zfar * fov;
   TFloat farX = farY * aspect;
   // ���ÿռ�����
   TFloat points[MO_FRUSTUM_CONER_POINT_COUNT] = {
      -nearX,  nearY, znear,
       nearX,  nearY, znear,
       nearX, -nearY, znear,
      -nearX, -nearY, znear,
      -farX,   farY,  zfar,
       farX,   farY,  zfar,
       farX,  -farY,  zfar,
      -farX,  -farY,  zfar};
   // ����ת������
   conerMatrix.Assign(matrix);
   conerMatrix.Invert();
   conerMatrix.Transform(coners, points, MO_FRUSTUM_CONER_COUNT);
   // ����ռ���λ��
   UpdateCenter();
}

MO_NAMESPACE_END
