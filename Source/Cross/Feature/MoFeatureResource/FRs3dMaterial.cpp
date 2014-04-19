#include "MoFrContent3dMaterial.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FRs3dMaterial, FResource3d);

//============================================================
// <T>������Դ3D���ʡ�</T>
//============================================================
FRs3dMaterial::FRs3dMaterial(){
}

//============================================================
// <T>������Դ3D���ʡ�</T>
//============================================================
FRs3dMaterial::~FRs3dMaterial(){
}

//============================================================
// <T>���������ﷴ���л���Ϣ����</T>
//
// @param pInput ������
// @return ������
//============================================================
TResult FRs3dMaterial::Unserialize(IDataInput* pInput){
   MO_CHECK(pInput, return ENull);
   // ��ȡ����Ϣ
   FResource3d::Unserialize(pInput);
   _info.Unserialize(pInput);
   // ��ȡ������
   TInt count = pInput->ReadInt8();
   for(TInt n = 0; n < count; n++){
      FRs3dMaterialTexture* pTexture = FRs3dMaterialTexture::InstanceCreate();
      pTexture->Unserialize(pInput);
      _textures.Push(pTexture);
   }
   return ESuccess;
}
      
//============================================================
// <T>�������ݡ�</T>
//============================================================
void FRs3dMaterial::Reset(){
   _info.Reset();
}

MO_NAMESPACE_END
