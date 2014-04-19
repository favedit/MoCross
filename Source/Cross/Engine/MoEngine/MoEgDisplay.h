#ifndef __MO_EG_DISPLAY_H__
#define __MO_EG_DISPLAY_H__
//************************************************************

#ifndef __MO_EG_COMMON_H__
#include "MoEgCommon.h"
#endif // __MO_EG_COMMON_H__

#ifndef __MO_EG_CORE_H__
#include "MoEgCore.h"
#endif // __MO_EG_CORE_H__

MO_NAMESPACE_BEGIN

//============================================================
// �ӿڶ���
class IHoverable;
class IFocusable;
class IDragable;
// ���Ͷ���
class FComponent;
typedef MO_EG_DECLARE FObjects<FComponent*> FComponentCollection;
class FDrawable;
typedef MO_EG_DECLARE FObjects<FDrawable*> FDrawableCollection;
class FRenderable2;
class FDisplay;
typedef MO_EG_DECLARE FObjects<FDisplay*> FDisplayCollection;
typedef MO_EG_DECLARE FList<FDisplay*> FDisplayList;
class FStageFrame;
class FStage;
class FParticleController;
class FFocusTester;

//==========================================================
// <T>�������</T>
//==========================================================
enum EComponent{
   // ����
   EComponent_Object = 0x0001,
   // ���
   EComponent_Component = 0x0002,
   // �ɻ��ƶ���
   EComponent_Drawable = 0x0004,
   // �ɻ��ƶ����
   EComponent_DrawableLayer = 0x0008,
   // ��Ⱦ����
   EComponent_Renderable = 0x0010,
   // �ɻ��������
   EComponent_Mouseable = 0x0020,
   // �ɻ���ȵ����
   EComponent_Hoverable = 0x0040,
   // �ɻ�ý������
   EComponent_Focusable = 0x0080,
   // ���ƶ�����
   EComponent_Move = 0x0100,
   // ��ʾ��̨
   EComponent_Stage = 0x0200,
   // ��ʾ����
   EComponent_Display = 0x0400,
   // ��ʾ����
   EComponent_DisplayContainer = 0x0800,
   // �ռ����
   EComponent_Spatial = 0x1000,
   // �ؼ�����
   EComponent_Control = 0x2000,
   // �ؼ�����
   EComponent_ControlContainer = 0x4000,
   // ��������
   EComponent_Frame = 0x8000,
};

//==========================================================
// <T>��ʾ����</T>
//==========================================================
enum EDisplay{
   // ����
   EDisplay_2d = 1,
   // ���
   EDisplay_3d = 2,
};
//----------------------------------------------------------
typedef TInt TComponentType;
typedef TInt TDisplayType;

//==========================================================
// <T>��ʾ������</T>
//==========================================================
enum EDisplayLayer{
   // δ֪
   EDisplayLayer_Unknown = 0,
   // �����
   EDisplayLayer_Face = 1,
   // ǰ����
   EDisplayLayer_Fore = 2,
   // ���Ӳ�
   EDisplayLayer_Particle = 3,
   // �����
   EDisplayLayer_Sprite = 4,
   // �����
   EDisplayLayer_Terrain = 5,
   // ������
   EDisplayLayer_Ground = 6,
   // �󾰲�
   EDisplayLayer_Back = 7,
};

//==========================================================
// <T>��̨֡����</T>
//==========================================================
enum EStageFrame{
   // δ֪
   EStageFrame_Unknown = 0,
   // ����֡
   EStageFrame_Ground = 1,
   // ����֡
   EStageFrame_Scene = 2,
   // ����֡
   EStageFrame_Face = 3,
};

//============================================================
// <T>����ӿڡ�</T>
//============================================================
class MO_EG_DECLARE ICanvas{
public:
   //------------------------------------------------------------
   // <T>��������ӿڡ�</T>
   MO_ABSTRACT ~ICanvas(){
   }
public:
   MO_VIRTUAL TResult Update() = 0;
};

//============================================================
// <T>�ɻ�����ӿڡ�</T>
//============================================================
class MO_EG_DECLARE IMouseable{
public:
   //------------------------------------------------------------
   // <T>�����ɻ�����ӿڡ�</T>
   MO_ABSTRACT ~IMouseable(){
   }
public:
   MO_VIRTUAL TResult MouseDown(SMouseEvent* pEvent) = 0;
   MO_VIRTUAL TResult MouseMove(SMouseEvent* pEvent) = 0;
   MO_VIRTUAL TResult MouseUp(SMouseEvent* pEvent) = 0;
};

//============================================================
// <T>�ɻ�ý���ӿڡ�</T>
//============================================================
class MO_EG_DECLARE IFocusable{
public:
   //------------------------------------------------------------
   // <T>�����ɻ�ý���ӿڡ�</T>
   MO_ABSTRACT ~IFocusable(){
   }
public:
   MO_VIRTUAL TResult FocusEnter() = 0;
   MO_VIRTUAL TResult FocusLeave() = 0;
};

//============================================================
// <T>�ɻ���ȵ�ӿڡ�</T>
//============================================================
class MO_EG_DECLARE IHoverable{
public:
   //------------------------------------------------------------
   // <T>�����ɻ���ȵ�ӿڡ�</T>
   MO_ABSTRACT ~IHoverable(){
   }
public:
   MO_VIRTUAL TResult HoverEnter() = 0;
   MO_VIRTUAL TResult HoverLeave() = 0;
};

//============================================================
// <T>����ק�ӿڡ�</T>
//============================================================
class MO_EG_DECLARE IDragable{
public:
   //------------------------------------------------------------
   // <T>��������ק�ӿڡ�</T>
   MO_ABSTRACT ~IDragable(){
   }
public:
   MO_VIRTUAL TResult DragBegin() = 0;
   MO_VIRTUAL TResult DragMove() = 0;
   MO_VIRTUAL TResult DragEnd() = 0;
};

//============================================================
// <T>������Ϣ��</T>
//============================================================
struct MO_EG_DECLARE STailInfo{
public:
   // ����
   SFloatPoint3 location;
   // �ߴ�
   SFloatSize3 size;
   // ��ת
   SFloatVector3 rotation;
   // ������ɫ
   SFloatColor4 groundColor;
   // ��������
   SFloatCoord coord;
public:
   //------------------------------------------------------------
   // <T>���������Ϣ��</T>
   STailInfo(){
   }
};
//------------------------------------------------------------
typedef MO_EG_DECLARE TFixVector<STailInfo, 64> TFsTailInfoVector;

//============================================================
// <T>���ٿ�������</T>
//============================================================
class MO_EG_DECLARE FTailController : public FObject{
protected:
   TInt _limit;
   TInt _interval;
   TFsTailInfoVector _infos;
   TTimeTick _lastTick;
public:
   FTailController();
   MO_ABSTRACT ~FTailController();
public:
   //------------------------------------------------------------
   // <T>��ü���������</T>
   MO_INLINE TInt Limit(){
      return _limit;
   }
   //------------------------------------------------------------
   // <T>���ü���������</T>
   MO_INLINE void SetLimit(TInt limit){
      _limit = limit;
   }
   //------------------------------------------------------------
   // <T>��ú�������</T>
   MO_INLINE TInt Interval(){
      return _interval;
   }
   //------------------------------------------------------------
   // <T>���ü���������</T>
   MO_INLINE void SetInterval(TInt interval){
      _interval = interval;
   }
   //------------------------------------------------------------
   // <T>������Ϣ���ϡ�</T>
   MO_INLINE TFsTailInfoVector& Infos(){
      return _infos;
   }
public:
   TResult Push(STailInfo& info);
   TResult Reset();
};

//============================================================
// <T>������ԡ�</T>
//============================================================
class MO_EG_DECLARE FComponentProperty{
protected:
   TString _name;
public:
   FComponentProperty();
   MO_ABSTRACT ~FComponentProperty();
public:
   //------------------------------------------------------------
   // <T>�ж����ơ�</T>
   MO_INLINE TCharC* Name(){
      return _name;
   }
   //------------------------------------------------------------
   // <T>�������ơ�</T>
   MO_INLINE void SetName(TCharC* pName){
      _name = pName;
   }
public:
   TResult Serialize(IDataOutput* pOutput);
   TResult Unserialize(IDataInput* pInput);
};
//----------------------------------------------------------
typedef FVector<FComponentProperty*> FComponentPropertyCollection;

//============================================================
// <T>������Լ��ϡ�</T>
//============================================================
class MO_EG_DECLARE FComponentProperties{
protected:
   FComponentPropertyCollection* _pProperties;
public:
   FComponentProperties();
   MO_ABSTRACT ~FComponentProperties();
public:
   //------------------------------------------------------------
   // <T>�ж����Լ��ϡ�</T>
   MO_INLINE FComponentPropertyCollection* Properties(){
      return _pProperties;
   }
public:
   TResult Serialize(IDataOutput* pOutput);
   TResult Unserialize(IDataInput* pInput);
};

//============================================================
// <T>���������ġ�</T>
//============================================================
class MO_EG_DECLARE SProcessContext{
public:
   FInstance* senderPtr;
public:
   //------------------------------------------------------------
   // <T>���촦�������ġ�</T>
   SProcessContext(){
      MO_CLEAR(senderPtr);
   }
};

//============================================================
// <T>�������</T>
//============================================================
class MO_EG_DECLARE FComponent : public FInstance
{
   MO_CLASS_DECLARE_INHERITS(FComponent, FInstance);
protected:
   TString _name;
   TBool _optionValid;
   TComponentType _objectCd;
   TInt _flagCd;
   FComponent* _pParent;
   // FComponentCollection* _pChildren;
   FComponentProperties* _pProperties;
   TBool _statusConstruct;
   TBool _statusSetup;
   TBool _statusReady;
   TTimeTick _lastUpdate;
public:
   FComponent();
   MO_ABSTRACT ~FComponent();
public:
   //------------------------------------------------------------
   // <T>�ж��Ƿ�Ϊָ�����ơ�</T>
   MO_INLINE TBool IsName(TCharC* pName){
      return _name.Equals(pName);
   }
   //------------------------------------------------------------
   // <T>������ơ�</T>
   MO_INLINE TCharC* Name(){
      return _name;
   }
   //------------------------------------------------------------
   // <T>�������ơ�</T>
   MO_INLINE void SetName(TCharC* pName){
      _name = pName;
   }
   //------------------------------------------------------------
   // <T>�ж��Ƿ�ָ������</T>
   MO_INLINE TBool IsObject(TInt value){
      return (_objectCd & value) == value;
   }
   //------------------------------------------------------------
   // <T>����Ƿ��и������</T>
   MO_INLINE TBool HasParent(){
      return _pParent != NULL;
   }
   //------------------------------------------------------------
   // <T>��ø������</T>
   MO_INLINE FComponent* Parent(){
      return _pParent;
   }
   //------------------------------------------------------------
   // <T>���ø������</T>
   MO_INLINE void SetParent(FComponent* pParent){
      _pParent = pParent;
   }
   ////------------------------------------------------------------
   //// <T>�ж��Ƿ����������</T>
   //MO_INLINE TBool HasChild(){
   //   return (_pChildren != NULL) ? !_pChildren->IsEmpty() : EFalse;
   //}
   ////------------------------------------------------------------
   //// <T>��������������</T>
   //MO_INLINE TInt ChildCount(){
   //   return (_pChildren != NULL) ? _pChildren->Count() : 0;
   //}
   ////------------------------------------------------------------
   //// <T>�����������ϡ�</T>
   //MO_INLINE FComponentCollection* Children(){
   //   if(_pChildren == NULL){
   //      _pChildren = MO_CREATE(FComponentCollection);
   //   }
   //   return _pChildren;
   //}
   ////------------------------------------------------------------
   //// <T>���ָ������λ�õ��������</T>
   //MO_INLINE FComponent* Child(TInt index){
   //   return _pChildren->Get(index);
   //}
   //------------------------------------------------------------
   // <T>���������ʱ�䡣</T>
   MO_INLINE TTimeTick LastUpdate(){
      return _lastUpdate;
   }
public:
   MO_ABSTRACT FComponent* TopComponent();
   //MO_ABSTRACT TResult RemoveFromParent();
   //FComponent* ChildGet(TCharC* pName);
   //FComponent* ChildFind(TCharC* pName);
   //FComponent* ChildSearch(TCharC* pName);
   //MO_ABSTRACT TResult ChildPush(FComponent* pComponent);
   //MO_ABSTRACT TResult ChildPushDirect(FComponent* pComponent);
   //MO_ABSTRACT TResult ChildRemove(FComponent* pComponent);
   //MO_ABSTRACT TResult ChildSwap(FComponent* pSource, FComponent* pTarget);
   //MO_ABSTRACT TResult ChildClear();
public:
   MO_ABSTRACT TResult OnConstruct();
   MO_ABSTRACT TResult OnSerialize(IDataOutput* pOutput);
   MO_ABSTRACT TResult OnUnserialize(IDataInput* pInput);
   MO_ABSTRACT TResult OnSetupBefore();
   MO_ABSTRACT TResult OnSetupAfter();
   MO_ABSTRACT TResult OnDispose();
public:
   MO_ABSTRACT TResult Construct();
   MO_ABSTRACT TResult Serialize(IDataOutput* pOutput);
   MO_ABSTRACT TResult Unserialize(IDataInput* pInput);
   MO_ABSTRACT TResult Setup();
   MO_ABSTRACT TResult Update();
   MO_ABSTRACT TResult ProcessBefore(SProcessContext* pContext);
   MO_ABSTRACT TResult ProcessAfter(SProcessContext* pContext);
   MO_ABSTRACT TResult Dispose();
};

//============================================================
// <T>���ƻ�����</T>
//============================================================
struct MO_EG_DECLARE SDrawableContext{
public:
   //const TInt LevelHigh = 1;
   //const TInt LevelLower = 2;
   TInt interval;
   TBool delay;
   TInt delayLevel;
   TBool dirty;
   //FCamera* cameraPtr;
   //FLight lightPtr;
   //FByteStream* dataPtr:
};

//============================================================
// <T>�ɻ��ƶ���</T>
//============================================================
class MO_EG_DECLARE FDrawable : public FComponent
{
   MO_CLASS_DECLARE_INHERITS(FDrawable, FComponent);
protected:
   // ״̬�ɼ�
   TBool _statusVisible;
   // ״̬��
   TBool _statusDirty;
   // ����
   SFloatPoint3 _location;
   // �ߴ�
   SFloatSize3 _size;
   // ��ת
   SFloatVector3 _rotation;
   // ������ɫ
   SFloatColor4 _groundColor;
   // ��������
   SFloatCoord _coord;
   // �任����
   SFloatMatrix3d _matrix;
   // ģ�ͱ任����
   SFloatMatrix3d _matrixModel;
   // ��״�任����
   SFloatMatrix3d _matrixTransform;
   // ���ձ任����
   SFloatMatrix3d _matrixFinal;
public:
   FDrawable();
   MO_ABSTRACT ~FDrawable();
public:
   //------------------------------------------------------------
   // <T>��ø����������</T>
   MO_INLINE FDrawable* ParentDrawable(){
      return (FDrawable*)_pParent;
   }
   //------------------------------------------------------------
   // <T>��ÿɼ�״̬��</T>
   MO_INLINE TBool StatusVisible(){
      return _statusVisible;
   }
   //------------------------------------------------------------
   // <T>�����״̬��</T>
   MO_INLINE TBool StatusDirty(){
      return _statusDirty;
   }
   //------------------------------------------------------------
   // <T>������ꡣ</T>
   MO_INLINE SFloatPoint3& Location(){
      return _location;
   }
   //------------------------------------------------------------
   // <T>��ô�С��</T>
   MO_INLINE SFloatSize3& Size(){
      return _size;
   }
   //------------------------------------------------------------
   // <T>�����ת��</T>
   MO_INLINE SFloatVector3& Rotation(){
      return _rotation;
   }
   //------------------------------------------------------------
   // <T>��ñ�����ɫ��</T>
   MO_INLINE SFloatColor4& GroundColor(){
      return _groundColor;
   }
   //------------------------------------------------------------
   // <T>����������ꡣ</T>
   MO_INLINE SFloatCoord& Coord(){
      return _coord;
   }
   //------------------------------------------------------------
   // <T>��ñ任����</T>
   MO_INLINE SFloatMatrix3d& Matrix(){
      return _matrix;
   }
   //------------------------------------------------------------
   // <T>���ģ�ͱ任����</T>
   MO_INLINE SFloatMatrix3d& MatrixModel(){
      return _matrixModel;
   }
   //------------------------------------------------------------
   // <T>��ü�ʱ�任����</T>
   MO_INLINE SFloatMatrix3d& MatrixFinal(){
      return _matrixFinal;
   }
public:
   MO_ABSTRACT TAny* Convert(EComponent componentCd);
public:
   MO_ABSTRACT TResult OnPaint();
   MO_ABSTRACT TResult OnFocusTest(FFocusTester* pTester);
public:
   MO_ABSTRACT TBool TestDrawable();
   MO_ABSTRACT TResult CalculateRectangle(SIntRectangle* pRectangle);
   MO_ABSTRACT TResult FilterRegion(FRenderRegion* pRegion);
public:
   MO_ABSTRACT void UpdateSelftMatrix(SDrawableContext* pContext);
   MO_ABSTRACT void UpdateParentMatrix();
   MO_ABSTRACT void UpdateMatrix();
   MO_ABSTRACT void UpdateAllMatrix(SDrawableContext* pContext);
   MO_ABSTRACT void UpdateDirty(SDrawableContext* pContext);
public:
   MO_ABSTRACT TResult SetVisible(TBool visible);
   MO_ABSTRACT TResult FocusTest(FFocusTester* pTester);
   MO_ABSTRACT TResult Dirty(TBool force = EFalse);
   MO_ABSTRACT TResult Paint();
   MO_ABSTRACT TResult Update();
public:
   MO_OVERRIDE TResult ProcessBefore(SProcessContext* pContext);
   MO_OVERRIDE TResult ProcessAfter(SProcessContext* pContext);
public:
   MO_ABSTRACT TResult Suspend();
   MO_ABSTRACT TResult Resume();
   MO_ABSTRACT TResult Dispose();
};

//============================================================
// <T>��Ⱦ���ݡ�</T>
//============================================================
struct SRenderableContent{
public:
   FRenderVertexStreams* vertexStreamsPtr;
   FRenderIndexBuffer* indexBufferPtr;
   FRenderTextures* texturesPtr;
public:
   //------------------------------------------------------------
   // <T>������Ⱦ������</T>
   SRenderableContent(){
      MO_CLEAR(vertexStreamsPtr);
      MO_CLEAR(indexBufferPtr);
      MO_CLEAR(texturesPtr);
   }
};

//============================================================
// <T>��ʾ����</T>
//============================================================
class MO_EG_DECLARE FDisplay : public FDrawable
{
   MO_CLASS_DECLARE_INHERITS(FDisplay, FDrawable);
protected:
   TDisplayType _typeCd;
   FDisplayCollection* _pDisplays;
   FRenderableCollection* _pRenderables;
public:
   FDisplay();
   MO_ABSTRACT ~FDisplay();
public:
   //------------------------------------------------------------
   // <T>������͡�</T>
   MO_INLINE TDisplayType TypeCd(){
      return _typeCd;
   }
   //------------------------------------------------------------
   // <T>�����ʾ���ϡ�</T>
   MO_INLINE FDisplayCollection* Displays(){
      return _pDisplays;
   }
   //------------------------------------------------------------
   // <T>�����Ⱦ���ϡ�</T>
   MO_INLINE FRenderableCollection* Renderables(){
      return _pRenderables;
   }
public:
   MO_ABSTRACT TResult DisplayPush(FDisplay* pDisplay);
   MO_ABSTRACT TResult DisplayRemove(FDisplay* pDisplay);
   MO_ABSTRACT TResult DisplayClear();
   MO_ABSTRACT TResult RenderablePush(FRenderable* pRenderable);
   MO_ABSTRACT TResult RenderableRemove(FRenderable* pRenderable);
   MO_ABSTRACT TResult RenderableClear();
public:
   MO_OVERRIDE TResult FilterRegion(FRenderRegion* pRegion);
   MO_OVERRIDE void UpdateAllMatrix(SDrawableContext* pContext);
   MO_OVERRIDE TResult ProcessBefore(SProcessContext* pContext);
   MO_OVERRIDE TResult ProcessAfter(SProcessContext* pContext);
   MO_OVERRIDE TResult Free();
public:
   MO_OVERRIDE TResult Suspend();
   MO_OVERRIDE TResult Resume();
   MO_OVERRIDE TResult Dispose();
};

//============================================================
// <T>��ʾ����ء�</T>
//============================================================
class MO_EG_DECLARE FDisplayPool : public FPool<FDrawable*>{
protected:
   TDisplayType _typeCd;
public:
   FDisplayPool();
   MO_ABSTRACT ~FDisplayPool();
public:
   //------------------------------------------------------------
   // <T>������͡�</T>
   MO_INLINE TDisplayType TypeCd(){
      return _typeCd;
   }
public:
   MO_VIRTUAL FDrawable* Create() = 0;
public:
   FDrawable* Alloc();
   void Free(FDrawable* pParticle);
};
//------------------------------------------------------------
typedef MO_EG_DECLARE FObjects<FDisplayPool*> FDisplayPoolCollection;

//============================================================
// <T>�ɻ��ƶ���㡣</T>
//============================================================
class MO_EG_DECLARE FDisplayLayer : public FDisplay
{
   MO_CLASS_DECLARE_INHERITS(FDisplayLayer, FDisplay);
protected:
   EDisplayLayer _layerCd;
   FStageFrame* _pStageFrame;
   FParticleController* _pParticleController;
   GPtr<FVisualRegion> _visualRegion;
public:
   FDisplayLayer();
   MO_ABSTRACT ~FDisplayLayer();
public:
   //------------------------------------------------------------
   // <T>�����ʾ�����͡�</T>
   MO_INLINE EDisplayLayer LayerCd(){
      return _layerCd;
   }
   //------------------------------------------------------------
   // <T>������ʾ�����͡�</T>
   MO_INLINE void SetLayerCd(EDisplayLayer layerCd){
      _layerCd = layerCd;
   }
   //------------------------------------------------------------
   // <T>�����̨��</T>
   MO_INLINE FStageFrame* StageFrame(){
      return _pStageFrame;
   }
   //------------------------------------------------------------
   // <T>������̨��</T>
   MO_INLINE void SetStageFrame(FStageFrame* pStage){
      _pStageFrame = pStage;
   }
   //------------------------------------------------------------
   // <T>������ӿ�������</T>
   MO_INLINE FParticleController* ParticleController(){
      return _pParticleController;
   }
   //------------------------------------------------------------
   // <T>��ÿɼ�����</T>
   MO_INLINE FVisualRegion* VisualRegion(){
      return _visualRegion;
   }
public:
   TResult OnFocusTest(FFocusTester* pTester);
public:
   MO_ABSTRACT TResult Setup();
   MO_OVERRIDE TResult FilterRegion(FRenderRegion* pRegion);
   MO_ABSTRACT TResult ProcessBefore(SProcessContext* pContext);
   MO_ABSTRACT TResult ProcessAfter(SProcessContext* pContext);
};
//------------------------------------------------------------
typedef MO_EG_DECLARE FVector<FDisplayLayer*> FDisplayLayerCollection;

//============================================================
// <T>�ռ��塣</T>
//============================================================
class MO_EG_DECLARE FSpatial : public FDrawable{
protected:
   FDisplayCollection* _pDisplays;
public:
   FSpatial();
   MO_ABSTRACT ~FSpatial();
public:
   //------------------------------------------------------------
   // <T>�����ʾ���ϡ�</T>
   MO_INLINE FDisplayCollection* Displays(){
      return _pDisplays;
   }
public:
   MO_ABSTRACT TResult DisplayPush(FDisplay* pDisplay);
   MO_ABSTRACT TResult DisplayRemove(FDisplay* pDisplay);
   MO_ABSTRACT TResult DisplayClear();
public:
   MO_OVERRIDE TResult FilterRegion(FRenderRegion* pRegion);
   MO_OVERRIDE void UpdateAllMatrix(SDrawableContext* pContext);
   MO_OVERRIDE TResult ProcessBefore(SProcessContext* pContext);
   MO_OVERRIDE TResult ProcessAfter(SProcessContext* pContext);
   MO_OVERRIDE TResult Free();
};

//============================================================
// <T>λͼ����</T>
//============================================================
class MO_EG_DECLARE FBitmap : public FDrawable{
protected:
   GPtr<FBitmapData> _data;
   GPtr<FRenderTexture> _texture;
   SIntSize2 _size;
public:
   FBitmap();
   MO_ABSTRACT ~FBitmap();
public:
   //------------------------------------------------------------
   // <T>������ݡ�</T>
   FBitmapData* Data(){
      return _data;
   }
   //------------------------------------------------------------
   // <T>�������</T>
   FRenderTexture* Texture(){
      return _texture;
   }
public:
   MO_ABSTRACT TResult Setup();
public:
   MO_OVERRIDE TResult FilterRegion(FRenderRegion* pRegion);
public:
   MO_OVERRIDE TResult Resize(TInt width, TInt height);
   MO_ABSTRACT TResult Clear(TColor color);
   MO_ABSTRACT TResult Clear(TColor color, SIntRectangle* pRectangle);
   MO_ABSTRACT TResult Update();
public:
   MO_ABSTRACT void FreeBitmap();
   MO_ABSTRACT void FreeTexture();
};

//============================================================
// <T>λͼ���塣</T>
//============================================================
class MO_EG_DECLARE FBitmapCanvas :
      public FBitmap,
      public ICanvas{
protected:
   SIntRectangle _clientRectangle;
   SIntRectangle _clipRectangle;
public:
   FBitmapCanvas();
   MO_ABSTRACT ~FBitmapCanvas();
public:
   //------------------------------------------------------------
   // <T>��ÿͻ���Χ��</T>
   MO_INLINE SIntRectangle& ClientRectangle(){
      return _clientRectangle;
   }
   //------------------------------------------------------------
   // <T>��ü�������</T>
   MO_INLINE SIntRectangle& ClipRectangle(){
      return _clipRectangle;
   }
public:
   MO_OVERRIDE TResult Setup();
   MO_OVERRIDE TResult Update();
public:
   MO_OVERRIDE TResult DrawLine(TColor color, TInt x1, TInt y1, TInt x2, TInt y2);
   MO_OVERRIDE TResult DrawLineHorizontal(TColor color, TInt x1, TInt x2, TInt y);
   MO_OVERRIDE TResult DrawLineVertical(TColor color, TInt y1, TInt y2, TInt x);
   MO_OVERRIDE TResult DrawTriangle(TColor color, TInt x1, TInt y1, TInt x2, TInt y2, TInt x3, TInt y3);
   MO_OVERRIDE TResult DrawRectangle(TColor color, TInt x1, TInt y1, TInt x2, TInt y2);
   MO_OVERRIDE TResult DrawRectangle(TColor color, SIntRectangle* pRectangle);
public:
   MO_OVERRIDE TResult FillTriangle(TColor color, TInt x1, TInt y1, TInt x2, TInt y2, TInt x3, TInt y3);
   MO_OVERRIDE TResult FillRectangle(TColor color, TInt x1, TInt y1, TInt x2, TInt y2);
   MO_OVERRIDE TResult FillRectangle(TColor color, SIntRectangle* pRectangle);
public:
   MO_OVERRIDE TResult DrawBitmap(FBitmapData* pBitmapData, TBool alpha, TInt x, TInt y);
   MO_OVERRIDE TResult DrawBitmap(FBitmapData* pBitmapData, TBool alpha, SIntRectangle* pSourceRectangle, TInt x, TInt y);
   MO_OVERRIDE TResult DrawBitmap(FBitmapData* pBitmapData, TBool alpha, SIntRectangle* pSourceRectangle, SIntRectangle* pTargetRectangle);
   MO_OVERRIDE TResult DrawBitmapGrid9(FBitmapData* pBitmapData, TBool alpha, SIntPadding* pSourcePadding, SIntRectangle* pTargetRectangle);
   MO_OVERRIDE TResult DrawBitmapGrid9(FBitmapData* pBitmapData, TBool alpha, SIntRectangle* pSourceRectangle, SIntPadding* pSourcePadding, SIntRectangle* pTargetRectangle);
};

//============================================================
// <T>��ʾ�����������͡�</T>
//============================================================
enum EMovieAction{
   EMovieAction_Play,
   EMovieAction_Visible,
   EMovieAction_Dispose,
};

//============================================================
// <T>��ʾ�������</T>
//============================================================
struct MO_EG_DECLARE SMovieAction{
public:
   // ��������
   EMovieAction actionCd;
   // �ɼ���
   TBool visible;
   // ����
   TInt directionCd;
   // ѭ������
   TInt loop;
   // ����
   TFloat rate;
public:
   //------------------------------------------------------------
   // <T>������ʾ�������</T>
   SMovieAction(){
   }
};
//------------------------------------------------------------
typedef MO_EG_DECLARE TList<SMovieAction> TMovieActionList;

//============================================================
// <T>֡�����¼���</T>
//============================================================
class MO_EG_DECLARE SFrameEvent : public SEvent{
public:
   //------------------------------------------------------------
   // <T>����֡�����¼���</T>
   SFrameEvent(TAny* pSender) : SEvent(pSender){
   }
};
//------------------------------------------------------------
typedef MO_EG_DECLARE TListeners<SFrameEvent> TFrameListeners;

//============================================================
// <T>��̨����</T>
//============================================================
class MO_EG_DECLARE FStageFrame : public FInstance
{
   MO_CLASS_DECLARE_INHERITS(FStageFrame, FInstance);
protected:
   // ����
   TString _name;
   // ��̨
   FStage* _pStage;
   // ֡����
   EStageFrame _frameCd;
   // ������ɫ
   SFloatColor4 _backgroundColor;
   // ��ȾĿ��
   GPtr<FRenderTarget> _renderTarget;
   // ��ʾ�㼯��
   FDisplayLayerCollection* _pLayers;
public:
   FStageFrame();
   MO_ABSTRACT ~FStageFrame();
public:
   //------------------------------------------------------------
   // <T>������ơ�</T>
   MO_INLINE TCharC* Name(){
      return _name;
   }
   //------------------------------------------------------------
   // <T>�������ơ�</T>
   MO_INLINE void SetName(TCharC* pName){
      _name = _name;
   }
   //------------------------------------------------------------
   // <T>�����̨��</T>
   MO_INLINE FStage* Stage(){
      return _pStage;
   }
   //------------------------------------------------------------
   // <T>������̨��</T>
   MO_INLINE void SetStage(FStage* pStage){
      _pStage = pStage;
   }
   //------------------------------------------------------------
   // <T>���֡���͡�</T>
   MO_INLINE EStageFrame FrameCd(){
      return _frameCd;
   }
   //------------------------------------------------------------
   // <T>����֡���͡�</T>
   MO_INLINE void SetFrameCd(EStageFrame frameCd){
      _frameCd = frameCd;
   }
   //------------------------------------------------------------
   // <T>��ñ�����ɫ��</T>
   MO_INLINE SFloatColor4& BackgroundColor(){
      return _backgroundColor;
   }
   //------------------------------------------------------------
   // <T>�����ȾĿ�ꡣ</T>
   MO_INLINE FRenderTarget* RenderTarget(){
      return _renderTarget;
   }
   //------------------------------------------------------------
   // <T>������ȾĿ�ꡣ</T>
   MO_INLINE void SetRenderTarget(FRenderTarget* pRenderTarget){
      return _renderTarget = pRenderTarget;
   }
   //------------------------------------------------------------
   // <T>��ò㼯�ϡ�</T>
   MO_INLINE FDisplayLayerCollection* Layers(){
      return _pLayers;
   }
public:
   MO_ABSTRACT TResult Setup();
public:
   FDisplayLayer* LayerFind(EDisplayLayer frameCd);
   void LayerClear();
   void LayerPush(FDisplayLayer* pFrame);
   void LayerRemove(FDisplayLayer* pFrame);
public:
   MO_ABSTRACT TResult FocusTest(FFocusTester* pTester);
public:
   MO_ABSTRACT TResult Active();
   MO_ABSTRACT TResult Deactive();
public:
   MO_ABSTRACT TResult BuildRegion(FRenderRegion* pRegion);
public:
   MO_ABSTRACT TResult ProcessBefore(SProcessContext* pContext);
   MO_ABSTRACT TResult ProcessInput();
   MO_ABSTRACT TResult ProcessLogic();
   MO_ABSTRACT TResult ProcessAfter(SProcessContext* pContext);
public:
   MO_ABSTRACT TResult Suspend();
   MO_ABSTRACT TResult Resume();
   MO_ABSTRACT TResult Dispose();
};
//------------------------------------------------------------
typedef MO_EG_DECLARE FObjects<FStageFrame*> FStageFrameCollection;

//============================================================
// <T>��̨��</T>
//============================================================
class MO_EG_DECLARE FStage: public FInstance
{
   MO_CLASS_DECLARE_INHERITS(FStage, FInstance);
protected:
   GPtr<FRenderView> _activeView;
   // �ӽǼ���
   FRenderViewCollection* _pViews;
   // ����ɫ
   SFloatColor4 _backgroundColor;
   // �����Դ
   GPtr<FDirectionalLight> _directionalLight;
   // ��Դ����
   FLightCollection* _pLights;
   // ��̨֡����
   FStageFrameCollection* _pFrames;
   // ֡�����������
   TFrameListeners _listenersFrameEnter;
   // ֡�뿪��������
   TFrameListeners _listenersFrameLeave;
public:
   FStage();
   MO_ABSTRACT ~FStage();
public:
   //------------------------------------------------------------
   // <T>����ӽǼ��ϡ�</T>
   MO_INLINE FRenderViewCollection* Views(){
      return _pViews;
   }
   //------------------------------------------------------------
   // <T>��ñ���ɫ��</T>
   MO_INLINE SFloatColor4& BackgroundColor(){
      return _backgroundColor;
   }
   //------------------------------------------------------------
   // <T>��÷����Դ��</T>
   MO_INLINE FDirectionalLight* DirectionalLight(){
      return _directionalLight;
   }
   //------------------------------------------------------------
   // <T���÷����Դ��</T>
   MO_INLINE void SetDirectionalLight(FDirectionalLight* pDirectionalLight){
      _directionalLight = pDirectionalLight;
   }
   //------------------------------------------------------------
   // <T>��ù�Դ���ϡ�</T>
   MO_INLINE FLightCollection* Lights(){
      return _pLights;
   }
   //------------------------------------------------------------
   // <T>���֡���ϡ�</T>
   MO_INLINE FStageFrameCollection* Frames(){
      return _pFrames;
   }
   //------------------------------------------------------------
   // <T>���֡����������ϡ�</T>
   MO_INLINE TFrameListeners& ListenersFrameEnter(){
      return _listenersFrameEnter;
   }
   //------------------------------------------------------------
   // <T>���֡����������ϡ�</T>
   MO_INLINE TFrameListeners& ListenersFrameLeave(){
      return _listenersFrameLeave;
   }
public:
   FStageFrame* FrameFind(EStageFrame frameCd);
   void FrameClear();
   void FramePush(FStageFrame* pLayer);
   void FrameRemove(FStageFrame* pLayer);
public:
   MO_OVERRIDE TResult Setup();
public:
   MO_ABSTRACT TResult Active();
   MO_ABSTRACT TResult Deactive();
public:
   MO_ABSTRACT TResult BuildRegion(FRenderRegion* pRegion);
public:
   MO_ABSTRACT TResult ProcessBefore(SProcessContext* pContext);
   MO_ABSTRACT TResult ProcessInput();
   MO_ABSTRACT TResult ProcessLogic();
   MO_ABSTRACT TResult ProcessAfter(SProcessContext* pContext);
public:
   MO_ABSTRACT TResult Suspend();
   MO_ABSTRACT TResult Resume();
   MO_ABSTRACT TResult Dispose();
};

//============================================================
// <T>��̨����̨��</T>
//============================================================
class MO_EG_DECLARE FStageConsole : public FConsole{
protected:
   // ��̨
   FStage* _pActiveStage;
   // ��ʾ������
   GPtr<FProcessor> _displayProcessor;
   // ��Ⱦ������
   GPtr<FProcessor> _renderableProcessor;
public:
   FStageConsole();
   MO_ABSTRACT ~FStageConsole();
public:
   //------------------------------------------------------------
   // <T>��ü������̨��</T>
   MO_INLINE FStage* ActiveStage(){
      return _pActiveStage;
   }
   //------------------------------------------------------------
   // <T>�����ʾ��������</T>
   MO_INLINE FProcessor* DisplayProcessor(){
      return _displayProcessor;
   }
   //------------------------------------------------------------
   // <T>�����Ⱦ��������</T>
   MO_INLINE FProcessor* RenderableProcessor(){
      return _renderableProcessor;
   }
public:
   MO_ABSTRACT void Setup();
   MO_ABSTRACT TResult Shutdown();
public:
   MO_ABSTRACT TResult SelectStage(FStage* pStage);
};

//============================================================
// <T>��̨��������</T>
//============================================================
class MO_EG_DECLARE RStageManager : public RSingleton<FStageConsole>{
};

//============================================================
// <T>�����������</T>
//============================================================
class MO_EG_DECLARE FFocusTester : public FObject{
public:
   TBool _statusInRange;
   TBool _statusChildren;
   TInt _level;
   SIntPoint2 _location;
   FDrawableCollection* _pDrawables;
public:
   FFocusTester();
   MO_ABSTRACT ~FFocusTester();
public:
   //------------------------------------------------------------
   // <T>����Ƿ��ڷ�Χ�ڡ�</T>
   MO_INLINE TBool StatusInRange(){
      return _statusInRange;
   }
   //------------------------------------------------------------
   // <T>�����Ƿ��ڷ�Χ�ڡ�</T>
   MO_INLINE void SetStatusInRange(TBool statusInRange){
      _statusInRange = statusInRange;
   }
   //------------------------------------------------------------
   // <T>����Ƿ��ѯ�Ӷ���</T>
   MO_INLINE TBool StatusChildren(){
      return _statusChildren;
   }
   //------------------------------------------------------------
   // <T>�����Ƿ��ѯ�Ӷ���</T>
   MO_INLINE void SetStatusChildren(TBool statusChildren){
      _statusChildren = statusChildren;
   }
   //------------------------------------------------------------
   // <T>��ò㼶��</T>
   MO_INLINE TInt Level(){
      return _level;
   }
   //------------------------------------------------------------
   // <T>���ò㼶��</T>
   MO_INLINE void SetLevel(TInt level){
      _level = level;
   }
   //------------------------------------------------------------
   // <T>���λ�á�</T>
   MO_INLINE SIntPoint2& Location(){
      return _location;
   }
   //------------------------------------------------------------
   // <T>��ÿɻ��ƶ��󼯺ϡ�</T>
   MO_INLINE FDrawableCollection* Drawables(){
      return _pDrawables;
   }
public:
   //------------------------------------------------------------
   // <T>��ü���Ķ���</T>
   MO_INLINE FDrawable* ActiveDrawable(){
      return _pDrawables->IsEmpty() ? NULL : _pDrawables->First();
   }
   //------------------------------------------------------------
   // <T>����һ������</T>
   MO_INLINE void Push(FDrawable* pDrawable){
      _pDrawables->Push(pDrawable);
   }
   //------------------------------------------------------------
   // <T>������ݡ�</T>
   MO_INLINE void TestReset(){
      _statusInRange = EFalse;
      _statusChildren = EFalse;
   }
   //------------------------------------------------------------
   // <T>������ݡ�</T>
   MO_INLINE void Clear(){
      _level = 0;
      _pDrawables->Clear();
   }
};

//============================================================
// <T>�������̨��</T>
//============================================================
class MO_EG_DECLARE FFocusConsole : public FConsole{
public:
   SIntPoint2 _focusLocation;
   FDrawable* _pHoverDrawable;
   FDrawable* _pFocusDrawable;
   FDrawable* _pDragDrawable;
   SIntPoint2 _startLocation;
   SIntPoint2 _dragLocation;
   SIntPoint2 _dragDrawableLocation;
   FDrawableCollection* _pFocusDrawables;
   FFocusTester* _pTester;
public:
   FFocusConsole();
   MO_ABSTRACT ~FFocusConsole();
public:
   //------------------------------------------------------------
   // <T>��ý���λ�á�</T>
   MO_INLINE SIntPoint2& FocusLocation(){
      return _focusLocation;
   }
   //------------------------------------------------------------
   // <T>����ȵ����</T>
   MO_INLINE FDrawable* HoverDrawable(){
      return _pHoverDrawable;
   }
   //------------------------------------------------------------
   // <T>��ý������</T>
   MO_INLINE FDrawable* FocusDrawable(){
      return _pFocusDrawable;
   }
   //------------------------------------------------------------
   // <T>��ý�����󼯺ϡ�</T>
   MO_INLINE FDrawableCollection* FocusDrawables(){
      return _pFocusDrawables;
   }
protected:
   FFocusTester* TestPosition(TInt x, TInt y);
public:
   TResult OnMouseDown(SMouseEvent* pEvent);
   TResult OnMouseMove(SMouseEvent* pEvent);
   TResult OnMouseUp(SMouseEvent* pEvent);
public:
   TResult Setup();
   TResult HoverDrawable(FDrawable* pDrawable);
   TResult FocusDrawable(FDrawable* pDrawable);
   TResult DragDrawable(FDrawable* pDrawable, TInt x, TInt y);
   TResult Process(EMouseButton buttonCd, TInt x, TInt y);
};

//============================================================
// <T>�����������</T>
//============================================================
class MO_EG_DECLARE RFocusManager : public RSingleton<FFocusConsole>{
};

MO_NAMESPACE_END

//************************************************************
#endif // __MO_EG_DISPLAY_H__
