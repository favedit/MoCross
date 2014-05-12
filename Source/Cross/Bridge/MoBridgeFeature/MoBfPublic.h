//============================================================
// <T>��ͨ���塣</T>
//============================================================
#ifndef __MO_BF_PUBLIC_H__
#define __MO_BF_PUBLIC_H__

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

#ifndef __MO_FEATURE_SCRIPT_H__
#include <MoFeatureScript.h>
#endif // __MO_FEATURE_SCRIPT_H__

//============================================================
/// @define ��������
#ifdef _MO_BF_EXPORTS
#define MO_BF_DECLARE MO_EXPORT
#else
#define MO_BF_DECLARE MO_IMPORT
#endif // _MO_BF_EXPORTS

//============================================================
// @define �����ռ䶨��
#define MO_NAMESPACE_BRIDGE_FEATURE MO:DX10
#define MO_NAMESPACE_BRIDGE_FEATURE_BEGIN    namespace MO_NAMESPACE_BRIDGE_FEATURE{
#define MO_NAMESPACE_BRIDGE_FEATURE_END      }
#define MO_NAMESPACE_BRIDGE_FEATURE_INCLUDE  MO_NAMESPACE_USING(MO_NAMESPACE_BRIDGE_FEATURE);

MO_NAMESPACE_BEGIN

MO_NAMESPACE_END

#endif // __MO_BF_PUBLIC_H__
