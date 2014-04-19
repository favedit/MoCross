#include "MoFrContent3dTexture.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FRs3dTexture, FResource3d);

//============================================================
// <T>������Դ3D����</T>
//============================================================
FRs3dTexture::FRs3dTexture(){
}

//============================================================
// <T>������Դ3D����</T>
//============================================================
FRs3dTexture::~FRs3dTexture(){
   Close();
}

//============================================================
// <T>���������ﷴ���л���Ϣ����</T>
//
// @param pInput ������
// @return ������
//============================================================
TResult FRs3dTexture::Unserialize(IDataInput* pInput){
   MO_CHECK(pInput, return ENull);
   // ��ȡ����Ϣ
   FResource3d::Unserialize(pInput);
   // ��ȡ��λͼ����
   TInt count = pInput->ReadInt16();
   for(TInt n = 0; n < count; n++){
      FRs3dTextureBitmap* pBitmap = MO_CREATE(FRs3dTextureBitmap);
      pBitmap->Unserialize(pInput);
      _bitmaps.Push(pBitmap);
   }
   return ESuccess;
}

MO_NAMESPACE_END
