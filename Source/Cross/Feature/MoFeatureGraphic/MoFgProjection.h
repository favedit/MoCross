#ifndef __MO_FG_PROJECTION_H__
#define __MO_FG_PROJECTION_H__
//************************************************************

#ifndef __MO_FG_COMMON_H__
#include "MoFgCommon.h"
#endif // __MO_FG_COMMON_H__

#define MO_DISPLAY3d_CONER_COUNT       8
#define MO_DISPLAY3d_CONER_POINT_COUNT 24

MO_NAMESPACE_BEGIN

//============================================================
// <T>ͶӰ��</T>
//============================================================
class MO_FG_DECLARE FProjection : public FInstance
{
   MO_CLASS_DECLARE_INHERITS(FProjection, FInstance);
protected:
   // ��С
   SIntSize2 _size;
   // �Ƕ�
   TFloat _angle;
   // �н�
   TFloat _fieldOfView;
   // ����
   TFloat _scale;
   // ��ƽ��
   TFloat _znear;
   // Զƽ��
   TFloat _zfar;
   // �任����
   SFloatMatrix3d _matrix;
public:
   FProjection();
   MO_ABSTRACT ~FProjection();
public:
   //------------------------------------------------------------
   // <T>��ô�С��</T>
   MO_INLINE SIntSize2& Size(){
      return _size;
   }
   //------------------------------------------------------------
   // <T>��ýǶȡ�</T>
   MO_INLINE TFloat Angle(){
      return _angle;
   }
   //------------------------------------------------------------
   // <T>���ýǶȡ�</T>
   MO_INLINE void SetAngle(TFloat angle){
      _angle = angle;
   }
   //------------------------------------------------------------
   // <T>��ý�ƽ�档</T>
   MO_INLINE TFloat Znear(){
      return _znear;
   }
   //------------------------------------------------------------
   // <T>���ý�ƽ�档</T>
   MO_INLINE void SetZnear(TFloat znear){
      _znear = znear;
   }
   //------------------------------------------------------------
   // <T>���Զƽ�档</T>
   MO_INLINE TFloat Zfar(){
      return _zfar;
   }
   //------------------------------------------------------------
   // <T>����Զƽ�档</T>
   MO_INLINE void SetZfar(TFloat zfar){
      _zfar = zfar;
   }
   //------------------------------------------------------------
   // <T>���ý�ƽ���Զƽ�档</T>
   MO_INLINE void SetZ(TFloat znear, TFloat zfar){
      _znear = znear;
      _zfar = zfar;
   }
   //------------------------------------------------------------
   // <T>��ñ任����</T>
   MO_INLINE SFloatMatrix3d& Matrix(){
      return _matrix;
   }
public:
   TFloat Distance();
   TFloat Radius();
public:
   TResult Assign(FProjection* pProjection);
   TResult Update();
};
//------------------------------------------------------------
typedef MO_FG_DECLARE FObjects<FProjection*> FProjectionCollection;

//============================================================
// <T>��������ͶӰ�ӽǡ�</T>
//============================================================
class MO_FG_DECLARE FOrthoProjection : public FProjection
{
   MO_CLASS_DECLARE_INHERITS(FOrthoProjection, FProjection);
public:
   FOrthoProjection();
   MO_ABSTRACT ~FOrthoProjection();
};

//============================================================
// <T>͸�Ӿ���ͶӰ�ӽǡ�</T>
//============================================================
class MO_FG_DECLARE FPerspectiveProjection : public FProjection
{
   MO_CLASS_DECLARE_INHERITS(FPerspectiveProjection, FProjection);
public:
   FPerspectiveProjection();
   MO_ABSTRACT ~FPerspectiveProjection();
};

MO_NAMESPACE_END

//************************************************************
#endif // __MO_FG_PROJECTION_H__
