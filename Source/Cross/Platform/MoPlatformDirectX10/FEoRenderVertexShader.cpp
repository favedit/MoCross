#include "MoEoRender.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FEoRenderVertexShader, FRenderVertexShader);

//============================================================
// <T>������Ⱦ����</T>
//============================================================
FEoRenderVertexShader::FEoRenderVertexShader(){
}

//============================================================
// <T>������Ⱦ����</T>
//============================================================
FEoRenderVertexShader::~FEoRenderVertexShader(){
}

//============================================================
// <T>���ô���</T>
//
// @return ������
//============================================================
TResult FEoRenderVertexShader::Setup(){
   _renderId.uint32 = glCreateShader(GL_VERTEX_SHADER);
   TResult resultCd = _pDevice->CheckError("glCreateShader", "Create vertex shader failure. (shader_id=%d)", _renderId.uint32);
   return resultCd;
}

//============================================================
// <T>���봦��</T>
//
// @param pSource �����ַ���
// @return ������
//============================================================
TResult FEoRenderVertexShader::Compile(TCharC* pSource){
   // �ϴ�����
   const GLchar* source[1];
   source[0] = (const GLchar*)pSource;
   glShaderSource(_renderId.uint32, 1, source, NULL);
   // ���봦��
   glCompileShader(_renderId.uint32);
   // ���Ա�����
   GLint status;
   glGetShaderiv(_renderId.uint32, GL_COMPILE_STATUS, &status);
   if(!status){
      // ��ô���
      GLsizei sourceLength;
      glGetShaderiv(_renderId.uint32, GL_SHADER_SOURCE_LENGTH, &sourceLength);
		GLchar* pShaderSource = MO_TYPES_ALLOC(GLchar, sourceLength);
		glGetShaderSource(_renderId.uint32, sourceLength, NULL, pShaderSource);
      // ���ԭ��
      GLsizei reasonLength = 0;
      glGetShaderiv(_renderId.uint32, GL_INFO_LOG_LENGTH, &reasonLength);
      GLchar* pReason = MO_TYPES_ALLOC(GLchar, reasonLength);
      glGetShaderInfoLog(_renderId.uint32, reasonLength, NULL, pReason);  
      MO_FATAL("Create vertex shader failure. (status=%d)\n%s\n%s", status, pReason, pShaderSource);
      // �ͷ���Դ
      MO_DELETE(pShaderSource);
      MO_DELETE(pReason);
      glDeleteShader(_renderId.uint32); 
      _renderId.uint32 = 0;
   }else{
      MO_INFO("Create vertex shader success. (status=%d)\n%s", status, pSource);
   }
   return ESuccess;
}

//============================================================
// <T>������</T>
//
// @return ������
//============================================================
TResult FEoRenderVertexShader::Suspend(){
   return ESuccess;
}

//============================================================
// <T>��������</T>
//
// @return ������
//============================================================
TResult FEoRenderVertexShader::Resume(){
   return ESuccess;
}

//============================================================
// <T>��������</T>
//
// @return ������
//============================================================
TResult FEoRenderVertexShader::Dispose(){
   TResult resultCd = ESuccess;
   if(_renderId.uint32 != 0){
      glDeleteShader(_renderId.uint32);
      resultCd = _pDevice->CheckError("glCreateShader", "Delete vertex shader failure. (shader_id=%d)", _renderId.uint32);
      _renderId.uint32 = 0;
   }
   return resultCd;
}

MO_NAMESPACE_END
