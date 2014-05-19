#include "MoPd9Render.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FPd9RenderDevice, FPdxRenderDevice);

//============================================================
// <T>������̨����</T>
//============================================================
FPd9RenderDevice::FPd9RenderDevice(){
   // ��ʼ����������
   _pCapability = MO_CREATE(FRenderCapability);
   _pCapability->SetCode("directx9");
   // ��ʼ����������
   //_optionTexture = EFalse;
   //_textureLimit = 0;
   // ��ʼ����������
   //_pLinkFlatTextures = MO_CREATE(FRenderFlatTextureList);
   //_pLinkCubeTextures = MO_CREATE(FRenderCubeTextureList);
   // ��ʼ���ӿ�ָ��
   MO_CLEAR(_piDirect3d);
   MO_CLEAR(_piDevice);
   // ע���༯��
   _pClassFactory->Register(MO_RENDEROBJECT_SHADERBUFFER,    FPd9RenderShaderBuffer::Class());
   _pClassFactory->Register(MO_RENDEROBJECT_SHADERATTRIBUTE, FRenderAttribute::Class());
   _pClassFactory->Register(MO_RENDEROBJECT_SHADERPARAMETER, FPd9RenderShaderParameter::Class());
   _pClassFactory->Register(MO_RENDEROBJECT_SHADERSAMPLER,   FRenderSampler::Class());
   _pClassFactory->Register(MO_RENDEROBJECT_LAYOUT,          FPd9RenderLayout::Class());
   _inDrawing = EFalse;
}

//============================================================
// <T>������̨����</T>
//============================================================
FPd9RenderDevice::~FPd9RenderDevice(){
   //// ɾ����������
   //MO_DELETE(_pLinkFlatTextures);
   //MO_DELETE(_pLinkCubeTextures);
   // �ͷ��ڴ�
   MO_RELEASE(_piDevice);
   MO_RELEASE(_piDirect3d);
   /// ɾ������
   MO_DELETE(_pCapability);
}

//============================================================
// <T>���»�����</T>
//============================================================
TBool FPd9RenderDevice::UpdateContext(){
   TBool result = EFalse;
   // ���ü���ĳ���
   if(_pActiveProgram != _pProgram){
      //FPd9RenderProgram* pProgrom = (FPd9RenderProgram*)_pProgram;
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
TResult FPd9RenderDevice::Setup(){
   // �����ô���
   TResult result = FRenderDevice::Setup();
   //............................................................
   RECT rect;
   GetClientRect(_windowHandle, &rect);
   TInt width = rect.right - rect.left;
   TInt height = rect.bottom - rect.top;
   //............................................................
   // ��������
   _piDirect3d = Direct3DCreate9(D3D_SDK_VERSION);
   if(_piDirect3d == NULL){
      MO_FATAL("Create direct3d 9 failure.");
      return EFailure;
   }
   // �����豸
   D3DPRESENT_PARAMETERS deviceDescriptor = {0};
   deviceDescriptor.Windowed = TRUE;
   deviceDescriptor.SwapEffect = D3DSWAPEFFECT_DISCARD;
   deviceDescriptor.BackBufferFormat = D3DFMT_UNKNOWN;
   deviceDescriptor.EnableAutoDepthStencil = TRUE;
   deviceDescriptor.AutoDepthStencilFormat = D3DFMT_D16;
   HRESULT dxResult = _piDirect3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, _windowHandle, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &deviceDescriptor, &_piDevice);
   if(FAILED(dxResult)){
      MO_FATAL("Create device failure.");
      return EFailure;
   }
   // ����״̬
   _piDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
   _piDevice->SetRenderState(D3DRS_LIGHTING, EFalse);
   _piDevice->SetRenderState(D3DRS_ZENABLE, ETrue);
   //............................................................
   // ������Ⱦ�汾
   TCharC* pVertexShaderProfile = D3DXGetVertexShaderProfile(_piDevice);
   _pCapability->SetShaderVertexVersion(pVertexShaderProfile);
   TCharC* pPixelShaderProfile = D3DXGetPixelShaderProfile(_piDevice);
   _pCapability->SetShaderFragmentVersion(pPixelShaderProfile);
   //............................................................
   // �����ӽ�
   D3DVIEWPORT9 viewport = {0};
   viewport.Width = width;
   viewport.Height = height;
   viewport.MinZ = 0.0f;
   viewport.MaxZ = 1.0f;
   dxResult = _piDevice->SetViewport(&viewport);
   if(FAILED(dxResult)){
      MO_FATAL("Create device failure.");
      return EFailure;
   }
   return ESuccess;
}

//============================================================
// <T>��ͣ����</T>
//
// @return ������
//============================================================
TResult FPd9RenderDevice::Suspend(){
   // ��ͣ����
   FRenderDevice::Suspend();
   return ESuccess;
}

//============================================================
// <T>��������</T>
//
// @return ������
//============================================================
TResult FPd9RenderDevice::Resume(){
   FRenderDevice::Resume();
   return ESuccess;
}

//============================================================
// <T>���ִ�д���</T>
//
// @param pCode ����
// @return ������
//============================================================
TResult FPd9RenderDevice::CheckError(HRESULT dxResult, TCharC* pCode, TCharC* pMessage, ...){
   // ��ô���ԭ��
   TResult resultCd = ESuccess;
   if(FAILED(dxResult)){
      // �������
      TCharC* pDescription = DXGetErrorDescription(dxResult);
      // ������Ϣ
      TFsText message;
      va_list params;
      va_start(params, pMessage);
      message.AppendFormatParameters(pMessage, params);
      va_end(params);
      MO_FATAL("Call method failure. (method=%s, message=%s, error=%s)", pCode, (TCharC*)message, pDescription);
   }
   return resultCd;
}

//============================================================
// <T>�������㻺�塣</T>
//
// @param pClass �����
// @return ���㻺��
//============================================================
FRenderVertexBuffer* FPd9RenderDevice::CreateVertexBuffer(FClass* pClass){
   FRenderVertexBuffer* pVertexBuffer = FPd9RenderVertexBuffer::InstanceCreate();
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
FRenderIndexBuffer* FPd9RenderDevice::CreateIndexBuffer(FClass* pClass){
   FRenderIndexBuffer* pIndexBuffer = FPd9RenderIndexBuffer::InstanceCreate();
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
FRenderProgram* FPd9RenderDevice::CreateProgrom(FClass* pClass){
   FPd9RenderProgram* pProgram = FPd9RenderProgram::InstanceCreate();
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
FRenderTarget* FPd9RenderDevice::CreateRenderTarget(FClass* pClass){
   FPd9RenderTarget* pRenderTarget = FPd9RenderTarget::InstanceCreate();
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
FRenderFlatTexture* FPd9RenderDevice::CreateFlatTexture(FClass* pClass){
   FPd9RenderFlatTexture* pTexture = FPd9RenderFlatTexture::InstanceCreate();
   pTexture->SetDevice(this);
   _storageTextures.Push(pTexture);
   //_pLinkFlatTextures->Push(pTexture);
   return pTexture;
}

//============================================================
// <T>�����ռ�����</T>
//
// @param pClass �����
// @return ����
//============================================================
FRenderCubeTexture* FPd9RenderDevice::CreateCubeTexture(FClass* pClass){
   FPd9RenderCubeTexture* pTexture = FPd9RenderCubeTexture::InstanceCreate();
   pTexture->SetDevice(this);
   _storageTextures.Push(pTexture);
   //_pLinkCubeTextures->Push(pTexture);
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
TResult FPd9RenderDevice::Clear(TFloat red, TFloat green, TFloat blue, TFloat alpha, TFloat depth){
   TInt r = (TInt)(red * 255.0f);
   TInt g = (TInt)(green * 255.0f);
   TInt b = (TInt)(blue * 255.0f);
   TInt a = (TInt)(alpha * 255.0f);
   D3DCOLOR color = D3DCOLOR_ARGB(a, r, g, b);
   _piDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, color, depth, 0);
   return ETrue;
}

//============================================================
// <T>���ñ������塣</T>
//
// @return ������
//============================================================
TResult FPd9RenderDevice::SetBackBuffer(TInt width, TInt height, TInt antiAlias, TBool depthed){
   return ESuccess;
}

//============================================================
// <T>�������ģʽ��</T>
//
// @param fillModeCd ���ģʽ
// @return ������
//============================================================
TResult FPd9RenderDevice::SetFillMode(ERenderFillMode fillModeCd){
   // ���״̬
   if(_fillModeCd == fillModeCd){
      return EContinue;
   }
   //D3D9_RASTERIZER_DESC description;
   //RType<D3D9_RASTERIZER_DESC>::Clear(&description);
   //description.FillMode = RDirectX9::ConvertFillMode(fillModeCd);
   //ID3D9RasterizerState* pRasterizerState = NULL;
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
TResult FPd9RenderDevice::SetDepthMode(TBool depth, ERenderDepthMode depthCd){
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
TResult FPd9RenderDevice::SetCullingMode(TBool cull, ERenderCullMode cullCd){
   // ���״̬
   if((_optionCull == cull) && (_optionCull == cullCd)){
      return EContinue;
   }
   //RDirectX9::ConvertCullMode(cullCd);
   //if(_piRasterizerState == NULL){
   //   D3D9_RASTERIZER_DESC descriptor;
   //   RType<D3D9_RASTERIZER_DESC>::Clear(&descriptor);
   //   descriptor.FillMode = D3D9_FILL_SOLID;
   //   descriptor.CullMode = D3D9_CULL_NONE;
   //   HRESULT dxResult = _piDevice->CreateRasterizerState(&descriptor, &_piRasterizerState);
   //   if(FAILED(dxResult)){
   //      MO_FATAL("Create rasterizer state failure.");
   //      return EFailure;
   //   }
   //}
   //_piDevice->RSSetState(_piRasterizerState);
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
//
// @param blend ��Ϸ�ʽ
// @param sourceCd ��Դ����
// @param targetCd Ŀ������
// @return ������
//============================================================
TResult FPd9RenderDevice::SetBlendFactors(TBool blend, ERenderBlendMode sourceCd, ERenderBlendMode targetCd){
   TFloat blendFactors[4] = {0};
   if(blend == ETrue){
      //_piDevice->OMSetBlendState(_piBlendEnableState, blendFactors, 0XFFFFFFFF);
   }else{
      //_piDevice->OMSetBlendState(_piBlendDisableState, blendFactors, 0XFFFFFFFF);
   }
   //_piDevice->OMSetBlendState(_piBlendEnableState, blendFactors, 0XFFFFFFFF);
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
TResult FPd9RenderDevice::SetScissorRectangle(TInt left, TInt top, TInt width, TInt height){
   RECT rect;
   rect.left = left;
   rect.top = top;
   rect.right = left + width;
   rect.bottom = top + height;
   _piDevice->SetScissorRect(&rect);
   return ETrue;
}

//============================================================
// <T>������ȾĿ�ꡣ</T>
//
// @param pRenderTarget ��ȾĿ��
// @return ������
//============================================================
TResult FPd9RenderDevice::SetRenderTarget(FRenderTarget* pRenderTarget){
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
TResult FPd9RenderDevice::SetProgram(FRenderProgram* pProgram){
   TResult resultCd = ESuccess;
   // ������
   //if(_pProgram == pProgram){
   //   return EContinue;
   //}
   // ���ó���
   if(pProgram != NULL){
      // ���ö���ű�
      FPd9RenderVertexShader* pVertexShader = pProgram->VertexShader()->Convert<FPd9RenderVertexShader>();
      IDirect3DVertexShader9* piVertexShader = pVertexShader->NativeShader();
      HRESULT dxResult = _piDevice->SetVertexShader(piVertexShader);
      if(FAILED(dxResult)){
         MO_FATAL("Set vertex shader failure.");
         return EFailure;
      }
      //MO_DEBUG("Set vertex shader. (shader=0x%08X)", piVertexShader);
      // �������ؽű�
      FPd9RenderFragmentShader* pFragmentShader = pProgram->FragmentShader()->Convert<FPd9RenderFragmentShader>();
      IDirect3DPixelShader9* piFragmentShader = pFragmentShader->NativeShader();
      dxResult = _piDevice->SetPixelShader(piFragmentShader);
      if(FAILED(dxResult)){
         MO_FATAL("Set pixel shader failure.");
         return EFailure;
      }
      //MO_DEBUG("Set pixel shader. (shader=0x%08X)", piFragmentShader);
   }
   _pProgram = pProgram;
   // ����Ƿ����ִ��
   _statistics->UpdateProgramCount();
   return resultCd;
}

//============================================================
// <T>���ò��֡�</T>
//
// @parma pLayout ����
// @return ������
//============================================================
TResult FPd9RenderDevice::SetLayout(FRenderLayout* pLayout){
   MO_CHECK(pLayout, return ENull);
   // ��ö�����
   TResult result = ESuccess;
   FPd9RenderLayout* pRenderLayout = pLayout->Convert<FPd9RenderLayout>();
   IDirect3DVertexBuffer9** piBuffers = pRenderLayout->Buffer();
   UINT* bufferStride = pRenderLayout->Stride();
   UINT* bufferOffset = pRenderLayout->Offset();
   // �����Ϣ
   TInt index = 0;
   TInt count = pRenderLayout->Count();
   for(TInt n = 0; n < count; n++){
      IDirect3DVertexBuffer9* piBuffer = piBuffers[n];
      if(piBuffer != NULL){
         HRESULT dxResult = _piDevice->SetStreamSource(index++, piBuffer, bufferOffset[n], bufferStride[n]);
         if(FAILED(dxResult)){
            MO_FATAL("Set stream source failure. (buffer=0x%08X)", piBuffer);
            return EFailure;
         }

      }
   }
   // ���ø�ʽ
   IDirect3DVertexDeclaration9* piDeclaration = pRenderLayout->NativeDeclaration();
   HRESULT dxResult = _piDevice->SetVertexDeclaration(piDeclaration);
   //TInt fvf = pRenderLayout->FormatCd();
   //HRESULT dxResult = _piDevice->SetFVF(fvf);
   if(FAILED(dxResult)){
      TCharC* pMessage = DXGetErrorDescription(dxResult);
      MO_FATAL("Draw indexed primitive failure. (error=%s)", pMessage);
      return EFailure;
   }
   _pLayout = (FPd9RenderLayout*)pLayout;
   //MO_DEBUG("Set vertex buffers. (slot=%d, count=%d)", 0, count);
   return ESuccess;
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
TResult FPd9RenderDevice::BindConstData(ERenderShader shaderCd, TInt slot, ERenderParameterFormat formatCd, TAnyC* pData, TInt length){
   // �����
   TBool changed = UpdateConsts(shaderCd, slot, pData, length);
   if(!changed){
      return EContinue;
   }
   // �޸�����
   TResult result = ESuccess;
   //switch (formatCd){
   //   case ERenderParameterFormat_Float1:{
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
   //   case ERenderParameterFormat_Float2:{
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
   //   case ERenderParameterFormat_Float3:{
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
   //   case ERenderParameterFormat_Float4:{
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
   //   case ERenderParameterFormat_Matrix3x3:{
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
   //   case ERenderParameterFormat_Matrix4x3:{
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
   //   case ERenderParameterFormat_Matrix4x4:{
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
TResult FPd9RenderDevice::BindConstFloat3(ERenderShader shaderCd, TInt slot, TFloat x, TFloat y, TFloat z){
   MO_FATAL_UNSUPPORT();
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
TResult FPd9RenderDevice::BindConstFloat4(ERenderShader shaderCd, TInt slot, TFloat x, TFloat y, TFloat z, TFloat w){
   MO_FATAL_UNSUPPORT();
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
TResult FPd9RenderDevice::BindConstMatrix3x3(ERenderShader shaderCd, TInt slot, const SFloatMatrix3d& matrix){
   MO_FATAL_UNSUPPORT();
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
TResult FPd9RenderDevice::BindConstMatrix4x4(ERenderShader shaderCd, TInt slot, const SFloatMatrix3d& matrix){
   MO_FATAL_UNSUPPORT();
   return ESuccess;
}

//============================================================
// <T>����Ⱦ���塣</T>
//
// @param pBuffer ��Ⱦ����
// @return ������
//============================================================
TResult FPd9RenderDevice::BindShaderBuffer(FRenderShaderBuffer* pBuffer){
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
TResult FPd9RenderDevice::BindVertexBuffer(TInt slot, FRenderVertexBuffer* pVertexBuffer, TInt offset, ERenderAttributeFormat formatCd){
   MO_ERROR_CHECK(slot >= 0, return EFailure, "Slot value is invalid. (slot=%d)", slot);
   // ��ö�����
   TResult result = ESuccess;
   FPd9RenderVertexBuffer* pBuffer = pVertexBuffer->Convert<FPd9RenderVertexBuffer>();
   //// �����Ϣ
   //ID3D9Buffer* piBuffer = pBuffer->NativeBuffer();
   //UINT bufferStride = pVertexBuffer->Stride();
   //UINT bufferOffset = offset;
   //// ��������
   //_piDevice->IASetVertexBuffers(slot, 1, &piBuffer, &bufferStride, &bufferOffset);
   //MO_DEBUG("Set vertex buffer. (slot=%d, buffer=0x%08X, stride=%d, offset=%d)", slot, piBuffer, bufferStride, bufferOffset);
   return result;
}

//============================================================
// <T>������</T>
//
// @param slot ���
// @param pTexture ����
// @return ������
//============================================================
TResult FPd9RenderDevice::BindTexture(TInt slot, FRenderTexture* pTexture){
   TResult result = ESuccess;
   //............................................................
   // ������
   ERenderTexture textureCd = pTexture->TextureCd();
   switch(textureCd){
      case ERenderTexture_Flat2d:{
         FPd9RenderFlatTexture* pFlatTexture = (FPd9RenderFlatTexture*)pTexture;
         IDirect3DTexture9* piTexture = pFlatTexture->NativeTexture();
         HRESULT dxResult = _piDevice->SetTexture(slot, piTexture);
         if(FAILED(dxResult)){
            MO_FATAL("Set texture failure. (texture=0x%08X)", piTexture);
            return EFailure;
         }
         //MO_DEBUG("Set texture 2d. (slot=%d, texture=0x%08X)", slot, pTexture);
         break;
      }
      case ERenderTexture_Cube:{
         FPd9RenderCubeTexture* pCubeTexture = (FPd9RenderCubeTexture*)pTexture;
         IDirect3DCubeTexture9* piTexture = pCubeTexture->NativeTexture();
         HRESULT dxResult = _piDevice->SetTexture(slot, piTexture);
         if(FAILED(dxResult)){
            MO_FATAL("Set texture failure. (texture=0x%08X)", piTexture);
            return EFailure;
         }
         //MO_DEBUG("Set texture cube. (slot=%d, texture=0x%08X)", slot, pTexture);
         break;
      }
      default:{
         MO_FATAL("Unknown texture type.");
         break;
      }
   }
   //............................................................
   // ͳ������
   _statistics->UpdateSamplerCount();
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
TResult FPd9RenderDevice::DrawTriangles(FRenderIndexBuffer* pIndexBuffer, TInt offset, TInt count){
   MO_CHECK(pIndexBuffer, return ENull);
   MO_CHECK(offset >= 0, return EOutRange);
   MO_CHECK(count > 0, return EOutRange);
   TResult resultCd = ESuccess;
   // ������ƿ�ʼ
   _pProgram->DrawBegin();
   // ����������
   FPd9RenderIndexBuffer* pBuffer = pIndexBuffer->Convert<FPd9RenderIndexBuffer>();
   IDirect3DIndexBuffer9* piIndices = pBuffer->NativeBuffer();
   MO_CHECK(piIndices, return ENull);
   HRESULT dxResult = _piDevice->SetIndices(piIndices);
   if(FAILED(dxResult)){
      return CheckError(dxResult, "SetIndices", "Set indices failure. (indices=0x%08X)", piIndices);
   }
   // ����������
   _renderDrawStatistics->Begin();
   TInt total = _pLayout->Total();
   dxResult = _piDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, total, offset, count / 3);
   if(FAILED(dxResult)){
      return CheckError(dxResult, "DrawIndexedPrimitive", "Draw indexed primitive failure. (offset=%d, count=%d)", offset, count);
   }
   //MO_DEBUG("Draw indexed. (offset=%d, count=%d)", offset, count);
   _renderDrawStatistics->Finish();
   // ������ƽ���
   _pProgram->DrawEnd();
   // ������
   _statistics->UpdateDraw(count);
   return resultCd;
}

//============================================================
// <T>��ʾ���档</T>
//
// @return ������
//============================================================
TResult FPd9RenderDevice::Present(){
   HRESULT dxResult = _piDevice->Present(NULL, NULL, NULL, NULL);
   if(FAILED(dxResult)){
      return CheckError(dxResult, "Present", "Present.");
   }
   return ESuccess;
}

//============================================================
// <T>����֡��ʼ����</T>
//
// @return ������
//============================================================
TResult FPd9RenderDevice::FrameBegin(){
   TResult resultCd = FRenderDevice::FrameBegin();
   //if(!_inDrawing){
      HRESULT dxResult = _piDevice->BeginScene();
      if(FAILED(dxResult)){
         MO_FATAL("Begin scene.");
         return EFailure;
      }
      _inDrawing = ETrue;
   //}
   return resultCd;
}

//============================================================
// <T>����֡��������</T>
//
// @return ������
//============================================================
TResult FPd9RenderDevice::FrameEnd(){
   TResult resultCd = FRenderDevice::FrameEnd();
   //if(_inDrawing){
      HRESULT dxResult = _piDevice->EndScene();
      if(FAILED(dxResult)){
         MO_FATAL("End scene.");
         return EFailure;
      }
      _inDrawing = EFalse;
   //}
   return resultCd;
}

MO_NAMESPACE_END
