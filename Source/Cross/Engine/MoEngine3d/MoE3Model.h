#ifndef __MO_E3_MODEL_H__
#define __MO_E3_MODEL_H__
//************************************************************

#ifndef __MO_E3_COMMON_H__
#include "MoE3Common.h"
#endif // __MO_E3_COMMON_H__

#ifndef __MO_E3_DISPLAY_H__
#include "MoE3Display.h"
#endif // __MO_E3_DISPLAY_H__

MO_NAMESPACE_BEGIN

//============================================================
class FModel3d;

//============================================================
// <T>ʵ��3D�����塣</T>
//============================================================
class MO_E3_DECLARE FModel3dRenderable : public FRenderable3d
{
   MO_CLASS_DECLARE_INHERITS(FModel3dRenderable, FRenderable3d);
protected:
   TString _modelName;
   TString _materialName;
public:
   FModel3dRenderable();
   MO_ABSTRACT ~FModel3dRenderable();
public:
   //------------------------------------------------------------
   // <T>���ģ�����ơ�</T>
   MO_INLINE TCharC* ModelName(){
      return _modelName;
   }
   //------------------------------------------------------------
   // <T>���ģ�����ơ�</T>
   MO_INLINE void SetModelName(TCharC* pModelName){
      _modelName = pModelName;
   }
   //------------------------------------------------------------
   // <T>��ò������ơ�</T>
   MO_INLINE TCharC* MaterialName(){
      return _materialName;
   }
   //------------------------------------------------------------
   // <T>���ò������ơ�</T>
   MO_INLINE void SetMaterialName(TCharC* pMaterialName){
      _materialName = pMaterialName;
   }
};
//------------------------------------------------------------
typedef MO_E3_DECLARE FObjects<FModel3dRenderable*> FModel3dRenderableCollection;

//============================================================
// <T>ʵ��3D�����塣</T>
//============================================================
class MO_E3_DECLARE FModel3dGeometry : public FRenderable3d
{
   MO_CLASS_DECLARE_INHERITS(FModel3dGeometry, FRenderable3d);
protected:
   FModel3d* _pModel;
   FRs3dGeometry* _pResource;
   FRs3dMaterial* _pMaterialResource;
   FBone3dCollection* _pBones;
public:
   FModel3dGeometry();
   MO_ABSTRACT ~FModel3dGeometry();
public:
   //------------------------------------------------------------
   // <T>���ģ��ʵ����</T>
   MO_INLINE FModel3d* Model(){
      return _pModel;
   }
   //------------------------------------------------------------
   // <T>����ģ��ʵ����</T>
   MO_INLINE void SetModel(FModel3d* pModel){
      _pModel = pModel;
   }
   //------------------------------------------------------------
   // <T>�����Դ��</T>
   MO_INLINE FRs3dGeometry* Resource(){
      return _pResource;
   }
public:
   TResult LoadResource(FRs3dGeometry* pResource);
};
//------------------------------------------------------------
typedef MO_E3_DECLARE FVector<FModel3dGeometry*> FModel3dGeometryCollection;

//============================================================
// <T>��ʾ3Dģ�͡�</T>
//============================================================
class MO_E3_DECLARE FModel3d : public FDisplay3d
{
   MO_CLASS_DECLARE_INHERITS(FModel3d, FDisplay3d);
protected:
   FRs3dModel* _pResource;
   FModel3dGeometryCollection* _pGeometrys;
   FAnimation3d* _pAnimation;
public:
   FModel3d();
   MO_ABSTRACT ~FModel3d();
public:
   //------------------------------------------------------------
   // <T>�����Դ��</T>
   MO_INLINE FRs3dModel* Resource(){
      return _pResource;
   }
   //------------------------------------------------------------
   // <T>�����Ⱦ���󼯺ϡ�</T>
   MO_INLINE FModel3dGeometryCollection* Geometrys(){
      return _pGeometrys;
   }
   //------------------------------------------------------------
   // <T>��ö�����</T>
   MO_INLINE FAnimation3d* Animation(){
      return _pAnimation;
   }
public:
   TResult LoadResource(FRs3dTemplate* pResource);
   TResult LoadResource(FRs3dModel* pResource);
};
//------------------------------------------------------------
typedef MO_E3_DECLARE FPool<FModel3d*> FModel3dPool;
typedef MO_E3_DECLARE FSet<TResourceId, FModel3dPool*> FModel3dPoolSet;
typedef MO_E3_DECLARE FDictionary<FModel3d*> FModel3dDictionary;

//============================================================
// <T>ʵ��3D�����塣</T>
//============================================================
class MO_E3_DECLARE FDynamicModel3dGeometry : public FRenderable3d
{
   MO_CLASS_DECLARE_INHERITS(FDynamicModel3dGeometry, FRenderable3d);
protected:
   FModel3d* _pModel;
   FRs3dGeometry* _pResource;
   FRs3dMaterial* _pMaterialResource;
   FModel3dRenderableCollection* _pModelRenderables;
   GDynamicRenderablePtrs _dynamicRenderables;
public:
   FDynamicModel3dGeometry();
   MO_ABSTRACT ~FDynamicModel3dGeometry();
public:
   //------------------------------------------------------------
   // <T>���ģ��ʵ����</T>
   MO_INLINE FModel3d* Model(){
      return _pModel;
   }
   //------------------------------------------------------------
   // <T>����ģ��ʵ����</T>
   MO_INLINE void SetModel(FModel3d* pModel){
      _pModel = pModel;
   }
   //------------------------------------------------------------
   // <T>���ģ����Ⱦ���ϡ�</T>
   MO_INLINE FModel3dRenderableCollection* ModelRenderables(){
      return _pModelRenderables;
   }
   //------------------------------------------------------------
   // <T>��ö�̬��Ⱦ���󼯺ϡ�</T>
   MO_INLINE GDynamicRenderablePtrs& DynamicRenderables(){
      return _dynamicRenderables;
   }
public:
   TResult Merge();
};
//------------------------------------------------------------
typedef MO_E3_DECLARE FVector<FDynamicModel3dGeometry*> FDynamicModel3dGeometryCollection;

//============================================================
// <T>��ʾ��̬ģ�͡�</T>
//============================================================
class MO_E3_DECLARE FDynamicModel3d : public FDisplay3d
{
   MO_CLASS_DECLARE_INHERITS(FDynamicModel3d, FDisplay3d);
protected:
   FModel3dRenderableCollection* _pModelRenderables;
   FDynamicModel3dGeometryCollection* _pGeometrys;
public:
   FDynamicModel3d();
   MO_ABSTRACT ~FDynamicModel3d();
public:
   //------------------------------------------------------------
   // <T>���ģ����Ⱦ���ϡ�</T>
   MO_INLINE FModel3dRenderableCollection* ModelRenderables(){
      return _pModelRenderables;
   }
   //------------------------------------------------------------
   // <T>�����Ⱦ���󼯺ϡ�</T>
   MO_INLINE FDynamicModel3dGeometryCollection* Geometrys(){
      return _pGeometrys;
   }
public:
   FDynamicModel3dGeometry* SyncGeometryByRenderable(FModel3dRenderable* pRenderable);
public:
   TResult PushRenderable(FModel3dRenderable* pRenderable);
   TResult Merge();
};

//============================================================
// <T>ʵ��3Dģ�͹�������</T>
//============================================================
class MO_E3_DECLARE FModel3dConsole : public FConsole{
protected:
   FModel3dDictionary* _pModels;
   FModel3dPoolSet* _pPools;
   FInstanceRenderableDictionary* _pInstanceRenderables;
public:
   FModel3dConsole();
   MO_ABSTRACT ~FModel3dConsole();
public:
   //------------------------------------------------------------
   // <T>���ģ�ͼ��ϡ�</T>
   MO_INLINE FModel3dPoolSet* Pools(){
      return _pPools;
   }
public:
   FModel3d* Create(TResourceId resourceId);
   FModel3d* Alloc(TResourceId resourceId);
   void Free(FModel3d* pModel);
public:
   FModel3d* Load(TCharC* pName);
   FInstanceRenderable* LoadInstance(FRenderable* pRenderable, TInt instanceCount = -1);
   void Clear();
};

MO_NAMESPACE_END

//************************************************************
#endif // __MO_E3_MODEL_H__
