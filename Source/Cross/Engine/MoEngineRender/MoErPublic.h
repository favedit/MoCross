//============================================================
// <T>��ͨ���塣</T>
//============================================================
#ifndef __MO_ER_PUBLIC_H__
#define __MO_ER_PUBLIC_H__

#ifndef __MO_COMMON_H__
#include <MoCommon.h>
#endif // __MO_COMMON_H__

#ifndef __MO_ENGINE_H__
#include <MoEngine.h>
#endif // __MO_ENGINE_H__

#ifndef __MO_ENGINE3D_H__
#include <MoEngine3d.h>
#endif // __MO_ENGINE3D_H__

//============================================================
/// @define ��������
#ifdef _MO_ER_EXPORTS
#define MO_ER_DECLARE MO_EXPORT
#else
#define MO_ER_DECLARE MO_IMPORT
#endif // _MO_ER_EXPORTS

MO_NAMESPACE_BEGIN

MO_NAMESPACE_END

#endif // __MO_ER_PUBLIC_H__
