#include "MoEfFont.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FEoFontConsole, FFontConsole);

//============================================================
// <T>�����������̨��</T>
//============================================================
FEoFontConsole::FEoFontConsole(){
   RType<FT_Library>::Clear(&_library);
}

//============================================================
// <T>�����������̨��</T>
//============================================================
FEoFontConsole::~FEoFontConsole(){
}

//============================================================
// <T>�򿪴���</T>
//============================================================
void FEoFontConsole::Open(){
   FFontConsole::Open();
   // ��ʼ����
   FT_Error result = FT_Init_FreeType(&_library);
   if(result){
      MO_FATAL("Initialize free type failure. (error=%d)", result);
   }
}

//============================================================
// <T>�رմ���</T>
//============================================================
void FEoFontConsole::Close(){
   // �ͷ���Դ
   FT_Done_FreeType(_library);
   // �رմ���
   FFontConsole::Close();
}

MO_NAMESPACE_END
