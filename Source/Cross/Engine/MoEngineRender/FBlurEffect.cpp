#include "MoErTechnique.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FBlurEffect, FAutomaticEffect);

//============================================================
// <T>������ȾЧ����</T>
//============================================================
FBlurEffect::FBlurEffect(){
}

//============================================================
// <T>������ȾЧ����</T>
//============================================================
FBlurEffect::~FBlurEffect(){
}

//============================================================
// <T>���ô���</T>
//============================================================
TResult FBlurEffect::Setup(){
   // ע�����Լ���
   //_attributeDescriptors.Register(ERenderVertexBuffer_Position, "va_position", ERenderVertexFormat_Float4);
   //_attributeDescriptors.Register(ERenderVertexBuffer_Color,    "va_color",    ERenderVertexFormat_ByteNormal4);
   // ע��������
   //_samplerDescriptors.Register(EEffectSampler_Diffuse, "fs_diffuse", ERenderSampler_PackDiffuse);
   return ESuccess;
}

//============================================================
// <T>���ƴ���</T>
//============================================================
TResult FBlurEffect::Draw(FRenderable* pRenderable){
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
