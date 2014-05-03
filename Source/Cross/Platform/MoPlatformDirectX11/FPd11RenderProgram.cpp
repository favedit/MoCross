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
TResult FPd11RenderProgram::BuildShader(FRenderShader* pShader, ID3D10Blob* piData){
   MO_CHECK(pShader, return ENull);
   MO_CHECK(piData, return ENull);
   MO_CHECK(_pDevice, return ENull);
   FPd11RenderDevice* pRenderDevice = _pDevice->Convert<FPd11RenderDevice>();
   //............................................................
   // �������
   TAny* pData = piData->GetBufferPointer();
   TInt dataLength = piData->GetBufferSize();
   // ��÷���ӿ�
   ID3D11ShaderReflection* piReflection = NULL;
   HRESULT dxResult = D3DReflect(pData, dataLength, IID_ID3D11ShaderReflection, (TAny**)&piReflection);
   if(FAILED(dxResult)){
      MO_FATAL("Reflect shader failure.");
      return EFailure;
   }
   // �������
   D3D11_SHADER_DESC shaderDescriptor;
   dxResult = piReflection->GetDesc(&shaderDescriptor);
   if(FAILED(dxResult)){
      MO_FATAL("Get reflect shader description failure.");
      return EFailure;
   }
   //............................................................
   // ��ó�������
   TInt constantBufferCount = shaderDescriptor.ConstantBuffers;
   for(TInt constantBufferIndex = 0; constantBufferIndex < constantBufferCount; constantBufferIndex++){
      ID3D11ShaderReflectionConstantBuffer* piConstantBuffer = piReflection->GetConstantBufferByIndex(constantBufferIndex);
      MO_CHECK(piConstantBuffer, continue);
      // ��û�����Ϣ
      D3D11_SHADER_BUFFER_DESC bufferDescriptor;
      dxResult = piConstantBuffer->GetDesc(&bufferDescriptor);
      if(FAILED(dxResult)){
         MO_FATAL("Get buffer description failure.");
         return EFailure;
      }
      //............................................................
      // ��ò�����Ϣ
      TInt variableCount = bufferDescriptor.Variables;
      for(TInt n = 0; n < variableCount; n++){
         ID3D11ShaderReflectionVariable* piVariable = piConstantBuffer->GetVariableByIndex(n);
         // ����������Ϣ
         D3D11_SHADER_VARIABLE_DESC variableDescriptor;
         dxResult = piVariable->GetDesc(&variableDescriptor);
         if(FAILED(dxResult)){
            MO_FATAL("Get variable description failure.");
            return EFailure;
         }
         ID3D11ShaderReflectionType* piVariableType = piVariable->GetType();
         D3D11_SHADER_TYPE_DESC typeDescriptor;
         dxResult = piVariableType->GetDesc(&typeDescriptor);
         if(FAILED(dxResult)){
            MO_FATAL("Get variable type description failure.");
            return EFailure;
         }
         // ��������
         FRenderShaderParameter* pParameter = FRenderShaderParameter::InstanceCreate();
         pParameter->SetName(variableDescriptor.Name);
         pShader->ParameterPush(pParameter);
      }
   }
   //............................................................
   // ��ó�������
   TInt attributeCount = shaderDescriptor.InputParameters;
   if(attributeCount > 0){
      for(TInt attributeIndex = 0; attributeIndex < attributeCount; attributeIndex++){
         // ���������Ϣ
         D3D11_SIGNATURE_PARAMETER_DESC attributeDescriptor;
         dxResult = piReflection->GetInputParameterDesc(attributeIndex, &attributeDescriptor);
         if(FAILED(dxResult)){
            MO_FATAL("Get attribute description failure.");
            return EFailure;
         }
         // ��������
         FRenderShaderAttribute* pAttribute = FRenderShaderAttribute::InstanceCreate();
         pAttribute->SetName(attributeDescriptor.SemanticName);
         pAttribute->SetIndex(attributeDescriptor.SemanticIndex);
         pShader->AttributePush(pAttribute);
      }
   }
   MO_RELEASE(piReflection);
   return ESuccess;
}

//============================================================
// <T>��������</T>
//
// @return ������
//============================================================
TResult FPd11RenderProgram::Build(){
   MO_CHECK(_pDevice, return ENull);
   TResult resultCd = ESuccess;
   FPd11RenderDevice* pRenderDevice = _pDevice->Convert<FPd11RenderDevice>();
   //............................................................
   // ����������Ⱦ��
   FPd11RenderVertexShader* pVertexShader = _pVertexShader->Convert<FPd11RenderVertexShader>();
   BuildShader(pVertexShader, pVertexShader->NativeData());
   // ����������Ⱦ��
   FPd11RenderFragmentShader* pFragmentShader = _pFragmentShader->Convert<FPd11RenderFragmentShader>();
   BuildShader(pFragmentShader, pFragmentShader->NativeData());
   //............................................................
   //// ����Ԫ��
   //MO_D3D11_INPUT_ELEMENT_DESC_ARRAY inputElements;
   //D3D11_INPUT_ELEMENT_DESC inputElement;
   //RType<D3D11_INPUT_ELEMENT_DESC>::Clear(&inputElement);
   //inputElement.SemanticName = attributeDescriptor.SemanticName;
   //inputElement.SemanticIndex = attributeDescriptor.SemanticIndex;
   //inputElement.Format = DXGI_FORMAT_R32G32B32_FLOAT;
   //inputElements.Push(inputElement);
   //ID3D11InputLayout* piInputLayout;
   //HRESULT dxResult = pRenderDevice->NativeDevice()->CreateInputLayout(inputElements.Memory(), inputElements.Length(), pData, dataLength, &piInputLayout);
   //if(FAILED(dxResult)){
   //   MO_FATAL("Create input layout failure.");
   //   return EFailure;
   //}
   //TAny* pVertexData = pVertexShader->NativeData()->GetBufferPointer();
   //TInt vertexDataLength = pVertexShader->NativeData()->GetBufferSize();

   //D3D11_INPUT_ELEMENT_DESC layout[] = {
   //   {"POSITION",  0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
   //   {"TEXCOORD0", 1, DXGI_FORMAT_R32G32_FLOAT,    0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
   //};
   //UINT numElements = ARRAYSIZE(layout);
   //ID3D11InputLayout* _pInputLayout;
   //HRESULT dxResult = pRenderDevice->NativeDevice()->CreateInputLayout(layout, numElements, pVertexData, vertexDataLength, &_pInputLayout);
   ////pRenderDevice->NativeContext()->IASetVertexBuffers(
   //if(FAILED(dxResult)){
   //   MO_FATAL("Create input layout failure.");
   //   return EFailure;
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
  // //............................................................
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
