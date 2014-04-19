#include "MoFmCore.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>�������ӻ���ء�</T>
//============================================================
FUiControlPool::FUiControlPool(){
   _typeCd = EControlType_Unknown;
}

//============================================================
// <T>�������ӻ���ء�</T>
//============================================================
FUiControlPool::~FUiControlPool(){
}

//============================================================
// <T>�ռ�һ�����Ӷ���</T>
//
// @return ���Ӷ���
//============================================================
FUiControl* FUiControlPool::Alloc(){
   // ����Ƿ���ʣ��
   TBool hasFree = HasFreeItem();
   if(!hasFree){
      FUiControl* pControl = Create();
      Store(pControl);
   }
   // �ռ�һ������
   return AllocFirst();
}

//============================================================
// <T>�ͷ�һ�����Ӷ���</T>
//
// @param pParticle ���Ӷ���
//============================================================
void FUiControlPool::Free(FUiControl* pControl){
   FreeLast(pControl);
}

MO_NAMESPACE_END
