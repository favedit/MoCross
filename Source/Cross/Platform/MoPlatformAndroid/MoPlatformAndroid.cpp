#include "MoPlatformAndroid.h"
      
MO_NAMESPACE_BEGIN

//============================================================
// <T>��ʼ����Ⱦ���洦��</T>
//============================================================
void MoPlatformAndroidInitialize(){
   MO_STATIC_INFO("Platform android initialize.");
   // ��ʼ�����������
   RAssetManager::Create(MO_CREATE(FEaAssetConsole));
}

//============================================================
// <T>������Ⱦ���洦��</T>
//============================================================
void MoPlatformAndroidStartup(){
   MO_STATIC_INFO("Platform android startup.");
}

//============================================================
// <T>�ر���Ⱦ���洦��</T>
//============================================================
void MoPlatformAndroidShutdown(){
   MO_STATIC_INFO("Platform android shutdown.");
}

//============================================================
// <T>�ͷ���Ⱦ���洦��</T>
//============================================================
void MoPlatformAndroidRelease(){
   MO_STATIC_INFO("Platform android release.");
}

MO_NAMESPACE_END
