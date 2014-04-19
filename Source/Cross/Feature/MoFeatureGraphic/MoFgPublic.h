//============================================================
// <T>��ͨ���塣</T>
//============================================================
#ifndef __MO_FG_PUBLIC_H__
#define __MO_FG_PUBLIC_H__

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
#ifdef _MO_FG_EXPORTS
#define MO_FG_DECLARE MO_EXPORT
#else
#define MO_FG_DECLARE MO_IMPORT
#endif // _MO_FG_EXPORTS

MO_NAMESPACE_BEGIN

MO_NAMESPACE_END

#endif // __MO_FG_PUBLIC_H__
