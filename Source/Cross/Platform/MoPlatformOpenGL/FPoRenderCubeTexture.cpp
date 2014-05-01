#include "MoPoRender.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FPoRenderCubeTexture, FRenderFlatTexture);

//============================================================
// <T>������ȾCUBE����</T>
//============================================================
FPoRenderCubeTexture::FPoRenderCubeTexture(){
   _textureId = 0;
}

//============================================================
// <T>������ȾCUBE����</T>
//============================================================
FPoRenderCubeTexture::~FPoRenderCubeTexture(){
}

//============================================================
// <T>���ô���</T>
//
// @return ������
//============================================================
TResult FPoRenderCubeTexture::OnSetup(){
   glGenTextures(1, &_textureId);
   MO_FATAL_CHECK(_textureId != 0, return EFailure,
         "Generate cube texture id failure. (texture_id=%d)", _textureId);
   glBindTexture(GL_TEXTURE_CUBE_MAP, _textureId);
   return ESuccess;
}

//============================================================
// <T>�ı��С����</T>
//
// @param width ���
// @param height �߶�
// @return ������
//============================================================
TResult FPoRenderCubeTexture::Resize(TInt size){
   _size.Set(size, size);
   return ESuccess;
}

//============================================================
// <T>���ô���</T>
//
// @return ������
//============================================================
TResult FPoRenderCubeTexture::Upload(TByteC* pData, TInt length){
   // ������
   MO_CHECK(pData, return ENull);
   MO_CHECK(length > 0, return ENull);
   // �����
   MO_FATAL_CHECK(_textureId != 0, return EFailure, "Texture id is invalid. (texture_id=%d)", _textureId);
   int faceSize = _size.Square();
   // �ϴ�����
   //glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
   glEnable(GL_TEXTURE_CUBE_MAP);
   //glEnable(GL_TEXTURE_GEN_S);   
   //glEnable(GL_TEXTURE_GEN_T);   
   //glEnable(GL_TEXTURE_GEN_R); 
   //glEnable(GL_NORMALIZE);
   glBindTexture(GL_TEXTURE_CUBE_MAP, _textureId);
   glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
   glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
   //glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP);
   //glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP);
   //glTexGeni(GL_R, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP);
   glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_RGBA, _size.width, _size.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, (const GLvoid*)(pData + sizeof(TUint32) * faceSize * 0));
   glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, GL_RGBA, _size.width, _size.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, (const GLvoid*)(pData + sizeof(TUint32) * faceSize * 1));
   glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, GL_RGBA, _size.width, _size.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, (const GLvoid*)(pData + sizeof(TUint32) * faceSize * 2));
   glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, GL_RGBA, _size.width, _size.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, (const GLvoid*)(pData + sizeof(TUint32) * faceSize * 3));
   glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, GL_RGBA, _size.width, _size.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, (const GLvoid*)(pData + sizeof(TUint32) * faceSize * 4));
   glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, GL_RGBA, _size.width, _size.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, (const GLvoid*)(pData + sizeof(TUint32) * faceSize * 5));
   //glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_REPEAT);  
   //glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_REPEAT);  
   //glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_REPEAT);  
   //// ���ù���
   //ERenderTextureFilter filterCd = pTexture->FilterCd();
   //switch(filterCd){
   //   case ERenderTextureFilter_Nearest:
   //      glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
   //      break;
   //   case ERenderTextureFilter_Linear:
   //      glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
   //      break;
   //}
   ////glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); 
   ////glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
   ////glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
   ////glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
   //// ����չ��
   //ERenderTextureWrap warpCd = pTexture->WrapCd();
   //switch(warpCd){
   //   case MO::ERenderTextureWrap_Clamp:
   //      //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
   //      break;
   //   case MO::ERenderTextureWrap_Repeat:
   //      //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   //      break;
   //}
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
TResult FPoRenderCubeTexture::Unserialize(IDataInput* pInput){
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
TResult FPoRenderCubeTexture::LoadDataFile(TCharC* pFileName){
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
TResult FPoRenderCubeTexture::Suspend(){
   return ESuccess;
}

//============================================================
// <T>��������</T>
//
// @return ������
//============================================================
TResult FPoRenderCubeTexture::Resume(){
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
TResult FPoRenderCubeTexture::Dispose(){
   return ESuccess;
}

MO_NAMESPACE_END
