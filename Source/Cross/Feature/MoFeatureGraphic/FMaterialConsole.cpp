#include "MoFgMaterial.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>������ʿ���̨��</T>
//============================================================
FMaterialConsole::FMaterialConsole(){
   _pMaterials = MO_CREATE(FMaterialCollection);
}

//============================================================
// <T>�������ʿ���̨��</T>
//============================================================
FMaterialConsole::~FMaterialConsole(){
   MO_DELETE(_pMaterials);
}

////============================================================
//// <T>����һ��ͼƬ����һ��λͼ���ʡ�</T>
////
//// @param pBitmap λͼ
//// @return λͼ����
////============================================================
//FBitmapMaterial* FMaterialConsole::BitmapMaterialFind(FBitmap* pBitmap){
//   MO_ASSERT(pBitmap);
//   TInt count = _pBitmapMaterials->Count();
//   for(TInt n = 0; n < count; n++){
//      FBitmapMaterial* pMaterial = (FBitmapMaterial*)_pBitmapMaterials->Get(n);
//      if(pMaterial->Bitmap() == pBitmap){
//         return pMaterial;
//      }
//   }
//   return NULL;
//}
//
////============================================================
//// <T>����һ��ͼƬͬ��һ��λͼ���ʡ�</T>
////
//// @param pBitmap λͼ
//// @return λͼ����
////============================================================
//FBitmapMaterial* FMaterialConsole::BitmapMaterialSync(FBitmap* pBitmap){
//   MO_ASSERT(pBitmap);
//   // ���Ҳ���
//   FBitmapMaterial* pMaterial = BitmapMaterialFind(pBitmap);
//   // ��������
//   if(pMaterial == NULL){
//      pMaterial = MO_CREATE(FBitmapMaterial);
//      pMaterial->SetBitmap(pBitmap);
//      pMaterial->Setup();
//      _pBitmapMaterials->Push(pMaterial);
//   }
//   return pMaterial;
//}

MO_NAMESPACE_END
