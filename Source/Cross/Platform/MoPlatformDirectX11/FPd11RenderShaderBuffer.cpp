#include "MoPd11Render.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FPd11RenderShaderBuffer, FRenderShaderBuffer);

//============================================================
// <T>������Ⱦ�����塣</T>
//============================================================
FPd11RenderShaderBuffer::FPd11RenderShaderBuffer(){
   MO_CLEAR(_piBuffer);
}

//============================================================
// <T>������Ⱦ�����塣</T>
//============================================================
FPd11RenderShaderBuffer::~FPd11RenderShaderBuffer(){
   MO_RELEASE(_piBuffer);
}

//============================================================
// <T>���ô�����</T>
//
// @return �������
//============================================================
TResult FPd11RenderShaderBuffer::Setup(){
   TResult resultCd = FRenderShaderBuffer::Setup();
   MO_CHECK(_pDevice, return ENull);
   MO_CHECK(_dataLength > 0, return EOutRange);
   FPd11RenderDevice* pRenderDevice = _pDevice->Convert<FPd11RenderDevice>();
   // ��������
   D3D11_BUFFER_DESC descriptor = {0};
   descriptor.ByteWidth = _dataLength;
   descriptor.Usage = D3D11_USAGE_DEFAULT;
   descriptor.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
   descriptor.CPUAccessFlags = 0;
   descriptor.MiscFlags = 0;
   descriptor.StructureByteStride = 0;
   // ��������
   D3D11_SUBRESOURCE_DATA data = {0};
   data.pSysMem = _pData->Memory();
   data.SysMemPitch = 0;
   data.SysMemSlicePitch = 0;
   // ��������
   HRESULT dxResult = pRenderDevice->NativeDevice()->CreateBuffer(&descriptor, &data, &_piBuffer);
   if(FAILED(dxResult)){
      MO_FATAL("Create buffer failure.");
      return EFailure;
   }
   return resultCd;
}

//============================================================
// <T>�ύ������</T>
//
// @return �������
//============================================================
TResult FPd11RenderShaderBuffer::Commit(){
   MO_CHECK(_pDevice, return ENull);
   TResult resultCd = ESuccess;
   FPd11RenderDevice* pRenderDevice = _pDevice->Convert<FPd11RenderDevice>();
   //............................................................
   // ��������
   TByte* pMemoryData = _pData->Memory();
   TInt dataLength = _pData->Length();
   pRenderDevice->NativeContext()->UpdateSubresource(_piBuffer, 0, NULL, pMemoryData, 0, 0);
   //D3D11_MAPPED_SUBRESOURCE mappedResource = {0};
   //HRESULT dxResult = pRenderDevice->NativeContext()->Map(_piBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
   //MO_LIB_MEMORY_COPY(mappedResource.pData, dataLength, pMemoryData, dataLength);
   //pRenderDevice->NativeContext()->Unmap(_piBuffer, 0);
   //GetErrorInfo();
   return resultCd;
}

//============================================================
// <T>�󶨴�����</T>
//
// @return �������
//============================================================
TResult FPd11RenderShaderBuffer::Bind(){
   MO_CHECK(_pDevice, return ENull);
   MO_CHECK(_slot >= 0, return EOutRange);
   TResult resultCd = ESuccess;
   FPd11RenderDevice* pRenderDevice = _pDevice->Convert<FPd11RenderDevice>();
   //............................................................
   // ��������
   if(_shaderCd == ERenderShader_Vertex){
      pRenderDevice->NativeContext()->VSSetConstantBuffers(_slot, 1, &_piBuffer);
   }else if(_shaderCd == ERenderShader_Fragment){
      pRenderDevice->NativeContext()->PSSetConstantBuffers(_slot, 1, &_piBuffer);
   }else{
      MO_FATAL("Render shader type is unknown. (shader=%d)", _shaderCd);
   }
   return resultCd;
}

MO_NAMESPACE_END