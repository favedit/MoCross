#ifndef __MO_FG_DISPLAY_H__
#define __MO_FG_DISPLAY_H__
//************************************************************

#ifndef __MO_FG_COMMON_H__
#include "MoFgCommon.h"
#endif // __MO_FG_COMMON_H__

#ifndef __MO_FG_GRAPHIC_H__
#include "MoFgGraphic.h"
#endif // __MO_FG_GRAPHIC_H__

MO_NAMESPACE_BEGIN

//============================================================
// <T>ʵ��3D�����塣</T>
//============================================================
class MO_FG_DECLARE FRenderRectangle : public FRenderable
{
   MO_CLASS_DECLARE_INHERITS(FRenderRectangle, FRenderable);
protected:
   SFloatPoint2 _location;
   SFloatSize2 _size;
   FRenderVertexBuffer* _pVertexBuffer;
public:
   FRenderRectangle();
   MO_ABSTRACT ~FRenderRectangle();
public:
   //------------------------------------------------------------
   // <T>���λ�á�</T>
   MO_INLINE SFloatPoint2& Location(){
      return _location;
   }
   //------------------------------------------------------------
   // <T>��ô�С��</T>
   MO_INLINE SFloatSize2& Size(){
      return _size;
   }
   //------------------------------------------------------------
   // <T>�����Ⱦ���㻺�塣</T>
   MO_INLINE FRenderVertexBuffer* VertexBuffer(){
      return _pVertexBuffer;
   }
public:
   MO_OVERRIDE TResult Setup();
};

//============================================================
// <T>ʵ��3D�����塣</T>
//============================================================
class MO_FG_DECLARE FRenderCube : public FRenderable
{
   MO_CLASS_DECLARE_INHERITS(FRenderCube, FRenderable);
public:
   FRenderCube();
   MO_ABSTRACT ~FRenderCube();
public:
   MO_OVERRIDE TResult Setup();
};

//============================================================
// <T>ʵ����Ⱦ����</T>
//============================================================
class MO_FG_DECLARE FInstanceRenderable : public FRenderable
{
   MO_CLASS_DECLARE_INHERITS(FInstanceRenderable, FRenderable);
protected:
   GPtr<FRenderVertexBuffer> _vertexBuffer;
   GPtr<FRenderable> _renderable;
   TInt _instanceCount;
public:
   FInstanceRenderable();
   MO_ABSTRACT ~FInstanceRenderable();
public:
   //------------------------------------------------------------
   // <T>�����Ⱦ����</T>
   MO_INLINE FRenderable* Renderable(){
      return _renderable;
   }
   //------------------------------------------------------------
   // <T>������Ⱦ����</T>
   MO_INLINE void SetRenderable(FRenderable* pRenderable){
      _renderable = pRenderable;
   }
   //------------------------------------------------------------
   // <T>���ʵ��������</T>
   MO_INLINE TInt InstanceCount(){
      return _instanceCount;
   }
   //------------------------------------------------------------
   // <T>����ʵ��������</T>
   MO_INLINE void SetInstanceCount(TInt instanceCount){
      _instanceCount = instanceCount;
   }
public:
   MO_OVERRIDE TResult Setup();
};
//------------------------------------------------------------
typedef MO_FG_DECLARE FDictionary<FInstanceRenderable*> FInstanceRenderableDictionary;

//============================================================
// <T>��̬��Ⱦ����</T>
//============================================================
class MO_FG_DECLARE FDynamicRenderable : public FRenderable
{
   MO_CLASS_DECLARE_INHERITS(FDynamicRenderable, FRenderable);
protected:
   TInt _vertexTotal;
   TInt _indexTotal;
   GPtrs<FRenderable> _renderables;
public:
   FDynamicRenderable();
   MO_ABSTRACT ~FDynamicRenderable();
public:
   //------------------------------------------------------------
   // <T>�����Ⱦ���󼯺ϡ�</T>
   MO_INLINE GPtrs<FRenderable>& Renderables(){
      return _renderables;
   }
public:
   FRenderVertexBuffer* SyncVertexBuffer(FRenderVertexBuffer* pBuffer);
   FRenderVertexStream* SyncVertexStream(FRenderVertexStream* pStream);
public:
   TBool TestMergeable(FRenderable* pRenderable);
   TResult Push(FRenderable* pRenderable);
public:
   MO_OVERRIDE TResult Setup();
};
//------------------------------------------------------------
typedef MO_FG_DECLARE GPtrs<FDynamicRenderable> GDynamicRenderablePtrs;

MO_NAMESPACE_END

//************************************************************
#endif // __MO_FG_DISPLAY_H__
