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
// <T>���ô���</T>
//============================================================
TResult FColorAutomaticEffect::OnSetup(){
   FAutomaticEffect::OnSetup();
   // ע�ᶥ�㳣��
   _constDescriptors.Register(ERenderShader_Vertex,   EEffectConst_Vertex_ModelMatrix,          "vc_model_matrix");
   _constDescriptors.Register(ERenderShader_Vertex,   EEffectConst_Vertex_ViewProjectionMatrix, "vc_view_projection_matrix");
   _constDescriptors.Register(ERenderShader_Vertex,   EEffectConst_Vertex_CameraPosition,       "vc_camera_position");
   _constDescriptors.Register(ERenderShader_Vertex,   EEffectConst_Vertex_LightDirection,       "vc_light_direction");
   // ע�����س���
   _constDescriptors.Register(ERenderShader_Fragment, EEffectConst_Fragment_CameraPosition,     "fc_camera_position");
   _constDescriptors.Register(ERenderShader_Fragment, EEffectConst_Fragment_LightDirection,     "fc_light_direction");
   // ע����ʳ���
   _constDescriptors.Register(ERenderShader_Fragment, EEffectConst_Fragment_Color,              "fc_color");
   _constDescriptors.Register(ERenderShader_Fragment, EEffectConst_Fragment_Alpha,              "fc_alpha");
   _constDescriptors.Register(ERenderShader_Fragment, EEffectConst_Fragment_AmbientColor,       "fc_ambient_color");
   _constDescriptors.Register(ERenderShader_Fragment, EEffectConst_Fragment_DiffuseColor,       "fc_diffuse_color");
   _constDescriptors.Register(ERenderShader_Fragment, EEffectConst_Fragment_SpecularColor,      "fc_specular_color");
   _constDescriptors.Register(ERenderShader_Fragment, EEffectConst_Fragment_Specular,           "fc_specular");
   _constDescriptors.Register(ERenderShader_Fragment, EEffectConst_Fragment_ReflectColor,       "fc_reflect_color");
   return ESuccess;
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
   BindConstMatrix4x4(EEffectConst_Vertex_ModelMatrix, &modelMatrix);
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
   BindConstMatrix4x4(EEffectConst_Vertex_ModelMatrix, _modelMatrixs, count);
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
   _vpMatrix.Assign(pCamera->Matrix());
   FProjection* pProjection = pCamera->Projection();
   _vpMatrix.Append(pProjection->Matrix());
   //............................................................
   // ���ó���
   BindConstMatrix4x4(EEffectConst_Vertex_ViewProjectionMatrix, &_vpMatrix);
   BindConstPosition3(EEffectConst_Vertex_CameraPosition, pCamera->Position());
   BindConstPosition3(EEffectConst_Fragment_CameraPosition, pCamera->Position());
   FDirectionalLight* pDirectionalLight = pRegion->DirectionalLight();
   if(pDirectionalLight != NULL){
      BindConstVector3(EEffectConst_Vertex_LightDirection, pDirectionalLight->Direction());
      BindConstVector3(EEffectConst_Fragment_LightDirection, pDirectionalLight->Direction());
   }
   //............................................................
   // ���ò���
   FRenderable* pRenderable = pRegion->VisibleRenderables()->Get(offset);
   FMaterial* pMaterial = pRenderable->Material();
   TCharC* pMaerialName = pMaterial->Name();
   BindConstFloat4(EEffectConst_Fragment_Color,         pMaterial->Color().min, pMaterial->Color().max, pMaterial->Color().rate, pMaterial->Color().merge);
   BindConstFloat4(EEffectConst_Fragment_Alpha,         pMaterial->Alpha().base, pMaterial->Alpha().rate, pMaterial->Alpha().level, pMaterial->Alpha().merge);
   BindConstColor4(EEffectConst_Fragment_AmbientColor,  pMaterial->AmbientColor());
   BindConstColor4(EEffectConst_Fragment_DiffuseColor,  pMaterial->DiffuseColor());
   BindConstColor4(EEffectConst_Fragment_SpecularColor, pMaterial->SpecularColor());
   BindConstFloat4(EEffectConst_Fragment_Specular,      pMaterial->SpecularInfo().base, pMaterial->SpecularInfo().rate, pMaterial->SpecularInfo().average, pMaterial->SpecularInfo().shadow);
   BindConstColor4(EEffectConst_Fragment_ReflectColor,  pMaterial->ReflectColor());
   //............................................................
   TResult resultCd = FAutomaticEffect::DrawGroup(pRegion, offset, count);
   //............................................................
   _renderDevice->SetProgram(NULL);
   return resultCd;
}

MO_NAMESPACE_END
