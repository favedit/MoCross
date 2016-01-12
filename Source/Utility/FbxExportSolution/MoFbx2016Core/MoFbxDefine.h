#pragma once

#include <fbxsdk.h>
#include <MoCommon.h>
#include <MoMath.h>

//============================================================
/// @define �Զ���ú���
#define MO_SOURCE_GETTER(T, N, V) \
   MO_INLINE T N() { \
      return V; \
   } \

/// @define �Զ����ú���
#define MO_SOURCE_SETTER(T, N, V) \
   MO_INLINE void Set##N(T value) { \
      V = value; \
   }

/// @define �Զ�������ú���
#define MO_SOURCE_GETSET(T, N, V) \
   MO_INLINE T N() { \
      return V; \
   } \
   MO_INLINE void Set##N(T value) { \
      V = value; \
   }

//============================================================
/// @define ��������
#ifdef _MO_FBX_EXPORTS
#define MO_FBX_DECLARE MO_EXPORT
#else
#define MO_FBX_DECLARE MO_IMPORT
#endif

//============================================================
MO_NAMESPACE_USING(FBXSDK_NAMESPACE);
