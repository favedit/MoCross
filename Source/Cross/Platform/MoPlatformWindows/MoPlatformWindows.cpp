#include "MoPlatformWindows.h"
      
MO_NAMESPACE_BEGIN

//============================================================
// <T>��ʼ���������洦��</T>
//============================================================
void MoPlatformWindowsInitialize(){
   MO_STATIC_INFO("Platform windows initialize.");
   // ��ʼ�����ڹ�����
   RRenderWindowManager::Create();
   // ��ʼ���Ʋ�������
   RAssetManager::Create(MO_CREATE(FEwAssetConsole));
}

//============================================================
// <T>�����������洦��</T>
//============================================================
void MoPlatformWindowsStartup(){
   MO_STATIC_INFO("Platform windows startup.");
}

//============================================================
// <T>�رմ������洦��</T>
//============================================================
void MoPlatformWindowsShutdown(){
   MO_STATIC_INFO("Platform windows shutdown.");
}

//============================================================
// <T>�ͷŴ������洦��</T>
//============================================================
void MoPlatformWindowsRelease(){
   MO_STATIC_INFO("Platform windows release.");
   // �ͷŲƲ�������
   RAssetManager::Destroy();
   // �ͷŴ��ڹ�����
   RRenderWindowManager::Destroy();
}

MO_NAMESPACE_END
