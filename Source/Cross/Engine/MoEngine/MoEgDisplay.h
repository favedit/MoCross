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
class FDrawable;
class FDisplay;
class FStageFrame;
class FStage;
class FParticleController;
class FFocusTester;
// ���϶���
typedef MO_EG_DECLARE FObjects<FComponent*> FComponentCollection;
typedef MO_EG_DECLARE FObjects<FDrawable*> FDrawableCollection;
typedef MO_EG_DECLARE FObjects<FDisplay*> FDisplayCollection;
typedef MO_EG_DECLARE FList<FDisplay*> FDisplayList;

//==========================================================
// <T>�������</T>
//==========================================================
enum EComponentOption{
   // ��Ч
   EComponentOption_Valid = 0x01,
};

//==========================================================
// <T>���״̬</T>
//==========================================================
enum EComponentStatus{
   // ����
   EComponentStatus_Construct = 0x01,
   // ����
   EComponentStatus_Setup = 0x02,
   // ׼��
   EComponentStatus_Ready = 0x04,
};

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
// <T>������ԡ�</T>
//============================================================
class MO_EG_DECLARE FComponentProperty : public FInstance
{
   MO_CLASS_DECLARE_INHERITS(FComponentProperty, FInstance);
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
typedef MO_EG_DECLARE GPtrDictionary<FComponentProperty> GComponentPropertyDictionary;

//============================================================
// <T>������Լ��ϡ�</T>
//============================================================
class MO_EG_DECLARE FComponentProperties : public FInstance
{
   MO_CLASS_DECLARE_INHERITS(FComponentProperties, FInstance);
protected:
   GComponentPropertyDictionary _properties;
public:
   FComponentProperties();
   MO_ABSTRACT ~FComponentProperties();
public:
   //------------------------------------------------------------
   // <T>�ж����Լ��ϡ�</T>
   MO_INLINE GComponentPropertyDictionary& Properties(){
      return _properties;
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
   TInt _optionFlag;
   TInt _statusFlag;
   FComponent* _pParent;
   GPtr<FComponentProperties> _properties;
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
   // <T>�ж��Ƿ���ָ�����á�</T>
   MO_INLINE TBool IsOption(TInt value){
      return (_optionFlag & value) == value;
   }
   //------------------------------------------------------------
   // <T>�����������ݡ�</T>
   MO_INLINE void SetOption(TInt flag, TBool value){
      if(value){
         _optionFlag |= flag;
      }else{
         _optionFlag &= ~flag;
      }
   }
   //------------------------------------------------------------
   // <T>�ж��Ƿ���ָ��״̬��</T>
   MO_INLINE TBool IsStatus(TInt value){
      return (_statusFlag & value) == value;
   }
   //------------------------------------------------------------
   // <T>����״̬���ݡ�</T>
   MO_INLINE void SetStatus(TInt flag, TBool value){
      if(value){
         _statusFlag |= flag;
      }else{
         _statusFlag &= ~flag;
      }
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
   //------------------------------------------------------------
   // <T>������Լ��ϡ�</T>
   MO_INLINE FComponentProperties* Properties(){
      return _properties;
   }
   //------------------------------------------------------------
   // <T>���������ʱ�䡣</T>
   MO_INLINE TTimeTick LastUpdate(){
      return _lastUpdate;
   }
public:
   MO_ABSTRACT FComponent* TopComponent();
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
// <T>�ű�����</T>
//============================================================
class MO_EG_DECLARE FScriptable : public FComponent
{
   MO_CLASS_DECLARE_INHERITS(FScriptable, FComponent);
protected:
   GPtr<FScriptInstance> _scriptInstance;
public:
   FScriptable();
   MO_ABSTRACT ~FScriptable();
public:
   //------------------------------------------------------------
   // <T>��ýű�ʵ����</T>
   MO_INLINE FScriptInstance* ScriptInstance(){
      return _scriptInstance;
   }
   //------------------------------------------------------------
   // <T>���ýű�ʵ����</T>
   MO_INLINE void SetScriptInstance(FScriptInstance* pScriptInstance){
      _scriptInstance = pScriptInstance;
   }
public:
   MO_ABSTRACT TResult ProcessBefore(SProcessContext* pContext);
   MO_ABSTRACT TResult ProcessAfter(SProcessContext* pContext);
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
   FDisplayCollection* _pDisplays;
   FRenderableCollection* _pRenderables;
public:
   FDisplay();
   MO_ABSTRACT ~FDisplay();
public:
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
public:
   FDisplayPool();
   MO_ABSTRACT ~FDisplayPool();
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

MO_NAMESPACE_END

//************************************************************
#endif // __MO_EG_DISPLAY_H__
