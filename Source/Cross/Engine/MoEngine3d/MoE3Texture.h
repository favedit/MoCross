#ifndef __MO_E3_TEXTURE_H__
#define __MO_E3_TEXTURE_H__
//************************************************************

#ifndef __MO_E3_COMMON_H__
#include "MoE3Common.h"
#endif // __MO_E3_COMMON_H__

#ifndef __MO_E3_DISPLAY_H__
#include "MoE3Display.h"
#endif // __MO_E3_DISPLAY_H__

MO_NAMESPACE_BEGIN

//============================================================
// <T>����3Dλͼ��</T>
//============================================================
class MO_E3_DECLARE FTexture3dBitmap : public FInstance
{
   MO_CLASS_DECLARE_INHERITS(FTexture3dBitmap, FInstance);
protected:
   FRs3dTextureBitmap* _pResource;
   GPtr<FRenderTexture> _renderTexture;
public:
   FTexture3dBitmap();
   MO_ABSTRACT ~FTexture3dBitmap();
public:
   //------------------------------------------------------------
   // <T>���λͼ��Դ��</T>
   MO_INLINE FRs3dTextureBitmap* Resource(){
      return _pResource;
   }
   //------------------------------------------------------------
   // <T>�����Ⱦ����</T>
   MO_INLINE FRenderTexture* RenderTexture(){
      return _renderTexture;
   }
public:
   MO_ABSTRACT TResult LoadResource(FRs3dTextureBitmap* pResource);
public:
   TResult Open();
   TResult Close();
};
//------------------------------------------------------------
typedef MO_E3_DECLARE FObjects<FTexture3dBitmap*> FTexture3dBitmapCollection;

//============================================================
// <T>��Դ3D�������̨��</T>
//============================================================
class MO_E3_DECLARE FTexture3dTexture : public FInstance
{
   MO_CLASS_DECLARE_INHERITS(FTexture3dTexture, FInstance);
protected:
   FRs3dTexture* _pResource;
   FTexture3dBitmapCollection* _pBitmaps;
public:
   FTexture3dTexture();
   MO_ABSTRACT ~FTexture3dTexture();
public:
   //------------------------------------------------------------
   // <T>���λͼ���ϡ�</T>
   MO_INLINE FRs3dTexture* Resource(){
      return _pResource;
   }
   //------------------------------------------------------------
   // <T>���λͼ���ϡ�</T>
   MO_INLINE FTexture3dBitmapCollection* Bitmaps(){
      return _pBitmaps;
   }
public:
   FTexture3dBitmap* FindByCode(TCharC* pCode);
public:
   MO_ABSTRACT TResult LoadResource(FRs3dTexture* pResource);
   MO_ABSTRACT TResult Open();
   MO_ABSTRACT TResult Close();
};
//------------------------------------------------------------
typedef MO_E3_DECLARE FDictionary<FTexture3dTexture*> FTexture3dTextureDictionary;

//============================================================
// <T>ʵ��3D�����������</T>
//============================================================
class MO_E3_DECLARE FTexture3dConsole : public FConsole{
protected:
   FTexture3dTextureDictionary* _pTextures;
public:
   FTexture3dConsole();
   MO_ABSTRACT ~FTexture3dConsole();
public:
   //------------------------------------------------------------
   // <T>��������ϡ�</T>
   MO_INLINE FTexture3dTextureDictionary* Textures(){
      return _pTextures;
   }
public:
   FTexture3dTexture* Find(TCharC* pName);
   FTexture3dTexture* Load(TCharC* pName);
};

MO_NAMESPACE_END

//************************************************************
#endif // __MO_E3_TEXTURE_H__
