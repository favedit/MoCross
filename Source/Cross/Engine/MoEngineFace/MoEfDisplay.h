#ifndef __MO_EF_DISPLAY_H__
#define __MO_EF_DISPLAY_H__
//************************************************************

#ifndef __MO_EF_COMMON_H__
#include "MoEfCommon.h"
#endif // __MO_EF_COMMON_H__

MO_NAMESPACE_BEGIN

//==========================================================
typedef TInt TControlId;
class FUiControl;

//==========================================================
// <T>��ʾ�ؼ�����</T>
//==========================================================
enum EControlType{
   // δ֪
   EControlType_Unknown,
   // ��̬��ǩ
   EControlType_StaticLabel,
   // ��ǩ
   EControlType_Label,
   // ��ѡ��
   EControlType_Radio,
   // ��ѡ��
   EControlType_Check,
   // ���ֿ�
   EControlType_Number,
   // �༭��
   EControlType_Edit,
   // ���༭��
   EControlType_RichEdit,
   // ����
   EControlType_Button,
   // ������
   EControlType_Slider,
   // ������
   EControlType_ScrollBar,
   // ������
   EControlType_ProgressBar,
   // ����
   EControlType_Calendar,
   // ͼƬ��
   EControlType_PictureBox,
   // �����
   EControlType_FontBox,
   // ������
   EControlType_MovieBox,
   // �����Ŀ
   EControlType_SlotItem,
   // ���
   EControlType_Slot,
   // ���
   EControlType_Panel,
   // ҳ�ؼ�
   EControlType_Page,
   // ��ҳ�ؼ�
   EControlType_PageControl,
   // ѡ����Ŀ
   EControlType_SelectItem,
   // ѡ���б�
   EControlType_Select,
   // �˵�����
   EControlType_MenuItem,
   // �˵�
   EControlType_Menu,
   // �б���Ŀ
   EControlType_ListItem,
   // �б���ͼ
   EControlType_ListView,
   // ���ڵ�����
   EControlType_TreeNodeType,
   // ���ڵ�㼶
   EControlType_TreeNodeLevel,
   // ���ڵ�
   EControlType_TreeNode,
   // ��Ŀ¼
   EControlType_TreeView,
   // ������
   EControlType_GridCell,
   // ���ѡ�����
   EControlType_GridCellCheck,
   // ������ָ���
   EControlType_GridCellNumber,
   // ����ı�����
   EControlType_GridCellText,
   // �����
   EControlType_GridRow,
   // �����
   EControlType_GridColumn,
   // ���ѡ��
   EControlType_GridColumnCheck,
   // �������
   EControlType_GridColumnNumber,
   // ����ı���
   EControlType_GridColumnText,
   // ���
   EControlType_GridView,
   // ԭ��
   EControlType_Widget,
   // ͣ����
   EControlType_Bar,
   // ��
   EControlType_Form,
   // ���
   EControlType_Table,
   // ����
   EControlType_Window,
};

//==========================================================
// <T>��ʾ�ؼ���־</T>
//==========================================================
enum EControlFlag{
   // ֧�ֹ���
   EControlFlag_Link = 0x00000001,
   // ��Ч��
   EControlFlag_Enable = 0x00000002,
   // �ɼ���
   EControlFlag_Visible = 0x00000004,
   // ֧���ڿհ�
   EControlFlag_Margin = 0x00000008,
   // ֧����հ�
   EControlFlag_Padding = 0x00000010,
   // ��ʾ�߿�
   EControlFlag_BorderInner = 0x00000020,
   // ��ʾ�߿�
   EControlFlag_BorderOuter = 0x00000040,
   // ֧������
   EControlFlag_Property = 0x00000080,
   // ֧������
   EControlFlag_Data = 0x00000100,
   // ֧�ֱ߿��
   EControlFlag_LayerBorder = 0x00001000,
   // ֧��ǰ����
   EControlFlag_LayerFore = 0x00002000,
   // ֧�ֱ�����
   EControlFlag_LayerGround = 0x00004000,
   // ֧�ֺ󾰲�
   EControlFlag_LayerBack = 0x00008000,
   // ֧�ֿؼ���ǩ
   EControlFlag_ControlLabel = 0x00010000,
   // ֧�ֿؼ�����
   EControlFlag_ControlNumber = 0x00020000,
   // ֧�ֿؼ�����
   EControlFlag_ControlLines = 0x00040000,
   // ֧�ֿؼ�ҳ��
   EControlFlag_ControlHtml = 0x00080000,
   // ֧������
   EControlFlag_ControlFont = 0x00100000,
   // ֧��ͼ��
   EControlFlag_ControlIcon = 0x00200000,
};

//============================================================
// <T>�ؼ�ͣ����</T>
//============================================================
enum EControlDock{
   // ��
   EControlDock_None = 0,
   // ��
   EControlDock_Left = 1,
   // ����
   EControlDock_LeftTop = 2,
   // ��
   EControlDock_Top = 3,
   // ����
   EControlDock_RightTop = 4,
   // ��
   EControlDock_Right = 5,
   // ����
   EControlDock_RightDown = 6,
   // ��
   EControlDock_Down = 7,
   // ����
   EControlDock_LeftDown = 8,
   // �м�
   EControlDock_Center = 9,
   // ���
   EControlDock_Fill = 10,
   // ���
   EControlDock_Mouse = 11,
};

//==========================================================
// <T>��ʾ�ؼ���־</T>
//==========================================================
enum EControlImageAlign{
   // ��
   EControlImageAlign_None = 0,
   // ��
   EControlImageAlign_Left = 1,
   // ����
   EControlImageAlign_LeftTop = 2,
   // ��
   EControlImageAlign_Top = 3,
   // ����
   EControlImageAlign_RightTop = 4,
   // ��
   EControlImageAlign_Right = 5,
   // ����
   EControlImageAlign_RightBottom = 6,
   // ��
   EControlImageAlign_Bottom = 7,
   // ����
   EControlImageAlign_LeftBottom = 8,
   // �м�
   EControlImageAlign_Center = 9,
   // ��Χ�հ�
   EControlImageAlign_Padding = 10,
   // �Ź���
   EControlImageAlign_Square = 11,
};

//============================================================
// <T>�ؼ��ı����롣</T>
//============================================================
enum EControlTextAlign{
   // δ֪
   EControlTextAlign_None = 0,
   // �����
   EControlTextAlign_Left = 1,
   // �м����
   EControlTextAlign_Center = 2,
   // �Ҷ���
   EControlTextAlign_Right = 3,
};

//============================================================
// <T>��������ʽ��</T>
//============================================================
enum EUiLineStyle{
   EUiLineStyle_Solid,
};

//============================================================
// <T>�����ߡ�</T>
//============================================================
struct MO_EF_DECLARE SUiLine{
public:
   TColor color;
   TInt width;
   EUiLineStyle styleCd;
public:
   SUiLine();
public:
   TResult Unserialize(IDataInput* pInput);
};

//============================================================
// <T>����߿�</T>
//============================================================
struct MO_EF_DECLARE SUiBorder{
public:
   SUiLine left;
   SUiLine top;
   SUiLine right;
   SUiLine bottom;
public:
   SUiBorder();
public:
   //------------------------------------------------------------
   // <T>�ж��Ƿ�Ϊ�ա�</T>
   MO_INLINE TBool IsEmpty(){
      return (left.width == 0) && (top.width == 0) && (right.width == 0) && (bottom.width == 0);
   }
public:
   TResult Unserialize(IDataInput* pInput);
};

//============================================================
// <T>���������塣</T>
//============================================================
struct MO_EF_DECLARE SUiFont{
public:
   TString fontName;
   TInt color;
   TInt size;
   TBool fix;
   TBool bold;
   TBool italic;
   TBool strikeout;
   TBool underline;
public:
   SUiFont();
public:
   TResult Unserialize(IDataInput* pInput);
public:
   void SaveInfo(SFontInfo& info);
};

//============================================================
// <T>����ͼƬ��</T>
//============================================================
struct MO_EF_DECLARE SUiPicture{
public:
   TResourceId resourceId;
   EControlImageAlign alignCd;
   SIntPoint2 location;
   SIntSize2 size;
   SIntPadding padding;
public:
   SUiPicture();
public:
   //------------------------------------------------------------
   // <T>�ж��Ƿ���Ч��</T>
   MO_INLINE TBool IsValid(){
      return (resourceId != 0);
   }
public:
   TResult Unserialize(IDataInput* pInput);
};

//============================================================
// <T>���滭�塣</T>
//============================================================
class MO_EF_DECLARE FUiCanvas : public FBitmapCanvas{
public:
   FUiCanvas();
   MO_ABSTRACT ~FUiCanvas();
public:
   TResult DrawBorder(SIntRectangle* pRectangle, SUiBorder* pBorder);
};

//============================================================
// <T>���湤���ࡣ</T>
//============================================================
class MO_EF_DECLARE RUiUtil{
public:
   static TResult CalculateDock(SIntPoint2* pLocation, SIntRectangle* pClientRect, SIntSize2* pTargetSize, EControlDock dockCd, SIntPadding* pDockPadding = NULL);
};

//============================================================
// <T>�ؼ�����</T>
//============================================================
class MO_EF_DECLARE FUiControl : public FDisplay{
protected:
   EControlType _controlCd;
   TString _className;
   TInt _flags;
   TBool _optionEnable;
   TBool _optionVisible;
   TWideString _label;
   EControlDock _dockCd;
   SIntPadding _margin;
   SIntPadding _padding;
   SUiBorder _borderOuter;
   SUiBorder _borderInner;
   TColor _foreColor;
   SUiPicture _forePicture;
   TColor _backColor;
   SUiPicture _backPicture;
   SIntRectangle _clientRectangle;
   SIntRectangle _statusRectangle;
protected:
   FMaterial* _pMaterial;
   FUiCanvas* _pCanvas;
public:
   FUiControl();
   MO_ABSTRACT ~FUiControl();
public:
   //------------------------------------------------------------
   // <T>��ÿؼ����͡�</T>
   MO_INLINE EControlType ControlCd(){
      return _controlCd;
   }
   //------------------------------------------------------------
   // <T>����������ơ�</T>
   MO_INLINE TCharC* ClassName(){
      return _className;
   }
   //------------------------------------------------------------
   // <T>��ñ�־���ϡ�</T>
   MO_INLINE TInt Flags(){
      return _flags;
   }
   //------------------------------------------------------------
   // <T>���Ա�־��</T>
   MO_INLINE TBool TestFlag(TInt flag){
      return (_flags & flag) == flag;
   }
   //------------------------------------------------------------
   // <T>��ñ�ǩ��</T>
   MO_INLINE TWideCharC* Label(){
      return _label;
   }
   //------------------------------------------------------------
   // <T>���ñ�ǩ��</T>
   MO_INLINE void SetLabel(TWideCharC* pLabel){
      _label = pLabel;
   }
   //------------------------------------------------------------
   // <T>���ͣ�����͡�</T>
   MO_INLINE EControlDock DockCd(){
      return _dockCd;
   }
   //------------------------------------------------------------
   // <T>����ͣ�����͡�</T>
   MO_INLINE void SetDockCd(EControlDock dockCd){
      _dockCd = dockCd;
   }
   //------------------------------------------------------------
   // <T>����ڿհס�</T>
   MO_INLINE SIntPadding& Margin(){
      return _margin;
   }
   //------------------------------------------------------------
   // <T>�����հס�</T>
   MO_INLINE SIntPadding& Padding(){
      return _padding;
   }
   //------------------------------------------------------------
   // <T>�����߿�</T>
   MO_INLINE SUiBorder& BorderOuter(){
      return _borderOuter;
   }
   //------------------------------------------------------------
   // <T>����ڱ߿�</T>
   MO_INLINE SUiBorder& BorderInner(){
      return _borderInner;
   }
public:
   //------------------------------------------------------------
   // <T>���ö�ά���ꡣ</T>
   MO_INLINE void SetLocationInt2(TInt x, TInt y){
      _location.Set((TFloat)x, (TFloat)y);
   }
public:
   FUiControl* ControlGet(TInt index, EControlType controlCd);
public:
   MO_ABSTRACT TResult OnUnserialize(IDataInput* pInput);
   MO_OVERRIDE TResult OnFocusTest(FFocusTester* pTester);
public:
   MO_OVERRIDE TResult Unserialize(IDataInput* pInput);
public:
   MO_OVERRIDE FMaterial* Material();
   MO_OVERRIDE TResult CalculateRectangle(SIntRectangle* pRectangle);
   MO_ABSTRACT TResult CalculateClientRectangle(SIntRectangle* pRectangle);
   MO_OVERRIDE TResult CalculateRenderable(SRenderable& renderable);
   MO_ABSTRACT FUiCanvas* Canvas();
   MO_OVERRIDE TResult Free();
};
//------------------------------------------------------------
typedef FVector<FUiControl*> FUiControlVector;
typedef FList<FUiControl*> FUiControlList;

//============================================================
// <T>�ؼ�������</T>
//============================================================
class MO_EF_DECLARE FUiControlContainer : public FUiControl{
public:
   FUiControlContainer();
   MO_ABSTRACT ~FUiControlContainer();
public:
   MO_OVERRIDE TResult Unserialize(IDataInput* pInput);
};

//============================================================
// <T>�ؼ�����ء�</T>
//============================================================
class MO_EF_DECLARE FUiControlPool : public FPool<FUiControl*>{
protected:
   EControlType _typeCd;
   TCharC* _pClassName;
public:
   FUiControlPool();
   MO_ABSTRACT ~FUiControlPool();
public:
   //------------------------------------------------------------
   // <T>������͡�</T>
   MO_INLINE EControlType TypeCd(){
      return _typeCd;
   }
   //------------------------------------------------------------
   // <T>��������ơ�</T>
   MO_INLINE TCharC* ClassName(){
      return _pClassName;
   }
public:
   MO_VIRTUAL FUiControl* Create() = 0;
public:
   FUiControl* Alloc();
   void Free(FUiControl* pControl);
};
//------------------------------------------------------------
typedef FVector<FUiControlPool*> FUiControlPoolCollection;

//==========================================================
#define MO_DEF_CONTROL_POOL(D, P, C, T, N) \
   class D P : public FUiControlPool{ \
   public: \
      P(){ \
         _typeCd = T; \
         _pClassName = N; \
      } \
   public: \
      FUiControl* Create(){ \
         return MO_CREATE(C); \
      } \
   }; \

//============================================================
// <T>�ؼ�����̨��</T>
//============================================================
class MO_EF_DECLARE FUiControlConsole : public FConsole{
protected:
   // �ؼ�����ؼ���
   FUiControlPoolCollection* _pPools;
public:
   FUiControlConsole();
   MO_ABSTRACT ~FUiControlConsole();
public:
   //------------------------------------------------------------
   // <T>��ÿؼ�����ؼ��ϡ�</T>
   MO_INLINE FUiControlPoolCollection* Pools(){
      return _pPools;
   }
public:
   MO_ABSTRACT TResult Setup();
public:
   MO_ABSTRACT FUiControlPool* PoolFind(EControlType typeCd, TCharC* pClassName = NULL);
   MO_ABSTRACT TResult PoolRegister(FUiControlPool* pPool);
   MO_ABSTRACT TResult PoolUnregister(FUiControlPool* pPool);
public:
   FUiControl* Alloc(EControlType typeCd, TCharC* pClassName = NULL);
   TResult Free(FUiControl* pControl);
public:
   MO_ABSTRACT TResult Dispose();
};

//============================================================
// <T>����������</T>
//============================================================
class MO_EF_DECLARE FUiFrame : public FUiControlContainer{
protected:
   TControlId _code;
   SIntPadding _dockPadding;
public:
   FUiFrame();
   MO_ABSTRACT ~FUiFrame();
public:
   //------------------------------------------------------------
   // <T>��ô��롣</T>
   MO_INLINE TControlId Code(){
      return _code;
   }
   //------------------------------------------------------------
   // <T>��ô��롣</T>
   MO_INLINE void SetCode(TControlId code){
      _code = code;
   }
public:
   MO_OVERRIDE TResult OnUnserialize(IDataInput* pInput);
   MO_OVERRIDE TResult OnPaint();
   MO_ABSTRACT TResult OnShow();
   MO_ABSTRACT TResult OnHide();
public:
   TResult Show();
   TResult Hide();
};
//------------------------------------------------------------
typedef MO_EF_DECLARE FSet<TControlId, FUiFrame*> FUiFrameSet;

//============================================================
// <T>�ؼ�����̨��</T>
//============================================================
class MO_EF_DECLARE FUiFrameConsole : public FConsole{
protected:
   // �ؼ�����ؼ���
   FUiControlPoolCollection* _pPools;
   // ֡����
   FUiFrameSet* _pFrames;
public:
   FUiFrameConsole();
   MO_ABSTRACT ~FUiFrameConsole();
public:
   //------------------------------------------------------------
   // <T>��ÿؼ�����ؼ��ϡ�</T>
   MO_INLINE FUiControlPoolCollection* Pools(){
      return _pPools;
   }
   //------------------------------------------------------------
   // <T>���ҳ�漯�ϡ�</T>
   MO_INLINE FUiFrameSet* Frames(){
      return _pFrames;
   }
public:
   MO_ABSTRACT TResult Setup();
   MO_ABSTRACT TResult Open();
public:
   FUiFrame* Find(TControlId frameId);
public:
   MO_ABSTRACT TResult Dispose();
};

//============================================================
// <T>�ؼ�����̨��</T>
//============================================================
class MO_EF_DECLARE FUiFaceConsole : public FConsole{
protected:
   // �ؼ�����̨
   FUiControlConsole* _pControlConsole;
   // ҳ�����̨
   FUiFrameConsole* _pFrameConsole;
public:
   FUiFaceConsole();
   MO_ABSTRACT ~FUiFaceConsole();
public:
   //------------------------------------------------------------
   // <T>��ÿؼ�����ؼ��ϡ�</T>
   MO_INLINE FUiControlConsole* ControlConsole(){
      return _pControlConsole;
   }
   //------------------------------------------------------------
   // <T>���ҳ�����̨��</T>
   MO_INLINE FUiFrameConsole* FrameConsole(){
      return _pFrameConsole;
   }
public:
   MO_ABSTRACT TResult Setup();
   MO_ABSTRACT TResult Open();
};

//============================================================
// <T>�����������</T>
//============================================================
class MO_EF_DECLARE RFaceManager : public RSingleton<FUiFaceConsole>{
};

MO_NAMESPACE_END

//************************************************************
#endif // __MO_EF_DISPLAY_H__
