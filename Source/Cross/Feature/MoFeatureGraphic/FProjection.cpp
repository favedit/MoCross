#include "MoFgProjection.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FProjection, FInstance);

//============================================================
// <T>����ͶӰ��</T>
//============================================================
FProjection::FProjection(){
   _size.Set(800, 600);
   _angle = 30.0f;
   _fieldOfView = MO_GRAPHIC_DEGREE_RATE * _angle;
   _znear = 0.1f;
   _zfar = 1000.0f;
}

//============================================================
// <T>����ͶӰ��</T>
//============================================================
FProjection::~FProjection(){
}

//============================================================
// <T>��ý�����롣</T>
//
// @return �������
//============================================================
TFloat FProjection::Distance(){
   return _zfar - _znear;
}
      
//============================================================
// <T>��ýǶȡ�</T>
//
// @return �Ƕ�
//============================================================
TFloat FProjection::Radius(){
   TFloat aspect = (TFloat)_size.width / (TFloat)_size.height;
   TFloat fov = tan(MO_GRAPHIC_DEGREE_RATE * _angle * 0.5f);
   TFloat farY = _zfar * fov;
   TFloat farX = farY * aspect;
   return sqrt((farX * farX) + (farY * farY) + (_zfar * _zfar));
}
      
//============================================================
// <T>�������ݡ�</T>
//
// @param pProjection ����
//============================================================
TResult FProjection::Assign(FProjection* pProjection){
   // ������
   MO_CHECK(pProjection, return ENull);
   // ��������
   _size.Assign(pProjection->_size);
   _angle = pProjection->_angle;
   _fieldOfView = pProjection->_fieldOfView;
   _znear = pProjection->_znear;
   _zfar = pProjection->_zfar;
   // ��������
   return Update();
}
      
//============================================================
// <T>���¾���</T>
//============================================================
TResult FProjection::Update(){
   _fieldOfView = MO_GRAPHIC_DEGREE_RATE * _angle;
   SPerspectiveMatrix3d matrix;
   matrix.PerspectiveFieldOfViewLH(_fieldOfView, (TFloat)_size.width / (TFloat)_size.height, _znear, _zfar);
   _matrix.Assign(matrix);
   return ESuccess;
}

MO_NAMESPACE_END
