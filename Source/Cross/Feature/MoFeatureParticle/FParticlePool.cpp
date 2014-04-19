#include "MoFtParticle.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>�������ӻ���ء�</T>
//============================================================
FParticlePool::FParticlePool(){
   _typeCd = 0;
}

//============================================================
// <T>�������ӻ���ء�</T>
//============================================================
FParticlePool::~FParticlePool(){
}

//============================================================
// <T>�ռ�һ�����Ӷ���</T>
//
// @return ���Ӷ���
//============================================================
FParticle* FParticlePool::Alloc(){
   // ����Ƿ���ʣ��
   TBool hasFree = HasFreeItem();
   if(!hasFree){
      FParticle* pParticle = Create();
      Store(pParticle);
   }
   // �ռ�һ������
   return AllocFirst();
}

//============================================================
// <T>�ͷ�һ�����Ӷ���</T>
//
// @param pParticle ���Ӷ���
//============================================================
void FParticlePool::Free(FParticle* pParticle){
   FreeLast(pParticle);
}

MO_NAMESPACE_END
