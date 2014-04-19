#include "MoE3Texture.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>����ʵ��3D�����������</T>
//============================================================
FTexture3dConsole::FTexture3dConsole(){
   _pTextures = MO_CREATE(FTexture3dTextureDictionary);
}

//============================================================
// <T>����ʵ��3D�����������</T>
//============================================================
FTexture3dConsole::~FTexture3dConsole(){
   MO_DELETE(_pTextures);
}

//============================================================
// <T>�������Ʋ�������ʵ����</T>
//
// @param pName ����
// @return ����ʵ��
//============================================================
FTexture3dTexture* FTexture3dConsole::Find(TCharC* pName){
   MO_CHECK(pName, return NULL);
   FTexture3dTexture* pTexture = _pTextures->Find(pName);
   return pTexture;
}

//============================================================
// <T>�������Ƽ�������ʵ����</T>
//
// @param pName ����
// @return ����ʵ��
//============================================================
FTexture3dTexture* FTexture3dConsole::Load(TCharC* pName){
   MO_CHECK(pName, return NULL);
   FTexture3dTexture* pTexture = _pTextures->Find(pName);
   if(pTexture == NULL){
      // �����Դ
      FRs3dTextureConsole* pRsTextureConsole = RResource3dManager::Instance().TextureConsole();
      FRs3dTexture* pRsTexture = pRsTextureConsole->Find(pName);
      // ����ʵ��
      pTexture = FTexture3dTexture::InstanceCreate();
      pTexture->LoadResource(pRsTexture);
      pTexture->Open();
      _pTextures->Set(pName, pTexture);
   }
   return pTexture;
}

MO_NAMESPACE_END
