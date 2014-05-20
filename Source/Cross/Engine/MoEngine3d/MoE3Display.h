#ifndef __MO_E3_DISPLAY_H__
#define __MO_E3_DISPLAY_H__
//************************************************************

#ifndef __MO_E3_COMMON_H__
#include "MoE3Common.h"
#endif // __MO_E3_COMMON_H__

MO_NAMESPACE_BEGIN

//============================================================
class FRenderable3d;
class FDisplay3d;
class FAnimation3d;

//============================================================
// <T>����Ⱦ3D����</T>
//============================================================
class MO_E3_DECLARE FRenderable3d : public FRenderable
{
   MO_CLASS_DECLARE_INHERITS(FRenderable3d, FRenderable);
public:
   FRenderable3d();
   MO_ABSTRACT ~FRenderable3d();
public:
   MO_ABSTRACT FAnimation3d* FindAnimation();
   MO_ABSTRACT FRs3dTrack* FindTrack();
public:
   //MO_OVERRIDE TResult CalculateRenderable(SRenderable& renderable);
   MO_OVERRIDE TResult BuildFlags();
};
//------------------------------------------------------------
typedef MO_E3_DECLARE FVector<FRenderable3d*> FRenderable3dVector;
typedef MO_E3_DECLARE FList<FRenderable3d*> FRenderable3dList;

//============================================================
// <T>����ʾ3D����</T>
//============================================================
class MO_E3_DECLARE FDisplay3d : public FDisplay
{
   MO_CLASS_DECLARE_INHERITS(FDisplay3d, FDisplay);
public:
   FDisplay3d();
   MO_ABSTRACT ~FDisplay3d();
};
//------------------------------------------------------------
typedef MO_E3_DECLARE FVector<FDisplay3d*> FDisplay3dVector;
typedef MO_E3_DECLARE FList<FDisplay3d*> FDisplay3dList;

//============================================================
// <T>ʵ��3D��ͷ��</T>
//============================================================
class MO_E3_DECLARE FBone3d : public FObject{
protected:
   FAnimation3d* _pAnimation;
   TResourceId _modelId;
   TInt _boneId;
   FRs3dBone* _pBoneResource;
   FRs3dTrack* _pTrackResource;
   SFloatMatrix3d _matrix;
public:
   FBone3d();
   MO_ABSTRACT ~FBone3d();
public:
   //------------------------------------------------------------
   // <T>��ö�������</T>
   MO_INLINE FAnimation3d* Animation(){
      return _pAnimation;
   }
   //------------------------------------------------------------
   // <T>���ö�������</T>
   MO_INLINE void SetAnimation(FAnimation3d* pAnimation){
      _pAnimation = pAnimation;
   }
   //------------------------------------------------------------
   // <T>���ģ����Դ��š�</T>
   MO_INLINE TResourceId ModelId(){
      return _modelId;
   }
   //------------------------------------------------------------
   // <T>����ģ����Դ��š�</T>
   MO_INLINE void SetModelId(TResourceId boneId){
      _modelId = boneId;
   }
   //------------------------------------------------------------
   // <T>��ù�ͷ��š�</T>
   MO_INLINE TInt BoneId(){
      return _boneId;
   }
   //------------------------------------------------------------
   // <T>���ù�ͷ��š�</T>
   MO_INLINE void SetBoneId(TInt boneId){
      _boneId = boneId;
   }
   //------------------------------------------------------------
   // <T>��ù�ͷ��Դ��</T>
   MO_INLINE FRs3dBone* BoneResource(){
      return _pBoneResource;
   }
   //------------------------------------------------------------
   // <T>��ø�����Դ��</T>
   MO_INLINE FRs3dTrack* TrackResource(){
      return _pTrackResource;
   }
   //------------------------------------------------------------
   // <T>��õ�ǰ����</T>
   MO_INLINE SFloatMatrix3d& Matrix(){
      return _matrix;
   }
public:
   TResult LoadResource(FRs3dBone* pResource);
   TResult Update(TTimeTick tick);
};
//------------------------------------------------------------
typedef MO_E3_DECLARE FVector<FBone3d*> FBone3dCollection;

//============================================================
// <T>ʵ��3D������</T>
//============================================================
class MO_E3_DECLARE FAnimation3d : public FObject{
protected:
   TThreadLocker _locker;
   TTimeTick _baseTick;
   TTimeTick _currentTick;
   TTimeTick _lastTick;
   FBone3dCollection* _pBones;
public:
   FAnimation3d();
   MO_ABSTRACT ~FAnimation3d();
public:
   //------------------------------------------------------------
   // <T>�����������</T>
   MO_INLINE TThreadLocker& Locker(){
      return _locker;
   }
   //------------------------------------------------------------
   // <T>��û���ʱ�̡�</T>
   MO_INLINE TTimeTick BaseTick(){
      return _baseTick;
   }
   //------------------------------------------------------------
   // <T>���û���ʱ�̡�</T>
   MO_INLINE void SetBaseTick(TTimeTick baseTick){
      _baseTick = baseTick;
   }
   //------------------------------------------------------------
   // <T>��ù�ͷ���ϡ�</T>
   MO_INLINE FBone3dCollection* Bones(){
      return _pBones;
   }
   //------------------------------------------------------------
   // <T>��õ�ǰʱ�̡�</T>
   MO_INLINE TTimeTick CurrentTick(){
      return _currentTick;
   }
public:
   FBone3d* FindBone(TInt boneId);
   FBone3d* FindBone(TResourceId modelId, TInt boneId);
public:
   TResult LoadResource(FRs3dAnimation* pResource);
   MO_OVERRIDE TResult Update();
   MO_OVERRIDE TResult Process();
};

MO_NAMESPACE_END

//************************************************************
#endif // __MO_E3_DISPLAY_H__
