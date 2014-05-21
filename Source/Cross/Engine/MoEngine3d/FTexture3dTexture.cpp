#include "MoE3Texture.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FTexture3dTexture, FInstance);

//============================================================
// <T>������Դ3D����</T>
//============================================================
FTexture3dTexture::FTexture3dTexture(){
   _pBitmaps = MO_CREATE(FTexture3dBitmapCollection);
}

//============================================================
// <T>������Դ3D����</T>
//============================================================
FTexture3dTexture::~FTexture3dTexture(){
   MO_DELETE(_pBitmaps);
}

//============================================================
// <T>���ݴ������λͼ��</T>
//
// @param pCode ����
// @return λͼ
//============================================================
FTexture3dBitmap* FTexture3dTexture::FindByCode(TCharC* pCode){
   TInt count = _pBitmaps->Count();
   for(TInt n = 0; n < count; n++){
      FTexture3dBitmap* pBitmap = _pBitmaps->Get(n);
      if(pBitmap != NULL){
         FRs3dTextureBitmap* pBitmapResource = pBitmap->Resource();
         if(pBitmapResource != NULL){
            if(pBitmapResource->IsCode(pCode)){
               return pBitmap;
            }
         }
      }
   }
   return NULL;
}

//============================================================
// <T>���������ﷴ���л���Ϣ����</T>
//
// @param pInput ������
// @return ������
//============================================================
TResult FTexture3dTexture::LoadResource(FRs3dTexture* pResource){
   MO_CHECK(pResource, return ENull);
   _pResource = pResource;
   // ��ȡ��λͼ����
   GRs3dTextureBitmapPtrs& bitmapResources = pResource->Bitmaps();
   TInt count = bitmapResources.Count();
   for(TInt n = 0; n < count; n++){
      FRs3dTextureBitmap* pBitmapResource = bitmapResources.Get(n);
      // ����ͼ��
      FTexture3dBitmap* pBitmap = FTexture3dBitmap::InstanceCreate();
      pBitmap->LoadResource(pBitmapResource);
      _pBitmaps->Push(pBitmap);
   }
   return ESuccess;
}

//============================================================
// <T>�򿪴���</T>
//
// @return ������
//============================================================
TResult FTexture3dTexture::Open(){
   TInt count = _pBitmaps->Count();
   for(TInt n = 0; n < count; n++){
      FTexture3dBitmap* pBitmap = _pBitmaps->Get(n);
      MO_CHECK(pBitmap, continue);
      pBitmap->Open();
   }
   return ESuccess;
}

//============================================================
// <T>�رմ���</T>
//
// @return ������
//============================================================
TResult FTexture3dTexture::Close(){
   TInt count = _pBitmaps->Count();
   for(TInt n = 0; n < count; n++){
      GPtr<FTexture3dBitmap> bitmap = _pBitmaps->Get(n);
      bitmap->Close();
      FTexture3dBitmap::InstanceDelete(bitmap);
   }
   return ESuccess;
}

MO_NAMESPACE_END
