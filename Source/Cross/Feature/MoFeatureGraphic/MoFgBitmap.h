#ifndef __MO_FG_BITMAP_H__
#define __MO_FG_BITMAP_H__
//************************************************************

#ifndef __MO_FG_COMMON_H__
#include "MoFgCommon.h"
#endif // __MO_FG_COMMON_H__

#ifndef __MO_FG_CORE_H__
#include "MoFgCore.h"
#endif // __MO_FG_CORE_H__

#ifndef __MO_FG_GRAPHIC_H__
#include "MoFgGraphic.h"
#endif // __MO_FG_GRAPHIC_H__

MO_NAMESPACE_BEGIN

//============================================================
// <T>λͼ�ṹ���ݡ�</T>
//============================================================
struct SBitmapData{
public:
   // λͼ��С
   SIntSize2 size; 
   // λͼ���
   TUint lineStride;
   // ��ת������
   TBool isInvertedY;
   // λͼ���ݵ�ַ
   TByte* pData;
public:
   //------------------------------------------------------------
   // <T>�����ʼλͼ�ṹ���ݡ�<T>
   SBitmapData(){
      lineStride = 0;
      isInvertedY = EFalse;
      MO_CLEAR(pData);
   }
};

//============================================================
// <T>ͼ�θ�ʽ��</T>
//============================================================
enum EImageFormat{
   EImageFormat_A8R8G8B8,
   EImageFormat_B8G8R8A8,
};

//============================================================
// <T>ͼ�Ρ�</T>
//============================================================
class MO_FG_DECLARE FImage : public FInstance
{
   MO_CLASS_DECLARE_INHERITS(FImage, FInstance);
public:
   // ��ʽ
   EImageFormat _formatCd;
   // ��С
   SIntSize2 _size;
   // ԭʼ��С
   SIntSize2 _originSize;
public:
   FImage();
   MO_ABSTRACT ~FImage();
public:
   //------------------------------------------------------------
   // <T>��ø�ʽ��</T>
   MO_INLINE EImageFormat FormatCd(){
      return _formatCd;
   }
   //------------------------------------------------------------
   // <T>���ø�ʽ��</T>
   MO_INLINE void SetFormatCd(EImageFormat formatCd){
      _formatCd = formatCd;
   }
   //------------------------------------------------------------
   // <T>��óߴ硣</T>
   MO_INLINE SIntSize2& Size(){
      return _size;
   }
   //------------------------------------------------------------
   // <T>���ԭʼ�ߴ硣</T>
   MO_INLINE SIntSize2& OriginSize(){
      return _originSize;
   }
   //------------------------------------------------------------
   // <T>������ݿ�ȡ�</T>
   MO_INLINE TInt DataStride(){
      return 4 * _size.width;
   }
   //------------------------------------------------------------
   // <T>������ݳ��ȡ�</T>
   MO_INLINE TInt DataLength(){
      return 4 * _size.width * _size.height;
   }
};

//============================================================
// <T>λͼ��</T>
//============================================================
class MO_FG_DECLARE FBitmapData : public FImage
{
   MO_CLASS_DECLARE_INHERITS(FBitmapData, FImage);
public:
   // ��Χ
   SIntRectangle _rectangle;
   // ����
   FByteStream* _pData;
public:
   FBitmapData(TInt width = 0, TInt height = 0);
   MO_ABSTRACT ~FBitmapData();
public:
   //------------------------------------------------------------
   // <T>���ֻ���ڴ档</T>
   MO_INLINE TByteC* MemoryC(){
      return _pData->MemoryC();
   }
   //------------------------------------------------------------
   // <T>����ڴ档</T>
   MO_INLINE TByte* Memory(){
      return _pData->Memory();
   }
   //------------------------------------------------------------
   // <T>������ݡ�</T>
   MO_INLINE FByteStream* Data(){
      return _pData;
   }
   //------------------------------------------------------------
   // <T>��÷�Χ��</T>
   MO_INLINE SIntRectangle& Rectangle(){
      _rectangle.SetSize(_size.width, _size.height);
      return _rectangle;
   }
public:
   MO_ABSTRACT TResult Resize(TInt width, TInt height);
   TResult UploadData(TByteC* pMemory, TInt width, TInt height);
};

//============================================================
// <T>λͼ���ߡ�</T>
//============================================================
class MO_FG_DECLARE RBitmap{
public:
   //------------------------------------------------------------
   // <T>�ϲ��������ء�</T>
   static MO_INLINE TColor MergeColor(TColor sourceColor, TColor targetColor){
      TInt targetRate = ((targetColor >> 24) & 0xFF);
      //............................................................
      // �����˳�һЩ��ɫ�������� 0xF8 �� С�� 0xF0 ʱ��������
      if(targetRate > 0xF8){
         return targetColor;
      }else if(targetRate < 0x08){
         return sourceColor;
      }
      //............................................................
      // �ֽ���Դ��ɫ
      TInt sourceR = ((sourceColor      ) & 0xFF);
      TInt sourceG = ((sourceColor >> 8 ) & 0xFF);
      TInt sourceB = ((sourceColor >> 16) & 0xFF);
      TInt sourceA = ((sourceColor >> 24) & 0xFF);
      //............................................................
      // �ֽ�Ŀ����ɫ
      TInt targetR = ((targetColor      ) & 0xFF);
      TInt targetG = ((targetColor >> 8 ) & 0xFF);
      TInt targetB = ((targetColor >> 16) & 0xFF);
      TInt targetA = ((targetColor >> 16) & 0xFF);
      //............................................................
      // ������Դ��ɫ����ϲ���ɫ
      TInt sourceRate = 256 - targetRate;
      TInt r = (sourceR * sourceRate + targetR * targetRate) >> 8;
      TInt g = (sourceG * sourceRate + targetG * targetRate) >> 8;
      TInt b = (sourceB * sourceRate + targetB * targetRate) >> 8;
      TInt a = (sourceA * sourceRate + targetA * targetRate) >> 8;
      //............................................................
      // �ϲ���ɫ
      TColor result = r + (g << 8) + (b << 16) + (a << 24);
      return result;
   }
public:
   static TColor MergeColor3(
         SFloatPoint2 position,
         SFloatPoint2 position1, TColor color1,
         SFloatPoint2 position2, TColor color2,
         SFloatPoint2 position3, TColor color3);
public:
   static TInt CalculateFitLength(TInt value);
public:
   static TBool ConvertToBitmapData(SBitmapData& bitmapData, TByteC* pData, TInt dataLength);
   static TBool ConvertToBitmapData(SBitmapData& bitmapData, SIntPoint2& validLoction, SIntSize2& validSize, TByteC* pData, TInt dataLength);
public:
   static TBool Copy(SBitmapData& dest, TInt x, TInt y, SBitmapData& source);
   static TBool Scroll(SBitmapData& bitmapData, TInt scrollX, TInt scrollY);
   static TInt CompressData2(TInt width, TInt height, TByte* pInputData, TByte* pOutputData);
public:
   static TInt DecodeBlock(IDataInput* pInput, IDataOutput* pOutput);
};

//============================================================
// <T>λͼ����</T>
//============================================================
//class MO_FG_DECLARE FBitmap2d : public FBitmap{
//protected:
//   FRenderFlatTexture* _pTexture;
//public:
//   FBitmap2d();
//   MO_ABSTRACT ~FBitmap2d();
//public:
//   //------------------------------------------------------------
//   // <T>�������</T>
//   MO_INLINE FRenderFlatTexture* Texture(){
//      return _pTexture;
//   }
//public:
//   MO_ABSTRACT TResult Setup();
//public:
//   MO_OVERRIDE FRenderTexture* RenderTexture();
//public:
//   MO_OVERRIDE TResult Resize(TInt width, TInt height);
//   MO_OVERRIDE TResult Clear(TColor color);
//   MO_OVERRIDE TResult Clear(TColor color, SIntRectangle* pRectangle);
//   MO_OVERRIDE TResult Update();
//public:
//   MO_OVERRIDE void FreeBitmap();
//   MO_OVERRIDE void FreeTexture();
//};
//
////============================================================
//// <T>λͼ����</T>
////============================================================
//class MO_FG_DECLARE FBitmapCube : public FBitmap{
//protected:
//   FRenderCubeTexture* _pTexture;
//public:
//   FBitmapCube();
//   MO_ABSTRACT ~FBitmapCube();
//public:
//   //------------------------------------------------------------
//   // <T>�������</T>
//   MO_INLINE FRenderCubeTexture* Texture(){
//      return _pTexture;
//   }
//public:
//   MO_ABSTRACT TResult Setup();
//public:
//   MO_OVERRIDE FRenderTexture* RenderTexture();
//public:
//   MO_OVERRIDE TResult Resize(TInt width, TInt height);
//   MO_OVERRIDE TResult Clear(TColor color);
//   MO_OVERRIDE TResult Clear(TColor color, SIntRectangle* pRectangle);
//   MO_OVERRIDE TResult Update();
//public:
//   MO_OVERRIDE void FreeBitmap();
//   MO_OVERRIDE void FreeTexture();
//};

////============================================================
//// <T>��̬λͼ������ӡ�</T>
////============================================================
//class MO_FG_DECLARE FDynamicBitmapCell : public FObject{
//protected:
//   SFloatCoord _coord;
//public:
//   FDynamicBitmapCell();
//   MO_ABSTRACT ~FDynamicBitmapCell();
//public:
//   //------------------------------------------------------------
//   // <T>�������</T>
//   MO_INLINE SFloatCoord Coord(){
//      return _coord;
//   }
//};
////------------------------------------------------------------
//typedef FList<FDynamicBitmapCell*> FDynamicBitmapCellList;
//
////============================================================
//// <T>��̬λͼ����</T>
////============================================================
//class MO_FG_DECLARE FDynamicBitmap : public FBitmap{
//protected:
//   SIntSize2 _limitSize;
//   SIntSize2 _cellSize;
//   SIntSize2 _cellCount;
//   FBytes* _pCells;
//   FDynamicBitmapCellList* _pBitmapCells;
//public:
//   FDynamicBitmap();
//   MO_ABSTRACT ~FDynamicBitmap();
//public:
//   //------------------------------------------------------------
//   // <T>������ƴ�С��</T>
//   MO_INLINE SIntSize2& LimitSize(){
//      return _limitSize;
//   }
//   //------------------------------------------------------------
//   // <T>��ø��Ӵ�С��</T>
//   MO_INLINE SIntSize2& CellSize(){
//      return _cellSize;
//   }
//protected:
//   TBool TestSizeable(TInt offsetX, TInt offsetY, TInt width, TInt height);
//   void SetSizeable(TInt offsetX, TInt offsetY, TInt width, TInt height, TInt value);
//public:
//   void SizeSetup();
//   void SizeClear();
//   FDynamicBitmapCell* SizeAlloc(SFloatRectangle& rectangle, TInt width, TInt height);
//   void SizeFree(FDynamicBitmapCell* pCell);
//};

MO_NAMESPACE_END

//************************************************************
#endif // __MO_FG_BITMAP_H__
