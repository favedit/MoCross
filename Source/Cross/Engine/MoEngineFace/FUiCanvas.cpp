#include "MoFmCore.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>������滭�塣</T>
//============================================================
FUiCanvas::FUiCanvas(){
}

//============================================================
// <T>�������滭�塣</T>
//============================================================
FUiCanvas::~FUiCanvas(){
}

//============================================================
// <T>���ƽ���߿�</T>
//
// @param color ��ɫ
// @param border �߿�
// @return ������
//============================================================
TResult FUiCanvas::DrawBorder(SIntRectangle* pRectangle, SUiBorder* pborder){
   // ������
   MO_CHECK(pRectangle, return ENull);
   MO_CHECK(pborder, return ENull);
   // ����߽�
   TInt left = pRectangle->left;
   TInt top = pRectangle->top;
   TInt right = pRectangle->Right();
   TInt bottom = pRectangle->Bottom();
   // �����ұ���
   DrawLineVertical(pborder->right.color, top, bottom, right);
   // �����±���
   DrawLineHorizontal(pborder->bottom.color, left, right, bottom);
   // ���������
   DrawLineVertical(pborder->left.color, top, bottom, left);
   // �����ϱ���
   DrawLineHorizontal(pborder->top.color, left, right, top);
   return ESuccess;
}

MO_NAMESPACE_END
