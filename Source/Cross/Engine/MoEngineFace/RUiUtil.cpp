#include "MoFmCore.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>����ͣ��λ�á�</T>
//
// @param pLocation ���λ��
// @param clientRect �ͻ�����
// @param targetSize Ŀ���С
// @param dockCd ͣ����ʽ
// @param pDockPadding ͣ�����
// @return ������
//============================================================
TResult RUiUtil::CalculateDock(SIntPoint2* pLocation, SIntRectangle* pClientRect, SIntSize2* pTargetSize, EControlDock dockCd, SIntPadding* pDockPadding){
   MO_CHECK(pLocation, return ENull);
   MO_CHECK(pClientRect, return ENull);
   MO_CHECK(pTargetSize, return ENull);
   // ���ͣ�����
   TInt paddingLeft = 0;
   TInt paddingTop = 0;
   TInt paddingRight = 0;
   TInt paddingBottom = 0;
   if(pDockPadding != NULL){
      paddingLeft = pDockPadding->left;
      paddingTop = pDockPadding->top;
      paddingRight = pDockPadding->right;
      paddingBottom = pDockPadding->bottom;
   }
   // �������
   TInt width = pClientRect->width - pTargetSize->width;
   TInt height = pClientRect->height - pTargetSize->height;
   TInt centerX = width >> 1;
   TInt centerY = height >> 1;
   // ����ͣ��λ��
   switch(dockCd){
      case EControlDock_Left:
         // �����
         pLocation->Set(paddingLeft, centerY);
         break;
      case EControlDock_LeftTop:
         // �����ϱ�
         pLocation->Set(paddingLeft, paddingTop);
         break;
      case EControlDock_Top:
         // ���ϱ�
         pLocation->Set(centerX, paddingTop);
         break;
      case EControlDock_RightTop:
         // �����ϱ�
         pLocation->Set(width - paddingRight, paddingTop);
         break;
      case EControlDock_Right:
         // ���ұ�
         pLocation->Set(width - paddingRight, centerY);
         break;
      case EControlDock_RightDown:
         // �����±�
         pLocation->Set(width - paddingRight, height - paddingBottom);
         break;
      case EControlDock_Down:
         // ���±�
         pLocation->Set(centerX, height - paddingBottom);
         break;
      case EControlDock_LeftDown:
         // �����±�
         pLocation->Set(paddingLeft, height - paddingBottom);
         break;
      case EControlDock_Center:
         // ���м�
         pLocation->Set(centerX, centerY);
         break;
   }
   return ESuccess;
}

MO_NAMESPACE_END
