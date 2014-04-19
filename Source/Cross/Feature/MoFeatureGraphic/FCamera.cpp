#include "MoFgCamera.h"

MO_NAMESPACE_BEGIN
   
MO_CLASS_IMPLEMENT_INHERITS(FCamera, FInstance);

//============================================================
// <T>���������</T>
//============================================================
FCamera::FCamera(){
   _axisUp.Set(0.0f, 1.0f, 0.0f);
}

//============================================================
// <T>���������</T>
//============================================================
FCamera::~FCamera(){
}

//============================================================
// <T>��ǰ/����ƶ�</T>
//
// @param value ����
//============================================================
void FCamera::DoWalk(TFloat value){
   _position.x += _direction.x * value;
   _position.z += _direction.z * value;
}
      
//============================================================
// <T>����/����ƽ��</T>
//
// @param value ����
//============================================================
void FCamera::DoStrafe(TFloat value){
   _position.x += _axisY.x * value;
   _position.z += _axisY.z * value;
}
      
//============================================================
// <T>����/�����ƶ�</T>
//
// @param value ����
//============================================================
void FCamera::DoFly(TFloat value){
   _position.y += value;
}
      
//============================================================
// <T>����/������ת</T>
//
// @param angle �Ƕ�
//============================================================
void FCamera::DoYaw(TFloat angle){
   // ��תY��
   SFloatMatrix3d matrix;
   matrix.RotationY(angle);
   // ��ת����
   SFloatVector3 direction = _direction;
   direction.Normalize();
   _direction = matrix.TransformVector3(direction);
   _direction.Normalize();
}
      
//============================================================
// <T>����/������ת</T>
//
// @param angle �Ƕ�
//============================================================
void FCamera::DoPitch(TFloat angle){
   // ��תX��
   SFloatMatrix3d matrix;
   //matrix.Rotation();
   //matrix.Rotation() .appendRotation(angle, new Vector3D(_axisX.x, _axisX.y, _axisX.z));
   // ��ת����
   //var dx:Number = direction.x;
   //var dy:Number = direction.y;
   //var dz:Number = direction.z;
   //var d:Vector3D = new Vector3D(dx, dy, dz);
   //d = m.transformVector(d);
   //direction.set(d.x, d.y, d.z);
   // ������¼н�
   //var dc:SFloatVector3 = new SFloatVector3(d.x, 0, d.z);
   //var angle:Number = Math.abs(Math.acos(direction.dot(dc)));
   //if(angle > RMath.DegreeRate * 88){
   //   direction.set(dx, dy, dz);
   //}
   //direction.normalize();
}
      
//============================================================
// <T>����Ŀ�ꡣ</T>
//============================================================
void FCamera::LookAt(TFloat x, TFloat y, TFloat z){
   _direction.Set(x - _position.x, y - _position.y, z - _position.z);
   _direction.Normalize();
}
      
//============================================================
// <T>�����ӽ�����Ϣ��</T>
//============================================================
TResult FCamera::UpdateFrustum(){
   //MO_CHECK(_pProjection, return ENull);
   //SIntSize2& size = _pProjection->Size();
   //_frustum.Update(_pProjection->Angle(), (TFloat)size.width, (TFloat)size.height,
   //      _pProjection->Znear(), _pProjection->Zfar(),
   //      _centerFront, _centerBack, _matrix);
   return ESuccess;
}
      
//============================================================
// <T>���������Ϣ��</T>
// <P>1. ���¿ռ����</P>
// <P>2. ����Ŀ��㡣</P>
//============================================================
TResult FCamera::Update(){
   // ����������
   _axisZ.Assign(_direction);
   _axisZ.Normalize();
   _axisUp.Cross(_axisX, _axisZ);
   _axisX.Normalize();
   _axisZ.Cross(_axisY, _axisX);
   _axisY.Normalize();
   // �������
   TFloat* pData = _matrix.Memory();
   pData[ 0] = _axisX.x;
   pData[ 1] = _axisY.x;
   pData[ 2] = _axisZ.x;
   pData[ 3] = 0.0;
   pData[ 4] = _axisX.y;
   pData[ 5] = _axisY.y;
   pData[ 6] = _axisZ.y;
   pData[ 7] = 0.0;
   pData[ 8] = _axisX.z;
   pData[ 9] = _axisY.z;
   pData[10] = _axisZ.z;
   pData[11] = 0.0;
   pData[12] = -_axisX.DotPoint3(_position);
   pData[13] = -_axisY.DotPoint3(_position);
   pData[14] = -_axisZ.DotPoint3(_position);
   pData[15] = 1.0;
   return ESuccess;
}
      
//============================================================
// <T>���������Ϣ��</T>
//============================================================
void FCamera::Transform(){
   //            var lookAt:Vector3D = new Vector3D();
   //            lookAt.setTo(cm.direction.x, cm.direction.y, cm.direction.z);
   //            lookAt.normalize();
   //            
   //            var adjustLookAt:Vector3D = new Vector3D();
   //            adjustLookAt.setTo(cm.direction.x, 0, cm.direction.z);
   //            adjustLookAt.normalize();
   //
   //            var dot:Number = 0;
   //            var dx:Number = 0;
   //            if(!fixY){
   //               dot = adjustLookAt.dotProduct(lookAt);
   //               dx = Math.acos(dot);
   //               dx = dx / Math.PI * 180;
   //            }
   //            dot = Vector3D.Z_AXIS.dotProduct(adjustLookAt);
   //            var dy:Number = Math.acos(dot);
   //            dy = dy / Math.PI * 180;
   //            var m:SGeMatrix3D = new SGeMatrix3D();
   //            m.appendScale(50, 50, 50);
   //            if(lookAt.y <= 0){
   //               m.appendRotation(dx, Vector3D.X_AXIS);
   //            }else{
   //               m.appendRotation(dx, axisLeft);
   //            }
   //            if(adjustLookAt.x <= 0){
   //               m.appendRotation(dy, Vector3D.Y_AXIS);
   //            }else{
   //               m.appendRotation(dy, axisDown);
   //            }
   //            if(cm.axisUp.y < 0){
   //               m.appendRotation(Math.PI, Vector3D.Z_AXIS);
   //            }
   //            m.appendTranslation(matrix.position.x, matrix.position.y, matrix.position.z);
   //            binder.writeMatrix3x4Data(m.rawData);
   //            //m.appendRotation(90, Vector3D.Y_AXIS);
   //            m.prepend(matrix);
   //var mi:SGeMatrix3D = new SGeMatrix3D();
   //var d:Vector3D = new Vector3D();
   //d.x = matrix.position.x - p.camera.position.x;
   //d.y = matrix.position.y - p.camera.position.y;
   //d.z = matrix.position.z - p.camera.position.z;
   //d.setTo(p.camera.direction.x, p.camera.direction.y, p.camera.direction.z);
   //d.normalize();
   //matrix.appendRotation(-p.camera.direction.x, Vector3D.X_AXIS);
   //matrix.appendRotation(-p.camera.direction.y, Vector3D.Y_AXIS);
   //matrix.appendRotation(-p.camera.direction.z, Vector3D.Z_AXIS);
   //matrix.identity();
   //matrix.appendRotation(10, Vector3D.Y_AXIS, d);
}
      
//============================================================
// <T>���������Ϣ��</T>
//============================================================
TCharC* FCamera::ToString(){
   return "Camera";
}

MO_NAMESPACE_END
