#include "MoPoRender.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FPoRenderProgram, FRenderProgram);

//============================================================
// <T>������Ⱦ����</T>
//============================================================
FPoRenderProgram::FPoRenderProgram(){
   _programId = 0;
}

//============================================================
// <T>������Ⱦ����</T>
//============================================================
FPoRenderProgram::~FPoRenderProgram(){
}

//============================================================
// <T>���ݴ����������������</T>
//
// @param pCode ����
// @return ��������
//============================================================
TInt FPoRenderProgram::FindAttribute(TCharC* pCode){
   MO_ASSERT(pCode);
   GLint slot = glGetAttribLocation(_programId, pCode);
   _pDevice->CheckError("glGetAttribLocation", "Find attribute location. (program_id=%d, code=%s)", _programId, pCode);
   return slot;
}

//============================================================
// <T>���ݴ�����Ҷ���������</T>
//
// @param pCode ����
// @return ��������
//============================================================
TInt FPoRenderProgram::FindDefine(TCharC* pCode){
   MO_ASSERT(pCode);
   GLint slot = glGetUniformLocation(_programId, pCode);
   _pDevice->CheckError("glGetUniformLocation", "Bind uniform location. (program_id=%d, code=%s)", _programId, pCode);
   return slot;
}

//============================================================
// <T>���ݴ�������Ե�ָ�����λ�á�</T>
//
// @param slot ���
// @param pCode ����
// @return ������
//============================================================
TResult FPoRenderProgram::BindAttribute(TInt slot, TCharC* pCode){
   MO_ASSERT(slot >= 0);
   MO_ASSERT(pCode);
   MO_ASSERT(_programId != 0);
   glBindAttribLocation(_programId, slot, pCode);
   TResult resultCd = _pDevice->CheckError("glBindAttribLocation", "Bind attribute location. (program_id=%d, slot=%d, code=%s)", _programId, slot, pCode);
   return resultCd;
}

//============================================================
// <T>���ô���</T>
//
// @return ������
//============================================================
TResult FPoRenderProgram::Setup(){
   _programId = glCreateProgram();
   // ����������Ⱦ��
   FPoRenderVertexShader* pVertexShader = FPoRenderVertexShader::InstanceCreate();
   pVertexShader->SetDevice(_pDevice);
   pVertexShader->Setup();
   _pVertexShader = pVertexShader;
   // ����������Ⱦ��
   FPoRenderFragmentShader* pFragmentShader = FPoRenderFragmentShader::InstanceCreate();
   pFragmentShader->SetDevice(_pDevice);
   pFragmentShader->Setup();
   _pFragmentShader = pFragmentShader;
   MO_INFO("Create program success. (program_id=%d, vertex_id=%d, fragment=%d)",
         _programId, pVertexShader->RenderId().uint32, pFragmentShader->RenderId().uint32);
   return ESuccess;
}

//============================================================
// <T>��������</T>
//
// @return ������
//============================================================
TResult FPoRenderProgram::Build(){
   TResult resultCd = ESuccess;
   // ���ö�����Ⱦ��
   GLuint vertexShaderId = _pVertexShader->RenderId().uint32;
   glAttachShader(_programId, vertexShaderId);
   resultCd = _pDevice->CheckError("glAttachShader", "Attach shader failure. (program_id=%d, shader_id=%d)", _programId, vertexShaderId);
   if(resultCd != ESuccess){
      return resultCd;
   }
   // ���ö�����Ⱦ��
   FPoRenderFragmentShader* pFragmentShader = (FPoRenderFragmentShader*)_pFragmentShader;
   GLuint fragmentShaderId = pFragmentShader->RenderId().uint32;
   glAttachShader(_programId, fragmentShaderId);
   resultCd = _pDevice->CheckError("glAttachShader", "Attach shader failure. (program_id=%d, shader_id=%d)", _programId, fragmentShaderId);
   if(resultCd != ESuccess){
      return resultCd;
   }
   return resultCd;
}

//============================================================
// <T>��������</T>
//
// @return ������
//============================================================
TResult FPoRenderProgram::Link(){
   TResult resultCd = ESuccess;
   // ��������
   glLinkProgram(_programId);
   // ��ý��
   GLint linkStatus = GL_TRUE;
   glGetProgramiv(_programId, GL_LINK_STATUS, &linkStatus);
   if(linkStatus == GL_FALSE){
      GLsizei length;
      glGetProgramiv(_programId, GL_INFO_LOG_LENGTH, &length);
		GLchar* pReason = (GLchar*)MO_MEM_ALLOC(sizeof(GLchar) * length);
		glGetProgramInfoLog(_programId, length, NULL, pReason);
      MO_FATAL("Link program failure. (status=%d, reason=%s)", linkStatus, pReason);
      MO_MEM_FREE(pReason);
      // �ͷų���
      glDeleteProgram(_programId);
      _programId = 0;
   }
   //............................................................
   // У�����
   glValidateProgram(_programId);
   // ��ý��
   GLint validateStatus = GL_TRUE;
   glGetProgramiv(_programId, GL_VALIDATE_STATUS, &validateStatus);
   if(validateStatus == GL_FALSE){
      GLsizei length;
      glGetProgramiv(_programId, GL_INFO_LOG_LENGTH, &length);
		GLchar* pReason = (GLchar*)MO_MEM_ALLOC(sizeof(GLchar) * length);
		glGetProgramInfoLog(_programId, length, NULL, pReason);
      MO_FATAL("Validate program failure. (status=%d, reason=%s)", validateStatus, pReason);
      MO_MEM_FREE(pReason);
      // �ͷų���
      glDeleteProgram(_programId);
      _programId = 0;
   }
   //............................................................
   glFinish();
   resultCd = _pDevice->CheckError("glFinish",
         "Finish program link faliure. (program_id=%d)", _programId);
   if(resultCd != ESuccess){
      return resultCd;
   }
   //............................................................
   MO_INFO("Link program success. (program_id=%d)", _programId);
   return resultCd;
}

//============================================================
// <T>������</T>
//
// @return ������
//============================================================
TResult FPoRenderProgram::Suspend(){
   return ESuccess;
}

//============================================================
// <T>��������</T>
//
// @return ������
//============================================================
TResult FPoRenderProgram::Resume(){
   return ESuccess;
}

//============================================================
// <T>��������</T>
//
// @return ������
//============================================================
TResult FPoRenderProgram::Dispose(){
   // �ͷ���Դ
   if(_programId != 0){
      glDeleteProgram(_programId);
      _programId = 0;
   }
   // �ͷų���
   MO_DELETE(_pVertexShader);
   MO_DELETE(_pFragmentShader);
   return ESuccess;
}

MO_NAMESPACE_END
