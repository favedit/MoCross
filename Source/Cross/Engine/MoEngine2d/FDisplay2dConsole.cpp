#include "MoE2Display.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>������ʾ�������̨��</T>
//============================================================
FDisplay2dConsole::FDisplay2dConsole(){
}

//============================================================
// <T>������ʾ�������̨��</T>
//============================================================
FDisplay2dConsole::~FDisplay2dConsole(){
}

//============================================================
// <T>�ռ�һ��ָ�����͵���ʾ����</T>
//
// @param typeCd ����
// @return ��ʾ����
//============================================================
FDisplay2d* FDisplay2dConsole::DisplayAlloc(TDisplayType typeCd){
   FDisplayPool* pPool = PoolFind(typeCd);
   MO_ASSERT(pPool);
   return (FDisplay2d*)pPool->Alloc();
}

//============================================================
// <T>�ͷ�һ��ָ�����͵���ʾ����</T>
//
// @return ��ʾ����
//============================================================
void FDisplay2dConsole::DisplayFree(FDisplay2d* pDisplay){
   TDisplayType typeCd = pDisplay->TypeCd();
   FDisplayPool* pPool = PoolFind(typeCd);
   MO_ASSERT(pPool);
   //return pPool->Free(pDisplay);
}

//============================================================
// <T>���ô���</T>
//============================================================
void FDisplay2dConsole::Setup(){
   _classFactory->Register("Picture", FPicture::Class());
   _classFactory->Register("Shape", FShape::Class());
   _classFactory->Register("Sprite", FSprite::Class());
   _classFactory->Register("Movie", FMovie::Class());
}

//============================================================
// <T>��û����</T>
//
// @param typecCd ����
// @return �����
//============================================================
FDisplayPool* FDisplay2dConsole::PoolFind(TDisplayType typeCd){
   //TInt count = _pPools->Count();
   //for(TInt n = 0; n < count; n++){
   //   FDisplayPool* pPool = _pPools->Get(n);
   //   if(pPool->TypeCd() == typeCd){
   //      return pPool;
   //   }
   //}
   return NULL;
}

//============================================================
// <T>�ͷŴ���</T>
//============================================================
TResult FDisplay2dConsole::Dispose(){
   return ESuccess;
}

MO_NAMESPACE_END
