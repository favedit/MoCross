#ifndef __MO_FG_COMMON_H__
#define __MO_FG_COMMON_H__
//************************************************************

#ifndef __MO_FG_PUBLIC_H__
#include "MoFgPublic.h"
#endif // __MO_FG_PUBLIC_H__

#ifndef __MO_FG_GEOM_H__
#include "MoFgGeom.h"
#endif // __MO_FG_GEOM_H__

#ifndef __MO_FG_STREAM_H__
#include "MoFgStream.h"
#endif // __MO_FG_STREAM_H__

#define MO_GRAPHIC_PI2         (MO_PI_FLOAT * 2)
#define MO_GRAPHIC_RADIAN_RATE (180.0f / MO_PI_FLOAT)
#define MO_GRAPHIC_DEGREE_RATE (MO_PI_FLOAT / 180.0f)

MO_NAMESPACE_BEGIN

//============================================================
// <T>��Դ�����</T>
//============================================================
struct SGraphicHandle{
public:
   TInt id;
   TInt index;
   TCharC* namePtr;
   FInstance* instancePtr;
   union SData{
      TInt32 int32;
      TUint32 uint32;
      TInt64 int64;
      TUint64 uint64;
   } data;
public:
   //------------------------------------------------------------
   // <T>������Դ�����</T>
   MO_INLINE SGraphicHandle(){
      id = 0;
      index = -1;
      MO_CLEAR(namePtr);
      MO_CLEAR(instancePtr);
      data.uint64 = 0;
   }
public:
   //------------------------------------------------------------
   // <T>������Դ�����</T>
   template <class T>
   MO_INLINE T* Convert(){
#ifdef _MO_DEBUG
      RClassManager::CheckConvert(instancePtr, T::Class());
#endif // _MO_DEBUG
      return (T*)instancePtr;
   }
public:
   //------------------------------------------------------------
   // <T>���32λ�������ݡ�</T>
   MO_INLINE TInt32 AsInt32(){
      return data.int32;
   }
   //------------------------------------------------------------
   // <T>����32λ�������ݡ�</T>
   MO_INLINE void SetInt32(TInt32 value){
      data.int32 = value;
   }
   //------------------------------------------------------------
   // <T>���64λ�������ݡ�</T>
   MO_INLINE TInt64 AsInt64(){
      return data.int64;
   }
   //------------------------------------------------------------
   // <T>����64λ�������ݡ�</T>
   MO_INLINE void SetInt64(TInt64 value){
      data.int64 = value;
   }
   //------------------------------------------------------------
   // <T>��÷Ǹ�32λ�������ݡ�</T>
   MO_INLINE TUint32 AsUint32(){
      return data.uint32;
   }
   //------------------------------------------------------------
   // <T>���÷Ǹ�32λ�������ݡ�</T>
   MO_INLINE void SetUint32(TUint32 value){
      data.uint32 = value;
   }
   //------------------------------------------------------------
   // <T>��÷Ǹ�64λ�������ݡ�</T>
   MO_INLINE TUint64 AsUint64(){
      return data.uint64;
   }
   //------------------------------------------------------------
   // <T>����64λ�������ݡ�</T>
   MO_INLINE void SetUint64(TUint64 value){
      data.uint64 = value;
   }
};
//------------------------------------------------------------
typedef SGraphicHandle TGraphicHandle;
typedef TVector<TGraphicHandle> TGraphicHandles;

//============================================================
// <T>����ͼ�ζ���</T>
//============================================================
class MO_FG_DECLARE FGraphicObject : public FInstance
{
   MO_CLASS_DECLARE_INHERITS(FGraphicObject, FInstance);
protected:
   FInstance* _pOwner;
   TBool _statusSetup;
public:
   FGraphicObject();
   MO_ABSTRACT ~FGraphicObject();
public:
   //------------------------------------------------------------
   // <T>���ӵ���ߡ�</T>
   MO_INLINE FInstance* Owner(){
      return _pOwner;
   }
   //------------------------------------------------------------
   // <T>����ӵ���ߡ�</T>
   MO_INLINE void SetOwner(FInstance* pOwner){
      _pOwner = pOwner;
   }
public:
   MO_ABSTRACT TResult OnSetup();
   TResult Setup();
};

MO_NAMESPACE_END
      
//************************************************************
#endif // __MO_FG_COMMON_H__
