#include "MoPd11Render.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FPd11RenderFlatTexture, FRenderFlatTexture);

//============================================================
// <T>����ƽ������</T>
//============================================================
FPd11RenderFlatTexture::FPd11RenderFlatTexture(){
   MO_CLEAR(_piTexture);
   MO_CLEAR(_piView);
}

//============================================================
// <T>����ƽ������</T>
//============================================================
FPd11RenderFlatTexture::~FPd11RenderFlatTexture(){
   MO_RELEASE(_piTexture);
   MO_RELEASE(_piView);
}

//============================================================
// <T>���ô���</T>
//
// @return ������
//============================================================
TResult FPd11RenderFlatTexture::OnSetup(){
   FRenderFlatTexture::OnSetup();
   //glGenTextures(1, &_textureId);
   //_graphicHandle.data.uint32 = _textureId;
   //MO_FATAL_CHECK(_textureId != 0, return EFailure,
   //      "Generate flat texture id failure. (texture_id=%d)", _textureId);
   //glBindTexture(GL_TEXTURE_2D, _textureId);
   return ESuccess;
}

//============================================================
// <T>�ı��С����</T>
//
// @param width ���
// @param height �߶�
// @return ������
//============================================================
TResult FPd11RenderFlatTexture::Resize(TInt width, TInt height){
   _size.Set(width, height);
   return ESuccess;
}

//============================================================
// <T>���ô���</T>
//
// @return ������
//============================================================
TResult FPd11RenderFlatTexture::Upload(TByteC* pData, TInt length){
   // ������
   MO_CHECK(pData, return ENull);
   MO_CHECK(length > 0, return ENull);
   MO_CHECK(_pDevice, return ENull);
   FPd11RenderDevice* pRenderDevice = _pDevice->Convert<FPd11RenderDevice>();
   // �ͷ���Դ
   MO_RELEASE(_piTexture);
   // ���ò���
   D3D11_TEXTURE2D_DESC descriptor;
   RType<D3D11_TEXTURE2D_DESC>::Clear(&descriptor);
   descriptor.Width = _size.width;
   descriptor.Height = _size.height;
   descriptor.MipLevels = 1;
   descriptor.ArraySize = 1;
   descriptor.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
   descriptor.SampleDesc.Count = 1;
   descriptor.Usage = D3D11_USAGE_DEFAULT;
   descriptor.BindFlags = D3D11_BIND_SHADER_RESOURCE;
   // �����ڴ�
   D3D11_SUBRESOURCE_DATA data;
   RType<D3D11_SUBRESOURCE_DATA>::Clear(&data);
   data.pSysMem = pData;
   data.SysMemPitch = sizeof(TUint32) * _size.width;
   // ��������
   HRESULT dxResult = pRenderDevice->NativeDevice()->CreateTexture2D(&descriptor, &data, &_piTexture);
   if(FAILED(dxResult)){
      MO_FATAL("Create buffer failure.");
      return EFailure;
   }
   // �ϴ�����
   D3D11_SHADER_RESOURCE_VIEW_DESC viewDescriptor;
   RType<D3D11_SHADER_RESOURCE_VIEW_DESC>::Clear(&viewDescriptor);
   viewDescriptor.Format = descriptor.Format;
   viewDescriptor.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
   viewDescriptor.Texture2D.MipLevels = descriptor.MipLevels;
   viewDescriptor.Texture2D.MostDetailedMip = 0;
   dxResult = pRenderDevice->NativeDevice()->CreateShaderResourceView(_piTexture, &viewDescriptor, &_piView);
   if(FAILED(dxResult)){
      MO_FATAL("Create buffer failure.");
      return EFailure;
   }
   //D3D11_MAPPED_TEXTURE2D mappedData;
   //_piTexture->Map(D3D11CalcSubresource(0, 0, 1), D3D11_MAP_WRITE_DISCARD, 0, &mappedData);
   //TByte* pMappedData = (TByte*)mappedData.pData;
   //MO_LIB_MEMORY_COPY(pMappedData, length, pData, length);
   //_piTexture->Unmap(D3D11CalcSubresource(0, 0, 1));
   return ESuccess;
}

//============================================================
// <T>���������ڷ����л����ݡ�</T>
//
// @return pInput ������
// @return ������
//============================================================
TResult FPd11RenderFlatTexture::Unserialize(IDataInput* pInput){
   // ������
   MO_CHECK(pInput, return ENull);
   // ��ȡ�ߴ�
   _size.Unserialize16(pInput);
   // �ϴ�����
   TByte* pData = pInput->PositionMemory();
   Upload(pData, 4 * _size.Square());
   return ESuccess;
}

//============================================================
// <T>���������ļ���</T>
//============================================================
TResult FPd11RenderFlatTexture::LoadDataFile(TCharC* pFileName){
   // ������
   MO_CHECK(pFileName, return ENull);
   // ��ȡ�ļ�
   FByteFile* pFile = MO_CREATE(FByteFile);
   pFile->LoadFile(pFileName);
   // �����л�����
   Unserialize(pFile);
   // �ͷ���Դ
   MO_DELETE(pFile);
   return ESuccess;
}

//============================================================
// <T>������</T>
//
// @return ������
//============================================================
TResult FPd11RenderFlatTexture::Suspend(){
   return ESuccess;
}

//============================================================
// <T>��������</T>
//
// @return ������
//============================================================
TResult FPd11RenderFlatTexture::Resume(){
   OnSetup();
   if(!_pData->IsEmpty()){
      Upload(_pData->MemoryC(), _pData->Length());
   }
   //MO_INFO("Resume texture. (texture_id=%d, size=%dx%d, data_length=%d)", _textureId, _size.width, _size.height, _pData->Length());
   return ESuccess;
}

//============================================================
// <T>��������</T>
//
// @return ������
//============================================================
TResult FPd11RenderFlatTexture::Dispose(){
   return ESuccess;
}

MO_NAMESPACE_END
