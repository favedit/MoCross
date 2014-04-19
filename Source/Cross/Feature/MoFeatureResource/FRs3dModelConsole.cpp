#include "MoFrContent3dModel.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FRs3dModelConsole, FConsole);

//============================================================
// <T>������Դ3Dģ�͹�������</T>
//============================================================
FRs3dModelConsole::FRs3dModelConsole(){
}

//============================================================
// <T>������Դ3Dģ�͹�������</T>
//============================================================
FRs3dModelConsole::~FRs3dModelConsole(){
}

//============================================================
// <T>������Դ���������Դ����</T>
//
// @param resourceId ��Դ����
// @return ��Դ����
//============================================================
FRs3dModel* FRs3dModelConsole::Load(TCharC* pName){
   FAssetStream* pStream = RAssetManager::Instance().OpenAssetStreamFormat("asset:/model/%s.ser", pName);
   MO_ERROR_CHECK(pStream, return NULL, "Open model stream failure. (resource_id=%s)", pName);
   // ��������
   FRs3dModel* pModel = MO_CREATE(FRs3dModel);
   pModel->Unserialize(pStream);
   // �ͷ���Դ
   RAssetManager::Instance().CloseAssetStream(pStream);
   return pModel;
}

//============================================================
// <T>������Դ���������Դ����</T>
//
// @param resourceId ��Դ����
// @return ��Դ����
//============================================================
FRs3dModel* FRs3dModelConsole::Find(TCharC* pName){
   FRs3dModel* pModel = _models.Find(pName);
   if(pModel == NULL){
      pModel = Load(pName);
      _models.Set(pName, pModel);
   }
   return pModel;
}

//============================================================
// <T>������Դ�������Դ����</T>
//
// @param resourceId ��Դ����
// @return ��Դ����
//============================================================
FRs3dModel* FRs3dModelConsole::Open(TCharC* pName){
   FRs3dModel* pModel = Find(pName);
   if(pModel != NULL){
      pModel->Open();
   }
   return pModel;
}

//============================================================
// <T>������ݡ�</T>
//============================================================
void FRs3dModelConsole::Clear(){
   _models.Clear();
}

MO_NAMESPACE_END
