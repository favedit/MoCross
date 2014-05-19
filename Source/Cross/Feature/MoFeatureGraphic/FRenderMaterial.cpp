#include "MoFgRender.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FRenderMaterial, FMaterial);

//============================================================
// <T>������Ⱦ���ʡ�</T>
//============================================================
FRenderMaterial::FRenderMaterial(){
}

//============================================================
// <T>������Ⱦ���ʡ�</T>
//============================================================
FRenderMaterial::~FRenderMaterial(){
}

//============================================================
// <T>����һ����Ⱦ��������</T>
//
// @param pMaterialTexture ��Ⱦ��������
// @return ������
//============================================================
TResult FRenderMaterial::TexturePush(FRenderMaterialTexture* pMaterialTexture){
   MO_CHECK(pMaterialTexture, return ENull);
   _textures.Push(pMaterialTexture);
   return ESuccess;
}

//============================================================
// <T>����һ����Ⱦ��������</T>
//
// @param pMaterialTexture ��Ⱦ��������
// @return ������
//============================================================
TResult FRenderMaterial::TextureRemove(FRenderMaterialTexture* pMaterialTexture){
   MO_CHECK(pMaterialTexture, return ENull);
   _textures.Remove(pMaterialTexture);
   return ESuccess;
}

//============================================================
// <T>���������Ⱦ��������</T>
//
// @return ������
//============================================================
TResult FRenderMaterial::TextureClear(){
   _textures.Clear();
   return ESuccess;
}

MO_NAMESPACE_END
