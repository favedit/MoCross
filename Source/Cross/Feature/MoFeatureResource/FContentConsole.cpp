#include "MoFrContent.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FContentConsole, FLoader);

//============================================================
// <T>�������ݿ���̨��</T>
//============================================================
FContentConsole::FContentConsole(){
}

//============================================================
// <T>�������ݿ���̨��</T>
//============================================================
FContentConsole::~FContentConsole(){
}

//============================================================
// <T>�������ݡ�</T>
//============================================================
TResult FContentConsole::Load(FContent* pContent){
   return ESuccess;
}

MO_NAMESPACE_END
