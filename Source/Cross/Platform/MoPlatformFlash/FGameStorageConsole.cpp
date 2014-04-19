#include "MoGmGameStorage.h"
#include "MoGmEnvironment.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>������Ϸ�洢����̨��</T>
//============================================================
FGameStorageConsole::FGameStorageConsole(){
   MO_CLEAR(_pGroups);
   MO_CLEAR(_pMaps);
   MO_CLEAR(_pMbdFile);
   MO_CLEAR(_pResourceGroupSet);
   _initiailized = EFalse;
   _pushedMbi = EFalse;
   MO_CLEAR(_mbiFileStream);
}

//============================================================
// <T>������Ϸ�洢����̨��</T>
//============================================================
FGameStorageConsole::~FGameStorageConsole(){
   Shutdown();
}

//============================================================
// <T>������Ϸ�洢����̨��</T>
//============================================================
TBool FGameStorageConsole::Startup(){
   if(_initiailized){
      MO_DEBUG("already init FGameStorageConsole.");
      return EFalse;
   }
   if(!InitMbi()){
      MO_DEBUG("InitMbi return EFalse.");
      return EFalse;
   }
   if(!InitMbd()){
      MO_DEBUG("InitMbd return EFalse.");
      return EFalse;
   }
   _initiailized = ETrue;
   MO_DEBUG("FGameStorageConsole Startup!");
   return ETrue;
}

//============================================================
// <T>������Ϸ�洢����̨��</T>
//============================================================
void FGameStorageConsole::Shutdown(){
   // �ر��ļ�
   _pMbdFile->Close();
   MO_DELETE(_pMbdFile);
   // ɾ����Դ��
   FGroupInfoVector::TIteratorC itrGroup = _pGroups->IteratorC();
   FGroupInfo* pGroup = NULL;
   while(itrGroup.Next()){
      pGroup = *itrGroup;
      MO_DELETE(pGroup);
   }
   MO_DELETE(_pGroups);
   // ɾ����ͼ
   FMapInfoVector::TIteratorC itrMap = _pMaps->IteratorC();
   FMapInfo* pMap = NULL;
   FMapTileInfo* pTile = NULL;
   while(itrMap.Next()){
      pMap = *itrMap;
      FMapTileInfoVector::TIteratorC itrMapTile = pMap->pTiles->IteratorC();
      while(itrMapTile.Next()){
         pTile = *itrMapTile;
         MO_DELETE(pTile);
      }
      MO_DELETE(pMap->pTiles);
      MO_DELETE(pMap);
   }
   MO_DELETE(_pMaps);
}

//============================================================
// <T>������Դ���ȡ����Դ���ļ�����</T>
//
// @param sourceId ��Դ���
// @param pOutputStream �����Դ��
//============================================================
TInt FGameStorageConsole::FindGroupBySourceId(TUint sourceId, FByteStream* pOutputStream){
   TInt groupId = -1;
   if(!_initiailized){
      MO_DEBUG("Don't setup game storage console.");
      return groupId;
   }
   if(0 == sourceId || NULL == pOutputStream){
      MO_DEBUG("Param is error.");
      return groupId;
   }
   groupId = _pResourceGroupSet->Find(sourceId);
   if(0 > FindGroupById(groupId, pOutputStream)){
      return -1;
   }
   return groupId;
}

//============================================================
// <T>������Դ����ȡ����Դ���ļ�����</T>
//
// @param groupId ��Դ����
// @param pOutputStream �����Դ��
//============================================================
TInt FGameStorageConsole::FindGroupById(TUint groupId, FByteStream* pOutputStream){
   TInt streamLength = -1;
   if(!_initiailized){
      MO_DEBUG("Don't setup game storage console.");
      return streamLength;
   }
   if(0 == groupId || NULL == pOutputStream){
      MO_DEBUG("Param is error.");
      return streamLength;
   }
   if(NULL == _pMbdFile){
      MO_DEBUG("Don't open game.mdb file.");
      return streamLength;
   }
   FGroupInfo* pGroupInfo = NULL;
   FGroupInfoVector::TIteratorC iterator = _pGroups->IteratorC();
   while(iterator.Next()){
      pGroupInfo = *iterator;
      if(pGroupInfo->id == groupId){
          streamLength = pGroupInfo->data.length;
          _pMbdFile->Seek(pGroupInfo->data.position);
          pOutputStream->ForceLength(streamLength);
          _pMbdFile->Read(pOutputStream->Memory(), pOutputStream->Length());
          break;
      }
   }
   return streamLength;
}

//============================================================
// <T>���ݵ�ͼ��Դ���ȡ����Դ���ļ�����</T>
//
// @param mapSourceId ��ͼ��Դ���
// @param pOutputStream �����Դ��
//============================================================
TInt FGameStorageConsole::FindMapSourceById(TUint mapSourceId, FByteStream* pOutputStream){
   TInt streamLength = -1;
   if(!_initiailized){
      MO_DEBUG("Don't setup game storage console.");
      return streamLength;
   }
   if(0 == mapSourceId || NULL == pOutputStream){
      MO_DEBUG("param is error.");
      return streamLength;
   }
   if(NULL == _pMbdFile){
      MO_DEBUG("Don't open game.mdb file.");
      return streamLength;
   }
   // ȡ����Ϣ 
   TInt mapId = ((mapSourceId % 1000000000) / 100000) % 100;
   TInt locationY = (mapSourceId % 10000) / 100; 
   TInt locationX = mapSourceId % 100;
   FMapInfo* pMapInfo = NULL;
   FMapTileInfo* pTileInfo = NULL;
   FMapInfoVector::TIteratorC itrMap = _pMaps->IteratorC();
   while(itrMap.Next()){
      pMapInfo = *itrMap;
      if(pMapInfo->id == mapId){
         FMapTileInfoVector::TIteratorC itrTile = pMapInfo->pTiles->IteratorC();
         while(itrTile.Next()){
            pTileInfo = *itrTile;
            TInt index = pMapInfo->width * locationY + locationX;
            if(pTileInfo->tileIndex == index){
               streamLength = pTileInfo->data.length;
               _pMbdFile->Seek(pTileInfo->data.position);
               pOutputStream->ForceLength(streamLength);
               _pMbdFile->Read(pOutputStream->Memory(), pOutputStream->Length());
               break;
            }
         }
         break;
      }
   }
   if(streamLength > 0){
      MO_DEBUG("Get map ground stream success. (ground_id=%d, map_id=%d, locationY=%d, locationX=%d, stream_length=%d)", mapSourceId, mapId, locationY, locationX, streamLength);
   }else{
      MO_DEBUG("Get map ground stream failure. (ground_id=%d, map_id=%d, locationY=%d, locationX=%d)", mapSourceId, mapId, locationY, locationX);
   }
   return streamLength;
}

//============================================================
// <T>��������Ϣ�ļ�����</T>
//
//============================================================
TBool FGameStorageConsole::PushMbiDataStream(FByteStream* pInputStream){
   if(NULL == pInputStream){
      MO_DEBUG("Input strams is null.");
      return EFalse;
   }
   _mbiFileStream = MO_CREATE(FByteFile);
   TInt length = pInputStream->Length();
   _mbiFileStream->ForceLength(length);
   _mbiFileStream->Assign(pInputStream->MemoryC(), length);
   _pushedMbi = ETrue;
   return ETrue;
}

//============================================================
// <T>��ʼ�������Ϣ�ļ���</T>
//
//============================================================
TBool FGameStorageConsole::InitMbi(){
   // ȡ���ļ�·��
   TCharC* pResourceRoot = REnvironmentManager::Instance().FindValue(MO_GM_ENV_RESOURCE_ROOT);
   if(NULL == pResourceRoot || *pResourceRoot == '\0'){
      MO_DEBUG("pResourceRoot is error.");
      return EFalse;
   }
   if(EFalse == _pushedMbi){
      MO_DEBUG("Not push game.mbi data stream.");
      return EFalse;
   }
   _pGroups = MO_CREATE(FGroupInfoVector);
   _pMaps = MO_CREATE(FMapInfoVector);
   _pResourceGroupSet = MO_CREATE(FResourceGroupSet);
   // �����ļ�����
   //TFsFileName mbiFileName;
   //mbiFileName.AssignFormat("%s/game.mbi", pResourceRoot);
   //FByteFile* pFile = MO_CREATE(FByteFile);
   //TBool result = pFile->LoadFile(mbiFileName.Memory());
   TBool result = ETrue;
   FByteFile* pFile = _mbiFileStream;
   if(EFalse != result){
      // ��ȡ��Դ������
      TInt groupCount = pFile->ReadInt32();
      FGroupInfo* pGroup = NULL;
      for(TInt n = 0; n < groupCount; n++){
         pGroup = MO_CREATE(FGroupInfo);
         if(NULL != pGroup){
            pGroup->id = pFile->ReadUint32();
            pGroup->data.position = pFile->ReadInt32();
            pGroup->data.length = pFile->ReadInt32();
            _pGroups->Push(pGroup);
            pGroup = NULL;
         }
      }
      // ��ȡ��ͼ����
      TInt mapCount = pFile->ReadInt32();
      FMapInfo* pMapInfo = NULL;
      FMapTileInfo* pMapTileInfo = NULL;
      for(TInt nMap = 0; nMap < mapCount; nMap++){
         pMapInfo = MO_CREATE(FMapInfo);
         pMapInfo->pTiles = MO_CREATE(FMapTileInfoVector);
         if(NULL != pMapInfo){
            pMapInfo->id = pFile->ReadInt32();
            pMapInfo->width = pFile->ReadInt16();
            pMapInfo->height = pFile->ReadInt16();
            pFile->ReadInt32();
            pFile->ReadInt32();
            TInt tileCount = pFile->ReadInt32();
            for(TInt nTile = 0; nTile < tileCount; nTile++){
               pMapTileInfo = MO_CREATE(FMapTileInfo);
               if(NULL != pMapTileInfo){
                  pMapTileInfo->tileIndex = nTile;
                  pMapTileInfo->data.position = pFile->ReadInt32();
                  pMapTileInfo->data.length = pFile->ReadInt32();
                  pMapInfo->pTiles->Push(pMapTileInfo);
                  MO_CLEAR(pMapTileInfo);
               }
            }
            _pMaps->Push(pMapInfo);
            MO_CLEAR(pMapInfo);
         }
      }
      pFile->ReadInt32();  // gFileLength
      // ��ȡ��Դ��Ӧ��
      TInt sourceCount = pFile->ReadInt32();
      for(TInt rn = 0; rn < sourceCount; rn++){
         // ��ȡ��Դ����
         pFile->ReadInt32();  //��Դ���
         pFile->ReadString(); //��Դ����
         pFile->ReadString(); //
         pFile->ReadString(); //
         pFile->ReadInt32();  //��Դ��С
      }
      // ��ȡ��Դ�鶨�弯��
      TInt gCount = pFile->ReadInt32();
      for(TInt gn = 0; gn < gCount; gn++){
         // ��ȡ��Դ������
         TInt gid = pFile->ReadInt32();
         TFsName gcdStr = (TChar*)pFile->ReadString();
         TInt gcd = RInt::Parse(gcdStr, 0);
         TInt gtb = pFile->ReadInt32();
         // ��ȡ��Դ�б�
         TInt grc = pFile->ReadInt32();
         for(TInt n = 0; n < grc; n++){
            TFsName cdStr = (TChar*)pFile->ReadString();
            TInt cd = RInt::Parse(cdStr, 0);
            _pResourceGroupSet->Set(cd, gcd);
         }
      }
   }
   MO_DELETE(pFile);
   MO_CLEAR(_mbiFileStream);
   return result;
}

//============================================================
// <T>��ʼ����������ļ���</T>
//
//============================================================
TBool FGameStorageConsole::InitMbd(){
   // ȡ���ļ�·��
   TCharC* pResourceRoot = REnvironmentManager::Instance().FindValue(MO_GM_ENV_RESOURCE_ROOT);
   if(NULL == pResourceRoot || *pResourceRoot == '\0'){
      return EFalse;
   }
   // ȡ���ļ�����
   TFsFileName mbdFileName;
   mbdFileName.AssignFormat("%s/game.mbd", pResourceRoot);
   FFileStream* pFileStream = MO_CREATE(FFileStream);
   if(NULL == pFileStream){
      return EFalse;
   }
   _pMbdFile = pFileStream;
   return _pMbdFile->Open(mbdFileName, EFileAccess_Read);
}

MO_NAMESPACE_END
