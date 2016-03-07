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
   TFsPath path;
   path.AppendFormat(TC("asset:/texture/%s.ser"), pName);
   // ��������
   FRs3dTexture* pTexture = FRs3dTexture::InstanceCreate();
   FAssetStream* pStream = RAssetManager::Instance().OpenAssetStream(path);
   MO_ERROR_CHECK(pStream, return NULL, TC("Open texture stream failure. (resource=%s)"), pName);
   // ��������
   pTexture->Unserialize(pStream);
   // �ͷ���Դ
   RAssetManager::Instance().CloseAssetStream(pStream);
   // ����������
   //FContentLoader* pLoader = FContentLoader::InstanceCreate();
   //pLoader->SetContent(pTexture);
   //RContentManager::Instance().PushLoader(pLoader);
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
