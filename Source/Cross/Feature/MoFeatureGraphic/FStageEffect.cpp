#include "MoFgTechnique.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FStageEffect, FEffect);

//============================================================
// <T>���쳡����Ⱦ����</T>
//============================================================
FStageEffect::FStageEffect(){
}

//============================================================
// <T>����������Ⱦ����</T>
//============================================================
FStageEffect::~FStageEffect(){
}

//============================================================
// <T>���ô���</T>
//============================================================
TResult FStageEffect::OnSetup(){
   return ESuccess;
}

//============================================================
// <T>�����С��</T>
//
// @return ������
//============================================================
TResult FStageEffect::Resize(TInt width, TInt height){
   return ESuccess;
}

//============================================================
// <T>���ƴ���</T>
//============================================================
TResult FStageEffect::Draw(FRenderable* pRenderable){
   //MO_ASSERT(pRenderable);
   //SRenderableContent content;
   //pRenderable->FetchRenderableContent(content);
   //SFloatMatrix3d& renderableMatrix = pRenderable->Matrix();
   //// ����豸
   //FRenderDevice* pRenderDevice = RDeviceManager::Instance().RenderDevice();
   ////............................................................
   //// �趨���Լ���
   //BindAttributeDescriptors(pRenderable);
   //// ����������
   //BindSamplerDescriptors(pRenderable);
   ////............................................................
   //// ����������������������
   //FRenderIndexBuffer* pIndexBuffer = content.indexBufferPtr;
   //pRenderDevice->DrawTriangles(pIndexBuffer, 0, pIndexBuffer->Count());
   return ESuccess;
}

MO_NAMESPACE_END
