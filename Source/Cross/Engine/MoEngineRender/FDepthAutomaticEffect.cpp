#include "MoErTechnique.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FDepthAutomaticEffect, FAutomaticEffect);

//============================================================
// <T>������ȾЧ����</T>
//============================================================
FDepthAutomaticEffect::FDepthAutomaticEffect(){
   _descriptor.supportInstance = ETrue;
}

//============================================================
// <T>������ȾЧ����</T>
//============================================================
FDepthAutomaticEffect::~FDepthAutomaticEffect(){
}

//============================================================
// <T>���ô���</T>
//============================================================
TResult FDepthAutomaticEffect::Setup(){
   FAutomaticEffect::Setup();
   // ע�᳣������
   //_constDescriptors.Register(ERenderShader_Vertex,   EEffectParameter_VertexModelMatrix,          "vc_model_matrix");
   //_constDescriptors.Register(ERenderShader_Vertex,   EEffectParameter_VertexViewProjectionMatrix, "vc_view_projection_matrix");
   //_constDescriptors.Register(ERenderShader_Vertex,   EEffectParameter_VertexCameraPosition,       "vc_camera_position");
   //_constDescriptors.Register(ERenderShader_Vertex,   EEffectParameter_VertexLightDirection,       "vc_light_direction");
   //_constDescriptors.Register(ERenderShader_Fragment, EEffectParameter_FragmentCameraPosition,     "fc_camera_position");
   //_constDescriptors.Register(ERenderShader_Fragment, EEffectParameter_FragmentLightDirection,     "fc_light_direction");
   //_constDescriptors.Register(ERenderShader_Fragment, EEffectParameter_FragmentColor,              "fc_color");
   //_constDescriptors.Register(ERenderShader_Fragment, EEffectParameter_FragmentAlpha,              "fc_alpha");
   //_constDescriptors.Register(ERenderShader_Fragment, EEffectParameter_FragmentAmbientColor,       "fc_ambient_color");
   //_constDescriptors.Register(ERenderShader_Fragment, EEffectParameter_FragmentDiffuseColor,       "fc_diffuse_color");
   //_constDescriptors.Register(ERenderShader_Fragment, EEffectParameter_FragmentSpecularColor,      "fc_specular_color");
   //_constDescriptors.Register(ERenderShader_Fragment, EEffectParameter_FragmentSpecular,           "fc_specular");
   //_constDescriptors.Register(ERenderShader_Fragment, EEffectParameter_FragmentReflectColor,       "fc_reflect_color");
   return ESuccess;
}

//============================================================
// <T>���ƴ���</T>
//============================================================
TResult FDepthAutomaticEffect::DrawRenderable(FRenderRegion* pRegion, FRenderable* pRenderable){
   MO_ASSERT(pRenderable);
   SFloatMatrix3d& renderableMatrix = pRenderable->Matrix();
   // ����豸
   FRenderDevice* pRenderDevice = RDeviceManager::Instance().Find<FRenderDevice>();
   //............................................................
   // ģ�;���
   SMatrix3d modelMatrix;
   pRenderable->CalculateModelMatrix(modelMatrix);
   modelMatrix.Append(renderableMatrix);
   //............................................................
   // ���ó���
   BindConstMatrix4x4(EEffectParameter_VertexModelMatrix4x4, &modelMatrix);
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
TResult FDepthAutomaticEffect::DrawInstanceRenderable(FRenderRegion* pRegion, FInstanceRenderable* pInstanceRenderable, TInt offset, TInt count){
   MO_CHECK(pRegion, return ENull);
   MO_CHECK(pInstanceRenderable, return ENull);
   // ����豸
   FRenderDevice* pRenderDevice = RDeviceManager::Instance().Find<FRenderDevice>();
   //............................................................
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
   pRenderDevice->DrawInstanceTriangles(pIndexBuffer, 0, count);
   return ESuccess;
}

//============================================================
// <T>���ƴ���</T>
//============================================================
TResult FDepthAutomaticEffect::DrawGroup(FRenderRegion* pRegion, TInt offset, TInt count){
   MO_CHECK(pRegion, return ENull);
   // �����豸״̬
   FRenderDevice* pRenderDevice = RDeviceManager::Instance().Find<FRenderDevice>();
   pRenderDevice->SetProgram(_program);
   //............................................................
   // ����任����
   FRenderView* pView = pRegion->ActiveView();
   FCamera* pCamera = pView->Camera();
   _vpMatrix.Assign(pCamera->Matrix());
   FProjection* pProjection = pCamera->Projection();
   _vpMatrix.Append(pProjection->Matrix());
   //............................................................
   // ���ó���
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
   pRenderDevice->SetProgram(NULL);
   return resultCd;
}

MO_NAMESPACE_END
