#include "MoFrContentPipeline.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FContentAssetPipeline, FContentPipeline);

//============================================================
// <T>����������Դ�ܵ���</T>
//============================================================
FContentAssetPipeline::FContentAssetPipeline(){
}

//============================================================
// <T>����������Դ�ܵ���</T>
//============================================================
FContentAssetPipeline::~FContentAssetPipeline(){
}

//============================================================
// <T>���ݴ���</T>
//
// @return ������
//============================================================
TResult FContentAssetPipeline::Process(FContentLoader* pLoader){
   MO_CHECK(pLoader, return ENull);
   TCharC* pAssetName = pLoader->AssetName();
   MO_CHECK(pAssetName, return ENull);
   // ����Դ
   GAssetStreamPtr stream = RAssetManager::Instance().OpenAssetStream(pAssetName);
   MO_ERROR_CHECK(stream.IsValid(), return EFailure, "Open stream failure. (asset=%s)", pAssetName);
   // ��ȡ����
   FContent* pContent = pLoader->Content();
   pContent->Unserialize(stream);
   pContent->Complete();
   return ESuccess;
}

MO_NAMESPACE_END
