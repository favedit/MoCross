#include "MoCrFeature.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FFeatureConsole, FConsole);

//============================================================
// <T>���칦�ܿ���̨��</T>
//============================================================
FFeatureConsole::FFeatureConsole(){
   _name = "Feature.Console";
}

//============================================================
// <T>�������ܿ���̨��</T>
//============================================================
FFeatureConsole::~FFeatureConsole(){
}

//============================================================
// <T>ע��һ�����ܡ�</T>
//
// @param pFeature ����
//============================================================
void FFeatureConsole::Register(FFeature* pFeature){
   _features.Push(pFeature);
}

//============================================================
// <T>ע��һ�����ܡ�</T>
//
// @param pFeature ����
//============================================================
void FFeatureConsole::Unregister(FFeature* pFeature){
   _features.Remove(pFeature);
}

//============================================================
// <T>��������</T>
//
// @return ������
//============================================================
TResult FFeatureConsole::Startup(){
   TInt count = _features.Count();
   for(TInt n = 0; n < count ; n++){
      FFeature* pFeature = _features.Get(n);
      pFeature->Startup();
   }
   return ESuccess;
}

//============================================================
// <T>������</T>
//
// @return ������
//============================================================
TResult FFeatureConsole::Suspend(){
   TInt count = _features.Count();
   for(TInt n = 0; n < count ; n++){
      FFeature* pFeature = _features.Get(n);
      pFeature->Suspend();
   }
   return ESuccess;
}

//============================================================
// <T>��������</T>
//
// @return ������
//============================================================
TResult FFeatureConsole::Resume(){
   TInt count = _features.Count();
   for(TInt n = 0; n < count ; n++){
      FFeature* pFeature = _features.Get(n);
      pFeature->Resume();
   }
   return ESuccess;
}

//============================================================
// <T>ֹͣ����</T>
//
// @return ������
//============================================================
TResult FFeatureConsole::Shutdown(){
   TInt count = _features.Count();
   for(TInt n = 0; n < count ; n++){
      FFeature* pFeature = _features.Get(n);
      pFeature->Shutdown();
   }
   return ESuccess;
}

MO_NAMESPACE_END
