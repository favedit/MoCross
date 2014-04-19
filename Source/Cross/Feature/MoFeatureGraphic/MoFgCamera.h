#ifndef __MO_FG_CAMERA_H__
#define __MO_FG_CAMERA_H__
//************************************************************

#ifndef __MO_FG_COMMON_H__
#include "MoFgCommon.h"
#endif // __MO_FG_COMMON_H__

#ifndef __MO_FG_PROJECTION_H__
#include "MoFgProjection.h"
#endif // __MO_FG_PROJECTION_H__

#ifndef __MO_FG_VIEWPORT_H__
#include "MoFgViewport.h"
#endif // __MO_FG_VIEWPORT_H__

#define MO_FRUSTUM_CONER_COUNT       8
#define MO_FRUSTUM_CONER_POINT_COUNT 24

MO_NAMESPACE_BEGIN

//============================================================
// <T>�ӽ���ƽ�����͡�</T>
//============================================================
enum EFrustumPlane{
   // ��ƽ��
   EFrustumPlane_Near = 0,
   // Զƽ��
   EFrustumPlane_Far = 1,
   // ��ƽ��
   EFrustumPlane_Left = 2,
   // ��ƽ��
   EFrustumPlane_Right = 3,
   // ��ƽ��
   EFrustumPlane_Top = 4,
   // ��ƽ��
   EFrustumPlane_Bottom = 5,
   // ƽ������
   EFrustumPlane_Count = 6,
};

//============================================================
//<T>������ƽ�档</T>
//============================================================
class MO_FG_DECLARE SFloatPlane{
public:
	// ��������a
   TFloat a;
	// ��������b
   TFloat b;
	// ��������c
   TFloat c;
	// ��������d
   TFloat d;
public:
   //------------------------------------------------------------
   //<T>���측����ƽ�档</T>
   MO_INLINE SFloatPlane(TFloat valueA = 0.0f, TFloat valueB = 0.0f, TFloat valueC = 0.0f, TFloat valueD = 0.0f){
      a = valueA;
      b = valueB;
      c = valueC;
      d = valueD;
   }
public:
   //------------------------------------------------------------
   //<T>��λ��׼������</T>
   MO_INLINE void Normalize(){
      TFloat r = 1 / sqrt((a * a) + (b * b) + (c * c));
      a *= r;
      b *= r;
      c *= r;
      d *= r;
   }
   //------------------------------------------------------------
   //<T>��˴���</T>
   MO_INLINE TFloat Dot(TFloat x, TFloat y, TFloat z){
      return (x * a) + (y * b) + (z * c ) + d;
   }
public:
   TCharC* ToString(TChar* pBuffer, TInt capacity);
};

//============================================================
// <T>�ӽ���ƽ�漯�ϡ�</T>
//============================================================
class MO_FG_DECLARE SFrustumPlanes{
public:
   SFloatPlane planes[EFrustumPlane_Count];
public:
   SFrustumPlanes();
public:
   TBool ContainsPoint(TFloat x, TFloat y, TFloat z);
   TBool ContainsCube(TFloat centerX, TFloat centerY, TFloat centerZ, TFloat size);
   TBool ContainsRectangle(TFloat cx, TFloat cy, TFloat cz, TFloat sx, TFloat sy, TFloat sz);
   TBool ContainsCorners(TFloat* pCorners);
   TBool ContainsSphere(TFloat px, TFloat py, TFloat pz, TFloat pr);
public:
   void UpdateVision(TFloat* pVision);
};

//============================================================
// <T>�ռ��ӽ��塣</T>
//============================================================
class MO_FG_DECLARE SFrustum{
public:
   // ת������
   SFloatMatrix3d conerMatrix;
   // ���ĵ�
   SFloatPoint3 center;
   // �뾶
   TFloat radius;
   // ��СX����
   TFloat minX;
   // ���X����
   TFloat maxX;
   // ��СY����
   TFloat minY;
   // ���Y����
   TFloat maxY;
   // ��СZ����
   TFloat minZ;
   // ���Z����
   TFloat maxZ;
   // ���㼯��
   TFloat coners[MO_FRUSTUM_CONER_POINT_COUNT];
public:
   SFrustum();
public:
   void UpdateCenter();
   void Update(TFloat pva, TFloat pvw, TFloat pvh, TFloat pvn, TFloat pvf, TFloat pfr, TFloat pbr, SFloatMatrix3d& matrix);
};

//============================================================
// <T>�����</T>
//============================================================
class MO_FG_DECLARE FCamera : public FInstance
{
   MO_CLASS_DECLARE_INHERITS(FCamera, FInstance);
protected:
   // ��������
   TFsName _typeName;
   // �任����
   SFloatMatrix3d _matrix;
   // ���λ��
   SFloatPoint3 _position;
   // �������
   SFloatVector3 _direction;
   // ����ǰλ��
   TFloat _centerFront;
   // ���ĺ�λ��
   TFloat _centerBack;
   // ����ƽ��λ��
   TFloat _focalNear;
   // Զ��ƽ��λ��
   TFloat _focalFar;
   // �ɼ��ӽ���
   SFrustumPlanes _planes;
   // �ӽ���
   SFrustum _frustum;
   // ������
   SFloatVector3 _axisUp;
   // X����
   SFloatVector3 _axisX;
   // Y����
   SFloatVector3 _axisY;
   // Z����
   SFloatVector3 _axisZ;
   // ͶӰ�任
   GPtr<FProjection> _projection;
   // ��ȾĿ��
   GPtr<FViewport> _viewport;
public:
   FCamera();
   MO_ABSTRACT ~FCamera();
public:
   //------------------------------------------------------------
   // <T>��ñ任����</T>
   MO_INLINE SFloatMatrix3d& Matrix(){
      return _matrix;
   }
   //------------------------------------------------------------
   // <T>������λ�á�</T>
   MO_INLINE SFloatPoint3& Position(){
      return _position;
   }
   //------------------------------------------------------------
   // <T>����������</T>
   MO_INLINE SFloatVector3& Direction(){
      return _direction;
   }
   //------------------------------------------------------------
   // <T>���ͶӰ�任��</T>
   MO_INLINE FProjection* Projection(){
      return _projection;
   }
   //------------------------------------------------------------
   // <T>����ͶӰ�任��</T>
   MO_INLINE void SetProjection(FProjection* pProjection){
      _projection = pProjection;
   }
   //------------------------------------------------------------
   // <T>��ñ任����</T>
   MO_INLINE FViewport* Viewport(){
      return _viewport;
   }
   //------------------------------------------------------------
   // <T>���ñ任����</T>
   MO_INLINE void SetViewport(FViewport* pViewport){
      _viewport = pViewport;
   }
public:
   void DoWalk(TFloat value);
   void DoStrafe(TFloat value);
   void DoFly(TFloat value);
   void DoYaw(TFloat angle);
   void DoPitch(TFloat angle);
   void LookAt(TFloat x, TFloat y, TFloat z);
public:
   TResult UpdateFrustum();
   TResult Update();
public:
   void Transform();
   TCharC* ToString();
};
//------------------------------------------------------------
typedef MO_FG_DECLARE FObjects<FCamera*> FCameraCollection;

//============================================================
// <T>�������������</T>
//============================================================
class MO_FG_DECLARE FOrthoCamera : public FCamera
{
   MO_CLASS_DECLARE_INHERITS(FOrthoCamera, FCamera);
public:
   FOrthoCamera();
   MO_ABSTRACT ~FOrthoCamera();
};

//============================================================
// <T>͸�Ӿ��������</T>
//============================================================
class MO_FG_DECLARE FPerspectiveCamera : public FCamera
{
   MO_CLASS_DECLARE_INHERITS(FPerspectiveCamera, FCamera);
public:
   FPerspectiveCamera();
   MO_ABSTRACT ~FPerspectiveCamera();
public:
};

MO_NAMESPACE_END

//************************************************************
#endif // __MO_FG_CAMERA_H__
