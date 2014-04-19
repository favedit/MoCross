#include "MoEoRender.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FEoRenderFlatTexture, FRenderFlatTexture);

//============================================================
// <T>����ƽ������</T>
//============================================================
FEoRenderFlatTexture::FEoRenderFlatTexture(){
   _textureId = 0;
}

//============================================================
// <T>����ƽ������</T>
//============================================================
FEoRenderFlatTexture::~FEoRenderFlatTexture(){
}

//============================================================
// <T>���ô���</T>
//
// @return ������
//============================================================
TResult FEoRenderFlatTexture::OnSetup(){
   FRenderFlatTexture::OnSetup();
   glGenTextures(1, &_textureId);
   _graphicHandle.data.uint32 = _textureId;
   MO_FATAL_CHECK(_textureId != 0, return EFailure,
         "Generate flat texture id failure. (texture_id=%d)", _textureId);
   glBindTexture(GL_TEXTURE_2D, _textureId);
   return ESuccess;
}

//============================================================
// <T>�ı��С����</T>
//
// @param width ���
// @param height �߶�
// @return ������
//============================================================
TResult FEoRenderFlatTexture::Resize(TInt width, TInt height){
   _size.Set(width, height);
   return ESuccess;
}

//============================================================
// <T>���ô���</T>
//
// @return ������
//============================================================
TResult FEoRenderFlatTexture::Upload(TByteC* pData, TInt length){
   // ������
   MO_CHECK(pData, return ENull);
   MO_CHECK(length > 0, return ENull);
   // �����
   MO_FATAL_CHECK(_textureId != 0, return EFailure,
         "Texture id is invalid. (texture_id=%d)", _textureId);
   // ������
   glBindTexture(GL_TEXTURE_2D, _textureId);
   // ���ù���
   switch(_filterCd){
      case ERenderTextureFilter_Nearest:
         glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
         glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
         break;
      case ERenderTextureFilter_Linear:
         glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
         glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
         break;
   }
   // ����չ��
   switch(_wrapCd){
      case MO::ERenderTextureWrap_Clamp:
         //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
         break;
      case MO::ERenderTextureWrap_Repeat:
         //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
         break;
   }
   //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
   //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
   // �ϴ�����
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _size.width, _size.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, (const GLvoid*)pData);
   if(_pData->MemoryC() != pData){
      _pData->Assign(pData, length);
   }
   return ESuccess;
}

//============================================================
// <T>���������ڷ����л����ݡ�</T>
//
// @return pInput ������
// @return ������
//============================================================
TResult FEoRenderFlatTexture::Unserialize(IDataInput* pInput){
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
TResult FEoRenderFlatTexture::LoadDataFile(TCharC* pFileName){
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
TResult FEoRenderFlatTexture::Suspend(){
   return ESuccess;
}

//============================================================
// <T>��������</T>
//
// @return ������
//============================================================
TResult FEoRenderFlatTexture::Resume(){
   OnSetup();
   if(!_pData->IsEmpty()){
      Upload(_pData->MemoryC(), _pData->Length());
   }
   MO_INFO("Resume texture. (texture_id=%d, size=%dx%d, data_length=%d)", _textureId, _size.width, _size.height, _pData->Length());
   return ESuccess;
}

//============================================================
// <T>��������</T>
//
// @return ������
//============================================================
TResult FEoRenderFlatTexture::Dispose(){
   return ESuccess;
}

MO_NAMESPACE_END
