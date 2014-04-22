#ifndef __MO_E2_DISPLAY_H__
#define __MO_E2_DISPLAY_H__
//************************************************************

#ifndef __MO_E2_COMMON_H__
#include "MoE2Common.h"
#endif // __MO_E2_COMMON_H__

MO_NAMESPACE_BEGIN

//============================================================
class FDisplay2d;
typedef MO_E2_DECLARE FVector<FDisplay2d*> FDisplay2dVector;
typedef MO_E2_DECLARE FList<FDisplay2d*> FDisplay2dList;

//==========================================================
// <T>��ʾ�������</T>
//==========================================================
enum EDisplayType{
   // ͼƬ
   EDisplayType_Picture = 1,
   // ��״
   EDisplayType_Shape = 2,
   // ����
   EDisplayType_Sprite = 3,
   // ����
   EDisplayType_Movie = 4,
};
//----------------------------------------------------------
typedef TInt TDisplayType;

//============================================================
struct SDisplayArgs{
};

//============================================================
// <T>��ʾ����</T>
//============================================================
class MO_E2_DECLARE FDisplay2d :
      public FRenderable,
      public IParticleAble
{
   MO_CLASS_DECLARE_INHERITS(FDisplay2d, FRenderable);
protected:
   // ����
   TDisplayType _typeCd;
   // ����
   SFloatPoint3 _gravityCenter;
   // ����
   FMaterial* _pMaterial;
public:
   FDisplay2d();
   MO_ABSTRACT ~FDisplay2d();
public:
   //------------------------------------------------------------
   // <T>������͡�</T>
   MO_INLINE TDisplayType TypeCd(){
      return _typeCd;
   }
   //------------------------------------------------------------
   // <T>������ġ�</T>
   MO_INLINE SFloatPoint3& GravityCenter(){
      return _gravityCenter;
   }
   //------------------------------------------------------------
   // <T>��ò��ʡ�</T>
   MO_OVERRIDE FMaterial* Material(){
      return _pMaterial;
   }
public:
   TResult SetMaterial(FMaterial* pMaterial);
public:
   MO_OVERRIDE TResult CalculateRenderable(SRenderable& renderable);
   MO_OVERRIDE TResult DoParticle(SParticleData& data);
   MO_OVERRIDE TResult Free();
};

//============================================================
// <T>������ʾ����</T>
//============================================================
class MO_E2_DECLARE FTailDisplay2d : public FDisplay2d
{
   MO_CLASS_DECLARE_INHERITS(FTailDisplay2d, FDisplay2d);
protected:
   // �Ƿ�ʹ�ø���
   TBool _optionTail;
   // ���ٿ�����
   FTailController* _pTailController;
public:
   FTailDisplay2d();
   MO_ABSTRACT ~FTailDisplay2d();
public:
   //------------------------------------------------------------
   // <T>��������Ƿ�ʹ�ø��١�</T>
   MO_INLINE TBool OptionTail(){
      return _optionTail;
   }
   //------------------------------------------------------------
   // <T>��ø��ٿ�������</T>
   MO_INLINE FTailController* TailController(){
      return _pTailController;
   }
public:
   TResult SetOptionTail(TBool value);
   MO_OVERRIDE TResult CalculateRenderable(SRenderable& renderable);
   MO_OVERRIDE TResult DoParticle(SParticleData& data);
};

//============================================================
// <T>��ʾ������</T>
//============================================================
class MO_E2_DECLARE FDisplay2dContainer : public FDisplay2d{
public:
   FDisplay2dContainer();
   MO_ABSTRACT ~FDisplay2dContainer();
};

//============================================================
// <T>λͼ����</T>
//============================================================
class MO_E2_DECLARE FPicture : public FTailDisplay2d
{
   MO_CLASS_DECLARE_INHERITS(FPicture, FTailDisplay2d);
protected:
   FPictureResource* _pResource;
public:
   FPicture();
   MO_ABSTRACT ~FPicture();
public:
   //------------------------------------------------------------
   // <T>���λͼ��</T>
   MO_INLINE FPictureResource* Resource(){
      return _pResource;
   }
public:
   TResult SetResource(FPictureResource* pResource);
};

//============================================================
// <T>��ʾ��״��</T>
//============================================================
class MO_E2_DECLARE FShape : public FDisplay2d{
public:
   FShape();
   MO_ABSTRACT ~FShape();
};

//============================================================
// <T>��ʾ���顣</T>
//============================================================
class MO_E2_DECLARE FSprite : public FDisplay2dContainer{
public:
   FSprite();
   MO_ABSTRACT ~FSprite();
};

//============================================================
// <T>��ʾ������</T>
//============================================================
class MO_E2_DECLARE FMovie : public FDisplay2d{
protected:
   FAnimationResource* _pResource;
   TFloat _rate;
   TMovieActionList _actions;
   TDateTime _startTick;
   TDateTime _lastTick;
   FAnimationClip* _pActiveClip;
   FAnimationFrame* _pActiveFrame;
   TBool _hasActiveAction;
   SMovieAction _activeAction;
public:
   FMovie();
   MO_ABSTRACT ~FMovie();
public:
   //------------------------------------------------------------
   // <T>���λͼ��</T>
   MO_INLINE FAnimationResource* Resource(){
      return _pResource;
   }
   //------------------------------------------------------------
   // <T>��ü��������</T>
   MO_INLINE FAnimationClip* ActiveClip(){
      return _pActiveClip;
   }
   //------------------------------------------------------------
   // <T>��ü���֡��</T>
   MO_INLINE FAnimationFrame* ActiveFrame(){
      return _pActiveFrame;
   }
public:
   MO_OVERRIDE TResult CalculateRenderable(SRenderable& renderable);
public:
   void LoadResource(FAnimationResource* pResource);
public:
   MO_ABSTRACT TResult PlayClear();
   MO_ABSTRACT TResult Play(SMovieAction* pAction);
   MO_ABSTRACT TResult ProcessPlay();
   MO_OVERRIDE TResult Process();
};

//============================================================
// <T>��ʾ�������̨��</T>
//============================================================
class MO_E2_DECLARE FDisplay2dConsole : public FConsole{
protected:
   GPtr<FClassFactory> _classFactory;
public:
   FDisplay2dConsole();
   MO_ABSTRACT ~FDisplay2dConsole();
public:
   //------------------------------------------------------------
   // <T>�������󹤳���</T>
   MO_INLINE FClassFactory* ClassFactory(){
      return _classFactory;
   }
public:
   FDisplay2d* DisplayAlloc(TDisplayType typeCd);
   void DisplayFree(FDisplay2d* pDisplay);
public:
   MO_ABSTRACT void Setup();
   MO_ABSTRACT TResult Dispose();
};

//============================================================
// <T>����������������</T>
//============================================================
class MO_E2_DECLARE RDisplay2dManager : public RSingleton<FDisplay2dConsole>{
};

MO_NAMESPACE_END

//************************************************************
#endif // __MO_E2_DISPLAY_H__
