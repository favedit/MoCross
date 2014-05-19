#ifndef __MO_FR_CONTENT3D_MATERIAL_H__
#define __MO_FR_CONTENT3D_MATERIAL_H__
//************************************************************

#ifndef __MO_FR_COMMON_H__
#include "MoFrCommon.h"
#endif // __MO_FR_COMMON_H__

#ifndef __MO_FR_CONTENT3D_BASE_H__
#include "MoFrContent3dBase.h"
#endif // __MO_FR_CONTENT3D_BASE_H__

MO_NAMESPACE_BEGIN

//============================================================
// <T>��Դ3D��������</T>
//============================================================
class MO_FR_DECLARE FRs3dMaterialTexture : public FInstance
{
   MO_CLASS_DECLARE_INHERITS(FRs3dMaterialTexture, FInstance);
protected:
   TString _code;
   TString _textureName;
public:
   FRs3dMaterialTexture();
   MO_ABSTRACT ~FRs3dMaterialTexture();
public:
   //------------------------------------------------------------
   // <T>�ж��Ƿ�ָ�����롣</T>
   MO_INLINE TBool IsCode(TCharC* pCode){
      return _code.Equals(pCode);
   }
   //------------------------------------------------------------
   // <T>��ô��롣</T>
   MO_INLINE TCharC* Code(){
      return _code;
   }
   //------------------------------------------------------------
   // <T>���ô��롣</T>
   MO_INLINE void SetCode(TCharC* pCode){
      _code = pCode;
   }
   //------------------------------------------------------------
   // <T>��������š�</T>
   MO_INLINE TCharC* TextureName(){
      return _textureName;
   }
public:
   MO_OVERRIDE TResult Unserialize(IDataInput* pInput);
};
//------------------------------------------------------------
typedef MO_FR_DECLARE GPtrs<FRs3dMaterialTexture> GRs3dMaterialTexturePtrs;

//============================================================
// <T>��Դ3D���ʡ�</T>
//============================================================
class MO_FR_DECLARE FRs3dMaterial : public FResource3d
{
   MO_CLASS_DECLARE_INHERITS(FRs3dMaterial, FResource3d);
protected:
   // ������Ϣ
   SMaterialInfo _info;
   // ������
   GRs3dMaterialTexturePtrs _textures;
public:
   FRs3dMaterial();
   MO_ABSTRACT ~FRs3dMaterial();
public:
   //------------------------------------------------------------
   // <T>��ò�����Ϣ��</T>
   MO_INLINE SMaterialInfo& Info(){
      return _info;
   }
   //------------------------------------------------------------
   // <T>��������ϡ�</T>
   MO_INLINE GRs3dMaterialTexturePtrs& Textures(){
      return _textures;
   }
public:
   MO_ABSTRACT TResult Unserialize(IDataInput* pInput);
public:
   void Reset();
};
//------------------------------------------------------------
typedef MO_FR_DECLARE GPtrDictionary<FRs3dMaterial> GRs3dMaterialPtrDictionary;

//============================================================
// <T>��Դ3D���ʿ���̨��</T>
//============================================================
class MO_FR_DECLARE FRs3dMaterialConsole : public FConsole
{
   MO_CLASS_DECLARE_INHERITS(FRs3dMaterialConsole, FConsole);
protected:
   GRs3dMaterialPtrDictionary _materials;
public:
   FRs3dMaterialConsole();
   MO_ABSTRACT ~FRs3dMaterialConsole();
public:
   //------------------------------------------------------------
   // <T>��ò����ֵ䡣</T>
   MO_INLINE GRs3dMaterialPtrDictionary& Materials(){
      return _materials;
   }
public:
   FRs3dMaterial* Find(TCharC* pName);
   FRs3dMaterial* Get(TCharC* pName);
public:
   void Clear();
};

MO_NAMESPACE_END

//************************************************************
#endif // __MO_FR_CONTENT3D_MATERIAL_H__
