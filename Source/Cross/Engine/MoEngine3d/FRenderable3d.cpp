#include "MoE3Display.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FRenderable3d, FRenderable);

//============================================================
// <T>�������Ⱦ3D����</T>
//============================================================
FRenderable3d::FRenderable3d(){
}

//============================================================
// <T>��������Ⱦ3D����</T>
//============================================================
FRenderable3d::~FRenderable3d(){
}

//============================================================
// <T>���Ҷ�����</T>
//
// @return ����
//============================================================
FAnimation3d* FRenderable3d::FindAnimation(){
   MO_FATAL_UNSUPPORT();
   return NULL;
}

//============================================================
// <T>���ҹ켣��</T>
//
// @return �켣
//============================================================
FRs3dTrack* FRenderable3d::FindTrack(){
   MO_FATAL_UNSUPPORT();
   return NULL;
}

//============================================================
// <T>������Ⱦ��Ϣ��</T>
//
// @param renderable ��Ⱦ��Ϣ
// @return ������
//============================================================
TResult FRenderable3d::CalculateRenderable(SRenderable& renderable){
   SRenderableItem& item = renderable.Alloc();
   // ��������
   //item.location.Assign(_location);
   //item.size.Assign(_size);
   //item.coord.Assign(_coord);
   //item.groundColor.Assign(_groundColor);
   // �������и�����
   //FComponent* pComponent = _pParent;
   //while(pComponent != NULL){
   //   if(pComponent->IsObject(EComponent_Drawable)){
   //      FDrawable* pDrawable = (FDrawable*)pComponent;
   //      renderable.matrix.Append(pDrawable->Matrix());
   //   }
   //   pComponent = pComponent->Parent();
   //}
   return ESuccess;
}

//============================================================
// <T>������־���ϡ�</T>
//============================================================
TResult FRenderable3d::BuildFlags(){
   return ESuccess;
}

MO_NAMESPACE_END
