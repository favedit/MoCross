#include "MoEgDisplay.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>����λͼ���塣</T>
//============================================================
FBitmapCanvas::FBitmapCanvas(){
}

//============================================================
// <T>����λͼ���塣</T>
//============================================================
FBitmapCanvas::~FBitmapCanvas(){
}

//============================================================
// <T>���ô���</T>
//
// @return ������
//============================================================
TResult FBitmapCanvas::Setup(){
   return FBitmap::Setup();
}

//============================================================
// <T>���´���</T>
//
// @return ������
//============================================================
TResult FBitmapCanvas::Update(){
   return FBitmap::Update();
}

//============================================================
// <T>����һ��ֱ�ߡ�</T>
//
// @param color ��ɫ
// @param x1 ��ʼ������
// @param y1 ��ʼ������
// @param x2 ����������
// @param y2 ����������
// @return ������
//============================================================
TResult FBitmapCanvas::DrawLine(TColor color, TInt x1, TInt y1, TInt x2, TInt y2){
   // �������
   TInt width = _size.width;
   TInt height = _size.height;
   TColor* pColors = (TColor*)_data->Memory();
   // ��������
   TInt k = 0;
   TInt x12 = x2 - x1;
   TInt y12 = y2 - y1;
   if(x12 * y12 < 0){
      k = 1;
   }
   TInt x = x1;
   TInt y = y1;
   TInt dx = MO_LIB_ABS(x12);
   TInt dy = MO_LIB_ABS(y12);
   TBool f = 0;
   if(dx < dy){
      f = 1;
      MO_LIB_SWAP(TInt,dx,dy);
      MO_LIB_SWAP(TInt,x,y);
   }
   TInt e = (dy << 1) - dx;
   // ���ƴ���
   for(TInt n = 0; n <= dx; n++){
      if(f == 1){
         TInt index = x * width + y;
         pColors[index] = color;
      }else{
         TInt index = y * width + x;
         pColors[index] = color;
      }
      x++;
      if(0 < e){
         e = e + ((dy - dx) << 1);
         if(0 == k){
            y++;
         }else{
            y--;
         }
      }else{
         e = e + (dy << 1);
      }
   }
   return ESuccess;
}

//============================================================
// <T>����һ������ֱ�ߡ�</T>
//
// @param color ��ɫ
// @param x1 ��ʼ������
// @param x2 ����������
// @param y ������
// @return ������
//============================================================
TResult FBitmapCanvas::DrawLineHorizontal(TColor color, TInt x1, TInt x2, TInt y){
   // �������
   TInt width = _size.width;
   TColor* pColors = (TColor*)_data->Memory();
   // ��ȡ��Ч����
   TInt bottom = _clipRectangle.Bottom();
   TInt right = _clipRectangle.Right();
   TInt left = _clipRectangle.left;
   TInt top = _clipRectangle.top;
   // �ж��Ƿ񳬳����巶Χ
   if((y < top) || (y > bottom)){
      return EFailure;
   }
   if(x1 < left){
      x1 = left;
   }
   if(x2 >= right){
      x2 = right;
   }
   // ���ƺ���ֱ��
   TInt index = width * y + x1;
   for(TInt n = x1; n <= x2; n++){
      pColors[index++] = color;
   }
   return ESuccess;
}

//============================================================
// <T>����һ������ֱ�ߡ�</T>
//
// @param color ��ɫ
// @param y1 ��ʼ������
// @param y2 ����������
// @param x ������
// @return ������
//============================================================
TResult FBitmapCanvas::DrawLineVertical(TColor color, TInt y1, TInt y2, TInt x){
   // �������
   TInt width = _size.width;
   TColor* pColors = (TColor*)_data->Memory();
   // �����Ч����
   TInt bottom = _clipRectangle.Bottom();
   TInt right = _clipRectangle.Right();
   TInt left = _clipRectangle.left;
   TInt top = _clipRectangle.top;
   // �ж��Ƿ񳬳����巶Χ
   if((x < left) || (x > right)){
      return EFailure;
   }
   if(y1 < top){
      y1 = top;
   }
   if(y2 >= bottom){
      y2 = bottom;
   }
   // ��������ֱ��
   TInt index = width * y1 + x;
   for(TInt n = y1; n <= y2; n++){
      pColors[index] = color;
      index += width;
   }
   return ESuccess;
}

//============================================================
// <T>����һ�������Ρ�</T>
//
// @param color ��ɫ
// @param x1 ��һ���������
// @param y1 ��һ����������
// @param x2 �ڶ���������
// @param y2 �ڶ�����������
// @param x3 ������������
// @param y3 ��������������
// @return ������
//============================================================
TResult FBitmapCanvas::DrawTriangle(TColor color, TInt x1, TInt y1, TInt x2, TInt y2, TInt x3, TInt y3){
   // ���Ƶ�һ����
   DrawLine(color, x1, y1, x2, y2);
   // ���Ƶڶ�����
   DrawLine(color, x2, y2, x3, y3);
   // ���Ƶ�������
   DrawLine(color, x1, y1, x3, y3);
   return ESuccess;
}

//============================================================
// <T>����һ�����Ρ�</T>
//
// @param color ��ɫ
// @param x1 ��ʼ������
// @param y1 ��ʼ������
// @param x2 ����������
// @param y2 ����������
// @return ������
//============================================================
TResult FBitmapCanvas::DrawRectangle(TColor color, TInt x1, TInt y1, TInt x2, TInt y2){
   TInt width = _size.width;
   TInt height = _size.height;
   TColor* pColors = (TColor*)_data->Memory();
   // ������߿�
   DrawLineVertical(color, y1, y2, x1);
   // �����ϱ߿�
   DrawLineHorizontal(color, x1, x2, y1);
   // �����ұ߿�
   DrawLineVertical(color, y1, y2, x2);
   // �����±߿�
   DrawLineHorizontal(color, x1, x2, y2);
   return ESuccess;
}

//============================================================
// <T>����һ�����Ρ�</T>
//
// @param color ��ɫ
// @param rectangle ����
// @return ������
//============================================================
TResult FBitmapCanvas::DrawRectangle(TColor color, SIntRectangle* pRectangle){
   MO_CHECK(pRectangle, return ENull);
   return DrawRectangle(color, pRectangle->left, pRectangle->top, pRectangle->Right(), pRectangle->Bottom());
}

//============================================================
// <T>���һ�������Ρ�</T>
//
// @param color ��ɫ
// @param x1 ��һ���������
// @param y1 ��һ����������
// @param x2 �ڶ���������
// @param y2 �ڶ�����������
// @param x3 ������������
// @param y3 ��������������
// @return ������
//============================================================
TResult FBitmapCanvas::FillTriangle(TColor color, TInt x1, TInt y1, TInt x2, TInt y2, TInt x3, TInt y3){
   // �������
   TInt width = _size.width;
   TColor* pColors = (TColor*)_data->Memory();
   // ���Ƶ�һ����
   DrawLine(color, x1, y1, x2, y2);
   // ���Ƶڶ�����
   DrawLine(color, x2, y2, x3, y3);
   // ���Ƶ�������
   DrawLine(color, x1, y1, x3, y3);
   // �������
   TInt minX;
   TInt minY;
   TInt maxX;
   TInt maxY;
   minX = MO_LIB_MIN(x1,x2);
   minX = MO_LIB_MIN(x3,minX);
   maxX = MO_LIB_MAX(x1,x2);
   maxX = MO_LIB_MAX(x3,maxX);
   minY = MO_LIB_MIN(y1,y2);
   minY = MO_LIB_MIN(y3,minY);
   maxY = MO_LIB_MAX(y1,y2);
   maxY = MO_LIB_MAX(y3,maxY);
   // ��ȡ��ʼλ������
   //TInt index = minY * width +minX;
   TInt beginX;
   TInt endX;
   // ��ʼ���������
   for(TInt y = minY; y <= maxY; y++){
      for(TInt x = minX; x <= maxX; x++){
         TInt index = y * width + x;
         TColor nowColor = pColors[index];
         if(color == nowColor){
            beginX = x;
            break;
         }
         index+=width;
      }
      for(TInt x = maxX; x >= minX; x--){
         TInt index =y * width +x;
         TColor nowColor = pColors[index];
         if(color == nowColor){
            endX = x;
            break;
         }
         index+=width;
      }
      if(beginX != endX){
         TInt nowIndex= y * width +beginX;
         for(TInt x = beginX; x <= endX; x++){
            pColors[nowIndex] = color;
            nowIndex ++;
         }
      }
   }
   return ESuccess;
}

//============================================================
// <T>���һ�����Ρ�</T>
//
// @param color ��ɫ
// @param x1 ��ʼ������
// @param y1 ��ʼ������
// @param x2 ����������
// @param y2 ����������
// @return ������
//============================================================
TResult FBitmapCanvas::FillRectangle(TColor color, TInt x1, TInt y1, TInt x2, TInt y2){
   // �������
   TInt width = _size.width;
   TColor* pColors = (TColor*)_data->Memory();
   // ��ȡ��Ч����
   TInt right = _clipRectangle.Right();
   TInt bottom = _clipRectangle.Bottom();
   TInt left = _clipRectangle.left;
   TInt top = _clipRectangle.top;
   // �ж�λ��
   if(x1 > x2){
      MO_LIB_SWAP(TInt, x1, x2);
   }
   if(y1 > y2){
      MO_LIB_SWAP(TInt, y1, y2);
   }
   // �ж��Ƿ񳬳���Χ
   if(x1 < left){
      x1 = left;
   }
   if(y1 < top){
      y1 = top;
   }
   if(x2 > right){
      x2 = right;
   }
   if(y2 > bottom){
      y2 = bottom;
   }
   // ��ȡ��ʼλ������
   TInt index = width * y1 + x1;
   // ����һ��
   TInt w = x2 - x1;
   TColor* pLine = pColors + index;
   for(TInt i = 0; i <= w; i++){
      *pLine++ = color;
   }
   // ���ʣ����
   TInt length = sizeof(TColor) * (x2 - x1 + 1);
   TInt beginIndex = index + width;
   for(TInt n = y1+1; n <= y2; n++){
      MO_LIB_MEMORY_COPY(pColors + beginIndex, length, pColors + index, length);
      beginIndex += width;
   }
   return ESuccess;
}

//============================================================
// <T>���һ�����Ρ�</T>
//
// @param color ��ɫ
// @param rectangle ����
// @return ������
//============================================================
TResult FBitmapCanvas::FillRectangle(TColor color, SIntRectangle* pRectangle){
   MO_CHECK(pRectangle, return ENull);
   return FillRectangle(color, pRectangle->left, pRectangle->top, pRectangle->Right(), pRectangle->Bottom());
}

//============================================================
// <T>����һ��λͼ��</T>
//
// @param pBitmapData λͼ
// @param x ������
// @param y ������
// @return ������
//============================================================
TResult FBitmapCanvas::DrawBitmap(FBitmapData* pBitmapData, TBool alpha, TInt x, TInt y){
   DrawBitmap(pBitmapData, alpha, NULL, x, y);
   return ESuccess;
}

//============================================================
// <T>����һ��λͼ��</T>
//
// @param pBitmapData λͼ
// @param pSourceRectangle ��Դ��Χ
// @param x ������
// @param y ������
// @return ������
//============================================================
TResult FBitmapCanvas::DrawBitmap(FBitmapData* pBitmapData, TBool alpha, SIntRectangle* pSourceRectangle, TInt x, TInt y){
   // �������
   TInt width = _size.width;
   TInt height = _size.height;
   TColor* pColors = (TColor*)_data->Memory();
   // ��ȡ��Χ
   TInt right = _clipRectangle.Right();
   TInt bottom = _clipRectangle.Bottom();
   TInt left = _clipRectangle.left;
   TInt top = _clipRectangle.top;
   // ���λͼ
   TColor* pBitmapColors =  (TColor*)pBitmapData->Memory();
   TInt bitmapWidth = pBitmapData->Size().width;
   TInt bitmapHeight = pBitmapData->Size().height;
   TInt bitmapRight;
   TInt bitmapBottom;
   if(NULL == pSourceRectangle){
      bitmapRight = x + bitmapWidth;
      bitmapBottom = y + bitmapHeight;
   }else {
      bitmapRight = pSourceRectangle->Right();
      bitmapBottom = pSourceRectangle->Bottom();
   }
   // ��ȡ��Ч��ʼλ�úͽ���λ��
   if(x < left){
      x = left;
   }
   if(y < top){
      y = top;
   }
   if(bitmapRight > right){
      bitmapRight = right;
   }
   if(bitmapBottom > bottom){
      bitmapBottom = bottom;
   }
   // ��ȡ��Ч��Ⱥ���Ч�߶�
   TInt bitmapValidWidth;
   TInt bitmapValidHeight;
   if(NULL == pSourceRectangle){
      bitmapValidWidth = bitmapRight - x;
      bitmapValidHeight = bitmapBottom - y;
   }else {
      bitmapValidWidth = pSourceRectangle->width;
      bitmapValidHeight = pSourceRectangle->height;
   }
   // �ж��Ƿ���л���
   if(bitmapValidWidth <= 0 || bitmapValidHeight <= 0){
      return EFailure;
   }
   // ��ʼ����
   if(alpha){
      TInt targetIndex = width * y + x;
      TInt sourceIndex = bitmapWidth * pSourceRectangle->top + pSourceRectangle->left;
      for(TInt n = 0; n < bitmapValidHeight; n++){
         TColor* pTarget = pColors + targetIndex;
         TColor* pSource = pBitmapColors + sourceIndex;
         for(TInt m = 0; m < bitmapValidWidth; m++){
            *pTarget++ = RBitmap::MergeColor(*pTarget, *pSource++);
         }
         targetIndex += width;
         sourceIndex += bitmapWidth;
      }
   } else {
      TInt length = sizeof(TColor) * (bitmapValidWidth + 1);
      TInt targetIndex = width * y + x;
      TInt sourceIndex = bitmapWidth * pSourceRectangle->top + pSourceRectangle->left;
      for(TInt n = 0; n < bitmapValidHeight; n++){
         MO_LIB_MEMORY_COPY(pColors + targetIndex, length, pBitmapColors + sourceIndex, length);
         targetIndex += width;
         sourceIndex += bitmapWidth;
      }
   }
   return ESuccess;
}

//============================================================
// <T>����һ��λͼ��</T>
//
// @param pBitmapData λͼ
// @param alpha �Ƿ�͸��
// @param pSourceRectangle ��Դ��Χ
// @param pTargetRectangle Ŀ�귶Χ
//============================================================
TResult FBitmapCanvas::DrawBitmap(FBitmapData* pBitmapData, TBool alpha, SIntRectangle* pSourceRectangle, SIntRectangle* pTargetRectangle){
   // ��ȡ����
   TInt width = _size.width;
   TColor* pColors = (TColor*)_data->Memory();
   // ��ȡ��Χ
   TInt right = _clipRectangle.Right();
   TInt bottom = _clipRectangle.Bottom();
   TInt left = _clipRectangle.left;
   TInt top = _clipRectangle.top;
   // ��ȡλͼ
   TColor* pBitmapColors =  (TColor*)pBitmapData->Memory();
   TInt bitmapWidth = pBitmapData->Size().width;
   // ��ȡ��Դ����
   TInt sourceWidth = pSourceRectangle->width;
   TInt sourceHeight = pSourceRectangle->height;
   TInt sourceleft = pSourceRectangle->left;
   TInt sourceTop = pSourceRectangle->top;
   TInt sourceRight = pSourceRectangle->Right();
   TInt sourceBottom = pSourceRectangle->Bottom();
   // ��ȡĿ�����
   TInt targetWidth = pTargetRectangle->width;
   TInt targetHeight = pTargetRectangle->height;
   TInt targetLeft = pTargetRectangle->left;
   TInt targetTop = pTargetRectangle->top;
   TInt targetRight = pTargetRectangle->Right();
   TInt targetBottom = pTargetRectangle->Bottom();
   // ��ȡ��Чλ��
   if(targetLeft < left){
      targetLeft = left;
   }
   if(targetTop < top){
      targetTop = top;
   }
   if(targetRight > right ){
      targetRight = right;
   }
   if(targetBottom > bottom){
      targetBottom = bottom;
   }
   // ��ȡ����
   TFloat widthRatio = (TFloat)sourceWidth / targetWidth;
   TFloat heightRatio = (TFloat)sourceHeight / targetHeight;
   // �������ص��õ�����
   TInt maxX = targetRight - targetLeft;
   TInt maxY = targetBottom - targetTop;
   for(TInt y = 0; y <= maxY; y++){
      TFloat sourceY = heightRatio * y;
      for(TInt x = 0; x <= maxX; x++){
         TFloat sourceX = widthRatio * x;
         // ��ȡ��ǰ���ص�����
         TInt locationX = ((TInt)sourceX) + sourceleft;
         TInt locationY = (TInt)sourceY + sourceTop;
         TInt bitmapIndex = locationY * bitmapWidth + locationX;
         TInt index = (y + targetTop) * width + (x + targetLeft);
         pColors[index] = pBitmapColors[bitmapIndex];  
      }
   }
   return ESuccess;
}

//============================================================
// <T>����һ��9����λͼ��</T>
//
// @param pBitmapData λͼ
// @param pSourcePadding ��Դ���
// @param pTargetRectangle Ŀ�귶Χ
// @return ������
//============================================================
TResult FBitmapCanvas::DrawBitmapGrid9(FBitmapData* pBitmapData, TBool alpha, SIntPadding* pSourcePadding, SIntRectangle* pTargetRectangle){
   // ��ȡλͼ����
   TInt bitmapWidth = pBitmapData->OriginSize().width;
   TInt bitmapHeight = pBitmapData->OriginSize().height;
   // ��ȡĿ���������
   TInt targetWidth = pTargetRectangle->width;
   TInt targetHeight = pTargetRectangle->height;
   TInt targetTop = pTargetRectangle->top;
   TInt targetLeft = pTargetRectangle->left;
   TInt targetRight = pTargetRectangle->Right();
   TInt targetBottom = pTargetRectangle->Bottom();
   // ��ȡƫ����
   TInt paddingLeft = pSourcePadding->left;
   TInt paddingTop = pSourcePadding->top;
   TInt paddingRight = pSourcePadding->right;
   TInt paddingBottom = pSourcePadding->bottom;
   // ��ȡ��Դ�м���δ�С
   TInt sourceCenterWidth = bitmapWidth - paddingLeft -paddingRight;
   TInt sourceCenterHeight = bitmapHeight - paddingTop - paddingBottom;
   // ��ȡ��Դ�м���ν�����λ��
   TInt sourceRightBottomX = bitmapWidth -paddingRight;
   TInt sourceRightBottomY = bitmapHeight -paddingBottom;
   // ��ȡĿ���м���δ�С
   TInt targetCenterWidth = targetWidth - paddingLeft -paddingRight;
   TInt targetCenterHeight = targetHeight - paddingTop - paddingBottom;
   TInt targetCenterLeft = targetLeft + paddingLeft;
   TInt targetCenterTop = targetTop + paddingTop;
   // ��ȡĿ���м���ν�����λ��
   TInt targetRightBottomX = targetLeft + targetWidth -paddingRight;
   TInt targetRightBottomY = targetTop + targetHeight -paddingBottom;
   // ��������
   if (0 != paddingLeft && 0 != paddingTop){
      SIntRectangle leftTopRectanle(0, 0, paddingLeft, paddingTop);
      DrawBitmap(pBitmapData, alpha, &leftTopRectanle, targetLeft, targetTop);
   }
   // ��������
   if(0 != paddingRight && 0 != paddingTop){
      SIntRectangle rightTopRectanle(sourceRightBottomX, 0, paddingRight, paddingTop);
      DrawBitmap(pBitmapData, alpha, &rightTopRectanle, targetRightBottomX, targetTop);
   }
   // ��������
   if(0 != paddingRight && 0 != paddingBottom){
      SIntRectangle rightBottomRectanle(sourceRightBottomX, sourceRightBottomY, paddingRight, paddingBottom);
      DrawBitmap(pBitmapData, alpha, &rightBottomRectanle, targetRightBottomX, targetRightBottomY);
   }
   // ��������
   if(0 != paddingLeft && 0 != paddingBottom){
      SIntRectangle leftBottomRectanle(0, sourceRightBottomY, paddingLeft, paddingBottom);
      DrawBitmap(pBitmapData, alpha, &leftBottomRectanle, targetLeft, targetRightBottomY);
   }
   // ��������
   if(0 != targetCenterWidth && 0 != paddingTop){
      SIntRectangle centerTopSourceRectanle(paddingLeft, 0, sourceCenterWidth, paddingTop);
      SIntRectangle centerTopTargetRectanle(targetCenterLeft, targetTop, targetCenterWidth, paddingTop);
      DrawBitmap(pBitmapData, alpha, &centerTopSourceRectanle, &centerTopTargetRectanle);
   }
   // ��������
   if(0 != paddingRight && 0 != targetCenterHeight){
      SIntRectangle centerRightSourceRectanle(sourceRightBottomX, paddingTop, paddingRight, sourceCenterHeight);
      SIntRectangle centerRightTargetRectanle(targetCenterLeft + targetCenterWidth, targetCenterTop, paddingRight, targetCenterHeight);
      DrawBitmap(pBitmapData, alpha, &centerRightSourceRectanle, &centerRightTargetRectanle);
   }
   // ��������
   if(0 != targetCenterWidth && 0 != paddingBottom){
      SIntRectangle centerBottomSourceRectanle(paddingLeft,sourceRightBottomY,sourceCenterWidth,paddingBottom);
      SIntRectangle centerBottomTargetRectanle(targetCenterLeft, targetCenterTop + targetCenterHeight, targetCenterWidth, paddingBottom);
      DrawBitmap(pBitmapData, alpha, &centerBottomSourceRectanle, &centerBottomTargetRectanle);
   }
   // ��������
   if(0 != paddingLeft && 0 != sourceCenterHeight){
      SIntRectangle centerLeftSourceRectanle(0, paddingTop, paddingLeft, sourceCenterHeight);
      SIntRectangle centerLeftTargetRectanle(targetLeft, targetCenterTop, paddingLeft, targetCenterHeight);
      DrawBitmap(pBitmapData, alpha, &centerLeftSourceRectanle, &centerLeftTargetRectanle);
   }
   // ������
   if(0 != targetCenterWidth && 0 != targetCenterHeight){
      SIntRectangle centerSourceRectanle(paddingLeft, paddingTop, sourceCenterWidth, sourceCenterHeight);
      SIntRectangle centerTargetRectanle(targetCenterLeft, targetCenterTop, targetCenterWidth, targetCenterHeight);
      DrawBitmap(pBitmapData, alpha, &centerSourceRectanle, &centerTargetRectanle);
   }
   return ESuccess;
}

//============================================================
// <T>����һ��9����λͼ��</T>
//
// @param pBitmapData λͼ
// @param pSourceRectangle ��Դ��Χ
// @param pSourcePadding ��Դ���
// @param pTargetRectangle Ŀ�귶Χ
// @return ������
//============================================================
TResult FBitmapCanvas::DrawBitmapGrid9(FBitmapData* pBitmapData, TBool alpha, SIntRectangle* pSourceRectangle, SIntPadding* pSourcePadding, SIntRectangle* pTargetRectangle){
   return ESuccess;
}

MO_NAMESPACE_END
