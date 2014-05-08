#ifndef __MO_PD10_CORE_H__
#define __MO_PD10_CORE_H__
//************************************************************

#ifdef _MO_WINDOWS
#ifndef _WINDOWS_
#include <Windows.h>
#endif // _WINDOWS_
#endif // _MO_WINDOWS

#ifndef __dxgi_h__
#include <DXGI.h>
#endif // __dxgi_h__

#ifndef __d3d10_1_h__
#include <d3d10_1.h>
#endif // __d3d10_1_h__

#ifndef __D3DX10_H__
#include <d3dx10.h>
#endif // __D3DX10_H__

#ifndef __D3D10SHADER_H__
#include <D3D10Shader.h>
#endif // __D3D10SHADER_H__

#ifndef __D3DCOMPILER_H__
#include <D3Dcompiler.h>
#endif // __D3DCOMPILER_H__

#ifndef __MO_PD10_COMMON_H__
#include "MoPd10Common.h"
#endif // __MO_PD10_COMMON_H__

MO_NAMESPACE_BEGIN

#define MO_INPUT_ELEMENT_MAXCNT 64

//============================================================
// <T>���Ͷ��塣</T>
typedef MO_PD10_DECLARE TFixArray<D3D10_INPUT_ELEMENT_DESC, MO_INPUT_ELEMENT_MAXCNT> MO_D3D10_INPUT_ELEMENT_DESC_ARRAY;

//============================================================
// <T>�豸���ߡ�</T>
//============================================================
class MO_PD10_DECLARE RDirectX10{
public:
   static D3D10_FILL_MODE ConvertFillMode(ERenderFillMode fillCd);
   static D3D10_CULL_MODE ConvertCullMode(ERenderCullMode cullCd);
   static DXGI_FORMAT ConvertIndexStride(ERenderIndexStride strideCd);
public:
   static ERenderShaderAttributeFormat ParseAttrbuteFormat(D3D_REGISTER_COMPONENT_TYPE componentType, TInt mask);
   static DXGI_FORMAT ConvertAttrbuteFormat(ERenderShaderAttributeFormat formatCd);
};

MO_NAMESPACE_END

//************************************************************
#endif // __MO_PD10_CORE_H__
