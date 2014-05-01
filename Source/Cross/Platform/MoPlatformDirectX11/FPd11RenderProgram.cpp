#include "MoPd11Render.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FPd11RenderProgram, FRenderProgram);

//============================================================
// <T>������Ⱦ����</T>
//============================================================
FPd11RenderProgram::FPd11RenderProgram(){
   //_programId = 0;
}

//============================================================
// <T>������Ⱦ����</T>
//============================================================
FPd11RenderProgram::~FPd11RenderProgram(){
}

//============================================================
// <T>���ݴ����������������</T>
//
// @param pCode ����
// @return ��������
//============================================================
TInt FPd11RenderProgram::FindAttribute(TCharC* pCode){
   MO_ASSERT(pCode);
   //GLint slot = glGetAttribLocation(_programId, pCode);
   //_pDevice->CheckError("glGetAttribLocation", "Find attribute location. (program_id=%d, code=%s)", _programId, pCode);
   //return slot;
   return 0;
}

//============================================================
// <T>���ݴ�����Ҷ���������</T>
//
// @param pCode ����
// @return ��������
//============================================================
TInt FPd11RenderProgram::FindDefine(TCharC* pCode){
   MO_ASSERT(pCode);
   //GLint slot = glGetUniformLocation(_programId, pCode);
   //_pDevice->CheckError("glGetUniformLocation", "Bind uniform location. (program_id=%d, code=%s)", _programId, pCode);
   //return slot;
   return 0;
}

//============================================================
// <T>���ݴ�������Ե�ָ�����λ�á�</T>
//
// @param slot ���
// @param pCode ����
// @return ������
//============================================================
TResult FPd11RenderProgram::BindAttribute(TInt slot, TCharC* pCode){
   MO_ASSERT(slot >= 0);
   MO_ASSERT(pCode);
   //MO_ASSERT(_programId != 0);
   //glBindAttribLocation(_programId, slot, pCode);
   //TResult resultCd = _pDevice->CheckError("glBindAttribLocation", "Bind attribute location. (program_id=%d, slot=%d, code=%s)", _programId, slot, pCode);
   //return resultCd;
   return ESuccess;
}

//============================================================
// <T>���ô���</T>
//
// @return ������
//============================================================
TResult FPd11RenderProgram::Setup(){
   MO_CHECK(_pDevice, return ENull);
   FPd11RenderDevice* pRenderDevice = _pDevice->Convert<FPd11RenderDevice>();
   // ����������Ⱦ��
   FPd11RenderVertexShader* pVertexShader = FPd11RenderVertexShader::InstanceCreate();
   pVertexShader->SetDevice(_pDevice);
   pVertexShader->SetProgram(this);
   pVertexShader->Setup();
   _pVertexShader = pVertexShader;
   // ����������Ⱦ��
   FPd11RenderFragmentShader* pFragmentShader = FPd11RenderFragmentShader::InstanceCreate();
   pFragmentShader->SetDevice(_pDevice);
   pFragmentShader->SetProgram(this);
   pFragmentShader->Setup();
   _pFragmentShader = pFragmentShader;
   MO_INFO("Create program success.");
   return ESuccess;
}

//============================================================
// <T>��������</T>
//
// @return ������
//============================================================
TResult FPd11RenderProgram::Build(){
   MO_CHECK(_pDevice, return ENull);
   FPd11RenderDevice* pRenderDevice = _pDevice->Convert<FPd11RenderDevice>();
   //pRenderDevice->NativeDevice()->VSSetShader();
   //pRenderDevice->NativeDevice()->PSSetShader();

   FPd11RenderVertexShader* pVertexShader = _pVertexShader->Convert<FPd11RenderVertexShader>();
   TAny* pVertexData = pVertexShader->NativeData()->GetBufferPointer();
   TInt vertexDataLength = pVertexShader->NativeData()->GetBufferSize();

   D3D11_INPUT_ELEMENT_DESC layout[] = {
      {"POSITION",  0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
      {"TEXCOORD0", 1, DXGI_FORMAT_R32G32_FLOAT,    0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
   };
   UINT numElements = ARRAYSIZE(layout);
   ID3D11InputLayout* _pInputLayout;
   HRESULT dxResult = pRenderDevice->NativeDevice()->CreateInputLayout(layout, numElements, pVertexData, vertexDataLength, &_pInputLayout);
   if(FAILED(dxResult)){
      MO_FATAL("Create input layout failure.");
      return EFailure;
   }

   TResult resultCd = ESuccess;
   // ���ö�����Ⱦ��

   //GLuint vertexShaderId = _pVertexShader->RenderId().uint32;
   //glAttachShader(_programId, vertexShaderId);
   //resultCd = _pDevice->CheckError("glAttachShader", "Attach shader failure. (program_id=%d, shader_id=%d)", _programId, vertexShaderId);
   //if(resultCd != ESuccess){
   //   return resultCd;
   //}
   //// ���ö�����Ⱦ��
   //FPd11RenderFragmentShader* pFragmentShader = (FPd11RenderFragmentShader*)_pFragmentShader;
   //GLuint fragmentShaderId = pFragmentShader->RenderId().uint32;
   //glAttachShader(_programId, fragmentShaderId);
   //resultCd = _pDevice->CheckError("glAttachShader", "Attach shader failure. (program_id=%d, shader_id=%d)", _programId, fragmentShaderId);
   //if(resultCd != ESuccess){
   //   return resultCd;
   //}
   return resultCd;
}

//============================================================
// <T>��������</T>
//
// @return ������
//============================================================
TResult FPd11RenderProgram::Link(){
   TResult resultCd = ESuccess;
  // // ��������
  // glLinkProgram(_programId);
  // // ��ý��
  // GLint linkStatus = GL_TRUE;
  // glGetProgramiv(_programId, GL_LINK_STATUS, &linkStatus);
  // if(linkStatus == GL_FALSE){
  //    GLsizei length;
  //    glGetProgramiv(_programId, GL_INFO_LOG_LENGTH, &length);
		//GLchar* pReason = (GLchar*)MO_MEM_ALLOC(sizeof(GLchar) * length);
		//glGetProgramInfoLog(_programId, length, NULL, pReason);
  //    MO_FATAL("Link program failure. (status=%d, reason=%s)", linkStatus, pReason);
  //    MO_MEM_FREE(pReason);
  //    // �ͷų���
  //    glDeleteProgram(_programId);
  //    _programId = 0;
  // }
  // //............................................................
  // // У�����
  // glValidateProgram(_programId);
  // // ��ý��
  // GLint validateStatus = GL_TRUE;
  // glGetProgramiv(_programId, GL_VALIDATE_STATUS, &validateStatus);
  // if(validateStatus == GL_FALSE){
  //    GLsizei length;
  //    glGetProgramiv(_programId, GL_INFO_LOG_LENGTH, &length);
		//GLchar* pReason = (GLchar*)MO_MEM_ALLOC(sizeof(GLchar) * length);
		//glGetProgramInfoLog(_programId, length, NULL, pReason);
  //    MO_FATAL("Validate program failure. (status=%d, reason=%s)", validateStatus, pReason);
  //    MO_MEM_FREE(pReason);
  //    // �ͷų���
  //    glDeleteProgram(_programId);
  //    _programId = 0;
  // }
  // //............................................................
  // glFinish();
  // resultCd = _pDevice->CheckError("glFinish",
  //       "Finish program link faliure. (program_id=%d)", _programId);
  // if(resultCd != ESuccess){
  //    return resultCd;
  // }
  // //............................................................
  // MO_INFO("Link program success. (program_id=%d)", _programId);
   return resultCd;
}

//============================================================
// <T>������</T>
//
// @return ������
//============================================================
TResult FPd11RenderProgram::Suspend(){
   return ESuccess;
}

//============================================================
// <T>��������</T>
//
// @return ������
//============================================================
TResult FPd11RenderProgram::Resume(){
   return ESuccess;
}

//============================================================
// <T>��������</T>
//
// @return ������
//============================================================
TResult FPd11RenderProgram::Dispose(){
   //// �ͷ���Դ
   //if(_programId != 0){
   //   glDeleteProgram(_programId);
   //   _programId = 0;
   //}
   //// �ͷų���
   //MO_DELETE(_pVertexShader);
   //MO_DELETE(_pFragmentShader);
   return ESuccess;
}

MO_NAMESPACE_END
