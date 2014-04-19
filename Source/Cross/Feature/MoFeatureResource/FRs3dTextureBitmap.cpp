#include "MoFrContent3dTexture.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FRs3dTextureBitmap, FInstance);

//============================================================
// <T>������Դ3D����λͼ��</T>
//============================================================
FRs3dTextureBitmap::FRs3dTextureBitmap(){
   _textureCd = EContent3dTexture_Unknown;
   _samplerCd = EContent3dSampler_Unknown;
   _pData = MO_CREATE(FBytes);
}

//============================================================
// <T>������Դ3D����λͼ��</T>
//============================================================
FRs3dTextureBitmap::~FRs3dTextureBitmap(){
   MO_DELETE(_pData);
}

//============================================================
// <T>���������ﷴ���л���Ϣ����</T>
//
// @param pInput ������
// @return ������
//============================================================
TResult FRs3dTextureBitmap::Unserialize(IDataInput* pInput){
   MO_CHECK(pInput, return ENull);
   // ��ȡ����
   _textureCd = (EContent3dTexture)pInput->ReadUint8();
   _samplerCd = (EContent3dSampler)pInput->ReadUint8();
   // ��ȡλͼ
   _size.Unserialize16(pInput);
   TInt dataLength = sizeof(TUint32) * _size.Square();
   _pData->ForceLength(dataLength);
   pInput->Read(_pData->Memory(), dataLength);
   return ESuccess;
}

MO_NAMESPACE_END
