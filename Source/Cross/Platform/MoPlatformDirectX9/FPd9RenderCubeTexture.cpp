#include "MoPd9Render.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FPd9RenderCubeTexture, FRenderFlatTexture);

//============================================================
// <T>������ȾCUBE����</T>
//============================================================
FPd9RenderCubeTexture::FPd9RenderCubeTexture(){
   MO_CLEAR(_piTexture);
}

//============================================================
// <T>������ȾCUBE����</T>
//============================================================
FPd9RenderCubeTexture::~FPd9RenderCubeTexture(){
   MO_RELEASE(_piTexture);
}

//============================================================
// <T>���ô���</T>
//
// @return ������
//============================================================
TResult FPd9RenderCubeTexture::OnSetup(){
   //glGenTextures(1, &_textureId);
   //MO_FATAL_CHECK(_textureId != 0, return EFailure,
   //      "Generate cube texture id failure. (texture_id=%d)", _textureId);
   //glBindTexture(GL_TEXTURE_CUBE_MAP, _textureId);
   return ESuccess;
}

//============================================================
// <T>�ı��С����</T>
//
// @param width ���
// @param height �߶�
// @return ������
//============================================================
TResult FPd9RenderCubeTexture::Resize(TInt size){
   _size.Set(size, size);
   return ESuccess;
}

//============================================================
// <T>���ô���</T>
//
// @return ������
//============================================================
TResult FPd9RenderCubeTexture::Upload(TByteC* pData, TInt length){
   // ������
   MO_CHECK(pData, return ENull);
   MO_CHECK(length > 0, return ENull);
   MO_CHECK(_pDevice, return ENull);
   FPd9RenderDevice* pRenderDevice = _pDevice->Convert<FPd9RenderDevice>();
   // �ͷ���Դ
   MO_RELEASE(_piTexture);
   // ��������
   HRESULT dxResult = pRenderDevice->NativeDevice()->CreateCubeTexture(_size.width, 0, 0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, &_piTexture, NULL);
   if(FAILED(dxResult)){
      MO_FATAL("Create texture 2d failure.");
      return EFailure;
   }
   // �ϴ�����
   TInt faceLength = _size.width * _size.width;
   TInt faceSize = sizeof(TUint32) * faceLength;
   for(TInt n = 0; n < 6; n++){
      D3DCUBEMAP_FACES faceCd = (D3DCUBEMAP_FACES)n;
      D3DLOCKED_RECT rect;
      dxResult = _piTexture->LockRect(faceCd, 0, &rect, NULL, 0);
      if(FAILED(dxResult)){
         MO_FATAL("Lock buffer failure.");
         return EFailure;
      }
      MO_LIB_MEMORY_COPY(rect.pBits, faceSize, pData + faceLength * n, faceSize);
      _piTexture->UnlockRect(faceCd, 0);
   }
   return ESuccess;
}

//============================================================
// <T>���������ڷ����л����ݡ�</T>
//
// @return pInput ������
// @return ������
//============================================================
TResult FPd9RenderCubeTexture::Unserialize(IDataInput* pInput){
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
TResult FPd9RenderCubeTexture::LoadDataFile(TCharC* pFileName){
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
TResult FPd9RenderCubeTexture::Suspend(){
   return ESuccess;
}

//============================================================
// <T>��������</T>
//
// @return ������
//============================================================
TResult FPd9RenderCubeTexture::Resume(){
   OnSetup();
   //if(!_pData->IsEmpty()){
   Upload(_pData->MemoryC(), _pData->Length());
   //}
   return ESuccess;
}

//============================================================
// <T>��������</T>
//
// @return ������
//============================================================
TResult FPd9RenderCubeTexture::Dispose(){
   return ESuccess;
}

MO_NAMESPACE_END
