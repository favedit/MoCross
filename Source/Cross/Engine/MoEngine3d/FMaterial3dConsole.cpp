#include "MoE3Material.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>����ʵ��3D���ʹ�������</T>
//============================================================
FMaterial3dConsole::FMaterial3dConsole(){
}

//============================================================
// <T>����ʵ��3D���ʹ�������</T>
//============================================================
FMaterial3dConsole::~FMaterial3dConsole(){
}

//============================================================
// <T>�������ƻ�ò���ʵ����</T>
//
// @param pName ����
// @return ����ʵ��
//============================================================
FMaterial3d* FMaterial3dConsole::Load(TCharC* pName){
   MO_CHECK(pName, return NULL);
   FMaterial3d* pMaterial = _materials.Find(pName);
   if(pMaterial == NULL){
      // �����Դ
      FRs3dMaterialConsole* pRsMaterialConsole = RResource3dManager::Instance().MaterialConsole();
      FRs3dMaterial* pRsMaterial = pRsMaterialConsole->Find(pName);
      MO_CHECK(pRsMaterial, return NULL);
      // ����ʵ��
      pMaterial = FMaterial3d::InstanceCreate();
      pMaterial->SetName(pName);
      pMaterial->LoadResource(pRsMaterial);
      _materials.Set(pName, pMaterial);
   }
   return pMaterial;
}

MO_NAMESPACE_END
