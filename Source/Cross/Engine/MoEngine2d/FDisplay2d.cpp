#include "MoE2Display.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FDisplay2d, FRenderable);

//============================================================
// <T>������ʾ����</T>
//============================================================
FDisplay2d::FDisplay2d(){
   _typeCd = 0;
}

//============================================================
// <T>������ʾ����</T>
//============================================================
FDisplay2d::~FDisplay2d(){
}

//============================================================
// <T>���ò��ʡ�</T>
//
// @param pMaterial ����
// @return ������
//============================================================
TResult FDisplay2d::SetMaterial(FMaterial* pMaterial){
   _pMaterial = pMaterial;
   return ESuccess;
}

//============================================================
// <T>������Ⱦ��Ϣ��</T>
//
// @param renderable ��Ⱦ��Ϣ
// @return ������
//============================================================
TResult FDisplay2d::CalculateRenderable(SRenderable& renderable){
   SRenderableItem& item = renderable.Alloc();
   //// ��������
   //item.location.Assign(_location);
   //// ���óߴ�
   //item.size.Assign(_size);
   //// ���÷���
   //item.rotation.Assign(_rotation);
   //// ��������
   //item.coord.Assign(_coord);
   //// ���ñ�����ɫ
   //item.groundColor.Assign(_groundColor);
   //// ��������
   //item.matrix.Identity();
   //item.matrix.Translate(-_gravityCenter.x, -_gravityCenter.y, -_gravityCenter.z);
   //item.matrix.Rotation(_rotation.x, _rotation.y, _rotation.z);
   //renderable.matrix.UpdateForce();
   return ESuccess;
}

//============================================================
// <T>���Ӵ���</T>
//
// @param data ��������
// @return ������
//============================================================
TResult FDisplay2d::DoParticle(SParticleData& data){
   // �ƶ�����
   //if(data.actionCd == EParticleAction_Move){
   //   _location.Assign(data.location);
   //   // _size.Assign(data.size);
   //   _rotation.Assign(data.rotation);
   //}
   //// �ͷŴ���
   //if(data.actionCd == EParticleAction_Free){
   //   Free();
   //}
   return ESuccess;
}

//============================================================
// <T>�ͷŴ���</T>
//
// @return ������
//============================================================
TResult FDisplay2d::Free(){
   // ���븸���
   //RemoveFromParent();
   // �ͷ��Լ�
   RDisplay2dManager::Instance().DisplayFree(this);
   return ESuccess;
}

MO_NAMESPACE_END
