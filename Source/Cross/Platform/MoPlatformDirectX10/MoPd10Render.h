#ifndef __MO_PD10_RENDER_H__
#define __MO_PD10_RENDER_H__
//************************************************************

#ifdef _MO_WINDOWS
#ifndef _WINDOWS_
#include <Windows.h>
#endif // _WINDOWS_
#endif // _MO_WINDOWS

#ifndef __dxgi_h__
#include <DXGI.h>
#endif // __dxgi_h__

#ifndef __d3d10_h__
#include <d3d10.h>
#endif // __d3d10_h__

#ifndef __D3DX10_H__
#include <d3dx10.h>
#endif // __D3DX10_H__

#ifndef __MO_PD10_COMMON_H__
#include "MoPd10Common.h"
#endif // __MO_PD10_COMMON_H__

MO_NAMESPACE_BEGIN

//============================================================
// <T>�豸���ߡ�</T>
//============================================================
class MO_PD10_DECLARE RDirectX10{
public:
   static D3D10_FILL_MODE ConvertFillMode(ERenderFillMode fillCd);
   static D3D10_CULL_MODE ConvertCullMode(ERenderCullMode cullCd);
   static DXGI_FORMAT ConvertIndexStride(ERenderIndexStride strideCd);
};

//============================================================
// <T>��Ⱦ���㻺�塣</T>
//============================================================
class MO_PD10_DECLARE FPd10RenderVertexBuffer : public FRenderVertexBuffer
{
   MO_CLASS_DECLARE_INHERITS(FPd10RenderVertexBuffer, FRenderVertexBuffer);
protected:
   ID3D10Buffer* _piBuffer;
public:
   FPd10RenderVertexBuffer();
   MO_ABSTRACT ~FPd10RenderVertexBuffer();
public:
   //------------------------------------------------------------
   // <T>��ñ��ػ��塣</T>
   MO_INLINE ID3D10Buffer* NativeBuffer(){
      return _piBuffer;
   }
public:
   MO_OVERRIDE TResult OnSetup();
public:
   MO_OVERRIDE TResult Upload(TByteC* pData, TInt length);
public:
   MO_OVERRIDE TResult Suspend();
   MO_OVERRIDE TResult Resume();
   MO_OVERRIDE TResult Dispose();
};

//============================================================
// <T>��Ⱦ�������塣</T>
//============================================================
class MO_PD10_DECLARE FPd10RenderIndexBuffer : public FRenderIndexBuffer
{
   MO_CLASS_DECLARE_INHERITS(FPd10RenderIndexBuffer, FRenderVertexBuffer);
protected:
   ID3D10Buffer* _piBuffer;
public:
   FPd10RenderIndexBuffer();
   MO_ABSTRACT ~FPd10RenderIndexBuffer();
public:
   //------------------------------------------------------------
   // <T>��ñ��ػ��塣</T>
   MO_INLINE ID3D10Buffer* NativeBuffer(){
      return _piBuffer;
   }
public:
   MO_OVERRIDE TResult OnSetup();
public:
   MO_OVERRIDE TResult Upload(TByteC* pMemory, TInt length);
public:
   MO_OVERRIDE TResult Suspend();
   MO_OVERRIDE TResult Resume();
   MO_OVERRIDE TResult Dispose();
};

//============================================================
// <T>������Ⱦ����</T>
//============================================================
class MO_PD10_DECLARE FPd10RenderVertexShader : public FRenderVertexShader
{
   MO_CLASS_DECLARE_INHERITS(FPd10RenderVertexShader, FRenderVertexShader);
protected:
   ID3D10Blob* _piShader;
public:
   FPd10RenderVertexShader();
   MO_ABSTRACT ~FPd10RenderVertexShader();
public:
   //------------------------------------------------------------
   // <T>��ñ�����Ⱦ����</T>
   MO_INLINE ID3D10Blob* NativeShader(){
      return _piShader;
   }
public:
   MO_OVERRIDE TResult Setup();
public:
   MO_OVERRIDE TResult Compile(TCharC* pSource);
public:
   MO_OVERRIDE TResult Suspend();
   MO_OVERRIDE TResult Resume();
   MO_OVERRIDE TResult Dispose();
};

//============================================================
// <T>������Ⱦ����</T>
//============================================================
class MO_PD10_DECLARE FPd10RenderFragmentShader : public FRenderFragmentShader
{
   MO_CLASS_DECLARE_INHERITS(FPd10RenderFragmentShader, FRenderVertexShader);
protected:
   ID3D10Blob* _piShader;
public:
   FPd10RenderFragmentShader();
   MO_ABSTRACT ~FPd10RenderFragmentShader();
public:
   //------------------------------------------------------------
   // <T>��ñ�����Ⱦ����</T>
   MO_INLINE ID3D10Blob* NativeShader(){
      return _piShader;
   }
public:
   MO_OVERRIDE TResult Setup();
public:
   MO_OVERRIDE TResult Compile(TCharC* pSource);
public:
   MO_OVERRIDE TResult Suspend();
   MO_OVERRIDE TResult Resume();
   MO_OVERRIDE TResult Dispose();
};

//============================================================
// <T>��Ⱦ����</T>
//============================================================
class MO_PD10_DECLARE FPd10RenderProgram : public FRenderProgram
{
   MO_CLASS_DECLARE_INHERITS(FPd10RenderProgram, FRenderProgram);
protected:
   //GLuint _programId;
public:
   FPd10RenderProgram();
   MO_ABSTRACT ~FPd10RenderProgram();
public:
   //------------------------------------------------------------
   // <T>��ô��롣</T>
   //MO_INLINE GLuint ProgramId(){
   //   return _programId;
   //}
public:
   MO_OVERRIDE TInt FindDefine(TCharC* pCode);
   MO_OVERRIDE TInt FindAttribute(TCharC* pCode);
   MO_OVERRIDE TResult BindAttribute(TInt slot, TCharC* pCode);
public:
   MO_OVERRIDE TResult Setup();
   MO_OVERRIDE TResult Build();
   MO_OVERRIDE TResult Link();
public:
   MO_OVERRIDE TResult Suspend();
   MO_OVERRIDE TResult Resume();
   MO_OVERRIDE TResult Dispose();
};

//============================================================
// <T>��ȾĿ�ꡣ</T>
//============================================================
class MO_PD10_DECLARE FPd10RenderTarget : public FRenderTarget
{
   MO_CLASS_DECLARE_INHERITS(FPd10RenderTarget, FRenderTarget);
protected:
   ID3D10RenderTargetView* _piRenderTarget;
   ID3D10DepthStencilView* _piDepthStencil;
public:
   FPd10RenderTarget();
   MO_ABSTRACT ~FPd10RenderTarget();
public:
   //------------------------------------------------------------
   // <T>��ñ�����ȾĿ�ꡣ</T>
   MO_INLINE ID3D10RenderTargetView* NativeRenderTarget(){
      return _piRenderTarget;
   }
   //------------------------------------------------------------
   // <T>���ñ�����ȾĿ�ꡣ</T>
   MO_INLINE void SetNativeRenderTarget(ID3D10RenderTargetView* piRenderTarget){
      _piRenderTarget = piRenderTarget;
   }
   //------------------------------------------------------------
   // <T>��ñ�����Ȼ��塣</T>
   MO_INLINE ID3D10DepthStencilView* NativeDepthStencil(){
      return _piDepthStencil;
   }
   //------------------------------------------------------------
   // <T>���ñ�����Ȼ��塣</T>
   MO_INLINE void SetNativeDepthStencil(ID3D10DepthStencilView* piDepthStencil){
      _piDepthStencil = piDepthStencil;
   }
public:
   MO_OVERRIDE TResult OnSetup();
public:
   MO_OVERRIDE TResult Suspend();
   MO_OVERRIDE TResult Resume();
   MO_OVERRIDE TResult Dispose();
};

//============================================================
// <T>��Ⱦƽ������</T>
//============================================================
class MO_PD10_DECLARE FPd10RenderFlatTexture : public FRenderFlatTexture
{
   MO_CLASS_DECLARE_INHERITS(FPd10RenderFlatTexture, FRenderFlatTexture);
protected:
   ID3D10Texture2D* _piTexture;
public:
   FPd10RenderFlatTexture();
   MO_ABSTRACT ~FPd10RenderFlatTexture();
public:
   //------------------------------------------------------------
   // <T>��ñ�������</T>
   MO_INLINE ID3D10Texture2D* NativeTexture(){
      return _piTexture;
   }
public:
   MO_OVERRIDE TResult OnSetup();
public:
   MO_OVERRIDE TResult Resize(TInt width, TInt height);
   MO_OVERRIDE TResult Unserialize(IDataInput* pInput);
   MO_OVERRIDE TResult Upload(TByteC* pData, TInt length);
   TResult LoadDataFile(TCharC* pFileName);
public:
   MO_OVERRIDE TResult Suspend();
   MO_OVERRIDE TResult Resume();
   MO_OVERRIDE TResult Dispose();
};

//============================================================
// <T>��ȾCUBE����</T>
//============================================================
class MO_PD10_DECLARE FPd10RenderCubeTexture : public FRenderCubeTexture
{
   MO_CLASS_DECLARE_INHERITS(FPd10RenderCubeTexture, FRenderFlatTexture);
protected:
   //GLuint _textureId;
public:
   FPd10RenderCubeTexture();
   MO_ABSTRACT ~FPd10RenderCubeTexture();
public:
   ////------------------------------------------------------------
   //// <T>��ô��롣</T>
   //MO_INLINE GLuint TextureId(){
   //   return _textureId;
   //}
public:
   MO_OVERRIDE TResult OnSetup();
public:
   MO_OVERRIDE TResult Resize(TInt size);
   MO_OVERRIDE TResult Unserialize(IDataInput* pInput);
   MO_OVERRIDE TResult Upload(TByteC* pData, TInt length);
   TResult LoadDataFile(TCharC* pFileName);
public:
   MO_OVERRIDE TResult Suspend();
   MO_OVERRIDE TResult Resume();
   MO_OVERRIDE TResult Dispose();
};

//============================================================
// <T>��Ⱦ�豸��</T>
//============================================================
class MO_PD10_DECLARE FPd10RenderDevice : public FRenderDevice
{
   MO_CLASS_DECLARE_INHERITS(FPd10RenderDevice, FRenderDevice);
protected:
   // ���ģʽ
   ERenderFillMode _fillModeCd;
   // �����Ϣ
   TBool _optionDepth;
   ERenderDepthMode _depthModeCd;
   // ������Ϣ
   TBool _optionCull;
   ERenderCullMode _cullModeCd;
   // �����Ϣ
   TBool _statusBlend;
   ERenderBlendMode _blendSourceCd;
   ERenderBlendMode _blendTargetCd;
   TInt _renderTextureActiveSlot;
   // ������Ϣ
   TBool _optionTexture;
   //GLint _vertexConstLimit;
   //GLint _vertexAttributeLimit;
   //GLint _fragmentConstLimit;
   //GLint _varyingLimit;
   //GLint _textureLimit;
   //GLint _textureSizeLimit;
   //GLint _textureTotalLimit;
   //GLint _renderTargetLimit;
   // �������㻺�弯��
   FRenderFlatTextureList* _pLinkFlatTextures;
   FRenderCubeTextureList* _pLinkCubeTextures;
   // Ч��ͳ��
   GPtr<FStatistics> _renderDrawStatistics;
   // �ӿ�ָ��
   HWND _windowHandle;
   IDXGISwapChain* _piSwapChain;
   ID3D10Device* _piDevice;
   GPtr<FPd10RenderTarget> _defaultRenderTarget;
public:
   FPd10RenderDevice();
   MO_ABSTRACT ~FPd10RenderDevice();
protected:
   TBool UpdateContext();
public:
   //------------------------------------------------------------
   // <T>��ô��ھ����</T>
   MO_INLINE HWND WindowHandle(){
      return _windowHandle;
   }
   //------------------------------------------------------------
   // <T>���ô��ھ����</T>
   MO_INLINE void SetWindowHandle(HWND handle){
      _windowHandle = handle;
   }
   //------------------------------------------------------------
   // <T>��ñ��ؽ�������</T>
   MO_INLINE IDXGISwapChain* NativeSwapChain(){
      return _piSwapChain;
   }
   //------------------------------------------------------------
   // <T>��ñ����豸��</T>
   MO_INLINE ID3D10Device* NativeDevice(){
      return _piDevice;
   }
public:
   MO_OVERRIDE TResult Setup();
   MO_ABSTRACT TResult Suspend();
   MO_ABSTRACT TResult Resume();
public:
   MO_OVERRIDE TResult CheckError(TCharC* pCode, TCharC* pMessage, ...);
public:
   MO_OVERRIDE FRenderVertexBuffer* CreateVertexBuffer(FClass* pClass = NULL);
   MO_OVERRIDE FRenderIndexBuffer* CreateIndexBuffer(FClass* pClass = NULL);
   MO_OVERRIDE FRenderProgram* CreateProgrom(FClass* pClass = NULL);
   MO_OVERRIDE FRenderTarget* CreateRenderTarget(FClass* pClass = NULL);
   MO_OVERRIDE FRenderFlatTexture* CreateFlatTexture(FClass* pClass = NULL);
   MO_OVERRIDE FRenderCubeTexture* CreateCubeTexture(FClass* pClass = NULL);
public:
   MO_OVERRIDE TResult Clear(TFloat red = 0.0f, TFloat green = 0.0f, TFloat blue = 0.0f, TFloat alpha = 1.0f, TFloat depth = 1.0f);
   MO_OVERRIDE TResult SetBackBuffer(TInt width, TInt height, TInt antiAlias, TBool depthed = ETrue);
   MO_OVERRIDE TResult SetFillMode(ERenderFillMode fillModeCd);
   MO_OVERRIDE TResult SetDepthMode(TBool depth, ERenderDepthMode depthCd = ERenderDepthMode_None);
   MO_OVERRIDE TResult SetCullingMode(TBool cull, ERenderCullMode cullCd = ERenderCullMode_None);
   MO_OVERRIDE TResult SetBlendFactors(TBool blend, ERenderBlendMode sourceCd = ERenderBlendMode_None, ERenderBlendMode targetCd = ERenderBlendMode_None);
   MO_OVERRIDE TResult SetScissorRectangle(TInt left, TInt top, TInt width, TInt height);
   MO_OVERRIDE TResult SetRenderTarget(FRenderTarget* pRenderTarget = NULL);
   MO_OVERRIDE TResult SetProgram(FRenderProgram* pProgram);
   MO_OVERRIDE TResult BindConstData(ERenderShader shaderCd, TInt slot, ERenderShaderConstForamt formatCd, TAnyC* pData, TInt length);
   MO_OVERRIDE TResult BindConstFloat3(ERenderShader shaderCd, TInt slot, TFloat x = 0.0f, TFloat y = 0.0f, TFloat z = 0.0f);
   MO_OVERRIDE TResult BindConstFloat4(ERenderShader shaderCd, TInt slot, TFloat x = 0.0f, TFloat y = 0.0f, TFloat z = 0.0f, TFloat w = 1.0f);
   MO_OVERRIDE TResult BindConstMatrix3x3(ERenderShader shaderCd, TInt slot, const SFloatMatrix3d& matrix);
   MO_OVERRIDE TResult BindConstMatrix4x4(ERenderShader shaderCd, TInt slot, const SFloatMatrix3d& matrix);
   MO_OVERRIDE TResult BindVertexBuffer(TInt slot, FRenderVertexBuffer* pVertexBuffer, TInt offset, ERenderVertexFormat formatCd);
   MO_OVERRIDE TResult BindTexture(TInt slot, FRenderTexture* pTexture);
   MO_OVERRIDE TResult DrawTriangles(FRenderIndexBuffer* pIndexBuffer, TInt offset, TInt count);
   MO_OVERRIDE TResult Present();
};

MO_NAMESPACE_END

//************************************************************
#endif // __MO_PD10_RENDER_H__
