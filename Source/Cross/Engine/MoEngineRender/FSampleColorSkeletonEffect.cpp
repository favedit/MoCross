#include "MoErSimplePipeline.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FSampleColorSkeletonEffect, FColorAutomaticEffect);

//============================================================
// <T>������Ӱ��ɫ�Զ���Ⱦ����</T>
//============================================================
FSampleColorSkeletonEffect::FSampleColorSkeletonEffect(){
   _descriptor.supportInstance = ETrue;
   _descriptor.supportSkeleton = ETrue;
}

//============================================================
// <T>������Ӱ��ɫ�Զ���Ⱦ����</T>
//============================================================
FSampleColorSkeletonEffect::~FSampleColorSkeletonEffect(){
}

//============================================================
// <T>���ô���</T>
//============================================================
TResult FSampleColorSkeletonEffect::Setup(){
   FColorAutomaticEffect::Setup();
   // ע�᳣������
   //_constDescriptors.Register(ERenderShader_Vertex, EEffectParameter_VertexBoneMatrix, "vc_bone_matrix");
   return ESuccess;
}

//============================================================
// <T>����ģ����Ϣ��</T>
//
// @param renderableDescriptor ��Ⱦ����
// @param pCode ����
// @param pTemplateContext ģ�廷��
// @return ������
//============================================================
TResult FSampleColorSkeletonEffect::BuildTemplate(SRenderableDescriptor& renderableDescriptor, MString* pCode, FTemplateContext* pTemplateContext){
   //FAutomaticEffect::BuildTemplate(renderableDescriptor, pCode, pTemplateContext);
   // �������ʵ������
   TInt vertexCount = renderableDescriptor.vertexCount;
   TInt boneCount = renderableDescriptor.boneCount;
   TInt instanceCount = RRenderUtil::CalculateInstanceCount(vertexCount, boneCount);
   TInt instanceBoneCount = boneCount * instanceCount;
   // ������Ϣ
   if(_dynamicDescriptor.supportInstance && pTemplateContext){
      pTemplateContext->DefineInt("instance.count", instanceCount);
      pTemplateContext->DefineInt("instance.bone.count", instanceBoneCount * 3);
   }else if(pTemplateContext){
      pTemplateContext->DefineInt("bone.count", instanceBoneCount);
   }
   return ESuccess;
}

//============================================================
// <T>���ƴ���</T>
//============================================================
TResult FSampleColorSkeletonEffect::DrawRenderable(FRenderRegion* pRegion, FRenderable* pRenderable){
   MO_CHECK(pRegion, return ENull);
   MO_CHECK(pRenderable, return ENull);
   //............................................................
   // ����ģ�;���
   SFloatMatrix3d modelMatrix;
   pRenderable->CalculateModelMatrix(modelMatrix);
   modelMatrix.Append(pRenderable->Matrix());
   BindConstMatrix4x4(EEffectParameter_VertexModelMatrix4x4, &modelMatrix);
   // �����������
   TInt boneCount = pRenderable->CalculateBoneMatrix(_boneMatrixs);
   BindConstMatrix4x3(EEffectParameter_VertexBoneMatrix4x3, (SFloatMatrix3d*)&_boneMatrixs, boneCount);
   //............................................................
   // �趨���Լ���
   BindAttributeDescriptors(pRenderable);
   // ����������
   BindSamplerDescriptors(pRenderable);
   //............................................................
   // ����������������������
   FRenderIndexBuffer* pIndexBuffer = pRenderable->IndexBuffer();
   _renderDevice->DrawTriangles(pIndexBuffer, 0, pIndexBuffer->Count());
   return ESuccess;
}

//============================================================
TResult FSampleColorSkeletonEffect::DrawInstanceRenderable(FRenderRegion* pRegion, FInstanceRenderable* pInstanceRenderable, TInt offset, TInt count){
   MO_CHECK(pRegion, return ENull);
   MO_CHECK(pInstanceRenderable, return ENull);
   FRenderableCollection* pRenderables = pRegion->VisibleRenderables();
   TInt boneMatrixCount = 0;
   for(TInt n = 0; n < count; n++){
      FRenderable* pRenderable = pRenderables->Get(offset + n);
      SFloatMatrix3d& renderableMatrix = pRenderable->Matrix();
      // ����ģ�;���
      SFloatMatrix3d modelMatrix;
      pRenderable->CalculateModelMatrix(modelMatrix);
      modelMatrix.Append(renderableMatrix);
      _modelMatrixs[n].Assign(modelMatrix);
      // �����������
      TInt boneCount = pRenderable->CalculateBoneMatrix(_boneMatrixs, boneMatrixCount, MO_EG_CONST_MATRIX_MAX - boneMatrixCount);
      boneMatrixCount += boneCount;
   }
   //............................................................
   BindConstMatrix4x4(EEffectParameter_VertexModelMatrix4x4, (SFloatMatrix3d*)&_modelMatrixs, count);
   BindConstMatrix4x3(EEffectParameter_VertexBoneMatrix4x3, (SFloatMatrix3d*)&_boneMatrixs, boneMatrixCount);
   //............................................................
   // �趨���Լ���
   BindAttributeDescriptors(pInstanceRenderable);
   // ����������
   BindSamplerDescriptors(pInstanceRenderable);
   //............................................................
   // ����������������������
   FRenderIndexBuffer* pIndexBuffer = pInstanceRenderable->IndexBuffer();
   _renderDevice->DrawInstanceTriangles(pIndexBuffer, 0, count);
   return ESuccess;
}

MO_NAMESPACE_END
