//============================================================
// <T>��ͨ���塣</T>
//============================================================
#ifndef __MO_PD9_PUBLIC_H__
#define __MO_PD9_PUBLIC_H__

#ifndef __MO_COMMON_H__
#include <MoCommon.h>
#endif // __MO_COMMON_H__

#ifndef __MO_MATH_H__
#include <MoMath.h>
#endif // __MO_MATH_H__

#ifndef __MO_FEATURE_GRAPHIC_H__
#include <MoFeatureGraphic.h>
#endif // __MO_FEATURE_GRAPHIC_H__

#ifndef __MO_ENGINE_H__
#include <MoEngine.h>
#endif // __MO_ENGINE_H__

//============================================================
/// @define ��������
#ifdef _MO_PD9_EXPORTS
#define MO_PD9_DECLARE MO_EXPORT
#else
#define MO_PD9_DECLARE MO_IMPORT
#endif // _MO_PD9_EXPORTS

MO_NAMESPACE_BEGIN

MO_NAMESPACE_END

#endif // __MO_PD9_PUBLIC_H__
