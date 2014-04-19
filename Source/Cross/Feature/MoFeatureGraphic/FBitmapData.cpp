#include "MoFgBitmap.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FBitmapData, FImage);

//============================================================
// <T>����λͼ��</T>
//============================================================
FBitmapData::FBitmapData(TInt width, TInt height){
   _pData = MO_CREATE(FByteStream);
   // ���ô�С
   if((width > 0) && (height > 0)){
      Resize(width, height);
   }
}

//============================================================
// <T>����λͼ��</T>
//============================================================
FBitmapData::~FBitmapData(){
   MO_DELETE(_pData);
}

//============================================================
// <T>�ı��С��</T>
//
// @param width ���
// @param height �߶�
//============================================================
TResult FBitmapData::Resize(TInt width, TInt height){
   // ������
   MO_CHECK(width > 0, return EInvalid);
   MO_CHECK(height > 0, return EInvalid);
   // ����С
   TInt originSize = sizeof(TColor) * _size.Square();
   TInt size = sizeof(TColor) * width * height;
   if(originSize == size){
      return EContinue;
   }
   // ���ô�С
   _size.Set(width, height);
   _originSize.Set(width, height);
   // ��������
   _pData->ForceSize(size);
   return ESuccess;
}

//============================================================
// <T>�ϴ�һ��λͼ���ݡ�</T>
//
// @param pMemory ����ָ��
// @param width ���
// @param height �߶�
//============================================================
TResult FBitmapData::UploadData(TByteC* pMemory, TInt width, TInt height){
   // ������
   MO_CHECK(pMemory, return ENull);
   MO_CHECK(width > 0, return EInvalid);
   MO_CHECK(height > 0, return EInvalid);
   // ��������
   TByteC* pReader = pMemory;
   TInt readerStride = sizeof(TUint32) * width;
   TByte* pWriter = _pData->Memory();
   TInt writerStride = sizeof(TUint32) * _size.width;
   for(TInt n = 0; n < height; n++){
      MO_LIB_MEMORY_COPY(pWriter, writerStride, pReader, readerStride);
      pWriter += writerStride;
      pReader += readerStride;
   }
   return ESuccess;
}

MO_NAMESPACE_END
