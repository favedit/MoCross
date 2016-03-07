#include "MoFrContent3dModel.h"
#include "MoFrContent3dTemplate.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>������Դ3Dģ�塣</T>
//============================================================
FRs3dTemplate::FRs3dTemplate(){
   _pModels = MO_CREATE(FRs3dModelCollection);
   _pRenderables = MO_CREATE(FRs3dTemplateRenderableCollection);
}

//============================================================
// <T>������Դ3Dģ�塣</T>
//============================================================
FRs3dTemplate::~FRs3dTemplate(){
   MO_DELETE(_pModels);
   MO_DELETE(_pRenderables);
}

//============================================================
// <T>���������ﷴ���л���Ϣ����</T>
//
// @param pInput ������
// @return ������
//============================================================
TResult FRs3dTemplate::Unserialize(IDataInput* pInput){
   MO_CHECK(pInput, return ENull);
   // ��ȡ������
   FResource3d::Unserialize(pInput);
   // ��ȡ�����б�
   TInt renderableCount = pInput->ReadInt16();
   for(TInt n = 0; n < renderableCount; n++){
      // ����ģ����Ⱦ����
      FRs3dTemplateRenderable* pRenderable = FRs3dTemplateRenderable::InstanceCreate();
      pRenderable->Unserialize(pInput);
      _pRenderables->Push(pRenderable);
      // ����ģ�ͼ���
      TCharC* pModelName = pRenderable->ModelName();
      FRs3dModel* pRsModel = RResource3dManager::Instance().ModelConsole()->Find(pModelName);
      MO_CHECK(pRsModel, return ENull);
      _pModels->PushUnique(pRsModel);
   }
   MO_DEBUG(TC("Unserialize template success. (code=%d, renderable_count=%d)"),
         _code, renderableCount);
   return ESuccess;
}

//============================================================
// <T>��ո��ټ��ϡ�</T>
//============================================================
void FRs3dTemplate::RenderableClear(){
   TInt count = _pRenderables->Count();
   for(TInt n = 0; n < count; n++){
      FRs3dTemplateRenderable* pRenderable = _pRenderables->Get(n);
      MO_DELETE(pRenderable);
   }
   _pRenderables->Clear();
}

MO_NAMESPACE_END
