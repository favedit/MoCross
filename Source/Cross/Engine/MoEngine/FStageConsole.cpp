#include "MoEgDisplay.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>������̨����̨��</T>
//============================================================
FStageConsole::FStageConsole(){
   MO_CLEAR(_pActiveStage);
}

//============================================================
// <T>������̨����̨��</T>
//============================================================
FStageConsole::~FStageConsole(){
}

//============================================================
// <T>��������</T>
//
// @return ������
//============================================================
TResult FStageConsole::Startup(){
   // ������ʾ������
   MO_CHECK(!_displayProcessor, return ENull);
   _displayProcessor = FProcessor::InstanceCreate();
   _displayProcessor->Startup();
   RProcessorManager::Instance().Register(_displayProcessor);
   // ������Ⱦ������
   MO_CHECK(!_renderableProcessor, return ENull);
   _renderableProcessor = FProcessor::InstanceCreate();
   _renderableProcessor->Startup();
   RProcessorManager::Instance().Register(_renderableProcessor);
   return ESuccess;
}

//============================================================
// <T>�رմ���</T>
//
// @return ������
//============================================================
TResult FStageConsole::Shutdown(){
   _displayProcessor->Shutdown();
   _renderableProcessor->Shutdown();
   return ESuccess;
}

//============================================================
// <T>ѡ��һ����̨��</T>
// <P>��̨Ϊ�ձ�ʾ���������̨��</P>
//
// @param pStage ��̨
// @return ������
//============================================================
TResult FStageConsole::SelectStage(FStage* pStage){
   // ����Ƿ����
   if(_pActiveStage == pStage){
      return EContinue;
   }
   // ȡ��������̨
   if(_pActiveStage != NULL){
      _pActiveStage->Deactive();
      _pActiveStage = NULL;
   }
   // ����ѡ����̨
   if(pStage != NULL){
      pStage->Active();
   }
   _pActiveStage = pStage;
   return ESuccess;
}

MO_NAMESPACE_END
