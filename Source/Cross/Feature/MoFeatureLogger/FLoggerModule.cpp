#include "MoFlFile.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>��־ģ�鹹������</T>
//
// @return �޷���ֵ
//============================================================
FLoggerModule::FLoggerModule(){
   _name = "Module.Logger";
}

//============================================================
// <T>��־ģ����������</T>
//
// @return �޷���ֵ
//============================================================
FLoggerModule::~FLoggerModule(){
}

//============================================================
// <T>������־ģ�����á�</T>
//
// @param FXmlNode* pConfig �����ļ���xml�����
// @return �����׷�ɹ�
//============================================================
TResult FLoggerModule::OnLoadConfig(FXmlNode* pConfig){
   TXmlNodeIteratorC iterator = pConfig->NodeIteratorC();
   while(iterator.Next()){
      if(iterator->IsName("Property")){
         TFsPath path = REnvironment::MappingPath("%s",  iterator->Text());
         _path.Assign(path.MemoryC());
      }else if(iterator->IsName("Writer")){
         // ����������־
         FBufferedLoggerWriter *pWriter = MO_CREATE(FBufferedLoggerWriter);
         TBool forceFlush = iterator->GetAsBool("force_flush", EFalse);
         TInt code = iterator->GetAsInt("id");
         TCharC* pName = iterator->Get("name");
         TInt capacity = iterator->GetAsInt("capacity");
         TFileInfo path = (TCharC*)_path;
         MO_DEBUG("Read logger writer config. (code=%d, name=%s, capacity=%d, path=%s)",
               code, pName, capacity, path.FullName());
         pWriter->SetCode(code);
         pWriter->SetName(pName);
         pWriter->SetCapacity(capacity);
         pWriter->SetPath(path.FullName());
         pWriter->SetForceToFlush(forceFlush);
         RLoggerManager::Instance().Register(pWriter);
      }
   }
   return ESuccess;
}

MO_NAMESPACE_END
