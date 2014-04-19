#ifndef __MO_FR_CONTENT3D_TEXTURE_H__
#define __MO_FR_CONTENT3D_TEXTURE_H__
//************************************************************

#ifndef __MO_FR_COMMON_H__
#include "MoFrCommon.h"
#endif // __MO_FR_COMMON_H__

#ifndef __MO_FR_CONTENT3D_BASE_H__
#include "MoFrContent3dBase.h"
#endif // __MO_FR_CONTENT3D_BASE_H__

MO_NAMESPACE_BEGIN

//============================================================
// <T>��Դ3D����λͼ��</T>
//============================================================
class MO_FR_DECLARE FRs3dTextureBitmap : public FInstance
{
   MO_CLASS_DECLARE_INHERITS(FRs3dTextureBitmap, FInstance);
protected:
   EContent3dTexture _textureCd;
   EContent3dSampler _samplerCd;
   SIntSize2 _size;
   FBytes* _pData;
public:
   FRs3dTextureBitmap();
   MO_ABSTRACT ~FRs3dTextureBitmap();
public:
   //------------------------------------------------------------
   // <T>����������͡�</T>
   MO_INLINE EContent3dTexture TextureCd(){
      return _textureCd;
   }
   //------------------------------------------------------------
   // <T>���ȡ�����͡�</T>
   MO_INLINE EContent3dSampler SamplerCd(){
      return _samplerCd;
   }
   //------------------------------------------------------------
   // <T>��óߴ硣</T>
   MO_INLINE SIntSize2& Size(){
      return _size;
   }
   //------------------------------------------------------------
   // <T>������ݡ�</T>
   MO_INLINE FBytes* Data(){
      return _pData;
   }
public:
   MO_ABSTRACT TResult Unserialize(IDataInput* pInput);
};
//------------------------------------------------------------
typedef MO_FR_DECLARE GPtrs<FRs3dTextureBitmap> GRs3dTextureBitmapPtrs;

//============================================================
// <T>��Դ3D����</T>
//============================================================
class MO_FR_DECLARE FRs3dTexture : public FResource3d
{
   MO_CLASS_DECLARE_INHERITS(FRs3dTexture, FResource3d);
protected:
   GRs3dTextureBitmapPtrs _bitmaps;
public:
   FRs3dTexture();
   MO_ABSTRACT ~FRs3dTexture();
public:
   //------------------------------------------------------------
   // <T>���λͼ���ϡ�</T>
   MO_INLINE GRs3dTextureBitmapPtrs& Bitmaps(){
      return _bitmaps;
   }
public:
   MO_ABSTRACT TResult Unserialize(IDataInput* pInput);
};
//------------------------------------------------------------
typedef MO_FR_DECLARE GPtrDictionary<FRs3dTexture> GRs3dTexturePtrDictionary;

//============================================================
// <T>��Դ3D�������̨��</T>
//============================================================
class MO_FR_DECLARE FRs3dTextureConsole : public FConsole
{
   MO_CLASS_DECLARE_INHERITS(FRs3dTextureConsole, FConsole);
protected:
   GRs3dTexturePtrDictionary _textures;
public:
   FRs3dTextureConsole();
   MO_ABSTRACT ~FRs3dTextureConsole();
public:
   //------------------------------------------------------------
   // <T>��������ϡ�</T>
   MO_INLINE GRs3dTexturePtrDictionary& Textures(){
      return _textures;
   }
public:
   MO_ABSTRACT FRs3dTexture* Load(TCharC* pName);
public:
   FRs3dTexture* Find(TCharC* pName);
   FRs3dTexture* Open(TCharC* pName);
public:
   void Clear();
};

MO_NAMESPACE_END

//************************************************************
#endif // __MO_FR_CONTENT3D_TEXTURE_H__
