#include "MoEgBitmap.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>����λͼ��������</T>
//============================================================
FBitmap::FBitmap(){
}

//============================================================
// <T>����λͼ��������</T>
//============================================================
FBitmap::~FBitmap(){
}

//============================================================
// <T>���ô���</T>
//
// @return ������
//============================================================
TResult FBitmap::Setup(){
   return ESuccess;
}

//============================================================
// <T>�ı��С��</T>
//
// @param width ���
// @param height �߶�
// @return ������
//============================================================
TResult FBitmap::Resize(TInt width, TInt height){
   return ESuccess;
}

//============================================================
// <T>������Ⱦ����</T>
//
// @param pRegion ��Ⱦ����
// @return ������
//============================================================
TResult FBitmap::FilterRegion(FRenderRegion* pRegion){
   if(_texture){
      //pRegion->Renderables()->Push(_texture);
   }
   return ESuccess;
}

//============================================================
// <T>������ݡ�</T>
//
// @param color ��ɫ
//============================================================
TResult FBitmap::Clear(TColor color){
   TInt size = (TInt)_size.Square();
   TColor* pWriter = (TColor*)_data->Memory();
   for(TInt n = 0; n < size; n++){
      *pWriter++ = color;
   }
   return ESuccess;
}

//============================================================
// <T>������ݡ�</T>
//
// @param color ��ɫ
// @param pRectangle ���η�Χ
//============================================================
TResult FBitmap::Clear(TColor color, SIntRectangle* pRectangle){
   // ������
   MO_CHECK(pRectangle, return ENull);
   // �������
   TInt left = pRectangle->left;
   TInt top = pRectangle->top;
   TInt width = pRectangle->width;
   TInt height = pRectangle->height;
   // ��鷶Χ
   if(left + width > _size.width){
      //width = _size.width - left;
   }
   if(top + height > _size.height){
      //height = _size.height - top;
   }
   // �������
   //TInt stride = _size.width - width;
   //TColor* pWriter = (TColor*)_data->Memory() + (_size.width * top) + left;
   //for(TInt y = 0; y < height; y++){
   //   for(TInt x = 0; x < width; x++){
   //      *pWriter++ = color;
   //   }
   //   pWriter += stride;
   //}
   return ESuccess;
}

//============================================================
// <T>����λͼ���塣</T>
//
// @return ������
//============================================================
TResult FBitmap::Update(){
   return ESuccess;
}

//============================================================
// <T>�ͷ�λͼ���ݡ�</T>
//============================================================
void FBitmap::FreeBitmap(){
   //_data->Free();
}

//============================================================
// <T>�ͷ��������ݡ�</T>
//============================================================
void FBitmap::FreeTexture(){
}

MO_NAMESPACE_END
