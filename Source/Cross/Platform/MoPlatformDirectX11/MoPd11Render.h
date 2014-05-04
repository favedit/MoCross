#ifndef __MO_PD11_RENDER_H__
#define __MO_PD11_RENDER_H__
//************************************************************

#ifndef __MO_PD11_COMMON_H__
#include "MoPd11Common.h"
#endif // __MO_PD11_COMMON_H__

#ifndef __MO_PD11_CORE_H__
#include "MoPd11Core.h"
#endif // __MO_PD11_CORE_H__

MO_NAMESPACE_BEGIN

//============================================================
// <T>��Ⱦ���㻺�塣</T>
//============================================================
class MO_PD11_DECLARE FPd11RenderVertexBuffer : public FRenderVertexBuffer
{
   MO_CLASS_DECLARE_INHERITS(FPd11RenderVertexBuffer, FRenderVertexBuffer);
protected:
   ID3D11Buffer* _piBuffer;
public:
   FPd11RenderVertexBuffer();
   MO_ABSTRACT ~FPd11RenderVertexBuffer();
public:
   //------------------------------------------------------------
   // <T>��ñ��ػ��塣</T>
   MO_INLINE ID3D11Buffer* NativeBuffer(){
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
class MO_PD11_DECLARE FPd11RenderIndexBuffer : public FRenderIndexBuffer
{
   MO_CLASS_DECLARE_INHERITS(FPd11RenderIndexBuffer, FRenderVertexBuffer);
protected:
   ID3D11Buffer* _piBuffer;
public:
   FPd11RenderIndexBuffer();
   MO_ABSTRACT ~FPd11RenderIndexBuffer();
public:
   //------------------------------------------------------------
   // <T>��ñ��ػ��塣</T>
   MO_INLINE ID3D11Buffer* NativeBuffer(){
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
// <T>��Ⱦ�����塣</T>
//============================================================
class MO_PD11_DECLARE FPd11RenderShaderBuffer : public FRenderObject
{
   MO_CLASS_DECLARE_INHERITS(FPd11RenderShaderBuffer, FRenderObject);
protected:
   TString _name;
   TInt _dataLength;
   FBytes* _pData;
   FBytes* _pCommit;
   TInt _commitLength;
   TInt _slot;
   ID3D11Buffer* _piBuffer;
public:
   FPd11RenderShaderBuffer();
   MO_ABSTRACT ~FPd11RenderShaderBuffer();
public:
   //------------------------------------------------------------
   // <T>������ơ�</T>
   MO_INLINE TCharC* Name(){
      return _name;
   }
   //------------------------------------------------------------
   // <T>�������ơ�</T>
   MO_INLINE void SetName(TCharC* pName){
      _name = pName;
   }
   //------------------------------------------------------------
   // <T>������ݳ��ȡ�</T>
   MO_INLINE TInt DataLength(){
      return _dataLength;
   }
   //------------------------------------------------------------
   // <T>�������ݳ��ȡ�</T>
   MO_INLINE void SetDataLength(TInt dataLength){
      _dataLength = dataLength;
   }
   //------------------------------------------------------------
   // <T>������ݡ�</T>
   MO_INLINE FBytes* Data(){
      return _pData;
   }
   //------------------------------------------------------------
   // <T>��ò�ۡ�</T>
   MO_INLINE TInt Solt(){
      return _slot;
   }
   //------------------------------------------------------------
   // <T>���ò�ۡ�</T>
   MO_INLINE void SetSolt(TInt slot){
      _slot = slot;
   }
   //------------------------------------------------------------
   // <T>��ñ��ػ��塣</T>
   MO_INLINE ID3D11Buffer* NativeiBuffer(){
      return _piBuffer;
   }
   //------------------------------------------------------------
   // <T>���ñ��ػ��塣</T>
   MO_INLINE void SetNativeiBuffer(ID3D11Buffer* piBuffer){
      _piBuffer = piBuffer;
   }
public:
   TResult Setup();
   TResult SetData(TInt index, TAnyC* pData, TInt length);
   TResult Update();
};
//------------------------------------------------------------
typedef MO_PD11_DECLARE GPtr<FPd11RenderShaderBuffer> GPd11RenderShaderBufferPtr;
typedef MO_PD11_DECLARE GPtrs<FPd11RenderShaderBuffer> GPd11RenderShaderBufferPtrs;

//============================================================
// <T>��Ⱦ��������</T>
//============================================================
class MO_PD11_DECLARE FPd11RenderShaderParameter : public FRenderShaderParameter
{
   MO_CLASS_DECLARE_INHERITS(FPd11RenderShaderParameter, FRenderShaderParameter);
protected:
   GPd11RenderShaderBufferPtr _buffer;
   ID3D11ShaderReflectionVariable* _piVariable;
public:
   FPd11RenderShaderParameter();
   MO_ABSTRACT ~FPd11RenderShaderParameter();
public:
   //------------------------------------------------------------
   // <T>��û��塣</T>
   MO_INLINE FPd11RenderShaderBuffer* Buffer(){
      return _buffer;
   }
   //------------------------------------------------------------
   // <T>���û��塣</T>
   MO_INLINE void SetBuffer(FPd11RenderShaderBuffer* pBuffer){
      _buffer = pBuffer;
   }
   //------------------------------------------------------------
   // <T>���û��塣</T>
   MO_INLINE void NativeVariable(FPd11RenderShaderBuffer* pBuffer){
      _buffer = pBuffer;
   }
   //------------------------------------------------------------
   // <T>��ñ��ر�����</T>
   MO_INLINE ID3D11ShaderReflectionVariable* NativeVariable(){
      return _piVariable;
   }
public:
   TResult LinkNative(ID3D11ShaderReflectionVariable* piVariable);
public:
   MO_OVERRIDE TResult Get(TAny* pData, TInt capacity);
   MO_OVERRIDE TResult Set(TAny* pData, TInt length);
};

//============================================================
// <T>��Ⱦ�����ԡ�</T>
//============================================================
class MO_PD11_DECLARE FPd11RenderShaderAttribute : public FRenderShaderAttribute
{
   MO_CLASS_DECLARE_INHERITS(FPd11RenderShaderAttribute, FRenderShaderAttribute);
protected:
public:
   FPd11RenderShaderAttribute();
   MO_ABSTRACT ~FPd11RenderShaderAttribute();
};

//============================================================
// <T>������Ⱦ����</T>
//============================================================
class MO_PD11_DECLARE FPd11RenderVertexShader : public FRenderVertexShader
{
   MO_CLASS_DECLARE_INHERITS(FPd11RenderVertexShader, FRenderVertexShader);
protected:
   ID3D10Blob* _piData;
   ID3D11ClassLinkage* _piLinkage;
   ID3D11VertexShader* _piShader;
public:
   FPd11RenderVertexShader();
   MO_ABSTRACT ~FPd11RenderVertexShader();
public:
   //------------------------------------------------------------
   // <T>��ñ������ݡ�</T>
   MO_INLINE ID3D10Blob* NativeData(){
      return _piData;
   }
   //------------------------------------------------------------
   // <T>��ñ�����Ⱦ����</T>
   MO_INLINE ID3D11VertexShader* NativeShader(){
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
class MO_PD11_DECLARE FPd11RenderFragmentShader : public FRenderFragmentShader
{
   MO_CLASS_DECLARE_INHERITS(FPd11RenderFragmentShader, FRenderVertexShader);
protected:
   ID3D10Blob* _piData;
   ID3D11PixelShader* _piShader;
public:
   FPd11RenderFragmentShader();
   MO_ABSTRACT ~FPd11RenderFragmentShader();
public:
   //------------------------------------------------------------
   // <T>��ñ������ݡ�</T>
   MO_INLINE ID3D10Blob* NativeData(){
      return _piData;
   }
   //------------------------------------------------------------
   // <T>��ñ�����Ⱦ����</T>
   MO_INLINE ID3D11PixelShader* NativeShader(){
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
class MO_PD11_DECLARE FPd11RenderProgram : public FRenderProgram
{
   MO_CLASS_DECLARE_INHERITS(FPd11RenderProgram, FRenderProgram);
protected:
   GPd11RenderShaderBufferPtrs _buffers;
   ID3D11InputLayout* _piInputLayout;
public:
   FPd11RenderProgram();
   MO_ABSTRACT ~FPd11RenderProgram();
public:
   //------------------------------------------------------------
   // <T>��û��弯�ϡ�</T>
   MO_INLINE GPd11RenderShaderBufferPtrs& Buffers(){
      return _buffers;
   }
public:
   MO_OVERRIDE TInt FindDefine(TCharC* pCode);
   MO_OVERRIDE TInt FindAttribute(TCharC* pCode);
   MO_OVERRIDE TResult BindAttribute(TInt slot, TCharC* pCode);
protected:
   FPd11RenderShaderBuffer* FindBuffer(TCharC* pName);
   TResult BuildShader(FRenderShader* pShader, ID3D10Blob* piData);
public:
   MO_OVERRIDE TResult Setup();
   MO_OVERRIDE TResult Build();
   MO_OVERRIDE TResult Link();
public:
   MO_OVERRIDE TResult SetConstVariable(ERenderShader shaderCd, TCharC* pName, TAnyC* pData, TInt length);
public:
   MO_OVERRIDE TResult Suspend();
   MO_OVERRIDE TResult Resume();
   MO_OVERRIDE TResult Dispose();
};

//============================================================
// <T>��ȾĿ�ꡣ</T>
//============================================================
class MO_PD11_DECLARE FPd11RenderTarget : public FRenderTarget
{
   MO_CLASS_DECLARE_INHERITS(FPd11RenderTarget, FRenderTarget);
protected:
   ID3D11RenderTargetView* _piRenderTarget;
   ID3D11DepthStencilView* _piDepthStencil;
public:
   FPd11RenderTarget();
   MO_ABSTRACT ~FPd11RenderTarget();
public:
   //------------------------------------------------------------
   // <T>��ñ�����ȾĿ�ꡣ</T>
   MO_INLINE ID3D11RenderTargetView* NativeRenderTarget(){
      return _piRenderTarget;
   }
   //------------------------------------------------------------
   // <T>���ñ�����ȾĿ�ꡣ</T>
   MO_INLINE void SetNativeRenderTarget(ID3D11RenderTargetView* piRenderTarget){
      _piRenderTarget = piRenderTarget;
   }
   //------------------------------------------------------------
   // <T>��ñ�����Ȼ��塣</T>
   MO_INLINE ID3D11DepthStencilView* NativeDepthStencil(){
      return _piDepthStencil;
   }
   //------------------------------------------------------------
   // <T>���ñ�����Ȼ��塣</T>
   MO_INLINE void SetNativeDepthStencil(ID3D11DepthStencilView* piDepthStencil){
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
class MO_PD11_DECLARE FPd11RenderFlatTexture : public FRenderFlatTexture
{
   MO_CLASS_DECLARE_INHERITS(FPd11RenderFlatTexture, FRenderFlatTexture);
protected:
   ID3D11Texture2D* _piTexture;
public:
   FPd11RenderFlatTexture();
   MO_ABSTRACT ~FPd11RenderFlatTexture();
public:
   //------------------------------------------------------------
   // <T>��ñ�������</T>
   MO_INLINE ID3D11Texture2D* NativeTexture(){
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
class MO_PD11_DECLARE FPd11RenderCubeTexture : public FRenderCubeTexture
{
   MO_CLASS_DECLARE_INHERITS(FPd11RenderCubeTexture, FRenderFlatTexture);
protected:
   //GLuint _textureId;
public:
   FPd11RenderCubeTexture();
   MO_ABSTRACT ~FPd11RenderCubeTexture();
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
class MO_PD11_DECLARE FPd11RenderDevice : public FRenderDevice
{
   MO_CLASS_DECLARE_INHERITS(FPd11RenderDevice, FRenderDevice);
protected:
   // ������Ϣ
   TBool _optionTexture;
   // �������㻺�弯��
   FRenderFlatTextureList* _pLinkFlatTextures;
   FRenderCubeTextureList* _pLinkCubeTextures;
   // �ӿ�ָ��
   HWND _windowHandle;
   IDXGISwapChain* _piSwapChain;
   ID3D11Device* _piDevice;
   ID3D11DeviceContext* _piContext;
   GPtr<FPd11RenderTarget> _defaultRenderTarget;
public:
   FPd11RenderDevice();
   MO_ABSTRACT ~FPd11RenderDevice();
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
   MO_INLINE ID3D11Device* NativeDevice(){
      return _piDevice;
   }
   //------------------------------------------------------------
   // <T>��ñ��ػ�����</T>
   MO_INLINE ID3D11DeviceContext* NativeContext(){
      return _piContext;
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
   MO_OVERRIDE TResult BindConstData(ERenderShader shaderCd, TInt slot, ERenderShaderParameterFormat formatCd, TAnyC* pData, TInt length);
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
#endif // __MO_PD11_RENDER_H__
