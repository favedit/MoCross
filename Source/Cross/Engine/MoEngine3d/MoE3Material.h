#ifndef __MO_E3_MATERIAL_H__
#define __MO_E3_MATERIAL_H__
//************************************************************

#ifndef __MO_E3_COMMON_H__
#include "MoE3Common.h"
#endif // __MO_E3_COMMON_H__

#ifndef __MO_E3_DISPLAY_H__
#include "MoE3Display.h"
#endif // __MO_E3_DISPLAY_H__

#ifndef __MO_E3_TEXTURE_H__
#include "MoE3Texture.h"
#endif // __MO_E3_TEXTURE_H__

MO_NAMESPACE_BEGIN

//============================================================
// <T>ʵ��3D��������</T>
//============================================================
class MO_E3_DECLARE FMaterial3dTexture : public FRenderMaterialTexture
{
   MO_CLASS_DECLARE_INHERITS(FMaterial3dTexture, FRenderMaterialTexture);
protected:
   GPtr<FRs3dMaterialTexture> _resource;
   GPtr<FRenderTexture> _renderTexture;
public:
   FMaterial3dTexture();
   MO_ABSTRACT ~FMaterial3dTexture();
public:
   //------------------------------------------------------------
   // <T>���������Դ��</T>
   MO_INLINE FRs3dMaterialTexture* Resource(){
      return _resource;
   }
   //------------------------------------------------------------
   // <T>�����Ⱦ����</T>
   MO_INLINE FRenderTexture* RenderTexture(){
      return _renderTexture;
   }
public:
   TResult LoadResource(FRs3dMaterialTexture* pResource);
};
//------------------------------------------------------------
typedef MO_E3_DECLARE GPtrs<FMaterial3dTexture> GMaterial3dTexturePtrs;

//============================================================
// <T>ʵ��3D���ʡ�</T>
//============================================================
class MO_E3_DECLARE FMaterial3d : public FRenderMaterial
{
   MO_CLASS_DECLARE_INHERITS(FMaterial3d, FMaterial);
protected:
   GMaterial3dTexturePtrs _materialTextures;
public:
   FMaterial3d();
   MO_ABSTRACT ~FMaterial3d();
public:
   //------------------------------------------------------------
   // <T>��������ϡ�</T>
   MO_INLINE GMaterial3dTexturePtrs& MaterialTextures(){
      return _materialTextures;
   }
public:
   TResult BuildDescriptor(SRenderableDescriptor& descriptor);
   TResult LoadResource(FRs3dMaterial* pResource);
};
//------------------------------------------------------------
typedef MO_E3_DECLARE GPtrDictionary<FMaterial3d> GMaterial3dPtrDictionary;

//============================================================
// <T>ʵ��3D���ʹ�������</T>
//============================================================
class MO_E3_DECLARE FMaterial3dConsole : public FConsole{
protected:
   GMaterial3dPtrDictionary _materials;
public:
   FMaterial3dConsole();
   MO_ABSTRACT ~FMaterial3dConsole();
public:
   //------------------------------------------------------------
   // <T>��������ϡ�</T>
   MO_INLINE GMaterial3dPtrDictionary& Textures(){
      return _materials;
   }
public:
   FMaterial3d* Load(TCharC* pName);
};

MO_NAMESPACE_END

//************************************************************
#endif // __MO_E3_MATERIAL_H__
