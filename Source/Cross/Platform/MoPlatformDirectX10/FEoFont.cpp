#include <freetype\ftglyph.h>
#include "MoEoFont.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FEoFont, FFont);

//============================================================
// <T>�������塣</T>
//============================================================
FEoFont::FEoFont(){
   RType<FT_Face>::Clear(&_face);
   _pData = MO_CREATE(FBytes);
}

//============================================================
// <T>�������塣</T>
//============================================================
FEoFont::~FEoFont(){
   MO_DELETE(_pData);
}

//============================================================
// <T>�򿪴���</T>
//
// @return ������
//============================================================
TResult FEoFont::Open(){
   FFont::Open();
   // ��������
   RAssetManager::Instance().OpenData(_pData, _assetName);
   // �����������
   FEoFontConsole* pConsole = (FEoFontConsole*)_pConsole;
   FT_Library& library = pConsole->NativeLibrary();
   FT_Error faceResult = FT_New_Memory_Face(library, _pData->MemoryC(), _pData->Length(), 0, &_face);
   //MO_DELETE(pBytes);
   if(faceResult){
      MO_FATAL("Create face failure. (error=%d)", faceResult);
   }
   // �����ַ���С
   FT_Error sizeResult = FT_Set_Pixel_Sizes(_face, _charSize.width, _charSize.height);
   if(sizeResult){
      MO_FATAL("Set pixel size failure. (error=%d)", sizeResult);
   }
   return ESuccess;
}

//============================================================
// <T>�رմ���</T>
//
// @return ������
//============================================================
TResult FEoFont::Close(){
   // �ͷ���Դ
   FT_Done_Face(_face);
   // �رմ���
   FFont::Close();
   return ESuccess;
}

//============================================================
// <T>����һ���ַ���</T>
// @param pBitmapData λͼ����
// @param pFontInfo ������Ϣ
// @param pCharInfo �ַ���Ϣ
// @param x ������
// @param y ������
// @param value ����
//============================================================
TResult FEoFont::InnerDrawChar(EFontDrawMode modeCd, FBitmapData* pBitmapData, SIntRectangle* pRectangle, SFontInfo* pFontInfo, SFontCharInfo* pCharInfo, TInt positionX, TInt positionY, TInt value){
   // ��������
   TInt index = FT_Get_Char_Index(_face, value);
   FT_Load_Glyph(_face, index, FT_LOAD_DEFAULT);
   // �������
   FT_Glyph glyph;
   FT_Error glyphResult = FT_Get_Glyph(_face->glyph, &glyph);
   MO_FATAL_CHECK(glyphResult == 0, return EFailure,
         "Get glyph failure. (error=%d)", glyphResult);
   // ��Ⱦλͼ
   FT_Error bitmapResult = FT_Glyph_To_Bitmap(&glyph, FT_RENDER_MODE_NORMAL, NULL, ETrue);
   MO_FATAL_CHECK(bitmapResult == 0, return EFailure,
         "Glyph to bitmap failure. (error=%d)", bitmapResult);
   //............................................................
   // ���λͼ��Ϣ
   FT_BitmapGlyph glyphBitmap = (FT_BitmapGlyph)glyph;
   TInt charX = glyphBitmap->left;
   TInt charY = _charSize.height - glyphBitmap->top;
   FT_Bitmap& bitmap = glyphBitmap->bitmap;
   TInt bitmapWidth = bitmap.width;
   TInt bitmapHeight = bitmap.rows;
   pCharInfo->left = charX;
   pCharInfo->top = charY;
   pCharInfo->width = charX + bitmapWidth;
   pCharInfo->height = charY + bitmapHeight;
   if(modeCd == EFontDrawMode_Test){
      return ESuccess;
   }
   //............................................................
   // ������Ч��Χ
   TInt width = bitmapWidth;
   TInt right = pRectangle->Right();
   if(positionX + charX + bitmapWidth > right){
      width = right - charX - positionX;
   }
   TInt height = bitmapHeight;
   TInt bottom = pRectangle->Bottom();
   if(positionY + charY + bitmapHeight > bottom){
      height = bottom - charY - positionY;
   }
   //............................................................
   // �ֽ���ɫ
   TInt targetR = ((pFontInfo->color      ) & 0xFF);
   TInt targetG = ((pFontInfo->color >> 8 ) & 0xFF);
   TInt targetB = ((pFontInfo->color >> 16) & 0xFF);
   TInt targetA = ((pFontInfo->color >> 24) & 0xFF);
   //............................................................
   // ���ƴ���
   TByte* pReader = bitmap.buffer;
   TInt memoryStride = pBitmapData->DataStride();
   TByte* pMemory = pBitmapData->Memory() + (memoryStride * (positionY + charY)) + (4 * (positionX + charX));
   for(TInt y = 0 ; y < height; y++){
      TUint32* pWriter = (TUint32*)pMemory;
      for(TInt x = 0 ; x < width; x++){
         TColor sourceColor = *pWriter;
         TInt targetRate = *pReader++;
         TInt sourceRate = 256 - targetRate;
         TInt r = (((sourceColor      ) & 0xFF) * sourceRate + targetR * targetRate) >> 8;
         TInt g = (((sourceColor >> 8 ) & 0xFF) * sourceRate + targetG * targetRate) >> 8;
         TInt b = (((sourceColor >> 16) & 0xFF) * sourceRate + targetB * targetRate) >> 8;
         TInt a = (((sourceColor >> 24) & 0xFF) * sourceRate + targetA * targetRate) >> 8;
         *pWriter++ = r + (g << 8) + (b << 16) + (a << 24);
      }
      pMemory += memoryStride;
   }
   FT_Done_Glyph(glyph);
   MO_CLEAR(glyph);
   return ESuccess;
}

//============================================================
// <T>�����ַ�����</T>
//
// @param pBitmapData λͼ����
// @param pRectangle ��Χ�����Ϊ�գ���Ĭ�Ϸ�ΧΪ����λͼ��
// @param pFontInfo ������Ϣ
// @param pText �ı�����
//============================================================
TResult FEoFont::InnerDrawText(EFontDrawMode modeCd, FBitmapData* pBitmapData, SIntRectangle* pRectangle, SFontInfo* pFontInfo, TWideCharC* pText){
   // ������
   if(modeCd == EFontDrawMode_Draw){
      MO_CHECK(pBitmapData, return ENull);
   }
   MO_CHECK(pText, return ENull);
   // ���ò���
   SFontInfo* pInfo = pFontInfo;
   if(pInfo == NULL){
      pInfo = &_fontInfo;
   }
   TInt startX = 0;
   TInt startY = 0;
   if(modeCd == EFontDrawMode_Draw){
      if(pRectangle == NULL){
         pRectangle = &pBitmapData->Rectangle();
      }
      startX = pRectangle->left;
      startY = pRectangle->top;
   }
   //............................................................
   // ������б
   FT_Matrix matrix;
   matrix.xx = 0x10000L;
   matrix.yy = 0x10000L;
   matrix.yx = 0;
   if(pInfo->italic){
      matrix.xy = (FT_Fixed)(0.5f * 0x10000L);
   }else{
      matrix.xy = 0;
   }
   FT_Set_Transform(_face, &matrix, 0);
   //............................................................
   // �����ַ���
   TInt width = 0;
   TInt height = 0;
   TInt minLeft = _charSize.width;
   TInt minTop = _charSize.height;
   TInt x = startX;
   TInt y = startY;
   SFontCharInfo charInfo;
   TBool fix = pInfo->fix;
   TInt length = RWideString::Length(pText);
   for(TInt n = 0; n < length; n++){
      TInt value = pText[n];
      // ���������ַ�
      if(value == '\r'){
         continue;
      }
      // ����س�
      if(value == '\n'){
         x = startX;
         y += _charSize.height;
         continue;
      }
      // ��������(3�ֿ�)
      if(value == '\t'){
         x += _charSize.width * 3;
         continue;
      }
      // �����ַ�
      InnerDrawChar(modeCd, pBitmapData, pRectangle, pInfo, &charInfo, x, y, value);
      // �����¸��ַ�λ��
      if(fix){
         x += _charSize.width;
      }else{
         x += charInfo.width;
      }
      // ���㷶Χ
      if(charInfo.top < minTop){
         minTop = charInfo.top;
      }
      if(charInfo.left < minLeft){
         minLeft = charInfo.left;
      }
      TInt offsetX = x - startX;
      if(offsetX > width){
         width = offsetX;
      }
      TInt offsetY = y + charInfo.height - startY;
      if(offsetY > height){
         height = offsetY;
      }
   }
   // ���������Ϣ
   if(pFontInfo != NULL){
      pFontInfo->width = width + minLeft;
      pFontInfo->height = height + minTop;
   }
   return ESuccess;
}

//============================================================
// <T>�����ַ�����С��</T>
//
// @param pFontInfo ������Ϣ
// @param pText �ı�����
//============================================================
TResult FEoFont::CalculateAnsiSize(SFontInfo* pFontInfo, TAnsiCharC* pText){
   // �ַ�ת��
   TString16 value;
   value.Assign8(pText);
   TChar16C* pWideText = value.MemoryC();
   // ����ߴ�
   return InnerDrawText(EFontDrawMode_Test, NULL, NULL, pFontInfo, pWideText);
}

//============================================================
// <T>�����ַ�����С��</T>
//
// @param pFontInfo ������Ϣ
// @param pText �ı�����
//============================================================
TResult FEoFont::CalculateWideSize(SFontInfo* pFontInfo, TWideCharC* pText){
   return InnerDrawText(EFontDrawMode_Test, NULL, NULL, pFontInfo, pText);
}

//============================================================
// <T>�����ַ�����</T>
//
// @param pBitmapData λͼ����
// @param pRectangle ��Χ�����Ϊ�գ���Ĭ�Ϸ�ΧΪ����λͼ��
// @param pFontInfo ������Ϣ
// @param pText �ı�����
//============================================================
TResult FEoFont::DrawAnsiText(FBitmapData* pBitmapData, SIntRectangle* pRectangle, SFontInfo* pFontInfo, TAnsiCharC* pText){
   // �ַ�ת��
   TString16 value;
   value.Assign8(pText);
   TChar16C* pWideText = value.MemoryC();
   // ��������
   return InnerDrawText(EFontDrawMode_Draw, pBitmapData, pRectangle, pFontInfo, pWideText);
}

//============================================================
// <T>�����ַ�����</T>
//
// @param pBitmapData λͼ����
// @param pRectangle ��Χ�����Ϊ�գ���Ĭ�Ϸ�ΧΪ����λͼ��
// @param pFontInfo ������Ϣ
// @param pText �ı�����
//============================================================
TResult FEoFont::DrawWideText(FBitmapData* pBitmapData, SIntRectangle* pRectangle, SFontInfo* pFontInfo, TWideCharC* pText){
   return InnerDrawText(EFontDrawMode_Draw, pBitmapData, pRectangle, pFontInfo, pText);
}

MO_NAMESPACE_END
