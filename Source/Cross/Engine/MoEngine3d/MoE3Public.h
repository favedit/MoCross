//============================================================
// <T>��ͨ���塣</T>
//============================================================
#ifndef __MO_E3_PUBLIC_H__
#define __MO_E3_PUBLIC_H__

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

#ifndef __MO_FEATURE_RESOURCE_H__
#include <MoFeatureResource.h>
#endif // __MO_FEATURE_RESOURCE_H__

#ifndef __MO_FEATURE_PARTICLE_H__
#include <MoFeatureParticle.h>
#endif // __MO_FEATURE_PARTICLE_H__

#ifndef __MO_ENGINE_H__
#include <MoEngine.h>
#endif // __MO_ENGINE_H__

//============================================================
/// @define ��������
#ifdef _MO_E3_EXPORTS
#define MO_E3_DECLARE MO_EXPORT
#else
#define MO_E3_DECLARE MO_IMPORT
#endif // _MO_E3_EXPORTS

MO_NAMESPACE_BEGIN

MO_NAMESPACE_END

#endif // __MO_E3_PUBLIC_H__
