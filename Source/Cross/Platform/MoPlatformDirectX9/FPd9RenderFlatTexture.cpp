#include "MoPd9Render.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FPd9RenderFlatTexture, FRenderFlatTexture);

//============================================================
// <T>����ƽ������</T>
//============================================================
FPd9RenderFlatTexture::FPd9RenderFlatTexture(){
   MO_CLEAR(_piTexture);
}

//============================================================
// <T>����ƽ������</T>
//============================================================
FPd9RenderFlatTexture::~FPd9RenderFlatTexture(){
   MO_RELEASE(_piTexture);
}

//============================================================
// <T>���ô���</T>
//
// @return ������
//============================================================
TResult FPd9RenderFlatTexture::OnSetup(){
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
TResult FPd9RenderFlatTexture::Resize(TInt width, TInt height){
   _size.Set(width, height);
   return ESuccess;
}

//============================================================
// <T>���ô���</T>
//
// @return ������
//============================================================
TResult FPd9RenderFlatTexture::Upload(TByteC* pData, TInt length){
   // ������
   MO_CHECK(pData, return ENull);
   MO_CHECK(length > 0, return ENull);
   MO_CHECK(_pDevice, return ENull);
   FPd9RenderDevice* pRenderDevice = _pDevice->Convert<FPd9RenderDevice>();
   // �ͷ���Դ
   MO_RELEASE(_piTexture);
   // ��������
   HRESULT dxResult = pRenderDevice->NativeDevice()->CreateTexture(_size.width, _size.height, 0, 0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, &_piTexture, NULL);
   if(FAILED(dxResult)){
      MO_FATAL("Create texture 2d failure.");
      return EFailure;
   }
   // �ϴ�����
   D3DLOCKED_RECT rect;
   dxResult = _piTexture->LockRect(0, &rect, NULL, 0);
   if(FAILED(dxResult)){
      MO_FATAL("Lock buffer failure.");
      return EFailure;
   }
   MO_LIB_MEMORY_COPY(rect.pBits, length, pData, length);
   _piTexture->UnlockRect(0);
   return ESuccess;
}

//============================================================
// <T>���������ڷ����л����ݡ�</T>
//
// @return pInput ������
// @return ������
//============================================================
TResult FPd9RenderFlatTexture::Unserialize(IDataInput* pInput){
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
TResult FPd9RenderFlatTexture::LoadDataFile(TCharC* pFileName){
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
TResult FPd9RenderFlatTexture::Suspend(){
   return ESuccess;
}

//============================================================
// <T>��������</T>
//
// @return ������
//============================================================
TResult FPd9RenderFlatTexture::Resume(){
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
TResult FPd9RenderFlatTexture::Dispose(){
   return ESuccess;
}

MO_NAMESPACE_END
