#include "MoErTechnique.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FColorAutomaticEffect, FAutomaticEffect);

//============================================================
// <T>������ɫ�Զ���Ⱦ����</T>
//============================================================
FColorAutomaticEffect::FColorAutomaticEffect(){
   _descriptor.supportInstance = ETrue;
}

//============================================================
// <T>������ɫ�Զ���Ⱦ����</T>
//============================================================
FColorAutomaticEffect::~FColorAutomaticEffect(){
}

//============================================================
// <T>���ƴ���</T>
//============================================================
TResult FColorAutomaticEffect::DrawRenderable(FRenderRegion* pRegion, FRenderable* pRenderable){
   MO_CHECK(pRegion, return ENull);
   MO_CHECK(pRenderable, return ENull);
   //............................................................
   // ����ģ�;���
   SMatrix3d modelMatrix;
   pRenderable->CalculateModelMatrix(modelMatrix);
   modelMatrix.Append(pRenderable->Matrix());
   BindConstMatrix4x4(EEffectParameter_VertexModelMatrix4x4, &modelMatrix);
   BindConstMatrix4x4(EEffectParameter_VertexModelViewProjectionMatrix4x4, &modelMatrix);
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
TResult FColorAutomaticEffect::DrawInstanceRenderable(FRenderRegion* pRegion, FInstanceRenderable* pInstanceRenderable, TInt offset, TInt count){
   MO_CHECK(pRegion, return ENull);
   MO_CHECK(pInstanceRenderable, return ENull);
   FRenderableCollection* pRenderables = pRegion->Renderables();
   for(TInt n = 0; n < count; n++){
      FRenderable* pRenderable = pRenderables->Get(offset + n);
      SFloatMatrix3d& renderableMatrix = pRenderable->Matrix();
      _modelMatrixs[n].Assign(renderableMatrix);
   }
   BindConstMatrix4x4(EEffectParameter_VertexModelMatrix4x4, _modelMatrixs, count);
   //............................................................
   // �趨���Լ���
   BindAttributeDescriptors(pInstanceRenderable);
   // ����������
   BindSamplerDescriptors(pInstanceRenderable);
   //............................................................
   // ����������������������
   FRenderIndexBuffer* pIndexBuffer = pInstanceRenderable->IndexBuffer();
   _renderDevice->DrawInstanceTriangles(pIndexBuffer, 0, 1);
   //............................................................
   UnbindAttributeDescriptors(pInstanceRenderable);
   return ESuccess;
}

//============================================================
// <T>���ƴ���</T>
//============================================================
TResult FColorAutomaticEffect::DrawGroup(FRenderRegion* pRegion, TInt offset, TInt count){
   MO_CHECK(pRegion, return ENull);
   // �����豸״̬
   _renderDevice->SetProgram(_program);
   //............................................................
   // ����任����
   FRenderView* pView = pRegion->ActiveView();
   FCamera* pCamera = pView->Camera();
   SFloatMatrix3d& viewMatrix = pCamera->Matrix();
   _vpMatrix.Assign(viewMatrix);
   FProjection* pProjection = pCamera->Projection();
   SFloatMatrix3d& projectionMatrix = pProjection->Matrix();
   _vpMatrix.Append(projectionMatrix);
   //............................................................
   // ���ó���
   BindConstMatrix4x4(EEffectParameter_VertexViewMatrix4x4, &viewMatrix);
   BindConstMatrix4x4(EEffectParameter_VertexProjectionMatrix4x4, &projectionMatrix);
   BindConstMatrix4x4(EEffectParameter_VertexViewProjectionMatrix4x4, &_vpMatrix);
   BindConstPosition3(EEffectParameter_VertexCameraPosition, pCamera->Position());
   BindConstPosition3(EEffectParameter_FragmentCameraPosition, pCamera->Position());
   FDirectionalLight* pDirectionalLight = pRegion->DirectionalLight();
   if(pDirectionalLight != NULL){
      BindConstVector3(EEffectParameter_VertexLightDirection, pDirectionalLight->Direction());
      BindConstVector3(EEffectParameter_FragmentLightDirection, pDirectionalLight->Direction());
   }
   //............................................................
   // ���ò���
   FRenderable* pRenderable = pRegion->VisibleRenderables()->Get(offset);
   FMaterial* pMaterial = pRenderable->Material();
   TCharC* pMaerialName = pMaterial->Name();
   BindConstFloat4(EEffectParameter_FragmentColor,         pMaterial->Color().min, pMaterial->Color().max, pMaterial->Color().rate, pMaterial->Color().merge);
   BindConstFloat4(EEffectParameter_FragmentAlpha,         pMaterial->Alpha().base, pMaterial->Alpha().rate, pMaterial->Alpha().level, pMaterial->Alpha().merge);
   BindConstColor4(EEffectParameter_FragmentAmbientColor,  pMaterial->AmbientColor());
   BindConstColor4(EEffectParameter_FragmentDiffuseColor,  pMaterial->DiffuseColor());
   BindConstColor4(EEffectParameter_FragmentSpecularColor, pMaterial->SpecularColor());
   BindConstFloat4(EEffectParameter_FragmentSpecular,      pMaterial->SpecularInfo().base, pMaterial->SpecularInfo().rate, pMaterial->SpecularInfo().average, pMaterial->SpecularInfo().shadow);
   BindConstColor4(EEffectParameter_FragmentReflectColor,  pMaterial->ReflectColor());
   //............................................................
   TResult resultCd = FAutomaticEffect::DrawGroup(pRegion, offset, count);
   //............................................................
   _renderDevice->SetProgram(NULL);
   return resultCd;
}

MO_NAMESPACE_END
