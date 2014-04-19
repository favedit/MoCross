#include "MoE3Scene.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FScene3dMovie, FInstance);

//============================================================
// <T>���춯����</T>
//============================================================
FScene3dMovie::FScene3dMovie(){
   MO_CLEAR(_pResource);
   _interval = 0;
}

//============================================================
// <T>����������</T>
//============================================================
FScene3dMovie::~FScene3dMovie(){
}

//============================================================
// <T>������Դ��</T>
//
// @param pResource ��Դ����
// @return ������
//============================================================
TResult FScene3dMovie::LoadResource(FRs3dSceneMovie* pResource){
   MO_CHECK(pResource, return ENull);
   _pResource = pResource;
   _interval = pResource->Interval() * 1000;
   return ESuccess;
}

//============================================================
// <T>��������</T>
//
// @param matrix ����
// @return ������
//============================================================
TResult FScene3dMovie::Process(SFloatMatrix3d& matrix){
   return ESuccess;
}

MO_NAMESPACE_END
