//============================================================
// <T>��ͨ���塣</T>
//============================================================
#ifndef __MO_FS_PUBLIC_H__
#define __MO_FS_PUBLIC_H__

#ifndef __MO_COMMON_H__
#include <MoCommon.h>
#endif // __MO_COMMON_H__

//============================================================
/// @define ��������
#ifdef _MO_FS_EXPORTS
#define MO_FS_DECLARE MO_EXPORT
#else
#define MO_FS_DECLARE MO_IMPORT
#endif // _MO_FS_EXPORTS

MO_NAMESPACE_BEGIN

MO_NAMESPACE_END

#endif // __MO_FS_PUBLIC_H__
