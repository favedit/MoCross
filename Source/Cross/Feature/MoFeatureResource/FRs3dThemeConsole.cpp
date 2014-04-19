#include "MoFrContent3dMaterial.h"
#include "MoFrContent3dTheme.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>������Դ3D�������̨��</T>
//============================================================
FRs3dThemeConsole::FRs3dThemeConsole(){
}

//============================================================
// <T>������Դ3D�������̨��</T>
//============================================================
FRs3dThemeConsole::~FRs3dThemeConsole(){
}

//============================================================
// <T>���Ĭ�����⡣</T>
//
// @return ����
//============================================================
FRs3dTheme* FRs3dThemeConsole::DefaultTheme(){
   return NULL;
}

//============================================================
// <T>������Դ��Ų������⡣</T>
//
// @param resourceId ��Դ���
// @return ����
//============================================================
FRs3dTheme* FRs3dThemeConsole::Find(TResourceId resourceId){
   return NULL;
}

//============================================================
// <T>���������ﷴ���л���Ϣ���ݡ�</T>
//
// @param pInput ������
// @return ������
//============================================================
TResult FRs3dThemeConsole::Unserialize(IDataInput* pInput){
   MO_CHECK(pInput, return ENull);
   GRs3dMaterialPtrDictionary& materials = RResource3dManager::Instance().MaterialConsole()->Materials();
   TInt count = pInput->ReadInt32();
   for(TInt n = 0; n < count; n++){
      FRs3dMaterial* pMaterial = MO_CREATE(FRs3dMaterial);
      pMaterial->Unserialize(pInput);
      materials.Set(pMaterial->Name(), pMaterial);
   }
   MO_DEBUG("Unserial theme material success. (material_count=%d)", count);
   return ESuccess;
}

//============================================================
// <T>�򿪴���</T>
//
// @param pCode ����
// @return ������
//============================================================
TResult FRs3dThemeConsole::Open(TCharC* pCode){
   FAssetStream* pStream = RAssetManager::Instance().OpenAssetStream(pCode);
   MO_ERROR_CHECK(pStream, return EFailure, "Open theme failure. (code=%s)", pCode);
   Unserialize(pStream);
   RAssetManager::Instance().CloseAssetStream(pStream);
   return ESuccess;
}

//============================================================
// <T>������ݡ�</T>
//============================================================
TResult FRs3dThemeConsole::Clear(){
   return ESuccess;
}

MO_NAMESPACE_END
