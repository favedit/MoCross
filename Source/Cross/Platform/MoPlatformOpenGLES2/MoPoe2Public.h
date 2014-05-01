//============================================================
// <T>��ͨ���塣</T>
//============================================================
#ifndef __MO_POE2_PUBLIC_H__
#define __MO_POE2_PUBLIC_H__

#ifndef __MO_COMMON_H__
#include <MoCommon.h>
#endif // __MO_COMMON_H__

#ifndef __MO_CORE_H__
#include <MoCore.h>
#endif // __MO_CORE_H__

#ifndef __MO_MATH_H__
#include <MoMath.h>
#endif // __MO_MATH_H__

#ifndef __MO_FEATURE_GRAPHIC_H__
#include <MoFeatureGraphic.h>
#endif // __MO_FEATURE_GRAPHIC_H__

#ifndef __MO_ENGINE_OPENGLE_H__
#include <MoPlatformOpenGL.h>
#endif // __MO_ENGINE_OPENGLE_H__

//============================================================
/// @define ��������
#ifdef _MO_POE2_EXPORTS
#define MO_POE2_DECLARE MO_EXPORT
#else
#define MO_POE2_DECLARE MO_IMPORT
#endif // _MO_POE2_EXPORTS

MO_NAMESPACE_BEGIN

MO_NAMESPACE_END

#endif // __MO_POE2_PUBLIC_H__
