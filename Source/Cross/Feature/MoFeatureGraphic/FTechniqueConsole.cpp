#include "MoFgTechnique.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>������Ⱦ������</T>
//============================================================
FTechniqueConsole::FTechniqueConsole(){
   _pTechniques = MO_CREATE(FTechniqueCollection);
}

//============================================================
// <T>������Ⱦ������</T>
//============================================================
FTechniqueConsole::~FTechniqueConsole(){
   MO_DELETE(_pTechniques);
}

//============================================================
// <T>���ô���</T>
//============================================================
void FTechniqueConsole::Setup(){
}

MO_NAMESPACE_END
