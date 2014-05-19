#include "MoPd9Render.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FPd9RenderProgram, FRenderProgram);

//============================================================
// <T>������Ⱦ����</T>
//============================================================
FPd9RenderProgram::FPd9RenderProgram(){
}

//============================================================
// <T>������Ⱦ����</T>
//============================================================
FPd9RenderProgram::~FPd9RenderProgram(){
}

//============================================================
// <T>���ݴ�����Ҷ���������</T>
//
// @param pCode ����
// @return ��������
//============================================================
TInt FPd9RenderProgram::FindDefine(TCharC* pCode){
   MO_ASSERT(pCode);
   return -1;
}

//============================================================
// <T>���ݴ����������������</T>
//
// @param pCode ����
// @return ��������
//============================================================
TInt FPd9RenderProgram::FindAttribute(TCharC* pCode){
   MO_ASSERT(pCode);
   return -1;
}

//============================================================
// <T>���ݴ�������Ե�ָ�����λ�á�</T>
//
// @param slot ���
// @param pCode ����
// @return ������
//============================================================
TResult FPd9RenderProgram::BindAttribute(TInt slot, TCharC* pCode){
   MO_ASSERT(slot >= 0);
   MO_ASSERT(pCode);
   return ESuccess;
}

//============================================================
// <T>���ô���</T>
//
// @return ������
//============================================================
TResult FPd9RenderProgram::Setup(){
   MO_CHECK(_pDevice, return ENull);
   FPd9RenderDevice* pRenderDevice = _pDevice->Convert<FPd9RenderDevice>();
   // ����������Ⱦ��
   FPd9RenderVertexShader* pVertexShader = FPd9RenderVertexShader::InstanceCreate();
   pVertexShader->SetDevice(_pDevice);
   pVertexShader->SetProgram(this);
   pVertexShader->Setup();
   _pVertexShader = pVertexShader;
   // ����������Ⱦ��
   FPd9RenderFragmentShader* pFragmentShader = FPd9RenderFragmentShader::InstanceCreate();
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
TResult FPd9RenderProgram::BuildShader(FRenderShader* pShader, FPd9RenderShaderBuffer* pBuffer, ID3DXConstantTable* piTable){
   MO_CHECK(pShader, return ENull);
   MO_CHECK(piTable, return ENull);
   MO_CHECK(_pDevice, return ENull);
   FPd9RenderDevice* pRenderDevice = _pDevice->Convert<FPd9RenderDevice>();
   ERenderShader shaderCd = pShader->ShaderCd();
   //............................................................
   // �������
   D3DXCONSTANTTABLE_DESC shaderDescriptor = {0};
   piTable->SetDefaults(pRenderDevice->NativeDevice());
   HRESULT dxResult = piTable->GetDesc(&shaderDescriptor);
   if(FAILED(dxResult)){
      MO_FATAL("Get reflect shader description failure.");
      return EFailure;
   }
   //............................................................
   // ��ó�������
   TInt constLength = 0;
   TUint constCount = 0;
   D3DXCONSTANT_DESC constDescriptors[256] = {0};
   TInt constantCount = shaderDescriptor.Constants;
   for(TInt constantIndex = 0; constantIndex < constantCount; constantIndex++){
      D3DXHANDLE handle = piTable->GetConstant(NULL, constantIndex);
      dxResult = piTable->GetConstantDesc(handle, constDescriptors, &constCount);
      if(FAILED(dxResult)){
         MO_FATAL("Get constant descriptor failure.");
         return EFailure;
      }
      if(constCount == 1){
         D3DXCONSTANT_DESC& constDescriptor = constDescriptors[0];
         if((constDescriptor.RegisterSet == D3DXRS_BOOL) || (constDescriptor.RegisterSet == D3DXRS_INT4) || (constDescriptor.RegisterSet == D3DXRS_FLOAT4)){
            // ���ò���
            FPd9RenderShaderParameter* pParameter = (FPd9RenderShaderParameter*)ParameterFind(constDescriptor.Name);
            if(pParameter == NULL){
               MO_FATAL("Shader parameter is not found. (name=%s)", constDescriptor.Name);
            }else{
               pParameter->SetStatusUsed(ETrue);
               pParameter->SetBuffer(pBuffer);
               pParameter->SetSlot(sizeof(TFloat) * 4 * constDescriptor.RegisterIndex);
               pParameter->SetSize(constDescriptor.Bytes);
               // �������λ��
               TInt offset = sizeof(TFloat) * 4 * constDescriptor.RegisterIndex + constDescriptor.Bytes;
               if(offset > constLength){
                  constLength = offset;
               }
            }
         }else if(constDescriptor.RegisterSet == D3DXRS_SAMPLER){
            // ����ȡ����
            FRenderSampler* pSampler = SamplerFind(constDescriptor.Name);
            if(pSampler == NULL){
               MO_FATAL("Shader sampler bound is not found. (name=%s)", constDescriptor.Name);
            }else{
               pSampler->SetStatusUsed(ETrue);
               pSampler->SetSlot(constDescriptor.RegisterIndex);
            }
         }else{
            MO_FATAL_UNSUPPORT();
         }
      }else{
         MO_FATAL_UNSUPPORT();
      }
   }
   //............................................................
   // ��������������
   GRenderShaderAttributeDictionary::TIterator attributeIterator = _attributes.Iterator();
   while(attributeIterator.Next()){
      FRenderAttribute* pAttribute = *attributeIterator;
      pAttribute->SetStatusUsed(ETrue);
   }
   //............................................................
   // ���û���
   pBuffer->SetDevice(_pDevice);
   pBuffer->SetStatusUsed(ETrue);
   pBuffer->SetShaderCd(shaderCd);
   pBuffer->SetDataLength(constLength);
   pBuffer->Setup();
   BufferPush(pBuffer);
   return ESuccess;
}

//============================================================
// <T>��������</T>
//
// @return ������
//============================================================
TResult FPd9RenderProgram::Build(){
   MO_CHECK(_pDevice, return ENull);
   TResult resultCd = ESuccess;
   FPd9RenderDevice* pRenderDevice = _pDevice->Convert<FPd9RenderDevice>();
   //............................................................
   // ����������Ⱦ��
   FPd9RenderVertexShader* pVertexShader = _pVertexShader->Convert<FPd9RenderVertexShader>();
   BuildShader(pVertexShader, pVertexShader->Buffer(), pVertexShader->NativeTable());
   //// ����������Ⱦ��
   FPd9RenderFragmentShader* pFragmentShader = _pFragmentShader->Convert<FPd9RenderFragmentShader>();
   BuildShader(pFragmentShader, pFragmentShader->Buffer(), pFragmentShader->NativeTable());
   return resultCd;
}

//============================================================
// <T>��������</T>
//
// @return ������
//============================================================
TResult FPd9RenderProgram::Link(){
   MO_CHECK(_pDevice, return ENull);
   TResult resultCd = ESuccess;
   FPd9RenderDevice* pRenderDevice = _pDevice->Convert<FPd9RenderDevice>();
   //............................................................
   // �������
   //FPd9RenderVertexShader* pVertexShader = _pVertexShader->Convert<FPd9RenderVertexShader>();
   //ID3D9Blob* piShaderData = pVertexShader->NativeData();
   ////............................................................
   //// ������������
   //TInt position = 0;
   //GRenderShaderAttributeDictionary::TIterator attributeIterator = _attributes.Iterator();
   //while(attributeIterator.Next()){
   //   FRenderAttribute* pAttribute = *attributeIterator;
   //   if(pAttribute->IsStatusUsed()){
   //      ERenderAttributeFormat formatCd = pAttribute->FormatCd();
   //      D3D9_INPUT_ELEMENT_DESC inputElement;
   //      RType<D3D9_INPUT_ELEMENT_DESC>::Clear(&inputElement);
   //      inputElement.SemanticName = pAttribute->Name();
   //      inputElement.SemanticIndex = pAttribute->Index();
   //      inputElement.Format = RDirectX9::ConvertAttrbuteFormat(formatCd) ;
   //      inputElement.AlignedByteOffset = position;
   //      inputElement.InputSlot = pAttribute->Slot();
   //      inputElement.AlignedByteOffset = 0;
   //      inputElement.InputSlotClass = D3D9_INPUT_PER_VERTEX_DATA;
   //      inputElements.Push(inputElement);
   //      position += RRenderAttributeFormat::CalculateSize(formatCd);
   //   }
   //}
   //// ����������
   //HRESULT dxResult = pRenderDevice->NativeDevice()->CreateInputLayout(
   //      inputElements.Memory(), inputElements.Length(),
   //      piShaderData->GetBufferPointer(), piShaderData->GetBufferSize(),
   //      &_piInputLayout);
   //if(FAILED(dxResult)){
   //   MO_FATAL("Create input layout failure.");
   //   return EFailure;
   //}
   //............................................................
   MO_INFO("Link program success.");
   return resultCd;
}

//============================================================
// <T>������</T>
//
// @return ������
//============================================================
TResult FPd9RenderProgram::Suspend(){
   return ESuccess;
}

//============================================================
// <T>��������</T>
//
// @return ������
//============================================================
TResult FPd9RenderProgram::Resume(){
   return ESuccess;
}

//============================================================
// <T>��������</T>
//
// @return ������
//============================================================
TResult FPd9RenderProgram::Dispose(){
   // �ͷų���
   MO_DELETE(_pVertexShader);
   MO_DELETE(_pFragmentShader);
   return ESuccess;
}

MO_NAMESPACE_END
