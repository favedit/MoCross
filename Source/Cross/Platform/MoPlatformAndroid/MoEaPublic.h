//============================================================
// <T>��ͨ���塣</T>
//============================================================
#ifndef __MO_EA_PUBLIC_H__
#define __MO_EA_PUBLIC_H__

#ifndef __MO_COMMON_H__
#include <MoCommon.h>
#endif // __MO_COMMON_H__

#ifndef __MO_ENGINE_H__
#include <MoEngine.h>
#endif // __MO_ENGINE_H__

//============================================================
/// @define ��������
#ifdef _MO_EA_EXPORTS
#define MO_EA_DECLARE MO_EXPORT
#else
#define MO_EA_DECLARE MO_IMPORT
#endif

MO_NAMESPACE_BEGIN

MO_NAMESPACE_END

#endif // __MO_EA_PUBLIC_H__
