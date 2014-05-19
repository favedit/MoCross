#include "MoErPipeline.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FBlurPass, FPipelinePass);

//============================================================
// <T>����Ӱ����Ⱦ���̡�</T>
//============================================================
FBlurPass::FBlurPass(){
   _name = "blur";
}

//============================================================
// <T>����Ӱ����Ⱦ���̡�</T>
//============================================================
FBlurPass::~FBlurPass(){
}

//============================================================
// <T>���ô���</T>
//
// @return ������
//============================================================
TResult FBlurPass::Setup(){
   TResult result = FPipelinePass::Setup();
   _effect = REffectManager::Instance().Build("blur", NULL);
   _renderRectangle = FRenderRectangle::InstanceCreate();
   _renderRectangle->Setup();
   return result;
}

//============================================================
// <T>����������</T>
//
// @return ������
//============================================================
TResult FBlurPass::DrawRegion(FRenderRegion* pRegion){
   // ���û���Ŀ��
   FRenderDevice* pRenderDevice = RDeviceManager::Instance().Find<FRenderDevice>();
   pRenderDevice->SetRenderTarget();
   pRenderDevice->SetProgram(_effect->Program());
   TInt diffuseSize = _effect->Program()->FindDefine("fc_diffuse_size");
   TInt positionSlot = _effect->Program()->FindAttribute("va_position");
   TInt coordSlot = _effect->Program()->FindAttribute("va_coord");
   TInt diffuseSlot = _effect->Program()->FindDefine("fs_diffuse");
   SIntSize2& textureSize = _inputTexture->Size();
   //............................................................
   // ������Ⱦ���ͽ��з���
   FRenderVertexBuffer* pVertexBuffer = _renderRectangle->VertexBuffer();
   FRenderIndexBuffer* pIndexBuffer = _renderRectangle->IndexBuffer();
   //pRenderDevice->BindConstFloat4(ERenderShader_Fragment, diffuseSize, (TFloat)textureSize.width, (TFloat)textureSize.height, 1.0f / (TFloat)textureSize.width, 1.0f / (TFloat)textureSize.height);
   //TFloat rate = 40.0f;
   //pRenderDevice->BindConstFloat4(ERenderShader_Fragment, diffuseSize,
   //    -1.0f / (TFloat)textureSize.width * rate,
   //    -1.0f / (TFloat)textureSize.height * rate,
   //    1.0f / (TFloat)textureSize.width * rate,
   //    1.0f / (TFloat)textureSize.height * rate);
   pRenderDevice->BindVertexBuffer(positionSlot, pVertexBuffer, 0, ERenderAttributeFormat_Float3);
   pRenderDevice->BindVertexBuffer(coordSlot, pVertexBuffer, sizeof(TFloat) * 3, ERenderAttributeFormat_Float2);
   pRenderDevice->BindTexture(diffuseSlot, _inputTexture);
   pRenderDevice->DrawTriangles(pIndexBuffer, 0, pIndexBuffer->Count());
   //............................................................
   // �رճ���
   pRenderDevice->SetProgram(NULL);
   return ESuccess;
}

MO_NAMESPACE_END
