#include "MoFrContent3dTexture.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FRs3dTextureConsole, FConsole);

//============================================================
// <T>������Դ3D�������̨��</T>
//============================================================
FRs3dTextureConsole::FRs3dTextureConsole(){
}

//============================================================
// <T>������Դ3D�������̨��</T>
//============================================================
FRs3dTextureConsole::~FRs3dTextureConsole(){
}

//============================================================
// <T>������Դ���������Դ����</T>
//
// @param resourceId ��Դ����
// @return ��Դ����
//============================================================
FRs3dTexture* FRs3dTextureConsole::Load(TCharC* pName){
   MO_CHECK(pName, return NULL);
   FAssetStream* pStream = RAssetManager::Instance().OpenAssetStreamFormat("asset:/texture/%s.ser", pName);
   MO_ERROR_CHECK(pStream, return NULL, "Open texture stream failure. (resource=%s)", pName);
   // ��������
   FRs3dTexture* pTexture = MO_CREATE(FRs3dTexture);
   pTexture->Unserialize(pStream);
   // �ͷ���Դ
   RAssetManager::Instance().CloseAssetStream(pStream);
   return pTexture;
}

//============================================================
// <T>������Դ���������Դ����</T>
//
// @param resourceId ��Դ����
// @return ��Դ����
//============================================================
FRs3dTexture* FRs3dTextureConsole::Find(TCharC* pName){
   FRs3dTexture* pTexture = _textures.Find(pName);
   if(pTexture == NULL){
      pTexture = Load(pName);
      _textures.Set(pName, pTexture);
   }
   return pTexture;
}

//============================================================
// <T>������Դ�������Դ����</T>
//
// @param resourceId ��Դ����
// @return ��Դ����
//============================================================
FRs3dTexture* FRs3dTextureConsole::Open(TCharC* pName){
   FRs3dTexture* pTexture = Find(pName);
   if(pTexture != NULL){
      pTexture->Open();
   }
   return pTexture;
}

//============================================================
// <T>������ݡ�</T>
//============================================================
void FRs3dTextureConsole::Clear(){
   _textures.Clear();
}

MO_NAMESPACE_END
