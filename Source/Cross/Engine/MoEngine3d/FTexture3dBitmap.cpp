#include "MoE3Texture.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FTexture3dBitmap, FInstance);

//============================================================
// <T>������Դ3D����λͼ��</T>
//============================================================
FTexture3dBitmap::FTexture3dBitmap(){
   MO_CLEAR(_pResource);
}

//============================================================
// <T>������Դ3D����λͼ��</T>
//============================================================
FTexture3dBitmap::~FTexture3dBitmap(){
}

//============================================================
// <T>����������Դ��</T>
//
// @param pResource ��Դ
// @return ������
//============================================================
TResult FTexture3dBitmap::LoadResource(FRs3dTextureBitmap* pResource){
   MO_CHECK(pResource, return ENull);
   _pResource = pResource;
   return ESuccess;
}

//============================================================
// <T>�򿪴���</T>
//
// @return ������
//============================================================
TResult FTexture3dBitmap::Open(){
   FRenderDevice* pRenderDevice = RDeviceManager::Instance().Find<FRenderDevice>();
   // ��ȡλͼ
   ERenderTexture textureCd = (ERenderTexture)_pResource->TextureCd();
   TCharC* pCode = _pResource->Code();
   FBytes* pData = _pResource->Data();
   SIntSize2& size = _pResource->Size();
   // ��������
   if(textureCd == ERenderTexture_Flat2d){
      _renderTexture = pRenderDevice->CreateFlatTexture();
      _renderTexture->Size().Assign(size);
   }else if(textureCd == ERenderTexture_Cube){
      _renderTexture = pRenderDevice->CreateCubeTexture();
      _renderTexture->Size().Set(size.width, size.width);
   }else{
      MO_FATAL_UNSUPPORT();
   }
   //_renderTexture->SetSamplerCd(pCode);
   _renderTexture->SetFilterCd(ERenderTextureFilter_Linear);
   _renderTexture->Setup();
   // �ϴ�����
   _renderTexture->Upload(pData->MemoryC(), pData->Length());
   return ESuccess;
}

//============================================================
// <T>�رմ򿪴���</T>
//
// @return ������
//============================================================
TResult FTexture3dBitmap::Close(){
   _renderTexture = NULL;
   return ESuccess;
}

MO_NAMESPACE_END
