#include "MoFrContent3dMaterial.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FRs3dMaterialConsole, FConsole);

//============================================================
// <T>������Դ3D���ʿ���̨��</T>
//============================================================
FRs3dMaterialConsole::FRs3dMaterialConsole(){
}

//============================================================
// <T>������Դ3D���ʿ���̨��</T>
//============================================================
FRs3dMaterialConsole::~FRs3dMaterialConsole(){
}

//============================================================
// <T>������Դ���Ʋ�����Դ����</T>
//
// @param pName ��Դ����
// @return ��Դ����
//============================================================
FRs3dMaterial* FRs3dMaterialConsole::Find(TCharC* pName){
   return _materials.Find(pName);
}

//============================================================
// <T>������Դ���ƻ����Դ����</T>
//
// @param pName ��Դ����
// @return ��Դ����
//============================================================
FRs3dMaterial* FRs3dMaterialConsole::Get(TCharC* pName){
   return _materials.Get(pName);
}

//============================================================
// <T>������ݡ�</T>
//============================================================
void FRs3dMaterialConsole::Clear(){
   _materials.Clear();
}

MO_NAMESPACE_END
