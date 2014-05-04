#include "MoPd11Render.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FPd11RenderDevice, FRenderDevice);

//============================================================
// <T>������̨����</T>
//============================================================
FPd11RenderDevice::FPd11RenderDevice(){
   // ��ʼ����������
   _pCapability = MO_CREATE(FRenderCapability);
   _pCapability->SetCode("directx11");
   _pCapability->SetShaderVertexVersion("vs_5_0");
   _pCapability->SetShaderFragmentVersion("ps_5_0");
   // ��ʼ����������
   _optionTexture = EFalse;
   //_textureLimit = 0;
   // ��ʼ����������
   _pLinkFlatTextures = MO_CREATE(FRenderFlatTextureList);
   _pLinkCubeTextures = MO_CREATE(FRenderCubeTextureList);
   // ��ʼ���ӿ�ָ��
   MO_CLEAR(_piSwapChain);
   MO_CLEAR(_piDevice);
   MO_CLEAR(_piContext);
   // ע���༯��
   _pClassFactory->Register(MO_RENDEROBJECT_SHADERATTRIBUTE, FPd11RenderShaderAttribute::Class());
   _pClassFactory->Register(MO_RENDEROBJECT_SHADERPARAMETER, FPd11RenderShaderParameter::Class());
   _pClassFactory->Register(MO_RENDEROBJECT_SHADERSAMPLER, FRenderShaderSampler::Class());
}

//============================================================
// <T>������̨����</T>
//============================================================
FPd11RenderDevice::~FPd11RenderDevice(){
   MO_DELETE(_pCapability);
   // ɾ����������
   MO_DELETE(_pLinkFlatTextures);
   MO_DELETE(_pLinkCubeTextures);
   // �ͷ��ڴ�
   MO_RELEASE(_piSwapChain);
   MO_RELEASE(_piDevice);
   MO_RELEASE(_piContext);
}

//============================================================
// <T>���»�����</T>
//============================================================
TBool FPd11RenderDevice::UpdateContext(){
   TBool result = EFalse;
   // ���ü���ĳ���
   if(_pActiveProgram != _pProgram){
      //FPd11RenderProgram* pProgrom = (FPd11RenderProgram*)_pProgram;
      //glUseProgram(pProgrom->ProgramId());
      //_pProgram = _pActiveProgram;
      result = ETrue;
   }
   return result;
}

//============================================================
// <T>���ô���</T>
//
// @return ������
//============================================================
TResult FPd11RenderDevice::Setup(){
   // �����ô���
   TResult result = FRenderDevice::Setup();
   // �����Ļ�豸
   FScreenDevice* pScreenDevice = RDeviceManager::Instance().Find<FScreenDevice>();
   SIntSize2& screenSize = pScreenDevice->Size();
   //............................................................
   // ����������
   DXGI_SWAP_CHAIN_DESC description;
   RType<DXGI_SWAP_CHAIN_DESC>::Clear(&description);
   description.BufferCount = 1;
   description.BufferDesc.Width = screenSize.width;
   description.BufferDesc.Height = screenSize.height;
   description.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
   TBool m_vsync_enabled = ETrue;
   if(m_vsync_enabled){
      description.BufferDesc.RefreshRate.Numerator = 1;
      description.BufferDesc.RefreshRate.Denominator = 60;
   }else{
      description.BufferDesc.RefreshRate.Numerator = 0;
      description.BufferDesc.RefreshRate.Denominator = 1;
   }
   description.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
   description.OutputWindow = _windowHandle;
   description.SampleDesc.Count = 1;
   description.SampleDesc.Quality = 0;
   description.Windowed = true;
   description.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
   description.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
   description.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
   description.Flags = 0;
   HRESULT dxResult = ::D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, 0, NULL, 0, D3D11_SDK_VERSION, &description, &_piSwapChain, &_piDevice, NULL, &_piContext);
   if(FAILED(dxResult)){
      MO_FATAL("Create device failure.");
      return EFailure;
   }
   //............................................................
   _defaultRenderTarget = FPd11RenderTarget::InstanceCreate();
   _defaultRenderTarget->SetDevice(this);
   _defaultRenderTarget->Setup();
   // ������ȾĿ��
   ID3D11Resource* pBackBuffer = NULL;
   dxResult = _piSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
   if(FAILED(dxResult)){
      MO_FATAL("Get backbugger failure.");
      return EFailure;
   }
   ID3D11RenderTargetView* pRenderTarget = NULL;
   dxResult = _piDevice->CreateRenderTargetView(pBackBuffer, NULL, &pRenderTarget);
   if(FAILED(dxResult)){
      MO_FATAL("Create render target view failure.");
      return EFailure;
   }
   MO_RELEASE(pBackBuffer);
   _defaultRenderTarget->SetNativeRenderTarget(pRenderTarget);
   _pActiveRenderTarget = _defaultRenderTarget;
   //............................................................
   // ������Ȼ���
   D3D11_TEXTURE2D_DESC depthBufferDesc;
   RType<D3D11_TEXTURE2D_DESC>::Clear(&depthBufferDesc);
   depthBufferDesc.Width = screenSize.width;
   depthBufferDesc.Height = screenSize.height;
   depthBufferDesc.MipLevels = 1;
   depthBufferDesc.ArraySize = 1;
   depthBufferDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
   depthBufferDesc.SampleDesc.Count = 1;
   depthBufferDesc.SampleDesc.Quality = 0;
   depthBufferDesc.Usage = D3D11_USAGE_DEFAULT;
   depthBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
   depthBufferDesc.CPUAccessFlags = 0;
   depthBufferDesc.MiscFlags = 0;
   ID3D11Texture2D* _pDepthStencilBuffer = NULL;
   dxResult = _piDevice->CreateTexture2D(&depthBufferDesc, NULL, &_pDepthStencilBuffer);
   if(FAILED(dxResult)){
      MO_FATAL("Get backbugger failure.");
      return EFailure;
   }
   //............................................................
   // ������Ȼ���
   D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
   RType<D3D11_DEPTH_STENCIL_DESC>::Clear(&depthStencilDesc);
   depthStencilDesc.DepthEnable = true;
   depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
   depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;
   depthStencilDesc.StencilEnable = true;
   depthStencilDesc.StencilReadMask = 0xFF;
   depthStencilDesc.StencilWriteMask = 0xFF;
   depthStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
   depthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
   depthStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
   depthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
   depthStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
   depthStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
   depthStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
   depthStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
   ID3D11DepthStencilState* _pDepthStencilState = NULL;
   dxResult = _piDevice->CreateDepthStencilState(&depthStencilDesc, &_pDepthStencilState);
   if(FAILED(dxResult)){
      MO_FATAL("Create depth stencil state failure.");
      return EFailure;
   }
   //............................................................
   // ������Ȼ���
   D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;
   RType<D3D11_DEPTH_STENCIL_VIEW_DESC>::Clear(&depthStencilViewDesc);
   depthStencilViewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
   depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
   depthStencilViewDesc.Texture2D.MipSlice = 0;
   ID3D11DepthStencilView* _pDepthStencilView = NULL;
   dxResult = _piDevice->CreateDepthStencilView(_pDepthStencilBuffer, &depthStencilViewDesc, &_pDepthStencilView);
   if(FAILED(dxResult)){
      MO_FATAL("Create depth stencil view failure.");
      return EFailure;
   }
   _defaultRenderTarget->SetOptionDepth(ETrue);
   _defaultRenderTarget->SetNativeDepthStencil(_pDepthStencilView);
   //............................................................
   // ������Ȼ���
   D3D11_RASTERIZER_DESC rasterDesc;
   RType<D3D11_RASTERIZER_DESC>::Clear(&rasterDesc);
   rasterDesc.AntialiasedLineEnable = false;
   rasterDesc.CullMode = D3D11_CULL_BACK;
   rasterDesc.DepthBias = 0;
   rasterDesc.DepthBiasClamp = 0.0f;
   rasterDesc.DepthClipEnable = true;
   rasterDesc.FillMode = D3D11_FILL_SOLID;
   rasterDesc.FrontCounterClockwise = false;
   rasterDesc.MultisampleEnable = false;
   rasterDesc.ScissorEnable = false;
   rasterDesc.SlopeScaledDepthBias = 0.0f;
   ID3D11RasterizerState* _pRasterState = NULL;
   dxResult = _piDevice->CreateRasterizerState(&rasterDesc, &_pRasterState);
   if(FAILED(dxResult)){
      MO_FATAL("Create rasterizer state view failure.");
      return EFailure;
   }
   _piContext->RSSetState(_pRasterState);
   //............................................................
   // �����ӽ�
   D3D11_VIEWPORT viewport;
   RType<D3D11_VIEWPORT>::Clear(&viewport);
   viewport.Width = (TFloat)screenSize.width;
   viewport.Height = (TFloat)screenSize.height;
   viewport.MinDepth = 0.0f;
   viewport.MaxDepth = 1.0f;
   viewport.TopLeftX = 0;
   viewport.TopLeftY = 0;
   _piContext->RSSetViewports(1, &viewport);
   return ESuccess;
}

//============================================================
// <T>��ͣ����</T>
//
// @return ������
//============================================================
TResult FPd11RenderDevice::Suspend(){
   // ��ͣ����
   FRenderDevice::Suspend();
   return ESuccess;
}

//============================================================
// <T>��������</T>
//
// @return ������
//============================================================
TResult FPd11RenderDevice::Resume(){
   FRenderDevice::Resume();
   return ESuccess;
}

//============================================================
// <T>���ִ�д���</T>
//
// @param pCode ����
// @return ������
//============================================================
TResult FPd11RenderDevice::CheckError(TCharC* pCode, TCharC* pMessage, ...){
   // ��ô���ԭ��
   TBool result = EFalse;
//   GLenum errorCode = 0;
//   TCharC* pErrorReason = NULL;
//   while(ETrue){
//      // ��ô���
//      GLenum code = glGetError();
//      if(code == GL_NO_ERROR){
//         break;
//      }
//      // ���ԭ��
//      switch(code){
//         case GL_INVALID_OPERATION:
//            pErrorReason = "Invalid operation.";
//            break;
//         case GL_INVALID_ENUM:
//            pErrorReason = "Invalid enum.";
//            break;
//         case GL_INVALID_VALUE:
//            pErrorReason = "Invalid value.";
//            break;
//         case GL_INVALID_FRAMEBUFFER_OPERATION:
//            pErrorReason = "Invalid paramebuffer opeartion."; 
//            break;
//         case GL_OUT_OF_MEMORY:
//            pErrorReason = "Out of memory.";
//            break;
//         default:
//            pErrorReason = "Unknown"; 
//            break;
//      }
//      result = ETrue;
//      errorCode = code;
//#ifdef _MO_WINDOWS
//      break;
//#endif // _MO_WINDOWS
//   }
//   //............................................................
//   // ���������Ϣ
//   if(result){
//      // ��ʽ���ɱ�����ַ�����Ϣ
//      TFsText message;
//      va_list params;
//      va_start(params, pMessage);
//      message.AppendFormatParameters(pMessage, params);
//      va_end(params);
//      // ���������Ϣ
//      MO_ERROR("%s (code=%s, error=0x%04X(%d), reason=%s)", (TCharC*)message, pCode, errorCode, errorCode, pErrorReason);
//   }
   return result;
}

//============================================================
// <T>�������㻺�塣</T>
//
// @param pClass �����
// @return ���㻺��
//============================================================
FRenderVertexBuffer* FPd11RenderDevice::CreateVertexBuffer(FClass* pClass){
   FRenderVertexBuffer* pVertexBuffer = FPd11RenderVertexBuffer::InstanceCreate();
   pVertexBuffer->SetDevice(this);
   _storageVertexBuffers.Push(pVertexBuffer);
   return pVertexBuffer;
}

//============================================================
// <T>�����������塣</T>
//
// @param pClass �����
// @return ��������
//============================================================
FRenderIndexBuffer* FPd11RenderDevice::CreateIndexBuffer(FClass* pClass){
   FRenderIndexBuffer* pIndexBuffer = FPd11RenderIndexBuffer::InstanceCreate();
   pIndexBuffer->SetDevice(this);
   _storageIndexBuffers.Push(pIndexBuffer);
   return pIndexBuffer;
}

//============================================================
// <T>��������</T>
//
// @param pClass �����
// @return ����
//============================================================
FRenderProgram* FPd11RenderDevice::CreateProgrom(FClass* pClass){
   FPd11RenderProgram* pProgram = FPd11RenderProgram::InstanceCreate();
   pProgram->SetDevice(this);
   _storagePrograms.Push(pProgram);
   return pProgram;
}

//============================================================
// <T>������ȾĿ�ꡣ</T>
//
// @param pClass �����
// @return ��ȾĿ��
//============================================================
FRenderTarget* FPd11RenderDevice::CreateRenderTarget(FClass* pClass){
   FPd11RenderTarget* pRenderTarget = FPd11RenderTarget::InstanceCreate();
   pRenderTarget->SetDevice(this);
   _storageTargets.Push(pRenderTarget);
   return pRenderTarget;
}

//============================================================
// <T>����ƽ������</T>
//
// @param pClass �����
// @return ����
//============================================================
FRenderFlatTexture* FPd11RenderDevice::CreateFlatTexture(FClass* pClass){
   FPd11RenderFlatTexture* pTexture = FPd11RenderFlatTexture::InstanceCreate();
   pTexture->SetDevice(this);
   _storageTextures.Push(pTexture);
   _pLinkFlatTextures->Push(pTexture);
   return pTexture;
}

//============================================================
// <T>�����ռ�����</T>
//
// @param pClass �����
// @return ����
//============================================================
FRenderCubeTexture* FPd11RenderDevice::CreateCubeTexture(FClass* pClass){
   FPd11RenderCubeTexture* pTexture = FPd11RenderCubeTexture::InstanceCreate();
   pTexture->SetDevice(this);
   _storageTextures.Push(pTexture);
   _pLinkCubeTextures->Push(pTexture);
   return pTexture;
}

//============================================================
// <T>������ݡ�</T>
//
// @param red ��ɫ
// @param green ��ɫ
// @param blue ��ɫ
// @param alpha ͸��
// @param depth ���
// @return ������
//============================================================
TResult FPd11RenderDevice::Clear(TFloat red, TFloat green, TFloat blue, TFloat alpha, TFloat depth){
   MO_CHECK(_pActiveRenderTarget, return ENull);
   FPd11RenderTarget* pRenderTarget = _pActiveRenderTarget->Convert<FPd11RenderTarget>();
   // �����ɫ
   FLOAT color[4];
   color[0] = red;
   color[1] = green;
   color[2] = blue;
   color[3] = alpha;
   _piContext->ClearRenderTargetView(pRenderTarget->NativeRenderTarget(), color);
   // ������
   if(pRenderTarget->OptionDepth()){
      _piContext->ClearDepthStencilView(pRenderTarget->NativeDepthStencil(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, depth, 0);
   }
   return ETrue;
}

//============================================================
// <T>���ñ������塣</T>
//
// @return ������
//============================================================
TResult FPd11RenderDevice::SetBackBuffer(TInt width, TInt height, TInt antiAlias, TBool depthed){
   return ESuccess;
}

//============================================================
// <T>�������ģʽ��</T>
//
// @param fillModeCd ���ģʽ
// @return ������
//============================================================
TResult FPd11RenderDevice::SetFillMode(ERenderFillMode fillModeCd){
   // ���״̬
   if(_fillModeCd == fillModeCd){
      return EContinue;
   }
   //D3D11_RASTERIZER_DESC description;
   //RType<D3D11_RASTERIZER_DESC>::Clear(&description);
   //description.FillMode = RDirectX11::ConvertFillMode(fillModeCd);
   //ID3D11RasterizerState* pRasterizerState = NULL;
   //_piDevice->CreateRasterizerState(&description, &pRasterizerState);
   //_piDevice->RSSetState(pRasterizerState);
//   // ��������
//#ifndef _MO_ANDROID
//   switch(fillModeCd){
//      case ERenderFillMode_Point:
//         glPolygonMode(GL_FRONT, GL_POINT);
//         glPolygonMode(GL_BACK, GL_POINT);
//         break;
//      case ERenderFillMode_Line:
//         glPolygonMode(GL_FRONT, GL_LINE);
//         glPolygonMode(GL_BACK, GL_LINE);
//         break;
//      case ERenderFillMode_Fill:
//         glPolygonMode(GL_FRONT, GL_FILL);
//         glPolygonMode(GL_BACK, GL_FILL);
//         break;
//   }
//#endif // _MO_ANDROID
//   _fillModeCd = fillModeCd;
//   _statistics->UpdateOptionFillCount();
   return ESuccess;
}

//============================================================
// <T>�������ģʽ��</T>
//
// @param depth ��ȿ���
// @param depthCd ���ģʽ
// @return ������
//============================================================
TResult FPd11RenderDevice::SetDepthMode(TBool depth, ERenderDepthMode depthCd){
   // ���״̬
   if((_optionDepth == depth) && (_depthModeCd == depthCd)){
      return EContinue;
   }
   //// ���ÿ���
   //if(_optionDepth != depth){
   //   if(depth){
   //      glEnable(GL_DEPTH_TEST);
   //   }else{
   //      glDisable(GL_DEPTH_TEST);
   //   }
   //   _optionDepth = depth;
   //   _statistics->UpdateOptionDeepCount();
   //}
   //// ��������
   //if(depth && _depthModeCd != depthCd){
   //   switch(depthCd){
   //      case ERenderDepthMode_Equal:
   //         glDepthFunc(GL_EQUAL);
   //         break;
   //      case ERenderDepthMode_NotEqual:
   //         glDepthFunc(GL_NOTEQUAL);
   //         break;
   //      case ERenderDepthMode_Less:
   //         glDepthFunc(GL_LESS);
   //         break;
   //      case ERenderDepthMode_LessEqual:
   //         glDepthFunc(GL_LEQUAL);
   //         break;
   //      case ERenderDepthMode_Greater:
   //         glDepthFunc(GL_GREATER);
   //         break;
   //      case ERenderDepthMode_GreaterEqual:
   //         glDepthFunc(GL_GEQUAL);
   //         break;
   //      case ERenderDepthMode_Always:
   //         glDepthFunc(GL_ALWAYS);
   //         break;
   //   }
   //   _depthModeCd = depthCd;
   //}
   return ESuccess;
}

//============================================================
// <T>���ü���ģʽ��</T>
//
// @param cull ���ÿ���
// @param cullCd ����ģʽ
// @return ������
//============================================================
TResult FPd11RenderDevice::SetCullingMode(TBool cull, ERenderCullMode cullCd){
   // ���״̬
   if((_optionCull == cull) && (_optionCull == cullCd)){
      return EContinue;
   }
   //// ���ÿ���
   //if(_optionCull != cull){
   //   if(cull){
   //      glEnable(GL_CULL_FACE);
   //   }else{
   //      glDisable(GL_CULL_FACE);
   //   }
   //   _optionCull = cull;
   //   _statistics->UpdateOptionCullCount();
   //}
   //// ��������
   //if(cull && _cullModeCd != cullCd){
   //   switch(cullCd){
   //      case ERenderCullMode_Front:
   //         glCullFace(GL_FRONT);
   //         break;
   //      case ERenderCullMode_Back:
   //         glCullFace(GL_BACK);
   //         break;
   //      case ERenderCullMode_Both:
   //         glCullFace(GL_FRONT_AND_BACK);
   //         break;
   //   }
   //   _cullModeCd = cullCd;
   //}
   return ESuccess;
}

//============================================================
// <T>���úϳɷ�ʽ��</T>
//============================================================
//GLenum ConvertBlendFactors(ERenderBlendMode value){
//   switch(value){
//      case ERenderBlendMode_SourceAlpha:
//         return GL_SRC_ALPHA;
//      case ERenderBlendMode_OneMinusSourceAlpha:
//         return GL_ONE_MINUS_SRC_ALPHA;
//      default:
//         break;
//   }
//   return 0;
//}

//============================================================
// <T>���úϳɷ�ʽ��</T>
//
// @param blend ��Ϸ�ʽ
// @param sourceCd ��Դ����
// @param targetCd Ŀ������
// @return ������
//============================================================
TResult FPd11RenderDevice::SetBlendFactors(TBool blend, ERenderBlendMode sourceCd, ERenderBlendMode targetCd){
   //// ���ÿ���
   //if(_statusBlend != blend){
   //   if(blend){
   //      glEnable(GL_BLEND);
   //   }else{
   //      glDisable(GL_BLEND);
   //   }
   //   _statusBlend = blend;
   //   _statistics->UpdateOptionBlendCount();
   //}
   //// ����Ч��
   //if(blend && ((_blendSourceCd != sourceCd) || (_blendTargetCd != targetCd))){
   //   GLenum source = ConvertBlendFactors(sourceCd);
   //   GLenum target = ConvertBlendFactors(targetCd);
   //   glBlendFunc(source, target);
   //   _blendSourceCd = sourceCd;
   //   _blendTargetCd = targetCd;
   //}
   return ETrue;
}

//============================================================
// <T>������Ч����</T>
//
// @param left ��λ��
// @param top ��λ��
// @param width ���
// @param height �߶�
// @return ������
//============================================================
TResult FPd11RenderDevice::SetScissorRectangle(TInt left, TInt top, TInt width, TInt height){
   D3D11_RECT rect;
   rect.left = left;
   rect.top = top;
   rect.right = left + width;
   rect.bottom = top + height;
   _piContext->RSSetScissorRects(1, &rect);
   return ETrue;
}

//============================================================
// <T>������ȾĿ�ꡣ</T>
//
// @param pRenderTarget ��ȾĿ��
// @return ������
//============================================================
TResult FPd11RenderDevice::SetRenderTarget(FRenderTarget* pRenderTarget){
   TResult result = ESuccess;
   //if(pRenderTarget == NULL){
   //   // �����ȾĿ��
   //   glBindFramebuffer(GL_FRAMEBUFFER, 0);
   //   result = CheckError("glBindFramebuffer", "Bind frame buffer. (buffer_id=%d)", 0);
   //   if(result != ESuccess){
   //      return result;
   //   }
   //   // �޸��ӽ�
   //   FScreenDevice* pScreenDevice = RDeviceManager::Instance().Find<FScreenDevice>();
   //   SIntSize2& screenSize = pScreenDevice->Size();
   //   glViewport(0, 0, screenSize.width, screenSize.height);
   //   return ESuccess;
   //}else{
   //   // ����ȾĿ��
   //   GLuint frameBufferId = pRenderTarget->RenderId().uint32;
   //   glBindFramebuffer(GL_FRAMEBUFFER, frameBufferId);
   //   result = CheckError("glBindFramebuffer", "Bind frame buffer. (buffer_id=%d)", frameBufferId);
   //   if(result != ESuccess){
   //      return result;
   //   }
   //   // �޸��ӽ�
   //   SIntSize2& size = pRenderTarget->Size();
   //   glViewport(0, 0, size.width, size.height);
   //   // �����ɫ
   //   SFloatColor4& backgroundColor = pRenderTarget->BackgroundColor();
   //   glClearColor(backgroundColor.red, backgroundColor.green, backgroundColor.blue, backgroundColor.alpha);
   //   //glClearDepth(1.0f);
   //   glClearStencil(0);
   //   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
   //}
   //_pActiveRenderTarget = pRenderTarget;
   return ESuccess;
}

//============================================================
// <T>���ó���</T>
//
// @param pProgram ����
// @return ������
//============================================================
TResult FPd11RenderDevice::SetProgram(FRenderProgram* pProgram){
   TResult resultCd = ESuccess;
   // ������
   if(_pProgram == pProgram){
      return EContinue;
   }
   // ���ó���
   if(pProgram != NULL){
      // ���ö���ű�
      FPd11RenderVertexShader* pVertexShader = pProgram->VertexShader()->Convert<FPd11RenderVertexShader>();
      ID3D11VertexShader* piVertexShader = pVertexShader->NativeShader();
      _piContext->VSSetShader(piVertexShader, NULL, 0);
      // �������ؽű�
      FPd11RenderFragmentShader* pFragmentShader = pProgram->VertexShader()->Convert<FPd11RenderFragmentShader>();
      ID3D11PixelShader* piFragmentShader = pFragmentShader->NativeShader();
      _piContext->PSSetShader(piFragmentShader, NULL, 0);
   }
   _pProgram = pProgram;
   // ����Ƿ����ִ��
   _statistics->UpdateProgramCount();
   return resultCd;
}

//============================================================
// <T>�󶨳������ݡ�</T>
//
// @parma shaderCd ��Ⱦ����
// @parma slot ���
// @parma pData ����
// @parma length ����
// @return ������
//============================================================
TResult FPd11RenderDevice::BindConstData(ERenderShader shaderCd, TInt slot, ERenderShaderParameterFormat formatCd, TAnyC* pData, TInt length){
   // �����
   TBool changed = UpdateConsts(shaderCd, slot, pData, length);
   if(!changed){
      return EContinue;
   }
   // �޸�����
   TResult result = ESuccess;
   //switch (formatCd){
   //   case ERenderShaderParameterFormat_Float1:{
   //      // ��鳤��
   //      if(length % 4 != 0){
   //         MO_ERROR("Length is invalid. (length=d)", length);
   //         return EFailure;
   //      }
   //      // �޸�����
   //      TInt count = length / 4;
   //      glUniform1fv(slot, count, (const GLfloat*)pData);
   //      // ������
   //      result = CheckError("glUniform1fv", "Bind const data failure. (shader_cd=%d, slot=%d, pData=0x%08X, length=%d)", shaderCd, slot, pData, length);
   //      break;
   //   }
   //   case ERenderShaderParameterFormat_Float2:{
   //      // ��鳤��
   //      if(length % 8 != 0){
   //         MO_ERROR("Length is invalid. (length=d)", length);
   //         return EFailure;
   //      }
   //      // �޸�����
   //      TInt count = length / 8;
   //      glUniform2fv(slot, count, (const GLfloat*)pData);
   //      // ������
   //      result = CheckError("glUniform2fv", "Bind const data failure. (shader_cd=%d, slot=%d, pData=0x%08X, length=%d)", shaderCd, slot, pData, length);
   //      break;
   //   }
   //   case ERenderShaderParameterFormat_Float3:{
   //      // ��鳤��
   //      if(length % 12 != 0){
   //         MO_ERROR("Length is invalid. (length=d)", length);
   //         return EFailure;
   //      }
   //      // �޸�����
   //      TInt count = length / 12;
   //      glUniform3fv(slot, count, (const GLfloat*)pData);
   //      // ������
   //      result = CheckError("glUniform3fv", "Bind const data failure. (shader_cd=%d, slot=%d, pData=0x%08X, length=%d)", shaderCd, slot, pData, length);
   //      break;
   //   }
   //   case ERenderShaderParameterFormat_Float4:{
   //      // ��鳤��
   //      if(length % 16 != 0){
   //         MO_ERROR("Length is invalid. (length=d)", length);
   //         return EFailure;
   //      }
   //      // �޸�����
   //      TInt count = length / 16;
   //      glUniform4fv(slot, count, (const GLfloat*)pData);
   //      // ������
   //      result = CheckError("glUniform4fv", "Bind const data failure. (shader_cd=%d, slot=%d, pData=0x%08X, length=%d)", shaderCd, slot, pData, length);
   //      break;
   //   }
   //   case ERenderShaderParameterFormat_Matrix3x3:{
   //      // ��鳤��
   //      if(length % 36 != 0){
   //         MO_ERROR("Length is invalid. (length=d)", length);
   //         return EFailure;
   //      }
   //      // �޸�����
   //      TInt count = length / 36;
   //      glUniformMatrix3fv(slot, count, GL_FALSE, (const GLfloat*)pData);
   //      // ������
   //      result = CheckError("glUniformMatrix4fv", "Bind const matrix3x3 failure. (shader_cd=%d, slot=%d, pData=0x%08X, length=%d)", shaderCd, slot, pData, length);
   //      break;
   //   }
   //   case ERenderShaderParameterFormat_Matrix4x3:{
   //      // ��鳤��
   //      if(length % 48 != 0){
   //         MO_ERROR("Length is invalid. (length=d)", length);
   //         return EFailure;
   //      }
   //      // �޸�����
   //      TInt count = length / 48;
   //      glUniform4fv(slot, count * 3, (const GLfloat*)pData);
   //      //glUniformMatrix4x3fv(slot, count, GL_FALSE, (const GLfloat*)pData);
   //      // ������
   //      result = CheckError("glUniformMatrix4x3fv", "Bind const matrix4x3 failure. (shader_cd=%d, slot=%d, pData=0x%08X, length=%d)", shaderCd, slot, pData, length);
   //      break;
   //   }
   //   case ERenderShaderParameterFormat_Matrix4x4:{
   //      // ��鳤��
   //      if(length % 64 != 0){
   //         MO_ERROR("Length is invalid. (length=d)", length);
   //         return EFailure;
   //      }
   //      // �޸�����
   //      TInt count = length >> 6;
   //      glUniformMatrix4fv(slot, count, GL_FALSE, (const GLfloat*)pData);
   //      // ������
   //      result = CheckError("glUniformMatrix4fv", "Bind const matrix4x4 failure. (shader_cd=%d, slot=%d, pData=0x%08X, length=%d)", shaderCd, slot, pData, length);
   //      break;
   //   }
   //}
   //// MO_INFO("Bind const buffer. (slot=%d, format_cd=%d, length=%d)", slot, formatCd, length);
   //_statistics->UpdateProgramCount(length);
   return ESuccess;
}

//============================================================
// <T>�󶨳�����ά��������</T>
//
// @parma shaderCd ��Ⱦ����
// @parma slot ���
// @parma x X����
// @parma y Y����
// @parma z Z����
// @parma w W����
// @return ������
//============================================================
TResult FPd11RenderDevice::BindConstFloat3(ERenderShader shaderCd, TInt slot, TFloat x, TFloat y, TFloat z){
   //// �����
   //TFloat data[3] = {x, y, z};
   //TInt length = sizeof(TFloat) * 3;
   //TBool changed = UpdateConsts(shaderCd, slot, data, length);
   //if(!changed){
   //   return EContinue;
   //}
   //// �޸�����
   //glUniform3fv(slot, 1, (const GLfloat*)data);
   //// ������
   //TResult result = CheckError("glUniform3fv", "Bind const float3 failure. (shader_cd=%d, slot=%d, value=%f,%f,%f)", shaderCd, slot, x, y, z);
   //_statistics->UpdateProgramCount(sizeof(data));
   //return result;
   return ESuccess;
}

//============================================================
// <T>�󶨳�����ά��������</T>
//
// @parma shaderCd ��Ⱦ����
// @parma slot ���
// @parma x X����
// @parma y Y����
// @parma z Z����
// @parma w W����
// @return ������
//============================================================
TResult FPd11RenderDevice::BindConstFloat4(ERenderShader shaderCd, TInt slot, TFloat x, TFloat y, TFloat z, TFloat w){
   //// �����
   //TFloat data[4] = {x, y, z, w};
   //TInt length = sizeof(TFloat) * 4;
   //TBool changed = UpdateConsts(shaderCd, slot, data, length);
   //if(!changed){
   //   return EContinue;
   //}
   //// �޸�����
   //glUniform4fv(slot, 1, (const GLfloat*)data);
   //// ������
   //TResult result = CheckError("glUniform4fv", "Bind const float4 failure. (shader_cd=%d, slot=%d, value=%f,%f,%f,%f)", shaderCd, slot, x, y, z, w);
   //_statistics->UpdateProgramCount(sizeof(data));
   //return result;
   return ESuccess;
}

//============================================================
// <T>�󶨳�����ά����</T>
//
// @parma shaderCd ��Ⱦ����
// @parma slot ���
// @parma matrix ����
// @return ������
//============================================================
TResult FPd11RenderDevice::BindConstMatrix3x3(ERenderShader shaderCd, TInt slot, const SFloatMatrix3d& matrix){
   // �����
   //TAnyC* pMemory = matrix.MemoryC();
   //TInt length = sizeof(TFloat) * 9;
   //TBool changed = UpdateConsts(shaderCd, slot, pMemory, length);
   //if(!changed){
   //   return EContinue;
   //}
   //// ת�þ���
   //GLfloat data[3][3];
   //data[0][0] = matrix.data[0][0];
   //data[0][1] = matrix.data[1][0];
   //data[0][2] = matrix.data[2][0];
   //data[1][0] = matrix.data[0][1];
   //data[1][1] = matrix.data[1][1];
   //data[1][2] = matrix.data[2][1];
   //data[2][0] = matrix.data[0][2];
   //data[2][1] = matrix.data[1][2];
   //data[2][2] = matrix.data[2][2];
   //glUniformMatrix3fv(slot, 1, GL_FALSE, (const GLfloat*)data);
   //// ������
   //TResult result = CheckError("glUniformMatrix3fv", "Bind const matrix3x3 failure. (shader_cd=%d, slot=%d)", shaderCd, slot);
   //_statistics->UpdateProgramCount(length);
   //return result;
   return ESuccess;
}

//============================================================
// <T>�󶨳�����ά����</T>
//
// @parma shaderCd ��Ⱦ����
// @parma slot ���
// @parma matrix ����
// @return ������
//============================================================
TResult FPd11RenderDevice::BindConstMatrix4x4(ERenderShader shaderCd, TInt slot, const SFloatMatrix3d& matrix){
   // �����
   TAnyC* pMemory = matrix.MemoryC();
   TInt length = sizeof(TFloat) * 16;
   TBool changed = UpdateConsts(shaderCd, slot, pMemory, length);
   if(!changed){
      return EContinue;
   }
//   // �޸�����
//#ifdef _MO_ANDROID
//   // ת�þ���
//   GLfloat data[4][4];
//   data[0][0] = matrix.data[0][0];
//   data[0][1] = matrix.data[1][0];
//   data[0][2] = matrix.data[2][0];
//   data[0][3] = matrix.data[3][0];
//   data[1][0] = matrix.data[0][1];
//   data[1][1] = matrix.data[1][1];
//   data[1][2] = matrix.data[2][1];
//   data[1][3] = matrix.data[3][1];
//   data[2][0] = matrix.data[0][2];
//   data[2][1] = matrix.data[1][2];
//   data[2][2] = matrix.data[2][2];
//   data[2][3] = matrix.data[3][2];
//   data[3][0] = matrix.data[0][3];
//   data[3][1] = matrix.data[1][3];
//   data[3][2] = matrix.data[2][3];
//   data[3][3] = matrix.data[3][3];
//   glUniformMatrix4fv(slot, 1, GL_FALSE, (const GLfloat*)data);
//#else
//   glUniformMatrix4fv(slot, 1, GL_TRUE, (const GLfloat*)pMemory);
//#endif // _MO_ANDROID
//   // ������
//   TResult result = CheckError("glUniformMatrix4fv", "Bind const matrix4x4 failure. (shader_cd=%d, slot=%d)", shaderCd, slot);
//   _statistics->UpdateProgramCount(length);
//   return result;
   return ESuccess;
}

//============================================================
// <T>�󶨶��㻺�塣</T>
//
// @param slot ���
// @param pVertexBuffer ���㻺��
// @param offset ƫ��λ��
// @param formatCd ��ʽ
// @return ������
//============================================================
TResult FPd11RenderDevice::BindVertexBuffer(TInt slot, FRenderVertexBuffer* pVertexBuffer, TInt offset, ERenderVertexFormat formatCd){
   MO_ERROR_CHECK(slot >= 0, return EFailure, "Slot value is invalid. (slot=%d)", slot);
   // ��ö�����
   TResult result = ESuccess;
   FPd11RenderVertexBuffer* pBuffer = pVertexBuffer->Convert<FPd11RenderVertexBuffer>();
   ////............................................................
   //// �趨������
   //GLuint bufferId = 0;
   //if(pBuffer != NULL){
   //   bufferId = pBuffer->BufferId();
   //}
   //glBindBuffer(GL_ARRAY_BUFFER, bufferId);
   //result = CheckError("glBindBuffer", "Bind buffer. (buffer_id=%d)", bufferId);
   //if(result != ESuccess){
   //   return result;
   //}
   ////............................................................
   //// �������
   //if(pBuffer != NULL){
   //   glEnableVertexAttribArray(slot);
   //   result = CheckError("glEnableVertexAttribArray", "Enable vertex attribute array. (slot=%d)", slot);
   //   if(result != ESuccess){
   //      return result;
   //   }
   //}else{
   //   glDisableVertexAttribArray(slot);
   //   result = CheckError("glDisableVertexAttribArray", "Disable vertex attribute array. (slot=%d)", slot);
   //   return result;
   //}
   ////............................................................
   //// ���ö�����
   //TInt stride = pVertexBuffer->Stride();
   //switch(formatCd){
   //   case ERenderVertexFormat_Byte4:
   //      glVertexAttribPointer(slot, 4, GL_UNSIGNED_BYTE, GL_FALSE, stride, (const GLvoid*)offset);
   //      break;
   //   case ERenderVertexFormat_ByteNormal4:
   //      glVertexAttribPointer(slot, 4, GL_UNSIGNED_BYTE, GL_TRUE, stride, (const GLvoid*)offset);
   //      break;
   //   case ERenderVertexFormat_Float1:
   //      glVertexAttribPointer(slot, 1, GL_FLOAT, GL_FALSE, stride, (const GLvoid*)offset);
   //      break;
   //   case ERenderVertexFormat_Float2:
   //      glVertexAttribPointer(slot, 2, GL_FLOAT, GL_FALSE, stride, (const GLvoid*)offset);
   //      break;
   //   case ERenderVertexFormat_Float3:
   //      glVertexAttribPointer(slot, 3, GL_FLOAT, GL_FALSE, stride, (const GLvoid*)offset);
   //      break;
   //   case ERenderVertexFormat_Float4:
   //      glVertexAttribPointer(slot, 4, GL_FLOAT, GL_FALSE, stride, (const GLvoid*)offset);
   //      break;
   //   default:
   //      MO_FATAL("Unknown vertex format. (format_cd=%d)", formatCd);
   //      break;
   //}
   //// ������
   //result = CheckError("glVertexAttribPointer", "Bind vertex attribute pointer. (slot=%d, format_cd=%d)", slot, formatCd);
   //_statistics->UpdateVertexBufferCount();
   //// MO_INFO("Bind vertex buffer. (slot=%d, offset=%d, format_cd=%d, stride=%d, buffer_id=%d, count=%d, length=%d)", slot, offset, formatCd, stride, bufferId, pVertexBuffer->Count(), pVertexBuffer->DataLength());
   return result;
}

//============================================================
// <T>������</T>
//
// @param slot ���
// @param pTexture ����
// @return ������
//============================================================
TResult FPd11RenderDevice::BindTexture(TInt slot, FRenderTexture* pTexture){
   TResult result = ESuccess;
   ////............................................................
   //// ��������
   //if(pTexture == NULL){
   //   glBindTexture(GL_TEXTURE_2D, 0);
   //   result = CheckError("glBindTexture", "Bind texture clear failure. (slot=%d)", slot);
   //   return result;
   //}
   ////............................................................
   //// ��������
   //if(_renderTextureActiveSlot != slot){
   //   TInt index = pTexture->Index();
   //   glUniform1i(slot, index);
   //   glActiveTexture(GL_TEXTURE0 + index);
   //   result = CheckError("glActiveTexture", "Active texture failure. (slot=%d, index=%d)", slot, index);
   //   if(result != ESuccess){
   //      return result;
   //   }
   //   _renderTextureActiveSlot = slot;
   //}
   ////............................................................
   //// ������
   //ERenderTexture textureCd = pTexture->TextureCd();
   //switch (textureCd){
   //   case ERenderTexture_Flat2d:{
   //      FPd11RenderFlatTexture* pFlatTexture = (FPd11RenderFlatTexture*)pTexture;
   //      GLuint textureId = pFlatTexture->TextureId();
   //      glBindTexture(GL_TEXTURE_2D, textureId);
   //      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
   //      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
   //      result = CheckError("glBindTexture", "Bind texture failure. (texture_id=%d)", textureId);
   //      if(result != ESuccess){
   //         return result;
   //      }
   //      break;
   //   }
   //   case ERenderTexture_Cube:{
   //      FPd11RenderCubeTexture* pCubeTexture = (FPd11RenderCubeTexture*)pTexture;
   //      GLuint textureId = pCubeTexture->TextureId();
   //      glBindTexture(GL_TEXTURE_CUBE_MAP, textureId);
   //      result = CheckError("glBindTexture", "Bind texture failure. (texture_id=%d)", textureId);
   //      if(result != ESuccess){
   //         return result;
   //      }
   //      break;
   //   }
   //   default:{
   //      MO_FATAL("Unknown texture type.");
   //      break;
   //   }
   //}
   ////............................................................
   //// ͳ������
   //_statistics->UpdateSamplerCount();
   return result;
}

//============================================================
// <T>���������Ρ�</T>
//
// @param pIndexBuffer ��������
// @param offset ��ʼλ��
// @param count ��������
// @return ������
//============================================================
TResult FPd11RenderDevice::DrawTriangles(FRenderIndexBuffer* pIndexBuffer, TInt offset, TInt count){
   MO_CHECK(pIndexBuffer, return ENull);
   MO_CHECK(offset >= 0, return EOutRange);
   MO_CHECK(count > 0, return EOutRange);
   // ���������
   TResult resultCd = ESuccess;
   FPd11RenderIndexBuffer* pBuffer = pIndexBuffer->Convert<FPd11RenderIndexBuffer>();
   // ����������
   ID3D11Buffer* piBuffer = pBuffer->NativeBuffer();
   if(piBuffer == NULL){
      MO_FATAL("Index buffer is null.");
      return ENull;
   }
   DXGI_FORMAT strideCd = RDirectX11::ConvertIndexStride(pIndexBuffer->StrideCd());
   _piContext->IASetIndexBuffer(piBuffer, strideCd, offset);
   // ����������
   _renderDrawStatistics->Begin();
   _piContext->DrawIndexed(count, offset, 0);
   _renderDrawStatistics->Finish();
   // ������
   _statistics->UpdateDraw(count);
   return resultCd;
}

//============================================================
// <T>��ʾ���档</T>
//
// @return ������
//============================================================
TResult FPd11RenderDevice::Present(){
   _piSwapChain->Present(0, DXGI_PRESENT_TEST);
   return ESuccess;
}

MO_NAMESPACE_END
