#include "MoE2Display.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>�������λͼ����</T>
//============================================================
FTailDisplay2d::FTailDisplay2d(){
   _optionTail = EFalse;
   MO_CLEAR(_pTailController);
}

//============================================================
// <T>��������λͼ����</T>
//============================================================
FTailDisplay2d::~FTailDisplay2d(){
   MO_DELETE(_pTailController);
}

//============================================================
// <T>�����Ƿ�ʹ�ø��١�</T>
//
// @param value �Ƿ�ʹ��
// @return ������
//============================================================
TResult FTailDisplay2d::SetOptionTail(TBool value){
   _optionTail = value;
   if(_optionTail){
      if(_pTailController == NULL){
         _pTailController = MO_CREATE(FTailController);
      }
      _pTailController->Reset();
   }
   return ESuccess;
}

//============================================================
// <T>������Ⱦ��Ϣ��</T>
//
// @param renderable ��Ⱦ��Ϣ
// @return ������
//============================================================
TResult FTailDisplay2d::CalculateRenderable(SRenderable& renderable){
   //if(_optionTail){
   //   TFsTailInfoVector& infos = _pTailController->Infos();
   //   TInt count = infos.Count();
   //   TFloat width = _size.width;
   //   TFloat height = _size.height;
   //   for(TInt n = 0; n < count; n++){
   //      STailInfo& info = infos.Get(n);
   //      SRenderableItem& item = renderable.Alloc();
   //      // ��������
   //      item.location.Assign(info.location);
   //      // ���óߴ�
   //      //item.size.Assign(info.size);
   //      item.size.Set(width, height);
   //      width *= 0.95f;
   //      height *= 0.95f;
   //      // ���÷���
   //      item.rotation.Assign(info.rotation);
   //      // ��������
   //      //item.coord.Assign(info.coord);
   //      item.coord.Assign(_coord);
   //      // ���ñ�����ɫ
   //      //item.groundColor.Assign(info.groundColor);
   //      item.groundColor.Assign(_groundColor);
   //      // ��������
   //      item.matrix.Identity();
   //      item.matrix.Translate(-_gravityCenter.x, -_gravityCenter.y, -_gravityCenter.z);
   //      item.matrix.Rotation(info.rotation.x, info.rotation.y, info.rotation.z);
   //   }
   //}else{
   //   SRenderableItem& item = renderable.Alloc();
   //   // ��������
   //   item.location.Assign(_location);
   //   // ���óߴ�
   //   item.size.Assign(_size);
   //   // ���÷���
   //   item.rotation.Assign(_rotation);
   //   // ��������
   //   item.coord.Assign(_coord);
   //   // ���ñ�����ɫ
   //   item.groundColor.Assign(_groundColor);
   //   // ��������
   //   item.matrix.Identity();
   //   item.matrix.Translate(-_gravityCenter.x, -_gravityCenter.y, -_gravityCenter.z);
   //   item.matrix.Rotation(_rotation.x, _rotation.y, _rotation.z);
   //   //renderable.matrix.UpdateForce();
   //}
   return ESuccess;
}

//============================================================
// <T>���Ӵ���</T>
//
// @param data ��������
// @return ������
//============================================================
TResult FTailDisplay2d::DoParticle(SParticleData& data){
   //// �ƶ�����
   //if(data.actionCd == EParticleAction_Move){
   //   if(_optionTail){
   //      STailInfo info;
   //      info.location.Assign(data.location);
   //      info.size.Assign(_size);
   //      info.rotation.Assign(data.rotation);
   //      _pTailController->Push(info);
   //   }else{
   //      _location.Assign(data.location);
   //      // _size.Assign(data.size);
   //      _rotation.Assign(data.rotation);
   //   }
   //}
   //// �ͷŴ���
   //if(data.actionCd == EParticleAction_Free){
   //   Free();
   //}
   return ESuccess;
}

MO_NAMESPACE_END
