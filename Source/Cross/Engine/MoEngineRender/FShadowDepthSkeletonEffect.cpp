#include "MoErShadowPipeline.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FShadowDepthSkeletonEffect, FAutomaticEffect);

//============================================================
// <T>������Ӱ����Զ���Ⱦ����</T>
//============================================================
FShadowDepthSkeletonEffect::FShadowDepthSkeletonEffect(){
}

//============================================================
// <T>������Ӱ����Զ���Ⱦ����</T>
//============================================================
FShadowDepthSkeletonEffect::~FShadowDepthSkeletonEffect(){
}

//============================================================
// <T>���ô���</T>
//============================================================
TResult FShadowDepthSkeletonEffect::Setup(){
   TResult resultCd = FAutomaticEffect::Setup();
   return resultCd;
}

//============================================================
// <T>���ƴ���</T>
//
// @param pRegion ��Ⱦ����
// @param pRenderable ��Ⱦ����
//============================================================
TResult FShadowDepthSkeletonEffect::DrawRenderable(FRenderRegion* pRegion, FRenderable* pRenderable){
   MO_ASSERT(pRegion);
   MO_ASSERT(pRenderable);
   FRenderView* pView = pRegion->ActiveView();
   FDirectionalLight* pLight = pRegion->DirectionalLight();
   FCamera* pLightCamera = pLight->Camera();
   FProjection* pLightProjection = pLightCamera->Projection();
   SFloatMatrix3d& renderableMatrix = pRenderable->Matrix();
   // ����豸
   FRenderDevice* pRenderDevice = RDeviceManager::Instance().Find<FRenderDevice>();
   //............................................................
   // ģ�;���
   SMatrix3d modelMatrix;
   pRenderable->CalculateModelMatrix(modelMatrix);
   modelMatrix.Append(renderableMatrix);
   // ����MVP����
   SMatrix3d modelViewMatrix;
   modelViewMatrix.Assign(modelMatrix);
   modelViewMatrix.Append(pLightCamera->Matrix());
   // ����MVP����
   SMatrix3d matrixMvp;
   matrixMvp.Assign(modelMatrix);
   matrixMvp.Append(_vpMatrix);
   //............................................................
   // ���ó���
   BindConstMatrix4x4(EEffectParameter_VertexModelMatrix4x4, &modelViewMatrix);
   BindConstMatrix4x4(EEffectParameter_VertexModelViewProjectionMatrix4x4, &matrixMvp);
   //............................................................
   // �趨���Լ���
   BindAttributeDescriptors(pRenderable);
   // ����������
   BindSamplerDescriptors(pRenderable);
   //............................................................
   // ����������������������
   FRenderIndexBuffer* pIndexBuffer = pRenderable->IndexBuffer();
   pRenderDevice->DrawTriangles(pIndexBuffer, 0, pIndexBuffer->Count());
   return ESuccess;
}

//============================================================
// <T>���ƴ���</T>
//============================================================
TResult FShadowDepthSkeletonEffect::DrawGroup(FRenderRegion* pRegion, TInt offset, TInt count){
   MO_CHECK(pRegion, return ENull);
   // ����任����
   FRenderView* pView = pRegion->ActiveView();
   FDirectionalLight* pLight = pRegion->DirectionalLight();
   FCamera* pLightCamera = pLight->Camera();
   _vpMatrix.Assign(pLightCamera->Matrix());
   FProjection* pLightProjection = pLightCamera->Projection();
   _vpMatrix.Append(pLightProjection->Matrix());
   // �����豸״̬
   FRenderDevice* pRenderDevice = RDeviceManager::Instance().Find<FRenderDevice>();
   pRenderDevice->SetProgram(_program);
   //............................................................
   TFloat lightZnear = pLightProjection->Znear();
   TFloat lightZfar = pLightProjection->Zfar();
   BindConstFloat4(EEffectParameter_FragmentCamera, 0.0f, 0.0f, lightZnear, 1.0f / lightZfar);
   //............................................................
   FAutomaticEffect::DrawGroup(pRegion, offset, count);
   //............................................................
   // �رճ���
   pRenderDevice->SetProgram(NULL);
   return ESuccess;
}

MO_NAMESPACE_END
