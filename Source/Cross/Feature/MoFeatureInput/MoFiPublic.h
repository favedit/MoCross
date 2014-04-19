//============================================================
// <T>��ͨ���塣</T>
//============================================================
#ifndef __MO_FI_PUBLIC_H__
#define __MO_FI_PUBLIC_H__

#ifndef __MO_COMMON_H__
#include <MoCommon.h>
#endif // __MO_COMMON_H__

#ifndef __MO_CORE_H__
#include <MoCore.h>
#endif // __MO_CORE_H__

#ifndef __MO_MATH_H__
#include <MoMath.h>
#endif // __MO_MATH_H__

//============================================================
/// @define ��������
#ifdef _MO_FI_EXPORTS
#define MO_FI_DECLARE MO_EXPORT
#else
#define MO_FI_DECLARE MO_IMPORT
#endif // _MO_FI_EXPORTS

MO_NAMESPACE_BEGIN

MO_NAMESPACE_END

#endif // __MO_FI_PUBLIC_H__
