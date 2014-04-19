#include "MoFgVisual.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FVisualConsole, FConsole);

//============================================================
// <T>����ɼ�����̨��</T>
//============================================================
FVisualConsole::FVisualConsole(){
   _pThread = MO_CREATE(FVisualThread);
   _pRegions = MO_CREATE(FVisualRegionCollection);
}

//============================================================
// <T>�����ɼ�����̨��</T>
//============================================================
FVisualConsole::~FVisualConsole(){
   MO_DELETE(_pRegions);
}

//============================================================
// <T>ע��һ���ɼ�����</T>
//
// @param pRegion �ɼ�����
// @return ������
//============================================================
TResult FVisualConsole::RegionRegister(FVisualRegion* pRegion){
   _regionLocker.Enter();
   _pRegions->Push(pRegion);
   _regionLocker.Leave();
   return ESuccess;
}

//============================================================
// <T>ע��һ���ɼ�����</T>
//
// @param pRegion �ɼ�����
// @return ������
//============================================================
TResult FVisualConsole::RegionUnregister(FVisualRegion* pRegion){
   _regionLocker.Enter();
   _pRegions->Remove(pRegion);
   _regionLocker.Leave();
   return ESuccess;
}

//============================================================
// <T>��������</T>
//
// @return ������
//============================================================
TResult FVisualConsole::Startup(){
   _pThread->SetConsole(this);
   _pThread->Start();
   return ESuccess;
}

//============================================================
// <T>�߼�����</T>
//
// @return ������
//============================================================
TResult FVisualConsole::Process(){
   _regionLocker.Enter();
   FVisualRegionCollection::TIteratorC iterator = _pRegions->IteratorC();
   while(iterator.Next()){
      FVisualRegion* pRegion = *iterator;
      pRegion->Process();
   }
   _regionLocker.Leave();
   return ESuccess;
}

//============================================================
// <T>�رմ���</T>
//
// @return ������
//============================================================
TResult FVisualConsole::Shutdown(){
   _pThread->Terminate();
   return ESuccess;
}

MO_NAMESPACE_END
