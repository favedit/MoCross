#include "MoEngineFace.h"
      
MO_NAMESPACE_BEGIN

//============================================================
// <T>��ʼ���������洦��</T>
//============================================================
void MoEngineFaceInitialize(){
   MO_STATIC_INFO("Engine face initialize.");
   // ��ʼ���ؼ�������
   RFaceManager::Create();
   RFaceManager::Instance().Setup();
   // ��ʼ�����й�����
   RRuntimeFrameManager::Create();
   // ��ʼ�����������
   RFontManager::Create(MO_CREATE(FEoFontConsole));
   RFontManager::Instance().Open();
}

//============================================================
// <T>�����������洦��</T>
//============================================================
void MoEngineFaceStartup(){
   MO_STATIC_INFO("Engine face startup.");
   // ע�Ỻ���
   FUiControlConsole* pControlConsole = RFaceManager::Instance().ControlConsole();
   pControlConsole->PoolRegister(MO_CREATE(FUiLabelPool));
   pControlConsole->PoolRegister(MO_CREATE(FUiEditPool));
   pControlConsole->PoolRegister(MO_CREATE(FUiButtonPool));
   pControlConsole->PoolRegister(MO_CREATE(FUiPanelPool));
   pControlConsole->PoolRegister(MO_CREATE(FUiPagePool));
   pControlConsole->PoolRegister(MO_CREATE(FUiPageControlPool));
   pControlConsole->PoolRegister(MO_CREATE(FUiBarPool));
   pControlConsole->PoolRegister(MO_CREATE(FUiFormPool));
   pControlConsole->PoolRegister(MO_CREATE(FUiWindowPool));
   // �����ؼ�������
   RRuntimeFrameManager::Instance().Setup();
   //............................................................
   // �򿪽��������
   RFaceManager::Instance().Open();
}

//============================================================
// <T>�رս������洦��</T>
//============================================================
void MoEngineFaceShutdown(){
   MO_STATIC_INFO("Engine face shutdown.");
}

//============================================================
// <T>�ͷŽ������洦��</T>
//============================================================
void MoEngineFaceRelease(){
   MO_STATIC_INFO("Engine face release.");
   // �ͷ����й�����
   RRuntimeFrameManager::Destroy();
   // �ͷſؼ�������
   RFaceManager::Destroy();
}

MO_NAMESPACE_END
