#include "MoE2Display.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>������ʾ�������̨��</T>
//============================================================
FDisplay2dConsole::FDisplay2dConsole(){
   _pPools = MO_CREATE(FDisplayPoolCollection);
}

//============================================================
// <T>������ʾ�������̨��</T>
//============================================================
FDisplay2dConsole::~FDisplay2dConsole(){
   MO_DELETE(_pPools);
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
   // ע��ͼƬ�����
   FPicturePool* pPicturePool = MO_CREATE(FPicturePool);
   PoolRegister(pPicturePool);
   // ע����״�����
   FShapePool* pShapePool = MO_CREATE(FShapePool);
   PoolRegister(pShapePool);
   // ע�ᾫ�黺���
   FSpritePool* pSpritePool = MO_CREATE(FSpritePool);
   PoolRegister(pSpritePool);
   // ע�ᶯ�������
   FMoviePool* pMoviePool = MO_CREATE(FMoviePool);
   PoolRegister(pMoviePool);
}

//============================================================
// <T>��û����</T>
//
// @param typecCd ����
// @return �����
//============================================================
FDisplayPool* FDisplay2dConsole::PoolFind(TDisplayType typeCd){
   TInt count = _pPools->Count();
   for(TInt n = 0; n < count; n++){
      FDisplayPool* pPool = _pPools->Get(n);
      if(pPool->TypeCd() == typeCd){
         return pPool;
      }
   }
   return NULL;
}

//============================================================
// <T>ע�Ỻ��ء�</T>
//
// @param pPool �����
//============================================================
void FDisplay2dConsole::PoolRegister(FDisplayPool* pPool){
   _pPools->Push(pPool);
}

//============================================================
// <T>ע������ء�</T>
//
// @param pPool �����
//============================================================
void FDisplay2dConsole::PoolUnregister(FDisplayPool* pPool){
   _pPools->Remove(pPool);
}

//============================================================
// <T>�ͷŴ���</T>
//============================================================
TResult FDisplay2dConsole::Dispose(){
   return ESuccess;
}

MO_NAMESPACE_END
