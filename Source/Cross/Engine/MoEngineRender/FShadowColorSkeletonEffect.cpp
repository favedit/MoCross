#include "MoErShadowPipeline.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FShadowColorSkeletonEffect, FColorAutomaticEffect);

//============================================================
// <T>������Ӱ��ɫ�Զ���Ⱦ����</T>
//============================================================
FShadowColorSkeletonEffect::FShadowColorSkeletonEffect(){
}

//============================================================
// <T>������Ӱ��ɫ�Զ���Ⱦ����</T>
//============================================================
FShadowColorSkeletonEffect::~FShadowColorSkeletonEffect(){
}

//============================================================
// <T>���ô���</T>
//============================================================
TResult FShadowColorSkeletonEffect::OnSetup(){
   FAutomaticEffect::OnSetup();
   return ESuccess;
}

//============================================================
// <T>���ƴ���</T>
//============================================================
TResult FShadowColorSkeletonEffect::DrawRenderable(FRenderRegion* pRegion, FRenderable* pRenderable){
   MO_ASSERT(pRegion);
   MO_ASSERT(pRenderable);
   FRenderView* pView = pRegion->ActiveView();
   FCamera* pCamera = pView->Camera();
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
   modelViewMatrix.Append(pCamera->Matrix());
   // ����MVP����
   SMatrix3d matrixMvp;
   matrixMvp.Assign(modelMatrix);
   matrixMvp.Append(_vpMatrix);
   //............................................................
   // ����MVP����
   SMatrix3d lightMvMatrix;
   lightMvMatrix.Assign(modelMatrix);
   lightMvMatrix.Append(pLightCamera->Matrix());
   // ����MVP����
   SMatrix3d lightMvpMatrix;
   lightMvpMatrix.Assign(modelMatrix);
   lightMvpMatrix.Append(_lightVpMatrix);
   //............................................................
   // ���ó���
   BindConstMatrix3x3(EEffectParameter_VertexModelMatrix3x3, &modelMatrix);
   BindConstMatrix4x4(EEffectParameter_VertexModelMatrix4x4, &modelMatrix);
   BindConstMatrix4x4(EEffectParameter_VertexModelViewProjectionMatrix4x4, &matrixMvp);
   BindConstMatrix4x4(EEffectParameter_VertexLightModelViewMatrix4x4, &lightMvMatrix);
   BindConstMatrix4x4(EEffectParameter_VertexLightModelViewProjectionMatrix4x4, &lightMvpMatrix);
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
TResult FShadowColorSkeletonEffect::DrawGroup(FRenderRegion* pRegion, TInt offset, TInt count){
   MO_CHECK(pRegion, return ENull);
   // ���������Ϣ
   FRenderTexture* pLightDepthTexture =  pRegion->Textures()->Get(0);
   FRenderView* pView = pRegion->ActiveView();
   FCamera* pCamera = pView->Camera();
   _vpMatrix.Assign(pCamera->Matrix());
   FProjection* pProjection = pCamera->Projection();
   _vpMatrix.Append(pProjection->Matrix());
   //............................................................
   // ���ù�Դ��Ϣ
   FDirectionalLight* pLight = pRegion->DirectionalLight();
   TFloat ambientShadow = pLight->Material()->AmbientShadow();
   TFloat diffuseShadow = pLight->Material()->DiffuseShadow();
   TFloat specularShadow = pLight->Material()->SpecularShadow();
   TFloat specularViewShadow = pLight->Material()->SpecularViewShadow();
   FCamera* pLightCamera = pLight->Camera();
   SFloatVector3& lightDirection = pLightCamera->Direction();
   _lightVpMatrix.Assign(pLightCamera->Matrix());
   FProjection* pLightProjection = pLightCamera->Projection();
   _lightVpMatrix.Append(pLightProjection->Matrix());
   // �����豸״̬
   FRenderDevice* pRenderDevice = RDeviceManager::Instance().Find<FRenderDevice>();
   pRenderDevice->SetProgram(_program);
   //............................................................
   // ���������Ϣ
   BindConstPosition3(EEffectParameter_VertexCameraPosition, pCamera->Position());
   BindConstPosition3(EEffectParameter_FragmentCameraPosition, pCamera->Position());
   // ���ù�Դ��Ϣ
   BindConstVector3(EEffectParameter_VertexLightDirection, lightDirection);
   BindConstVector3(EEffectParameter_FragmentLightDirection, lightDirection);
   // ���ù�Դ���
   SIntSize2& depthSize = pLightDepthTexture->Size();
   TFloat lightZnear = pLightProjection->Znear();
   TFloat lightZfar = pLightProjection->Zfar();
   BindConstFloat4(EEffectParameter_FragmentLightDepth, -1.0f / (TFloat)depthSize.width, 1.0f / (TFloat)depthSize.width, lightZnear, 1.0f / lightZfar);
   //............................................................
   // ���ò���
   FRenderable* pRenderable = pRegion->VisibleRenderables()->Get(offset);
   FMaterial* pMaterial = pRenderable->Material();
   BindConstFloat4(EEffectParameter_FragmentShadowMaterial,    ambientShadow, diffuseShadow, specularShadow, specularViewShadow);
   BindConstFloat4(EEffectParameter_FragmentShadowMaterialInv, 1.0f - ambientShadow, 1.0f - diffuseShadow, 1.0f - specularShadow, 1.0f - specularViewShadow);
   BindConstFloat4(EEffectParameter_FragmentColor,             pMaterial->Color().min, pMaterial->Color().max, pMaterial->Color().rate, pMaterial->Color().merge);
   BindConstFloat4(EEffectParameter_FragmentAlpha,             pMaterial->Alpha().base, pMaterial->Alpha().rate, pMaterial->Alpha().level, pMaterial->Alpha().merge);
   BindConstColor4(EEffectParameter_FragmentAmbientColor,      pMaterial->AmbientColor());
   BindConstColor4(EEffectParameter_FragmentDiffuseColor,      pMaterial->DiffuseColor());
   BindConstColor4(EEffectParameter_FragmentDiffuseViewColor,  pMaterial->DiffuseViewColor());
   BindConstColor4(EEffectParameter_FragmentSpecularColor,     pMaterial->SpecularColor());
   BindConstFloat4(EEffectParameter_FragmentSpecular,          pMaterial->SpecularInfo().base, pMaterial->SpecularInfo().rate, pMaterial->SpecularInfo().average, pMaterial->SpecularInfo().shadow);
   BindConstColor4(EEffectParameter_FragmentSpecularViewColor, pMaterial->SpecularViewColor());
   BindConstFloat4(EEffectParameter_FragmentSpecularView,      pMaterial->SpecularViewInfo().base, pMaterial->SpecularViewInfo().rate, pMaterial->SpecularViewInfo().average, pMaterial->SpecularViewInfo().shadow);
   BindConstColor4(EEffectParameter_FragmentReflectColor,      pMaterial->ReflectColor());
   //............................................................
   // ����������
   BindSampler(ERenderSampler_LightDepth, pLightDepthTexture);
   //............................................................
   FAutomaticEffect::DrawGroup(pRegion, offset, count);
   //............................................................
   // �رճ���
   pRenderDevice->SetProgram(NULL);
   return ESuccess;
}

MO_NAMESPACE_END
