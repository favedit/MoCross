#include "MoFrContent3dMaterial.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FRs3dMaterialTexture, FInstance);

//============================================================
// <T>������Դ3D��������</T>
//============================================================
FRs3dMaterialTexture::FRs3dMaterialTexture(){
   _samplerCd = EContent3dSampler_Unknown;
}

//============================================================
// <T>������Դ3D��������</T>
//============================================================
FRs3dMaterialTexture::~FRs3dMaterialTexture(){
}

//============================================================
// <T>���������ﷴ���л���Ϣ����</T>
//
// @param pInput ������
// @return ������
//============================================================
TResult FRs3dMaterialTexture::Unserialize(IDataInput* pInput){
   MO_CHECK(pInput, return ENull);
   _samplerCd = (EContent3dSampler)pInput->ReadUint8();
   _textureName.UnserializeAutomatic(pInput);
   return ESuccess;
}

MO_NAMESPACE_END
