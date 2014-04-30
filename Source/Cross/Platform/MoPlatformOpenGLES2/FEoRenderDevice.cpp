#include "MoEoRender.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FEoRenderDevice, FRenderDevice);

//============================================================
// <T>������̨����</T>
//============================================================
FEoRenderDevice::FEoRenderDevice(){
   _pCapability = MO_CREATE(FRenderCapability);
   // ��ʼ����������
   _optionTexture = EFalse;
   _renderTextureActiveSlot = -1;
   _textureLimit = 0;
   // ��ʼ����������
   _pLinkFlatTextures = MO_CREATE(FRenderFlatTextureList);
   _pLinkCubeTextures = MO_CREATE(FRenderCubeTextureList);
}

//============================================================
// <T>������̨����</T>
//============================================================
FEoRenderDevice::~FEoRenderDevice(){
   MO_DELETE(_pCapability);
   // ɾ����������
   MO_DELETE(_pLinkFlatTextures);
   MO_DELETE(_pLinkCubeTextures);
}

//============================================================
// <T>���»�����</T>
//============================================================
TBool FEoRenderDevice::UpdateContext(){
   TBool result = EFalse;
   // ���ü���ĳ���
   if(_pActiveProgram != _pProgram){
      FEoRenderProgram* pProgrom = (FEoRenderProgram*)_pProgram;
      glUseProgram(pProgrom->ProgramId());
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
TResult FEoRenderDevice::Setup(){
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
   // GL_CCW��ʾ��ʱ��Ϊ����
   // glFrontFace(GL_CCW);
   return ESuccess;
}

//============================================================
// <T>��ͣ����</T>
//
// @return ������
//============================================================
TResult FEoRenderDevice::Suspend(){
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
TResult FEoRenderDevice::Resume(){
   FRenderDevice::Resume();
   return ESuccess;
}

//============================================================
// <T>���ִ�д���</T>
//
// @param pCode ����
// @return ������
//============================================================
TResult FEoRenderDevice::CheckError(TCharC* pCode, TCharC* pMessage, ...){
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
// <T>�������㻺�塣</T>
//
// @param pClass �����
// @return ���㻺��
//============================================================
FRenderVertexBuffer* FEoRenderDevice::CreateVertexBuffer(FClass* pClass){
   FRenderVertexBuffer* pVertexBuffer = FEoRenderVertexBuffer::InstanceCreate();
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
FRenderIndexBuffer* FEoRenderDevice::CreateIndexBuffer(FClass* pClass){
   FRenderIndexBuffer* pIndexBuffer = FEoRenderIndexBuffer::InstanceCreate();
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
FRenderProgram* FEoRenderDevice::CreateProgrom(FClass* pClass){
   FEoRenderProgram* pProgram = FEoRenderProgram::InstanceCreate();
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
FRenderTarget* FEoRenderDevice::CreateRenderTarget(FClass* pClass){
   FEoRenderTarget* pRenderTarget = FEoRenderTarget::InstanceCreate();
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
FRenderFlatTexture* FEoRenderDevice::CreateFlatTexture(FClass* pClass){
   FEoRenderFlatTexture* pTexture = FEoRenderFlatTexture::InstanceCreate();
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
FRenderCubeTexture* FEoRenderDevice::CreateCubeTexture(FClass* pClass){
   FEoRenderCubeTexture* pTexture = FEoRenderCubeTexture::InstanceCreate();
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
TResult FEoRenderDevice::Clear(TFloat red, TFloat green, TFloat blue, TFloat alpha, TFloat depth){
   glClearColor(red, green, blue, alpha);
   glClearDepthf(depth);
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   return ETrue;
}

//============================================================
// <T>���ñ������塣</T>
//
// @return ������
//============================================================
TResult FEoRenderDevice::SetBackBuffer(TInt width, TInt height, TInt antiAlias, TBool depthed){
   return ESuccess;
}

//============================================================
// <T>�������ģʽ��</T>
//
// @param fillModeCd ���ģʽ
// @return ������
//============================================================
TResult FEoRenderDevice::SetFillMode(ERenderFillMode fillModeCd){
   // ���״̬
   if(_fillModeCd == fillModeCd){
      return EContinue;
   }
   // ��������
#ifndef _MO_ANDROID
   switch(fillModeCd){
      case ERenderFillMode_Point:
         glPolygonMode(GL_FRONT, GL_POINT);
         glPolygonMode(GL_BACK, GL_POINT);
         break;
      case ERenderFillMode_Line:
         glPolygonMode(GL_FRONT, GL_LINE);
         glPolygonMode(GL_BACK, GL_LINE);
         break;
      case ERenderFillMode_Fill:
         glPolygonMode(GL_FRONT, GL_FILL);
         glPolygonMode(GL_BACK, GL_FILL);
         break;
   }
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
TResult FEoRenderDevice::SetDepthMode(TBool depth, ERenderDepthMode depthCd){
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
      _statistics->UpdateOptionDeepCount();
   }
   // ��������
   if(depth && _depthModeCd != depthCd){
      switch(depthCd){
         case ERenderDepthMode_Equal:
            glDepthFunc(GL_EQUAL);
            break;
         case ERenderDepthMode_NotEqual:
            glDepthFunc(GL_NOTEQUAL);
            break;
         case ERenderDepthMode_Less:
            glDepthFunc(GL_LESS);
            break;
         case ERenderDepthMode_LessEqual:
            glDepthFunc(GL_LEQUAL);
            break;
         case ERenderDepthMode_Greater:
            glDepthFunc(GL_GREATER);
            break;
         case ERenderDepthMode_GreaterEqual:
            glDepthFunc(GL_GEQUAL);
            break;
         case ERenderDepthMode_Always:
            glDepthFunc(GL_ALWAYS);
            break;
      }
      _depthModeCd = depthCd;
   }
   return ESuccess;
}

//============================================================
// <T>���ü���ģʽ��</T>
//
// @param cull ���ÿ���
// @param cullCd ����ģʽ
// @return ������
//============================================================
TResult FEoRenderDevice::SetCullingMode(TBool cull, ERenderCullMode cullCd){
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
      _statistics->UpdateOptionCullCount();
   }
   // ��������
   if(cull && _cullModeCd != cullCd){
      switch(cullCd){
         case ERenderCullMode_Front:
            glCullFace(GL_FRONT);
            break;
         case ERenderCullMode_Back:
            glCullFace(GL_BACK);
            break;
         case ERenderCullMode_Both:
            glCullFace(GL_FRONT_AND_BACK);
            break;
      }
      _cullModeCd = cullCd;
   }
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
TResult FEoRenderDevice::SetBlendFactors(TBool blend, ERenderBlendMode sourceCd, ERenderBlendMode targetCd){
   // ���ÿ���
   if(_statusBlend != blend){
      if(blend){
         glEnable(GL_BLEND);
      }else{
         glDisable(GL_BLEND);
      }
      _statusBlend = blend;
      _statistics->UpdateOptionBlendCount();
   }
   // ����Ч��
   if(blend && ((_blendSourceCd != sourceCd) || (_blendTargetCd != targetCd))){
      GLenum source = ROpenGLES2::ConvertBlendFactors(sourceCd);
      GLenum target = ROpenGLES2::ConvertBlendFactors(targetCd);
      glBlendFunc(source, target);
      _blendSourceCd = sourceCd;
      _blendTargetCd = targetCd;
   }
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
TResult FEoRenderDevice::SetScissorRectangle(TInt left, TInt top, TInt width, TInt height){
   glScissor(left, top, width, height);
   return ETrue;
}

//============================================================
// <T>������ȾĿ�ꡣ</T>
//
// @param pRenderTarget ��ȾĿ��
// @return ������
//============================================================
TResult FEoRenderDevice::SetRenderTarget(FRenderTarget* pRenderTarget){
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
      GLuint frameBufferId = pRenderTarget->RenderId().uint32;
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
TResult FEoRenderDevice::SetProgram(FRenderProgram* pProgram){
   // ������
   //if(_pProgram == pProgram){
   //   return EContinue;
   //}
   // ��ó�����
   GLuint programId = GL_ZERO;
   if(pProgram != NULL){
      FEoRenderProgram* pRenderProgram = (FEoRenderProgram*)pProgram;
      programId = pRenderProgram->ProgramId();
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
// <T>�󶨳������ݡ�</T>
//
// @parma shaderCd ��Ⱦ����
// @parma slot ���
// @parma pData ����
// @parma length ����
// @return ������
//============================================================
TResult FEoRenderDevice::BindConstData(ERenderShader shaderCd, TInt slot, ERenderShaderConstForamt formatCd, TAnyC* pData, TInt length){
   // �����
   TBool changed = UpdateConsts(shaderCd, slot, pData, length);
   if(!changed){
      return EContinue;
   }
   // �޸�����
   TResult result = ESuccess;
   switch (formatCd){
      case ERenderShaderConstForamt_Float1:{
         // ��鳤��
         if(length % 4 != 0){
            MO_ERROR("Length is invalid. (length=d)", length);
            return EFailure;
         }
         // �޸�����
         TInt count = length / 4;
         glUniform1fv(slot, count, (const GLfloat*)pData);
         // ������
         result = CheckError("glUniform1fv", "Bind const data failure. (shader_cd=%d, slot=%d, pData=0x%08X, length=%d)", shaderCd, slot, pData, length);
         break;
      }
      case ERenderShaderConstForamt_Float2:{
         // ��鳤��
         if(length % 8 != 0){
            MO_ERROR("Length is invalid. (length=d)", length);
            return EFailure;
         }
         // �޸�����
         TInt count = length / 8;
         glUniform2fv(slot, count, (const GLfloat*)pData);
         // ������
         result = CheckError("glUniform2fv", "Bind const data failure. (shader_cd=%d, slot=%d, pData=0x%08X, length=%d)", shaderCd, slot, pData, length);
         break;
      }
      case ERenderShaderConstForamt_Float3:{
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
      case ERenderShaderConstForamt_Float4:{
         // ��鳤��
         if(length % 16 != 0){
            MO_ERROR("Length is invalid. (length=d)", length);
            return EFailure;
         }
         // �޸�����
         TInt count = length / 16;
         glUniform4fv(slot, count, (const GLfloat*)pData);
         // ������
         result = CheckError("glUniform4fv", "Bind const data failure. (shader_cd=%d, slot=%d, pData=0x%08X, length=%d)", shaderCd, slot, pData, length);
         break;
      }
      case ERenderShaderConstForamt_Matrix3x3:{
         // ��鳤��
         if(length % 36 != 0){
            MO_ERROR("Length is invalid. (length=d)", length);
            return EFailure;
         }
         // �޸�����
         TInt count = length / 36;
         glUniformMatrix3fv(slot, count, GL_FALSE, (const GLfloat*)pData);
         // ������
         result = CheckError("glUniformMatrix4fv", "Bind const matrix3x3 failure. (shader_cd=%d, slot=%d, pData=0x%08X, length=%d)", shaderCd, slot, pData, length);
         break;
      }
      case ERenderShaderConstForamt_Matrix4x3:{
         // ��鳤��
         if(length % 48 != 0){
            MO_ERROR("Length is invalid. (length=d)", length);
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
      case ERenderShaderConstForamt_Matrix4x4:{
         // ��鳤��
         if(length % 64 != 0){
            MO_ERROR("Length is invalid. (length=d)", length);
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
TResult FEoRenderDevice::BindConstFloat3(ERenderShader shaderCd, TInt slot, TFloat x, TFloat y, TFloat z){
   // �����
   TFloat data[3] = {x, y, z};
   TInt length = sizeof(TFloat) * 3;
   TBool changed = UpdateConsts(shaderCd, slot, data, length);
   if(!changed){
      return EContinue;
   }
   // �޸�����
   glUniform3fv(slot, 1, (const GLfloat*)data);
   // ������
   TResult result = CheckError("glUniform3fv", "Bind const float3 failure. (shader_cd=%d, slot=%d, value=%f,%f,%f)", shaderCd, slot, x, y, z);
   _statistics->UpdateProgramCount(sizeof(data));
   return result;
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
TResult FEoRenderDevice::BindConstFloat4(ERenderShader shaderCd, TInt slot, TFloat x, TFloat y, TFloat z, TFloat w){
   // �����
   TFloat data[4] = {x, y, z, w};
   TInt length = sizeof(TFloat) * 4;
   TBool changed = UpdateConsts(shaderCd, slot, data, length);
   if(!changed){
      return EContinue;
   }
   // �޸�����
   glUniform4fv(slot, 1, (const GLfloat*)data);
   // ������
   TResult result = CheckError("glUniform4fv", "Bind const float4 failure. (shader_cd=%d, slot=%d, value=%f,%f,%f,%f)", shaderCd, slot, x, y, z, w);
   _statistics->UpdateProgramCount(sizeof(data));
   return result;
}

//============================================================
// <T>�󶨳�����ά����</T>
//
// @parma shaderCd ��Ⱦ����
// @parma slot ���
// @parma matrix ����
// @return ������
//============================================================
TResult FEoRenderDevice::BindConstMatrix3x3(ERenderShader shaderCd, TInt slot, const SFloatMatrix3d& matrix){
   // �����
   TAnyC* pMemory = matrix.MemoryC();
   TInt length = sizeof(TFloat) * 9;
   TBool changed = UpdateConsts(shaderCd, slot, pMemory, length);
   if(!changed){
      return EContinue;
   }
   // ת�þ���
   GLfloat data[3][3];
   data[0][0] = matrix.data[0][0];
   data[0][1] = matrix.data[1][0];
   data[0][2] = matrix.data[2][0];
   data[1][0] = matrix.data[0][1];
   data[1][1] = matrix.data[1][1];
   data[1][2] = matrix.data[2][1];
   data[2][0] = matrix.data[0][2];
   data[2][1] = matrix.data[1][2];
   data[2][2] = matrix.data[2][2];
   glUniformMatrix3fv(slot, 1, GL_FALSE, (const GLfloat*)data);
   // ������
   TResult result = CheckError("glUniformMatrix3fv", "Bind const matrix3x3 failure. (shader_cd=%d, slot=%d)", shaderCd, slot);
   _statistics->UpdateProgramCount(length);
   return result;
}

//============================================================
// <T>�󶨳�����ά����</T>
//
// @parma shaderCd ��Ⱦ����
// @parma slot ���
// @parma matrix ����
// @return ������
//============================================================
TResult FEoRenderDevice::BindConstMatrix4x4(ERenderShader shaderCd, TInt slot, const SFloatMatrix3d& matrix){
   // �����
   TAnyC* pMemory = matrix.MemoryC();
   TInt length = sizeof(TFloat) * 16;
   TBool changed = UpdateConsts(shaderCd, slot, pMemory, length);
   if(!changed){
      return EContinue;
   }
   // �޸�����
#ifdef _MO_ANDROID
   // ת�þ���
   GLfloat data[4][4];
   data[0][0] = matrix.data[0][0];
   data[0][1] = matrix.data[1][0];
   data[0][2] = matrix.data[2][0];
   data[0][3] = matrix.data[3][0];
   data[1][0] = matrix.data[0][1];
   data[1][1] = matrix.data[1][1];
   data[1][2] = matrix.data[2][1];
   data[1][3] = matrix.data[3][1];
   data[2][0] = matrix.data[0][2];
   data[2][1] = matrix.data[1][2];
   data[2][2] = matrix.data[2][2];
   data[2][3] = matrix.data[3][2];
   data[3][0] = matrix.data[0][3];
   data[3][1] = matrix.data[1][3];
   data[3][2] = matrix.data[2][3];
   data[3][3] = matrix.data[3][3];
   glUniformMatrix4fv(slot, 1, GL_FALSE, (const GLfloat*)data);
#else
   glUniformMatrix4fv(slot, 1, GL_TRUE, (const GLfloat*)pMemory);
#endif // _MO_ANDROID
   // ������
   TResult result = CheckError("glUniformMatrix4fv", "Bind const matrix4x4 failure. (shader_cd=%d, slot=%d)", shaderCd, slot);
   _statistics->UpdateProgramCount(length);
   return result;
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
TResult FEoRenderDevice::BindVertexBuffer(TInt slot, FRenderVertexBuffer* pVertexBuffer, TInt offset, ERenderVertexFormat formatCd){
   MO_ERROR_CHECK(slot >= 0, return EFailure, "Slot value is invalid. (slot=%d)", slot);
   // ��ö�����
   TResult result = ESuccess;
   FEoRenderVertexBuffer* pBuffer = pVertexBuffer->Convert<FEoRenderVertexBuffer>();
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
      case ERenderVertexFormat_Byte4:
         glVertexAttribPointer(slot, 4, GL_UNSIGNED_BYTE, GL_FALSE, stride, (const GLvoid*)offset);
         break;
      case ERenderVertexFormat_ByteNormal4:
         glVertexAttribPointer(slot, 4, GL_UNSIGNED_BYTE, GL_TRUE, stride, (const GLvoid*)offset);
         break;
      case ERenderVertexFormat_Float1:
         glVertexAttribPointer(slot, 1, GL_FLOAT, GL_FALSE, stride, (const GLvoid*)offset);
         break;
      case ERenderVertexFormat_Float2:
         glVertexAttribPointer(slot, 2, GL_FLOAT, GL_FALSE, stride, (const GLvoid*)offset);
         break;
      case ERenderVertexFormat_Float3:
         glVertexAttribPointer(slot, 3, GL_FLOAT, GL_FALSE, stride, (const GLvoid*)offset);
         break;
      case ERenderVertexFormat_Float4:
         glVertexAttribPointer(slot, 4, GL_FLOAT, GL_FALSE, stride, (const GLvoid*)offset);
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
// @param pTexture ����
// @return ������
//============================================================
TResult FEoRenderDevice::BindTexture(TInt slot, FRenderTexture* pTexture){
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
      TInt index = pTexture->Index();
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
         FEoRenderFlatTexture* pFlatTexture = (FEoRenderFlatTexture*)pTexture;
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
         FEoRenderCubeTexture* pCubeTexture = (FEoRenderCubeTexture*)pTexture;
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
// <T>���������Ρ�</T>
//
// @param pIndexBuffer ��������
// @param offset ��ʼλ��
// @param count ��������
// @return ������
//============================================================
TResult FEoRenderDevice::DrawTriangles(FRenderIndexBuffer* pIndexBuffer, TInt offset, TInt count){
   MO_ASSERT(pIndexBuffer);
   MO_ASSERT(offset >= 0);
   MO_ASSERT(count > 0);
   TResult result = ESuccess;
   // ���������
   FEoRenderIndexBuffer* pBuffer = pIndexBuffer->Convert<FEoRenderIndexBuffer>();
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
   GLenum strideCd = ROpenGLES2::ConvertIndexStride(pIndexBuffer->StrideCd());
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
TResult FEoRenderDevice::Present(){
   //glFlush();
   return ESuccess;
}

MO_NAMESPACE_END
