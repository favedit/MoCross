#ifndef __MO_POE2_TECHNIQUE_H__
#define __MO_POE2_TECHNIQUE_H__
//************************************************************

#ifndef __MO_POE2_COMMON_H__
#include "MoPoe2Common.h"
#endif // __MO_POE2_COMMON_H__

#ifndef __MO_POE2_RENDER_H__
#include "MoPoe2Render.h"
#endif // __MO_POE2_RENDER_H__

MO_NAMESPACE_BEGIN

//============================================================
// <T>��ʾ��ɫ��Ⱦ����</T>
//============================================================
class MO_POE2_DECLARE FPoe22dColorEffect : public FEffect{
protected:
   TInt _limitCount;
   TInt _count;
   SFloatMatrix3d _mvpMatrix;
   //FPoe2RenderVertexBuffer* _pVertexPositionBuffer;
   //FDataStream* _pPositionData;
   //FPoe2RenderVertexBuffer* _pVertexColorBuffer;
   //FDataStream* _pColorData;
   //FPoe2RenderIndexBuffer* _pIndexBuffer;
public:
   FPoe22dColorEffect();
   MO_ABSTRACT ~FPoe22dColorEffect();
public:
   ////------------------------------------------------------------
   //// <T>������Ƹ�����</T>
   //MO_INLINE TInt LimitCount(){
   //   return _limitCount;
   //}
   ////------------------------------------------------------------
   //// <T>��ö���λ�û��塣</T>
   //MO_INLINE FPoe2RenderVertexBuffer* VertexPositionBuffer(){
   //   return _pVertexPositionBuffer;
   //}
   ////------------------------------------------------------------
   //// <T>��ö�����ɫ���塣</T>
   //MO_INLINE FPoe2RenderVertexBuffer* VertexColorBuffer(){
   //   return _pVertexColorBuffer;
   //}
   ////------------------------------------------------------------
   //// <T>����������塣</T>
   //MO_INLINE FPoe2RenderIndexBuffer* IndexBuffer(){
   //   return _pIndexBuffer;
   //}
public:
   MO_OVERRIDE TResult Setup();
public:
   MO_ABSTRACT TResult UpdateBegin();
   MO_ABSTRACT TResult WriteRenderable(FRenderable* pRenderable);
   MO_ABSTRACT TResult UpdateEnd();
public:
   MO_OVERRIDE TResult Resize(TInt width, TInt height);
   MO_OVERRIDE TResult Draw();
};

//============================================================
// <T>��ʾ��Ⱦ������</T>
//============================================================
class MO_POE2_DECLARE FPoe22dTextureEffect : public FEffect{
protected:
   TInt _limitCount;
   TInt _count;
   SFloatMatrix3d _mvpMatrix;
   //GLint _effectAttributes[EEffectVertexAttribute_Count];
   //GLint _effectSamplers[EEffectSampler_Count];
   //FPoe2RenderVertexBuffer* _pVertexPositionBuffer;
   //FDataStream* _pPositionData;
   //FPoe2RenderVertexBuffer* _pVertexColorBuffer;
   //FDataStream* _pColorData;
   //FPoe2RenderVertexBuffer* _pVertexCoordBuffer;
   //FDataStream* _pCoordData;
   //FPoe2RenderIndexBuffer* _pIndexBuffer;
public:
   FPoe22dTextureEffect();
   MO_ABSTRACT ~FPoe22dTextureEffect();
public:
   ////------------------------------------------------------------
   //// <T>��ö���λ�û��塣</T>
   //MO_INLINE FPoe2RenderVertexBuffer* VertexPositionBuffer(){
   //   return _pVertexPositionBuffer;
   //}
   ////------------------------------------------------------------
   //// <T>��ö�����ɫ���塣</T>
   //MO_INLINE FPoe2RenderVertexBuffer* VertexColorBuffer(){
   //   return _pVertexColorBuffer;
   //}
   ////------------------------------------------------------------
   //// <T>��ö������껺�塣</T>
   //MO_INLINE FPoe2RenderVertexBuffer* VertexCoordBuffer(){
   //   return _pVertexCoordBuffer;
   //}
   ////------------------------------------------------------------
   //// <T>����������塣</T>
   //MO_INLINE FPoe2RenderIndexBuffer* IndexBuffer(){
   //   return _pIndexBuffer;
   //}
public:
   MO_OVERRIDE TResult Setup();
public:
   MO_ABSTRACT TResult UpdateBegin();
   MO_ABSTRACT TResult WriteRenderable(FRenderable* pRenderable);
   MO_ABSTRACT TResult UpdateEnd();
public:
   MO_OVERRIDE TResult Resize(TInt width, TInt height);
   MO_OVERRIDE TResult Draw();
};

//============================================================
// <T>��ʾ��Ⱦ������</T>
//============================================================
class MO_POE2_DECLARE FPoe23dTextureEffect : public FEffect{
public:
   FPoe23dTextureEffect();
   MO_ABSTRACT ~FPoe23dTextureEffect();
public:
   MO_OVERRIDE TResult Setup();
public:
   MO_OVERRIDE TResult Resize(TInt width, TInt height);
   MO_OVERRIDE TResult Draw(FRenderable* pRenderable);
   MO_OVERRIDE TResult DrawGroup(FRenderRegion* pRegion, TInt offset, TInt count);
};

//============================================================
// <T>��ʾ��Ⱦ����</T>
//============================================================
class MO_POE2_DECLARE FPoe23dSkeleton4Program : public FPoRenderProgram{
protected:
   TInt _boneCount;
   TInt _weightCount;
	GLint _vertexConstMvpMatrix;
   GLint _vertexConstBoneMatrixs;
   GLint _attributePosition;
   GLint _attributeColor;
   GLint _attributeCoord;
   GLint _attributeBoneIndex;
   GLint _attributeBoneWeight;
   GLint _samplerColor;
   FByteStream* _pBoneStream;
public:
   FPoe23dSkeleton4Program();
   MO_ABSTRACT ~FPoe23dSkeleton4Program();
public:
   //------------------------------------------------------------
   // <T>��ù�ͷ������</T>
   MO_INLINE TInt BoneCount(){
      return _boneCount;
   }
   //------------------------------------------------------------
   // <T>���ù�ͷ������</T>
   MO_INLINE void SetBoneCount(TInt boneCount){
      _boneCount = boneCount;
   }
   //------------------------------------------------------------
   // <T>���Ȩ��������</T>
   MO_INLINE TInt WeightCount(){
      return _weightCount;
   }
   //------------------------------------------------------------
   // <T>����Ȩ��������</T>
   MO_INLINE void SetWeightCount(TInt weightCount){
      _weightCount = weightCount;
   }
public:
   MO_OVERRIDE TResult MakeVertexSource(FRenderSource* pSource);
   MO_OVERRIDE TResult MakeFragmentSource(FRenderSource* pSource);
public:
   MO_OVERRIDE TResult Build();
};
//------------------------------------------------------------
typedef MO_POE2_DECLARE FVector<FPoe23dSkeleton4Program*> FPoe23dSkeleton4ProgramVector;

//============================================================
// <T>��ʾ��Ⱦ������</T>
//============================================================
class MO_POE2_DECLARE FPoe23dSkeleton4Effect : public FEffect{
protected:
   FPoe23dSkeleton4ProgramVector* _pPrograms;
   SFloatMatrix3d _mvpMatrix;
   SFloatMatrix3d _vpMatrix;
   //GLint _effectAttributes[EEffectVertexAttribute_Count];
   //GLint _effectSamplers[EEffectSampler_Count];
   FByteStream* _pBoneStream;
public:
   FPoe23dSkeleton4Effect();
   MO_ABSTRACT ~FPoe23dSkeleton4Effect();
public:
   MO_OVERRIDE TResult Setup();
public:
   MO_OVERRIDE TResult Resize(TInt width, TInt height);
   MO_OVERRIDE TResult Draw(FRenderRegion* pRegion, FRenderable* pRenderable);
   MO_OVERRIDE TResult DrawGroup(FRenderRegion* pRegion, TInt offset, TInt count);
};

MO_NAMESPACE_END

//************************************************************
#endif // __MO_EG_TECHNIQUE_H__
