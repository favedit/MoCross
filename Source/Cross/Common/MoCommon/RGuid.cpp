#ifdef _MO_LINUX
#include <uuid/uuid.h>
#endif // _MO_LINUX
#include "MoCmLanguage.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>����һ��Ψһ��š�</T>
//
// @return Ψһ���
//============================================================
TGuid RGuid::Generate(){
   TGuid value;
#ifdef _MO_LINUX
   uuid_t uuid;
   uuid_generate(uuid);
   for(TInt n = 0; n < 16; n++){
      value.AppendFormat("%2X", uuid[n]);
   }
#endif // _MO_LINUX
   return value;
}

MO_NAMESPACE_END

