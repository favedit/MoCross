#include "MoFbxCore.h"

//============================================================
// <T>�ص������塣</T>
//============================================================
/*
MO_EXTERN_C{
   TInt Exporter();
   typedef TInt (*CallBackExporter)(TCharC* pFileName, ExpInterface* piExpInterface, Interface* piInterface, TBool suppressPrompts, TUint32 options);
}

//============================================================
// <T>���쳡����������</T>
//
// @return ʵ��ָ��
//============================================================
PPtr F3dsSceneExport::Construct(){
   return this;
}

//============================================================
// <T>����������������</T>
//============================================================
void F3dsSceneExport::Dispose(){
}

//============================================================
// <T>���֧�ֵ���չ��������</T>
//
// @return ��չ������
//============================================================
TInt32 F3dsSceneExport::ExtCount(){
   return 1;
}

//============================================================
// <T>���ָ�������ĵ���չ����</T>
//
// @return ��չ������
//============================================================
TCharC* F3dsSceneExport::Ext(TInt32 index){
   switch(index) {
   case 0:
      return MO_3E_EXT;
   }
   return MO_3E_EMPTY;
}

//============================================================
// <T>��ø�Ҫ������</T>
//
// @return ��Ҫ����
//============================================================
TCharC* F3dsSceneExport::ShortDesc(){
   return MO_3E_DESC_SHORT;
}

//============================================================
// <T>�����ϸ������</T>
//
// @return ��ϸ����
//============================================================
TCharC* F3dsSceneExport::LongDesc(){
   return MO_3E_DESC_LONG;
}

//============================================================
// <T>����������ơ�</T>
//
// @return ��������
//============================================================
TCharC* F3dsSceneExport::AuthorName(){
   return MO_3E_AUTHOR;
}

//============================================================
// <T>��ð�Ȩ���ݡ�</T>
//
// @return ��Ȩ����
//============================================================
TCharC* F3dsSceneExport::CopyrightMessage(){
   return MO_3E_COPYRIGHT;
}

//============================================================
// <T>��ø�������1��</T>
//
// @return ��������
//============================================================
TCharC* F3dsSceneExport::OtherMessage1(){
   return MO_3E_EMPTY;
}

//============================================================
// <T>��ø�������2��</T>
//
// @return ��������
//============================================================
TCharC* F3dsSceneExport::OtherMessage2(){
   return MO_3E_EMPTY;
}

//============================================================
// <T>��õ�ǰ�汾��</T>
//
// @return ��ǰ�汾
//============================================================
TUint32 F3dsSceneExport::Version(){
   return MO_3E_VERSION;
}

//============================================================
// <T>��������</T>
//
// @return ������
// @return ������
//============================================================
TInt32 F3dsSceneExport::DoExport(TCharC* pFileName, ExpInterface* piExpInterface, Interface* piInterface, TInt32 suppressPrompts, TUlong options){
   MO_INFO(TC("3DS scene export start."));
   // ��̬���ص�����
   HMODULE hModule = LoadLibraryEx(MO_3E_LIBRARY, NULL, 0);
   MO_INFO(TC("Find Mo3dsExporter library. (handle=0x%08X)"), hModule);
   if(NULL == hModule){
      MO_INFO(TC("3DS scene export failure. (Module is null)"));
      return IMPEXP_FAIL;
   }
   // ��ú���ָ��
   CallBackExporter pfExporter = (CallBackExporter)GetProcAddress(hModule, "DoExport");
   MO_INFO(TC("Find DoExport method. (handle=0x%08X)"), pfExporter);
   if(NULL == pfExporter){
      // ���ؽ��
      TBool check = FreeLibrary(hModule);
      if(!check){
         MO_INFO(TC("Free library failure. (result=%d)"), check);
      }
      MO_INFO(TC("3DS scene export failure. (Method is null)"));
      return IMPEXP_FAIL;
   }
   // ���ú�������
   TInt result = pfExporter(pFileName, piExpInterface, piInterface, suppressPrompts, options);
   // �ͷŵ�����
   TBool check = FreeLibrary(hModule);
   if(!check){
      MO_INFO(TC("Free library failure. (handle=0x%08X, result=%d)"), hModule, check);
   }
   MO_INFO(TC("Free library success. (handle=0x%08X, result=%d)"), hModule, check);
   // ���ؽ��
   MO_INFO(TC("3DS scene export success."));
   return (TInt32)result;
}

//============================================================
// <T>��ʾ�����</T>
//
// @param ext ��չ������
// @param options ��������
// @return ������
//============================================================
TBool F3dsSceneExport::SupportsOptions(TInt ext, TUint32 options){
   return (SCENE_EXPORT_SELECTED == options) ? TRUE : FALSE;
}

//============================================================
// <T>��ʾ���ڡ�</T>
//============================================================
void F3dsSceneExport::ShowAbout(HWND hWnd){
}
*/
