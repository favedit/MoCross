#ifndef __MO_E3_SCENE_H__
#define __MO_E3_SCENE_H__
//************************************************************

#ifndef __MO_E3_COMMON_H__
#include "MoE3Common.h"
#endif // __MO_E3_COMMON_H__

#ifndef __MO_E3_DISPLAY_H__
#include "MoE3Display.h"
#endif // __MO_E3_DISPLAY_H__

#ifndef __MO_E3_TEMPLATE_H__
#include "MoE3Template.h"
#endif // __MO_E3_TEMPLATE_H__

MO_NAMESPACE_BEGIN

//============================================================
// <T>����������</T>
//============================================================
class MO_E3_DECLARE FScene3dMovie : public FInstance
{
   MO_CLASS_DECLARE_INHERITS(FScene3dMovie, FInstance);
protected:
   TTimeSpan _interval;
   FRs3dSceneMovie* _pResource;
public:
   FScene3dMovie();
   MO_ABSTRACT ~FScene3dMovie();
public:
   MO_ABSTRACT TResult LoadResource(FRs3dSceneMovie* pResource);
public:
   MO_ABSTRACT TResult Process(SFloatMatrix3d& matrix);
};
//------------------------------------------------------------
typedef MO_E3_DECLARE GPtrs<FScene3dMovie> FScene3dMoviePtrs;

//============================================================
// <T>����������</T>
//============================================================
class MO_E3_DECLARE FScene3dMovieRotation : public FScene3dMovie
{
   MO_CLASS_DECLARE_INHERITS(FScene3dMovieRotation, FScene3dMovie);
protected:
   SFloatVector3 _rotation;
   TTimeTick _lastTick;
public:
   FScene3dMovieRotation();
   MO_ABSTRACT ~FScene3dMovieRotation();
public:
   MO_OVERRIDE TResult LoadResource(FRs3dSceneMovie* pResource);
public:
   MO_OVERRIDE TResult Process(SFloatMatrix3d& matrix);
};

//============================================================
// <T>����3D���ʡ�</T>
//============================================================
class MO_E3_DECLARE FScene3dMaterial : public FMaterial
{
   MO_CLASS_DECLARE_INHERITS(FScene3dMaterial, FMaterial);
public:
   FScene3dMaterial();
   MO_ABSTRACT ~FScene3dMaterial();
public:
   TResult LoadSceneResource(FRs3dSceneMaterial* pResource);
};

//============================================================
// <T>ʵ��3D��ʾ����</T>
//============================================================
class MO_E3_DECLARE FScene3dDisplay : public FTemplate3d
{
   MO_CLASS_DECLARE_INHERITS(FScene3dDisplay, FTemplate3d);
protected:
   GPtr<FRs3dSceneDisplay> _resource;
   GMaterialPtrDictionary _materials;
   FScene3dMoviePtrs _movies;
public:
   FScene3dDisplay();
   MO_ABSTRACT ~FScene3dDisplay();
public:
   //------------------------------------------------------------
   // <T>��ò��ʼ��ϡ�</T>
   MO_INLINE GMaterialPtrDictionary& Materials(){
      return _materials;
   }
   //------------------------------------------------------------
   // <T>��ö������ϡ�</T>
   MO_INLINE FScene3dMoviePtrs& Movies(){
      return _movies;
   }
public:
   TResult LoadSceneResource(FRs3dSceneDisplay* pResource);
   TResult LoadResource(FRs3dTemplate* pResource);
public:
   MO_OVERRIDE TResult ProcessBefore(SProcessContext* pContext);
};

//============================================================
// <T>ʵ��3D����֡��</T>
//============================================================
class MO_E3_DECLARE FScene3dFrame : public FStageLayer
{
   MO_CLASS_DECLARE_INHERITS(FScene3dFrame, FStageLayer);
protected:
   GPtr<FDisplayLayer> _skyLayer;
   GPtr<FDisplayLayer> _mapLayer;
   GPtr<FDisplayLayer> _spaceLayer;
   GPtr<FDisplayLayer> _faceLayer;
public:
   FScene3dFrame();
   MO_ABSTRACT ~FScene3dFrame();
public:
   //------------------------------------------------------------
   // <T>ʵ��3D����֡��</T>
   MO_INLINE FDisplayLayer* SkyLayer(){
      return _skyLayer;
   }
   //------------------------------------------------------------
   // <T>ʵ��3D����֡��</T>
   MO_INLINE FDisplayLayer* MapLayer(){
      return _mapLayer;
   }
   //------------------------------------------------------------
   // <T>ʵ��3D����֡��</T>
   MO_INLINE FDisplayLayer* SpaceLayer(){
      return _spaceLayer;
   }
   //------------------------------------------------------------
   // <T>ʵ��3D����֡��</T>
   MO_INLINE FDisplayLayer* FaceLayer(){
      return _faceLayer;
   }
public:
   MO_OVERRIDE TResult Setup();
};

//============================================================
// <T>ʵ��3D������</T>
//============================================================
class MO_E3_DECLARE FScene3d : public FStage
{
   MO_CLASS_DECLARE_INHERITS(FScene3d, FStage);
protected:
   TString _name;
   GPtr<FScene3dFrame> _sceneFrame;
   FRs3dScene* _pResource;
public:
   FScene3d();
   MO_ABSTRACT ~FScene3d();
public:
   //------------------------------------------------------------
   // <T>��ó���֡��</T>
   MO_INLINE FScene3dFrame* SceneFrame(){
      return _sceneFrame;
   }
public:
   MO_OVERRIDE TResult Setup();
public:
   TResult LoadTechniqueResource(FRs3dSceneTechnique* pResource);
   TResult LoadRegionResource(FRs3dSceneRegion* pResource);
   TResult LoadDisplayResource(FDisplayLayer* pLayer, FRs3dSceneDisplay* pResource);
   TResult LoadSkyResource(FRs3dSceneSky* pResource);
   TResult LoadMapResource(FRs3dSceneMap* pResource);
   TResult LoadSpaceResource(FRs3dSceneSpace* pResource);
   TResult LoadResource(FRs3dScene* pResource);
public:
   MO_OVERRIDE TResult Suspend();
   MO_OVERRIDE TResult Resume();
   MO_OVERRIDE TResult Dispose();
};
//------------------------------------------------------------
typedef MO_E3_DECLARE FDictionary<FScene3d*> FScene3dDictionary;

//============================================================
// <T>ʵ��3D��������̨��</T>
//============================================================
class MO_E3_DECLARE FScene3dConsole : public FConsole
{
   MO_CLASS_DECLARE_INHERITS(FScene3dConsole, FConsole);
protected:
   FScene3dDictionary* _pScenes;
public:
   FScene3dConsole();
   MO_ABSTRACT ~FScene3dConsole();
public:
   //------------------------------------------------------------
   // <T>���ģ�ͼ��ϡ�</T>
   MO_INLINE FScene3dDictionary* Scenes(){
      return _pScenes;
   }
public:
   FScene3d* Load(TCharC* pName);
   TResult Free(FScene3d* pScene);
public:
   void Clear();
public:
   MO_OVERRIDE TResult Suspend();
   MO_OVERRIDE TResult Resume();
   MO_OVERRIDE TResult Dispose();
};

MO_NAMESPACE_END

//************************************************************
#endif // __MO_E3_SCENE_H__
