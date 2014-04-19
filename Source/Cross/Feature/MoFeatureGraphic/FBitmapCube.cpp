#include "MoFgBitmap.h"

MO_NAMESPACE_BEGIN

////============================================================
//// <T>����λͼ��������</T>
////============================================================
//FBitmapCube::FBitmapCube(){
//   MO_CLEAR(_pTexture);
//}
//
////============================================================
//// <T>����λͼ��������</T>
////============================================================
//FBitmapCube::~FBitmapCube(){
//   MO_DELETE(_pTexture);
//}
//
////============================================================
//// <T>���ô���</T>
////
//// @return ������
////============================================================
//TResult FBitmapCube::Setup(){
//   MO_ASSERT(!_pTexture);
//   // ����豸
//   //FRenderDevice* pDevice = RDeviceManager::Instance().RenderDevice();
//   //// ��������
//   //SIntSize2& bitmapSize = _size;
//   //_pTexture = pDevice->CreateCubeTexture();
//   //_pTexture->Size().Assign(bitmapSize);
//   //_pTexture->SetFormatCd(ERenderTextureFormat_BGRA);
//   //_pTexture->SetFilterCd(ERenderTextureFilter_Nearest);
//   //_pTexture->SetWrapCd(ERenderTextureWrap_Clamp);
//   //_pTexture->Setup();
//   return ESuccess;
//}
//
////============================================================
//// <T>�����Ⱦ����</T>
////
//// @return ��Ⱦ����
////============================================================
//FRenderTexture* FBitmapCube::RenderTexture(){
//   return _pTexture;
//}
//
////============================================================
//// <T>�ı��С��</T>
////
//// @param width ���
//// @param height �߶�
//// @return ������
////============================================================
//TResult FBitmapCube::Resize(TInt width, TInt height){
//   // ���λͼ��С
//   FBitmapData::Resize(width, height);
//   _originSize.Set(width, height);
//   // ���������С
//   _pTexture->Resize(width);
//   return ESuccess;
//}
//
////============================================================
//// <T>������ݡ�</T>
////
//// @param color ��ɫ
////============================================================
//TResult FBitmapCube::Clear(TColor color){
//   TInt size = _size.Square();
//   TColor* pWriter = (TColor*)_pData->Memory();
//   for(TInt n = 0; n < size; n++){
//      *pWriter++ = color;
//   }
//   return ESuccess;
//}
//
////============================================================
//// <T>������ݡ�</T>
////
//// @param color ��ɫ
//// @param pRectangle ���η�Χ
////============================================================
//TResult FBitmapCube::Clear(TColor color, SIntRectangle* pRectangle){
//   // ������
//   MO_CHECK(pRectangle, return ENull);
//   // �������
//   TInt left = pRectangle->left;
//   TInt top = pRectangle->top;
//   TInt width = pRectangle->width;
//   TInt height = pRectangle->height;
//   // ��鷶Χ
//   if(left + width > _size.width){
//      width = _size.width - left;
//   }
//   if(top + height > _size.height){
//      height = _size.height - top;
//   }
//   // �������
//   TInt stride = _size.width - width;
//   TColor* pWriter = ((TColor*)_pData->Memory()) + (_size.width * top) + left;
//   for(TInt y = 0; y < height; y++){
//      for(TInt x = 0; x < width; x++){
//         *pWriter++ = color;
//      }
//      pWriter += stride;
//   }
//   return ESuccess;
//}
//
////============================================================
//// <T>����λͼ���塣</T>
////
//// @return ������
////============================================================
//TResult FBitmapCube::Update(){
//   // �ϴ�����
//   _pTexture->Upload(_pData->MemoryC(), DataLength());
//   return ESuccess;
//}
//
////============================================================
//// <T>�ͷ�λͼ���ݡ�</T>
////============================================================
//void FBitmapCube::FreeBitmap(){
//   _pData->Free();
//}
//
////============================================================
//// <T>�ͷ��������ݡ�</T>
////============================================================
//void FBitmapCube::FreeTexture(){
//   _pTexture->Free();
//}

MO_NAMESPACE_END
