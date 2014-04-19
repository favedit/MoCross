#ifndef __MO_GE_DISPLAY_H__
#define __MO_GE_DISPLAY_H__
//************************************************************

#ifndef __MO_GE_COMMON_H__
#include "MoGeCommon.h"
#endif // __MO_GE_COMMON_H__

MO_NAMESPACE_BEGIN

//============================================================
// <T>����̨����</T>
//============================================================
class MO_GE_DECLARE FGameStage : public FStage
{
   MO_CLASS_DECLARE_INHERITS(FGameStage, FStage);
protected:
   SIntSize2 _size;
protected:
   FDisplayLayer* _pSpriteLayer;
protected:
   FStageFrame* _pGroundFrame;
   FStageFrame* _pSceneFrame;
   FStageFrame* _pFaceFrame;
public:
   FGameStage();
   MO_ABSTRACT ~FGameStage();
public:
   //------------------------------------------------------------
   // <T>��óߴ硣</T>
   MO_INLINE SIntSize2& Size(){
      return _size;
   }
public:
   //------------------------------------------------------------
   // <T>��þ���㡣</T>
   MO_INLINE FDisplayLayer* SpriteLayer(){
      return _pSpriteLayer;
   }
public:
   //------------------------------------------------------------
   // <T>��ñ���֡��</T>
   MO_INLINE FStageFrame* GroundFrame(){
      return _pGroundFrame;
   }
   //------------------------------------------------------------
   // <T>��ó���֡��</T>
   MO_INLINE FStageFrame* SceneFrame(){
      return _pSceneFrame;
   }
   //------------------------------------------------------------
   // <T>��ý���֡��</T>
   MO_INLINE FStageFrame* FaceFrame(){
      return _pFaceFrame;
   }
public:
   MO_OVERRIDE TResult Setup();
public:
   MO_OVERRIDE TResult ProcessInput();
};

//============================================================
// <T>��Ϸ������</T>
//============================================================
class MO_GE_DECLARE FGameScene : public FScene3d
{
   MO_CLASS_DECLARE_INHERITS(FGameScene, FScene3d);
public:
   FGameScene();
   MO_ABSTRACT ~FGameScene();
public:
   MO_OVERRIDE TResult Setup();
public:
   MO_OVERRIDE TResult ProcessInput();
};
//------------------------------------------------------------
typedef MO_GE_DECLARE FDictionary<FGameScene*> FGameSceneDictionary;

//============================================================
// <T>��Ϸ��������̨��</T>
//============================================================
class MO_GE_DECLARE FGameSceneConsole : public FConsole
{
   MO_CLASS_DECLARE_INHERITS(FScene3dConsole, FConsole);
protected:
   FGameSceneDictionary* _pScenes;
public:
   FGameSceneConsole();
   MO_ABSTRACT ~FGameSceneConsole();
public:
   //------------------------------------------------------------
   // <T>���ģ�ͼ��ϡ�</T>
   MO_INLINE FGameSceneDictionary* Scenes(){
      return _pScenes;
   }
public:
   FGameScene* Load(TCharC* pName);
   TResult Free(FGameScene* pScene);
public:
   void Clear();
public:
   MO_OVERRIDE TResult Suspend();
   MO_OVERRIDE TResult Resume();
   MO_OVERRIDE TResult Dispose();
};

//============================================================
// <T>ʵ��3D��������</T>
//============================================================
class MO_GE_DECLARE RGameSceneManager : public RSingleton<FGameSceneConsole>{
};

MO_NAMESPACE_END

//************************************************************
#endif // __MO_EG_DISPLAY_H__
