#include "MoEgEntity.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>�������ӻ���ء�</T>
//============================================================
FEntityPool::FEntityPool(){
   _typeCd = EEntityType_Unknown;
}

//============================================================
// <T>�������ӻ���ء�</T>
//============================================================
FEntityPool::~FEntityPool(){
}

//============================================================
// <T>�ռ�һ�����Ӷ���</T>
//
// @return ���Ӷ���
//============================================================
FEntity* FEntityPool::Alloc(){
   // ����Ƿ���ʣ��
   TBool hasFree = HasFreeItem();
   if(!hasFree){
      FEntity* pEntity = Create();
      Store(pEntity);
   }
   // �ռ�һ������
   return AllocFirst();
}

//============================================================
// <T>�ͷ�һ�����Ӷ���</T>
//
// @param pParticle ���Ӷ���
//============================================================
void FEntityPool::Free(FEntity* pEntity){
   FreeLast(pEntity);
}

MO_NAMESPACE_END
