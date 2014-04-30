#include "MoPd10Render.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FPd10RenderFlatTexture, FRenderFlatTexture);

//============================================================
// <T>����ƽ������</T>
//============================================================
FPd10RenderFlatTexture::FPd10RenderFlatTexture(){
   //_textureId = 0;
}

//============================================================
// <T>����ƽ������</T>
//============================================================
FPd10RenderFlatTexture::~FPd10RenderFlatTexture(){
}

//============================================================
// <T>���ô���</T>
//
// @return ������
//============================================================
TResult FPd10RenderFlatTexture::OnSetup(){
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
TResult FPd10RenderFlatTexture::Resize(TInt width, TInt height){
   _size.Set(width, height);
   return ESuccess;
}

//============================================================
// <T>���ô���</T>
//
// @return ������
//============================================================
TResult FPd10RenderFlatTexture::Upload(TByteC* pData, TInt length){
   // ������
   MO_CHECK(pData, return ENull);
   MO_CHECK(length > 0, return ENull);
   MO_CHECK(_pDevice, return ENull);
   FPd10RenderDevice* pRenderDevice = _pDevice->Convert<FPd10RenderDevice>();
   D3D10_TEXTURE2D_DESC description;
   RType<D3D10_TEXTURE2D_DESC>::Clear(&description);
   description.Width = _size.width;
   description.Height = _size.height;
   description.MipLevels = 1;
   description.ArraySize = 1;
   description.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
   description.SampleDesc.Count = 1;
   description.Usage = D3D10_USAGE_DYNAMIC;
   description.BindFlags = D3D10_BIND_SHADER_RESOURCE;
   description.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;
   D3D10_SUBRESOURCE_DATA data;
   RType<D3D10_SUBRESOURCE_DATA>::Clear(&data);
   data.pSysMem = pData;
   HRESULT dxResult = pRenderDevice->NativeDevice()->CreateTexture2D(&description, &data, &_piTexture);
   if(FAILED(dxResult)){
      MO_FATAL("Create buffer failure.");
      return EFailure;
   }
   // �ϴ�����
   //D3D10_MAPPED_TEXTURE2D mappedData;
   //_piTexture->Map(D3D10CalcSubresource(0, 0, 1), D3D10_MAP_WRITE_DISCARD, 0, &mappedData);
   //TByte* pMappedData = (TByte*)mappedData.pData;
   //MO_LIB_MEMORY_COPY(pMappedData, length, pData, length);
   //_piTexture->Unmap(D3D10CalcSubresource(0, 0, 1));
   return ESuccess;
}

//============================================================
// <T>���������ڷ����л����ݡ�</T>
//
// @return pInput ������
// @return ������
//============================================================
TResult FPd10RenderFlatTexture::Unserialize(IDataInput* pInput){
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
TResult FPd10RenderFlatTexture::LoadDataFile(TCharC* pFileName){
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
TResult FPd10RenderFlatTexture::Suspend(){
   return ESuccess;
}

//============================================================
// <T>��������</T>
//
// @return ������
//============================================================
TResult FPd10RenderFlatTexture::Resume(){
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
TResult FPd10RenderFlatTexture::Dispose(){
   return ESuccess;
}

MO_NAMESPACE_END
