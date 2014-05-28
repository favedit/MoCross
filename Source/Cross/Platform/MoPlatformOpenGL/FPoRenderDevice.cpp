#include "MoPoRender.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FPoRenderDevice, FRenderDevice);

//============================================================
// <T>������̨����</T>
//============================================================
FPoRenderDevice::FPoRenderDevice(){
   _pCapability = MO_CREATE(FRenderCapability);
   // ��ʼ����������
   _optionTexture = EFalse;
   _renderTextureActiveSlot = -1;
   _textureLimit = 0;
   // ��ʼ����������
   _pLinkFlatTextures = MO_CREATE(FRenderFlatTextureList);
   _pLinkCubeTextures = MO_CREATE(FRenderCubeTextureList);
   // ע���༯��
   _pClassFactory->Register(MO_RENDEROBJECT_LAYOUT,            FPoRenderLayout::Class());
   _pClassFactory->Register(MO_RENDEROBJECT_PROGRAM_BUFFER,    FRenderProgramBuffer::Class());
   _pClassFactory->Register(MO_RENDEROBJECT_PROGRAM_PARAMETER, FPoRenderProgramParameter::Class());
   _pClassFactory->Register(MO_RENDEROBJECT_PROGRAM_ATTRIBUTE, FRenderProgramAttribute::Class());
   _pClassFactory->Register(MO_RENDEROBJECT_PROGRAM_SAMPLER,   FRenderProgramSampler::Class());
   _pClassFactory->Register(MO_RENDEROBJECT_BUFFER_VERTEX,     FPoRenderVertexBuffer::Class());
   _pClassFactory->Register(MO_RENDEROBJECT_BUFFER_INDEX,      FPoRenderIndexBuffer::Class());
   _pClassFactory->Register(MO_RENDEROBJECT_PROGRAM,           FPoRenderProgram::Class());
   _pClassFactory->Register(MO_RENDEROBJECT_TARGET,            FPoRenderTarget::Class());
   _pClassFactory->Register(MO_RENDEROBJECT_TEXTURE_2D,        FPoRenderFlatTexture::Class());
   _pClassFactory->Register(MO_RENDEROBJECT_TEXTURE_CUBE,      FPoRenderCubeTexture::Class());
}

//============================================================
// <T>������̨����</T>
//============================================================
FPoRenderDevice::~FPoRenderDevice(){
   MO_DELETE(_pCapability);
   // ɾ����������
   MO_DELETE(_pLinkFlatTextures);
   MO_DELETE(_pLinkCubeTextures);
}

//============================================================
// <T>���»�����</T>
//============================================================
TBool FPoRenderDevice::UpdateContext(){
   TBool result = EFalse;
   // ���ü���ĳ���
   if(_pActiveProgram != _pProgram){
      FPoRenderProgram* pProgrom = _pProgram->Convert<FPoRenderProgram>();
      GLuint programId = pProgrom->NativeCode();
      glUseProgram(programId);
      _pProgram = _pActiveProgram;
      result = ETrue;
   }
   return result;
}

//============================================================
// <T>���ݴ������������ݡ�</T>
//
// @param ����
// @return ����
//============================================================
TInt GlRenderGetInteger(TInt code){
   GLint value = 0;
   glGetIntegerv(code, &value);
   return value;
}

//============================================================
// <T>���ô���</T>
//
// @return ������
//============================================================
TResult FPoRenderDevice::Setup(){
   // �����ô���
   TResult result = FRenderDevice::Setup();
   //............................................................
#ifdef _MO_WINDOWS
   // ��ʼ����
   GLenum initResult = glewInit();
   if(GLEW_OK != initResult){
      const GLubyte* pReason = glewGetErrorString(initResult);
      MO_FATAL("Initialize opengl glew library failure. (reason=%s)", pReason);
   }
   // ���汾
   if(glewIsSupported("GL_VERSION_2_0")){
      MO_INFO("Initialize OpenGL library ready for OpenGL 2.0.");
   }else{
      MO_FATAL("Initialize OpenGL library not supported.");
   }
#endif // _MO_WINDOWS
   //............................................................
   // �������
   const GLubyte* byteGlVersion = glGetString(GL_VERSION);  
   const GLubyte* byteGlVendor = glGetString(GL_VENDOR);  
   const GLubyte* byteGlRenderer = glGetString(GL_RENDERER);  
   const GLubyte* byteSLVersion = glGetString(GL_SHADING_LANGUAGE_VERSION);  
   const GLubyte* byteExtensions = glGetString(GL_EXTENSIONS);  
   MO_INFO("OpenGL setup. (Version    : %s)", byteGlVersion);
   MO_INFO("OpenGL setup. (Vendor     : %s)", byteGlVendor);
   MO_INFO("OpenGL setup. (Render     : %s)", byteGlRenderer);
   MO_INFO("OpenGL setup. (GLSL       : %s)", byteSLVersion);
   MO_INFO("OpenGL setup. (Extensions : %s)", byteExtensions);
   // �������
   TInt vertexConstLimit = GlRenderGetInteger(GL_MAX_VERTEX_UNIFORM_VECTORS);
   TInt fragmentConstLimit = GlRenderGetInteger(GL_MAX_FRAGMENT_UNIFORM_VECTORS);
#ifndef _MO_ANDROID
   _pCapability->SetRenderTargetLimit(GlRenderGetInteger(GL_MAX_DRAW_BUFFERS));
   //_pCapability->SetVertexConstLimit(GlRenderGetInteger(GL_MAX_VERTEX_UNIFORM_COMPONENTS) / 4);
   //_pCapability->SetFragmentConstLimit(GlRenderGetInteger(GL_MAX_FRAGMENT_UNIFORM_COMPONENTS) / 4);
#else
   //vertexConstLimit = MO_LIB_MIN(vertexConstLimit, 256);
   //fragmentConstLimit = MO_LIB_MIN(fragmentConstLimit, 256);
#endif // _MO_ANDROID
   _pCapability->SetVertexConstLimit(vertexConstLimit);
   _pCapability->SetVertexAttributeLimit(GlRenderGetInteger(GL_MAX_VERTEX_ATTRIBS));
   _pCapability->SetFragmentConstLimit(fragmentConstLimit);
   _pCapability->SetVaryingLimit(GlRenderGetInteger(GL_MAX_VARYING_VECTORS));
   _pCapability->SetSamplerLimit(GlRenderGetInteger(GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS));
   _pCapability->SetSamplerSizeLimit(GlRenderGetInteger(GL_MAX_TEXTURE_SIZE));
   _pCapability->Track();
   //MO_INFO("GL_MAX_VARYING_FLOATS=%d", GlRenderGetInteger(GL_MAX_VARYING_FLOATS));
   MO_INFO("GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS=%d", GlRenderGetInteger(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS));
   MO_INFO("GL_MAX_TEXTURE_IMAGE_UNITS=%d", GlRenderGetInteger(GL_MAX_TEXTURE_IMAGE_UNITS));
   //MO_INFO("GL_MAX_DRAW_BUFFERS=%d", GlRenderGetInteger(GL_MAX_DRAW_BUFFERS));
   //MO_INFO("GL_MAX_TEXTURE_UNITS=%d", GlRenderGetInteger(GL_MAX_TEXTURE_UNITS));
   //............................................................
   // ��������
   TInt vertexConstTotal = sizeof(SFloat4) * _pCapability->VertexConstLimit();
   _pVertexConsts->ForceLength(vertexConstTotal);
   RMemory::Clear(_pVertexConsts->Memory(), _pVertexConsts->Length());
   TInt fragmentConstTotal = sizeof(SFloat4) * _pCapability->FragmentConstLimit();
   _pFragmentConsts->ForceLength(fragmentConstTotal);
   RMemory::Clear(_pFragmentConsts->Memory(), _pFragmentConsts->Length());
   //............................................................
   // ���ýű�������
   _shaderTransformer = FPoRenderShaderTransformer::InstanceCreate();
   _shaderOptimizer = FPoRenderShaderOptimizer::InstanceCreate();
   //............................................................
   // GL_CCW��ʾ��ʱ��Ϊ����
   // glFrontFace(GL_CCW);
   return ESuccess;
}

//============================================================
// <T>��ͣ����</T>
//
// @return ������
//============================================================
TResult FPoRenderDevice::Suspend(){
   // ��ɴ���
   glFinish();
   // ��ճ���
   glUseProgram(0);
   // ��ͣ����
   FRenderDevice::Suspend();
   return ESuccess;
}

//============================================================
// <T>��������</T>
//
// @return ������
//============================================================
TResult FPoRenderDevice::Resume(){
   FRenderDevice::Resume();
   return ESuccess;
}

//============================================================
// <T>���ִ�д���</T>
//
// @param pCode ����
// @return ������
//============================================================
TResult FPoRenderDevice::CheckError(TCharC* pCode, TCharC* pMessage, ...){
   // ��ô���ԭ��
   TBool result = EFalse;
   GLenum errorCode = 0;
   TCharC* pErrorReason = NULL;
   while(ETrue){
      // ��ô���
      GLenum code = glGetError();
      if(code == GL_NO_ERROR){
         break;
      }
      // ���ԭ��
      switch(code){
         case GL_INVALID_OPERATION:
            pErrorReason = "Invalid operation.";
            break;
         case GL_INVALID_ENUM:
            pErrorReason = "Invalid enum.";
            break;
         case GL_INVALID_VALUE:
            pErrorReason = "Invalid value.";
            break;
         case GL_INVALID_FRAMEBUFFER_OPERATION:
            pErrorReason = "Invalid paramebuffer opeartion."; 
            break;
         case GL_OUT_OF_MEMORY:
            pErrorReason = "Out of memory.";
            break;
         default:
            pErrorReason = "Unknown"; 
            break;
      }
      result = ETrue;
      errorCode = code;
#ifdef _MO_WINDOWS
      break;
#endif // _MO_WINDOWS
   }
   //............................................................
   // ���������Ϣ
   if(result){
      // ��ʽ���ɱ�����ַ�����Ϣ
      TFsText message;
      va_list params;
      va_start(params, pMessage);
      message.AppendFormatParameters(pMessage, params);
      va_end(params);
      // ���������Ϣ
      MO_ERROR("%s (code=%s, error=0x%04X(%d), reason=%s)", (TCharC*)message, pCode, errorCode, errorCode, pErrorReason);
   }
   return result;
}

//============================================================
// <T>���ñ������塣</T>
//
// @return ������
//============================================================
TResult FPoRenderDevice::SetBackBuffer(TInt width, TInt height, TInt antiAlias, TBool depthed){
   return ESuccess;
}

//============================================================
// <T>�������ģʽ��</T>
//
// @param fillModeCd ���ģʽ
// @return ������
//============================================================
TResult FPoRenderDevice::SetFillMode(ERenderFillMode fillModeCd){
   // ���״̬
   if(_fillModeCd == fillModeCd){
      return EContinue;
   }
   // ��������
   GLenum fillEnum = ROpenGL::ConvertFillMode(fillModeCd);
#ifndef _MO_ANDROID
   glPolygonMode(GL_FRONT, fillEnum);
   glPolygonMode(GL_BACK, fillEnum);
#endif // _MO_ANDROID
   _fillModeCd = fillModeCd;
   _statistics->UpdateOptionFillCount();
   return ESuccess;
}

//============================================================
// <T>�������ģʽ��</T>
//
// @param depth ��ȿ���
// @param depthCd ���ģʽ
// @return ������
//============================================================
TResult FPoRenderDevice::SetDepthMode(TBool depth, ERenderDepthMode depthCd){
   // ���״̬
   if((_optionDepth == depth) && (_depthModeCd == depthCd)){
      return EContinue;
   }
   // ���ÿ���
   if(_optionDepth != depth){
      if(depth){
         glEnable(GL_DEPTH_TEST);
      }else{
         glDisable(GL_DEPTH_TEST);
      }
      _optionDepth = depth;
   }
   // ��������
   if(depth && _depthModeCd != depthCd){
      GLenum depthEnum = ROpenGL::ConvertDepthMode(depthCd);
      glDepthFunc(depthEnum);
      _depthModeCd = depthCd;
   }
   _statistics->UpdateOptionDeepCount();
   return ESuccess;
}

//============================================================
// <T>���ü���ģʽ��</T>
//
// @param cull ���ÿ���
// @param cullCd ����ģʽ
// @return ������
//============================================================
TResult FPoRenderDevice::SetCullingMode(TBool cull, ERenderCullMode cullCd){
   // ���״̬
   if((_optionCull == cull) && (_optionCull == cullCd)){
      return EContinue;
   }
   // ���ÿ���
   if(_optionCull != cull){
      if(cull){
         glEnable(GL_CULL_FACE);
      }else{
         glDisable(GL_CULL_FACE);
      }
      _optionCull = cull;
   }
   // ��������
   if(cull && _cullModeCd != cullCd){
      GLenum cullEnum = ROpenGL::ConvertCullMode(cullCd);
      glCullFace(cullEnum);
      _cullModeCd = cullCd;
   }
   _statistics->UpdateOptionCullCount();
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
TResult FPoRenderDevice::SetBlendFactors(TBool blend, ERenderBlendMode sourceCd, ERenderBlendMode targetCd){
   // ���״̬
   if((_statusBlend == blend) && (_blendSourceCd == sourceCd) && (_blendTargetCd == targetCd)){
      return EConsole;
   }
   // ���ÿ���
   if(_statusBlend != blend){
      if(blend){
         glEnable(GL_BLEND);
      }else{
         glDisable(GL_BLEND);
      }
      _statusBlend = blend;
   }
   // ����Ч��
   if(blend && ((_blendSourceCd != sourceCd) || (_blendTargetCd != targetCd))){
      GLenum source = ROpenGL::ConvertBlendFactors(sourceCd);
      GLenum target = ROpenGL::ConvertBlendFactors(targetCd);
      glBlendFunc(source, target);
      _blendSourceCd = sourceCd;
      _blendTargetCd = targetCd;
   }
   _statistics->UpdateOptionBlendCount();
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
TResult FPoRenderDevice::SetScissorRectangle(TInt left, TInt top, TInt width, TInt height){
   glScissor(left, top, width, height);
   return ETrue;
}

//============================================================
// <T>������ȾĿ�ꡣ</T>
//
// @param pRenderTarget ��ȾĿ��
// @return ������
//============================================================
TResult FPoRenderDevice::SetRenderTarget(FRenderTarget* pRenderTarget){
   TResult result = ESuccess;
   if(pRenderTarget == NULL){
      // �����ȾĿ��
      glBindFramebuffer(GL_FRAMEBUFFER, 0);
      result = CheckError("glBindFramebuffer", "Bind frame buffer. (buffer_id=%d)", 0);
      if(result != ESuccess){
         return result;
      }
      // �޸��ӽ�
      FScreenDevice* pScreenDevice = RDeviceManager::Instance().Find<FScreenDevice>();
      SIntSize2& screenSize = pScreenDevice->Size();
      glViewport(0, 0, screenSize.width, screenSize.height);
      return ESuccess;
   }else{
      // ����ȾĿ��
      FPoRenderTarget* pGlRenderTarget = pRenderTarget->Convert<FPoRenderTarget>();
      GLuint frameBufferId = pGlRenderTarget->NativeCode();
      glBindFramebuffer(GL_FRAMEBUFFER, frameBufferId);
      result = CheckError("glBindFramebuffer", "Bind frame buffer. (buffer_id=%d)", frameBufferId);
      if(result != ESuccess){
         return result;
      }
      // �޸��ӽ�
      SIntSize2& size = pRenderTarget->Size();
      glViewport(0, 0, size.width, size.height);
      // �����ɫ
      SFloatColor4& backgroundColor = pRenderTarget->BackgroundColor();
      glClearColor(backgroundColor.red, backgroundColor.green, backgroundColor.blue, backgroundColor.alpha);
      //glClearDepth(1.0f);
      glClearStencil(0);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
   }
   _pActiveRenderTarget = pRenderTarget;
   return ESuccess;
}

//============================================================
// <T>���ó���</T>
//
// @param pProgram ����
// @return ������
//============================================================
TResult FPoRenderDevice::SetProgram(FRenderProgram* pProgram){
   // ������
   //if(_pProgram == pProgram){
   //   return EContinue;
   //}
   // ��ó�����
   GLuint programId = GL_ZERO;
   if(pProgram != NULL){
      FPoRenderProgram* pRenderProgram = pProgram->Convert<FPoRenderProgram>();
      programId = pRenderProgram->NativeCode();
   }
   // ���ó���
   glUseProgram(programId);
   _pProgram = pProgram;
   // ������
   TResult result = CheckError("glUseProgram", "Set program failure. (program=0x%08X, program_id=%d)", pProgram, programId);
   // ����Ƿ����ִ��
   _statistics->UpdateProgramCount();
   return result;
}

//============================================================
// <T>���ò��֡�</T>
//
// @parma pLayout ����
// @return ������
//============================================================
TResult FPoRenderDevice::SetLayout(FRenderLayout* pLayout){
   MO_CHECK(pLayout, return ENull);
   // ��ö�����
   TResult result = ESuccess;
   FPoRenderLayout* pRenderLayout = pLayout->Convert<FPoRenderLayout>();
   // �����Ϣ
   TInt count = pRenderLayout->Count();
   TInt* pSlots = pRenderLayout->Slots();
   FRenderVertexBuffer** pBuffers = pRenderLayout->Buffers();
   TInt* bufferOffset = pRenderLayout->Offset();
   ERenderAttributeFormat* formatCds = pRenderLayout->Formats();
   for(TInt n = 0; n < count; n++){
      BindVertexBuffer(pSlots[n], pBuffers[n], bufferOffset[n], formatCds[n]);
   }
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
TResult FPoRenderDevice::BindConst(ERenderShader shaderCd, TInt slot, ERenderParameterFormat formatCd, TAnyC* pData, TInt length){
   // �����
   TBool changed = UpdateConsts(shaderCd, slot, pData, length);
   if(!changed){
      return EContinue;
   }
   // �޸�����
   TResult result = ESuccess;
   switch (formatCd){
      case ERenderParameterFormat_Float1:{
         // ��鳤��
         if(length % 4 != 0){
            MO_ERROR("Length is invalid. (length=%d)", length);
            return EFailure;
         }
         // �޸�����
         TInt count = length / 4;
         glUniform1fv(slot, count, (const GLfloat*)pData);
         // ������
         result = CheckError("glUniform1fv", "Bind const data failure. (shader_cd=%d, slot=%d, pData=0x%08X, length=%d)", shaderCd, slot, pData, length);
         break;
      }
      case ERenderParameterFormat_Float2:{
         // ��鳤��
         if(length % 8 != 0){
            MO_ERROR("Length is invalid. (length=%d)", length);
            return EFailure;
         }
         // �޸�����
         TInt count = length / 8;
         glUniform2fv(slot, count, (const GLfloat*)pData);
         // ������
         result = CheckError("glUniform2fv", "Bind const data failure. (shader_cd=%d, slot=%d, pData=0x%08X, length=%d)", shaderCd, slot, pData, length);
         break;
      }
      case ERenderParameterFormat_Float3:{
         // ��鳤��
         if(length % 12 != 0){
            MO_ERROR("Length is invalid. (length=d)", length);
            return EFailure;
         }
         // �޸�����
         TInt count = length / 12;
         glUniform3fv(slot, count, (const GLfloat*)pData);
         // ������
         result = CheckError("glUniform3fv", "Bind const data failure. (shader_cd=%d, slot=%d, pData=0x%08X, length=%d)", shaderCd, slot, pData, length);
         break;
      }
      case ERenderParameterFormat_Float4:{
         // ��鳤��
         if(length % 16 != 0){
            MO_ERROR("Length is invalid. (length=%d)", length);
            return EFailure;
         }
         // �޸�����
         TInt count = length / 16;
         glUniform4fv(slot, count, (const GLfloat*)pData);
         // ������
         result = CheckError("glUniform4fv", "Bind const data failure. (shader_cd=%d, slot=%d, pData=0x%08X, length=%d)", shaderCd, slot, pData, length);
         break;
      }
      case ERenderParameterFormat_Float3x3:{
         // ��鳤��
         if(length % 36 != 0){
            MO_ERROR("Length is invalid. (length=%d)", length);
            return EFailure;
         }
         // �޸�����
         TInt count = length / 36;
         glUniformMatrix3fv(slot, count, GL_FALSE, (const GLfloat*)pData);
         // ������
         result = CheckError("glUniformMatrix4fv", "Bind const matrix3x3 failure. (shader_cd=%d, slot=%d, pData=0x%08X, length=%d)", shaderCd, slot, pData, length);
         break;
      }
      case ERenderParameterFormat_Float4x3:{
         // ��鳤��
         if(length % 48 != 0){
            MO_ERROR("Length is invalid. (length=%d)", length);
            return EFailure;
         }
         // �޸�����
         TInt count = length / 48;
         glUniform4fv(slot, count * 3, (const GLfloat*)pData);
         //glUniformMatrix4x3fv(slot, count, GL_FALSE, (const GLfloat*)pData);
         // ������
         result = CheckError("glUniformMatrix4x3fv", "Bind const matrix4x3 failure. (shader_cd=%d, slot=%d, pData=0x%08X, length=%d)", shaderCd, slot, pData, length);
         break;
      }
      case ERenderParameterFormat_Float4x4:{
         // ��鳤��
         if(length % 64 != 0){
            MO_ERROR("Length is invalid. (length=%d)", length);
            return EFailure;
         }
         // �޸�����
         TInt count = length >> 6;
         glUniformMatrix4fv(slot, count, GL_FALSE, (const GLfloat*)pData);
         // ������
         result = CheckError("glUniformMatrix4fv", "Bind const matrix4x4 failure. (shader_cd=%d, slot=%d, pData=0x%08X, length=%d)", shaderCd, slot, pData, length);
         break;
      }
   }
   // MO_INFO("Bind const buffer. (slot=%d, format_cd=%d, length=%d)", slot, formatCd, length);
   _statistics->UpdateProgramCount(length);
   return ESuccess;
}

//============================================================
// <T>����Ⱦ���塣</T>
//
// @param pBuffer ��Ⱦ����
// @return ������
//============================================================
TResult FPoRenderDevice::BindConstBuffer(FRenderProgramBuffer* pBuffer){
   MO_FATAL_UNSUPPORT();
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
TResult FPoRenderDevice::BindVertexBuffer(TInt slot, FRenderVertexBuffer* pVertexBuffer, TInt offset, ERenderAttributeFormat formatCd){
   MO_ERROR_CHECK(slot >= 0, return EFailure, "Slot value is invalid. (slot=%d)", slot);
   // ��ö�����
   TResult result = ESuccess;
   FPoRenderVertexBuffer* pBuffer = pVertexBuffer->Convert<FPoRenderVertexBuffer>();
   //............................................................
   // �趨������
   GLuint bufferId = 0;
   if(pBuffer != NULL){
      bufferId = pBuffer->BufferId();
   }
   glBindBuffer(GL_ARRAY_BUFFER, bufferId);
   result = CheckError("glBindBuffer", "Bind buffer. (buffer_id=%d)", bufferId);
   if(result != ESuccess){
      return result;
   }
   //............................................................
   // �������
   if(pBuffer != NULL){
      glEnableVertexAttribArray(slot);
      result = CheckError("glEnableVertexAttribArray", "Enable vertex attribute array. (slot=%d)", slot);
      if(result != ESuccess){
         return result;
      }
   }else{
      glDisableVertexAttribArray(slot);
      result = CheckError("glDisableVertexAttribArray", "Disable vertex attribute array. (slot=%d)", slot);
      return result;
   }
   //............................................................
   // ���ö�����
   TInt stride = pVertexBuffer->Stride();
   switch(formatCd){
      case ERenderAttributeFormat_Float1:
         glVertexAttribPointer(slot, 1, GL_FLOAT, GL_FALSE, stride, (const GLvoid*)offset);
         break;
      case ERenderAttributeFormat_Float2:
         glVertexAttribPointer(slot, 2, GL_FLOAT, GL_FALSE, stride, (const GLvoid*)offset);
         break;
      case ERenderAttributeFormat_Float3:
         glVertexAttribPointer(slot, 3, GL_FLOAT, GL_FALSE, stride, (const GLvoid*)offset);
         break;
      case ERenderAttributeFormat_Float4:
         glVertexAttribPointer(slot, 4, GL_FLOAT, GL_FALSE, stride, (const GLvoid*)offset);
         break;
      case ERenderAttributeFormat_Byte4:
         glVertexAttribPointer(slot, 4, GL_UNSIGNED_BYTE, GL_FALSE, stride, (const GLvoid*)offset);
         break;
      case ERenderAttributeFormat_Byte4Normal:
         glVertexAttribPointer(slot, 4, GL_UNSIGNED_BYTE, GL_TRUE, stride, (const GLvoid*)offset);
         break;
      default:
         MO_FATAL("Unknown vertex format. (format_cd=%d)", formatCd);
         break;
   }
   // ������
   result = CheckError("glVertexAttribPointer", "Bind vertex attribute pointer. (slot=%d, format_cd=%d)", slot, formatCd);
   _statistics->UpdateVertexBufferCount();
   // MO_INFO("Bind vertex buffer. (slot=%d, offset=%d, format_cd=%d, stride=%d, buffer_id=%d, count=%d, length=%d)", slot, offset, formatCd, stride, bufferId, pVertexBuffer->Count(), pVertexBuffer->DataLength());
   return result;
}

//============================================================
// <T>������</T>
//
// @param slot ���
// @param index ����
// @param pTexture ����
// @return ������
//============================================================
TResult FPoRenderDevice::BindTexture(TInt slot, TInt index, FRenderTexture* pTexture){
   TResult result = ESuccess;
   //............................................................
   // ��������
   if(pTexture == NULL){
      glBindTexture(GL_TEXTURE_2D, 0);
      result = CheckError("glBindTexture", "Bind texture clear failure. (slot=%d)", slot);
      return result;
   }
   //............................................................
   // ��������
   if(_renderTextureActiveSlot != slot){
      MO_CHECK(index >= 0, return EOutRange);
      glUniform1i(slot, index);
      glActiveTexture(GL_TEXTURE0 + index);
      result = CheckError("glActiveTexture", "Active texture failure. (slot=%d, index=%d)", slot, index);
      if(result != ESuccess){
         return result;
      }
      _renderTextureActiveSlot = slot;
   }
   //............................................................
   // ������
   ERenderTexture textureCd = pTexture->TextureCd();
   switch (textureCd){
      case ERenderTexture_Flat2d:{
         FPoRenderFlatTexture* pFlatTexture = (FPoRenderFlatTexture*)pTexture;
         GLuint textureId = pFlatTexture->TextureId();
         glBindTexture(GL_TEXTURE_2D, textureId);
         glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
         glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
         result = CheckError("glBindTexture", "Bind texture failure. (texture_id=%d)", textureId);
         if(result != ESuccess){
            return result;
         }
         break;
      }
      case ERenderTexture_Cube:{
         FPoRenderCubeTexture* pCubeTexture = (FPoRenderCubeTexture*)pTexture;
         GLuint textureId = pCubeTexture->TextureId();
         glBindTexture(GL_TEXTURE_CUBE_MAP, textureId);
         result = CheckError("glBindTexture", "Bind texture failure. (texture_id=%d)", textureId);
         if(result != ESuccess){
            return result;
         }
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
// <T>������ݡ�</T>
//
// @param red ��ɫ
// @param green ��ɫ
// @param blue ��ɫ
// @param alpha ͸��
// @param depth ���
// @return ������
//============================================================
TResult FPoRenderDevice::Clear(TFloat red, TFloat green, TFloat blue, TFloat alpha, TFloat depth){
   glClearColor(red, green, blue, alpha);
   glClearDepthf(depth);
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   return ETrue;
}

//============================================================
// <T>���������Ρ�</T>
//
// @param pIndexBuffer ��������
// @param offset ��ʼλ��
// @param count ��������
// @return ������
//============================================================
TResult FPoRenderDevice::DrawTriangles(FRenderIndexBuffer* pIndexBuffer, TInt offset, TInt count){
   MO_ASSERT(pIndexBuffer);
   MO_ASSERT(offset >= 0);
   MO_ASSERT(count > 0);
   TResult result = ESuccess;
   // ���������
   FPoRenderIndexBuffer* pBuffer = pIndexBuffer->Convert<FPoRenderIndexBuffer>();
   // ����������
   GLuint bufferId = pBuffer->BufferId();
   MO_ASSERT(bufferId != 0);
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, pBuffer->BufferId());
   result = CheckError("glBindBuffer",
         "Bind element array buffer failure. (index=0x%08X, offset=%d, count=%d, buffer_id)", pIndexBuffer, offset, count, bufferId);
   if(result != ESuccess){
       return result;
   }
   _renderDrawStatistics->Begin();
   GLenum strideCd = ROpenGL::ConvertIndexStride(pIndexBuffer->StrideCd());
   glDrawElements(GL_TRIANGLES, count, strideCd, (const GLvoid*)(sizeof(TUint16) * offset));
   _renderDrawStatistics->Finish();
   // MO_INFO("Draw elements. (buffer_id=%d, offset=%d, count=%d)", bufferId, offset, count);
   result = CheckError("glDrawElements",
         "Draw triangles failure. (index=0x%08X, offset=%d, count=%d)", pIndexBuffer, offset, count);
   if(result != ESuccess){
       return result;
   }
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
   result = CheckError("glBindBuffer",
         "Bind element array buffer failure. (index=0x%08X, offset=%d, count=%d)", pIndexBuffer, offset, count);
   if(result != ESuccess){
       return result;
   }
   // ������
   _statistics->UpdateDraw(count);
   return result;
}

//============================================================
// <T>��ʾ���档</T>
//
// @return ������
//============================================================
TResult FPoRenderDevice::Present(){
   //glFlush();
   return ESuccess;
}

MO_NAMESPACE_END
