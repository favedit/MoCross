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
// ���Ͷ���
class FComponent;
class FDrawable;
class FDisplay;
class FStageLayer;
class FStage;
class FParticleController;
class FFocusTester;
// ���϶���
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

//============================================================
// <T>������ԡ�</T>
//============================================================
class MO_EG_DECLARE FComponentProperty : public FInstance
{
   MO_CLASS_DECLARE_INHERITS(FComponentProperty, FInstance);
protected:
   TString _name;
   TInt _version;
public:
   FComponentProperty();
   MO_ABSTRACT ~FComponentProperty();
public:
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
   // <T>��ð汾��</T>
   MO_INLINE TInt Version(){
      return _version;
   }
   //------------------------------------------------------------
   // <T>���ð汾��</T>
   MO_INLINE void SetVersion(TInt version){
      _version = version;
   }
public:
   MO_ABSTRACT TResult Serialize(IDataOutput* pOutput);
   MO_ABSTRACT TResult Unserialize(IDataInput* pInput);
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
   MO_ABSTRACT TResult Serialize(IDataOutput* pOutput);
   MO_ABSTRACT TResult Unserialize(IDataInput* pInput);
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
   MO_ABSTRACT TResult Update(SProcessContext* pContext);
   MO_ABSTRACT TResult ProcessBefore(SProcessContext* pContext);
   MO_ABSTRACT TResult ProcessAfter(SProcessContext* pContext);
   MO_ABSTRACT TResult Dispose();
};
//------------------------------------------------------------
typedef MO_EG_DECLARE GPtrs<FComponent> GComponentPtrs;

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
//------------------------------------------------------------
typedef MO_EG_DECLARE GPtrs<FScriptable> GScriptablePtrs;

//============================================================
// <T>���ƻ�����</T>
//============================================================
struct MO_EG_DECLARE SDrawableContext{
public:
   TInt interval;
   TBool delay;
   TInt delayLevel;
   TBool dirty;
};

//============================================================
// <T>�ɻ��ƶ���</T>
//============================================================
class MO_EG_DECLARE FDrawable : public FComponent
{
   MO_CLASS_DECLARE_INHERITS(FDrawable, FComponent);
protected:
   // ״̬׼����
   TBool _statusReady;
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
   // ǰ����ɫ
   SFloatColor4 _foreColor;
   // ������ɫ
   SFloatColor4 _groundColor;
   // ��������
   SFloatCoord _coord;
   // �任����
   SFloatMatrix3d _matrix;
   // ģ�;���
   SFloatMatrix3d _matrixModel;
   // �任����
   SFloatMatrix3d _matrixTransform;
public:
   FDrawable();
   MO_ABSTRACT ~FDrawable();
public:
   //------------------------------------------------------------
   // <T>��ø����������</T>
   MO_INLINE FDrawable* ParentDrawable(){
      return _pParent->Convert<FDrawable>();
   }
   //------------------------------------------------------------
   // <T>���׼��״̬��</T>
   MO_INLINE TBool StatusReady(){
      return _statusReady;
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
   // <T>���ǰ����ɫ��</T>
   MO_INLINE SFloatColor4& ForeColor(){
      return _foreColor;
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
   // <T>��þ���</T>
   MO_INLINE SFloatMatrix3d& Matrix(){
      return _matrix;
   }
   //------------------------------------------------------------
   // <T>���ģ�;���</T>
   MO_INLINE SFloatMatrix3d& MatrixModel(){
      return _matrixModel;
   }
   //------------------------------------------------------------
   // <T>��ñ任����</T>
   MO_INLINE SFloatMatrix3d& MatrixTransform(){
      return _matrixTransform;
   }
public:
   MO_ABSTRACT TResult OnPaint();
   MO_ABSTRACT TResult OnFocusTest(FFocusTester* pTester);
public:
   MO_ABSTRACT TBool TestReady();
   MO_ABSTRACT TBool TestDrawable();
   MO_ABSTRACT TResult CalculateRectangle(SIntRectangle* pRectangle);
   MO_ABSTRACT TResult FilterRegion(FRenderRegion* pRegion);
public:
   MO_ABSTRACT TResult UpdateSelftMatrix(SDrawableContext* pContext);
   MO_ABSTRACT TResult UpdateParentMatrix();
   MO_ABSTRACT TResult UpdateMatrix();
   MO_ABSTRACT TResult UpdateAllMatrix(SDrawableContext* pContext);
   MO_ABSTRACT TResult UpdateDirty(SDrawableContext* pContext);
public:
   MO_ABSTRACT TResult SetVisible(TBool visible);
   MO_ABSTRACT TResult FocusTest(FFocusTester* pTester);
   MO_ABSTRACT TResult Dirty(TBool force = EFalse);
   MO_ABSTRACT TResult Paint();
public:
   MO_OVERRIDE TResult Update(SProcessContext* pContext);
   MO_OVERRIDE TResult ProcessBefore(SProcessContext* pContext);
   MO_OVERRIDE TResult ProcessAfter(SProcessContext* pContext);
public:
   MO_ABSTRACT TResult Suspend();
   MO_ABSTRACT TResult Resume();
   MO_ABSTRACT TResult Dispose();
};

//============================================================
// <T>��ʾ����</T>
//============================================================
class MO_EG_DECLARE FDisplay : public FDrawable
{
   MO_CLASS_DECLARE_INHERITS(FDisplay, FDrawable);
public:
   typedef GPtrs<FDisplay> GDisplayPtrs;
protected:
   GDisplayPtrs _displays;
   GRenderablePtrs _renderables;
   GScriptablePtrs _scriptables;
public:
   FDisplay();
   MO_ABSTRACT ~FDisplay();
public:
   //------------------------------------------------------------
   // <T>�����ʾ���ϡ�</T>
   MO_INLINE GDisplayPtrs& Displays(){
      return _displays;
   }
   //------------------------------------------------------------
   // <T>�����Ⱦ���ϡ�</T>
   MO_INLINE GRenderablePtrs& Renderables(){
      return _renderables;
   }
   //------------------------------------------------------------
   // <T>��ýű����ϡ�</T>
   MO_INLINE GScriptablePtrs& Scriptables(){
      return _scriptables;
   }
public:
   MO_ABSTRACT TResult RenderablePush(FRenderable* pRenderable);
   MO_ABSTRACT TResult RenderableRemove(FRenderable* pRenderable);
   MO_ABSTRACT TResult RenderableClear();
   MO_ABSTRACT TResult DisplayPush(FDisplay* pDisplay);
   MO_ABSTRACT TResult DisplayRemove(FDisplay* pDisplay);
   MO_ABSTRACT TResult DisplayClear();
   MO_ABSTRACT TResult ScriptablePush(FScriptable* pScriptable);
   MO_ABSTRACT TResult ScriptableRemove(FScriptable* pScriptable);
   MO_ABSTRACT TResult ScriptableClear();
public:
   MO_OVERRIDE TResult FilterRegion(FRenderRegion* pRegion);
   MO_OVERRIDE TResult UpdateAllMatrix(SDrawableContext* pContext);
   MO_OVERRIDE TResult Update(SProcessContext* pContext);
   MO_OVERRIDE TResult ProcessBefore(SProcessContext* pContext);
   MO_OVERRIDE TResult ProcessAfter(SProcessContext* pContext);
   MO_OVERRIDE TResult Free();
public:
   MO_OVERRIDE TResult Suspend();
   MO_OVERRIDE TResult Resume();
   MO_OVERRIDE TResult Dispose();
};
//------------------------------------------------------------
typedef MO_EG_DECLARE GPtrs<FDisplay> GDisplayPtrs;

//============================================================
// <T>�ɻ��ƶ���㡣</T>
//============================================================
class MO_EG_DECLARE FDisplayLayer : public FDisplay
{
   MO_CLASS_DECLARE_INHERITS(FDisplayLayer, FDisplay);
protected:
   FStageLayer* _pStageLayer;
   FParticleController* _pParticleController;
   GPtr<FVisualRegion> _visualRegion;
public:
   FDisplayLayer();
   MO_ABSTRACT ~FDisplayLayer();
public:
   //------------------------------------------------------------
   // <T>�����̨�㡣</T>
   MO_INLINE FStageLayer* StageLayer(){
      return _pStageLayer;
   }
   //------------------------------------------------------------
   // <T>������̨�㡣</T>
   MO_INLINE void SetStageLayer(FStageLayer* pStageLayer){
      _pStageLayer = pStageLayer;
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
class MO_EG_DECLARE FStageLayer : public FInstance
{
   MO_CLASS_DECLARE_INHERITS(FStageLayer, FInstance);
protected:
   // ����
   TString _name;
   // ��̨
   FStage* _pStage;
   // ������ɫ
   SFloatColor4 _backgroundColor;
   // ��ȾĿ��
   GPtr<FRenderTarget> _renderTarget;
   // ��ʾ�㼯��
   FDisplayLayerCollection* _pLayers;
public:
   FStageLayer();
   MO_ABSTRACT ~FStageLayer();
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
   FDisplayLayer* LayerFind(TCharC* pName);
   TResult LayerPush(FDisplayLayer* pLayer);
   TResult LayerRemove(FDisplayLayer* pLayer);
   TResult LayerClear();
public:
   MO_ABSTRACT TResult FocusTest(FFocusTester* pTester);
public:
   MO_ABSTRACT TResult Active();
   MO_ABSTRACT TResult Deactive();
public:
   MO_ABSTRACT TResult BuildRegion(FRenderRegion* pRegion);
public:
   MO_ABSTRACT TResult Update(SProcessContext* pContext);
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
typedef MO_EG_DECLARE GPtrs<FStageLayer> GStageLayerPtrs;

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
   // �����㼯��
   GStageLayerPtrs _layers;
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
   // <T>��ó����㼯�ϡ�</T>
   MO_INLINE GStageLayerPtrs& Layers(){
      return _layers;
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
   FStageLayer* LayerFind(TCharC* pName);
   TResult LayerPush(FStageLayer* pLayer);
   TResult LayerRemove(FStageLayer* pLayer);
   TResult LayerClear();
public:
   MO_OVERRIDE TResult Setup();
public:
   MO_ABSTRACT TResult Active();
   MO_ABSTRACT TResult Deactive();
public:
   MO_ABSTRACT TResult BuildRegion(FRenderRegion* pRegion);
public:
   MO_ABSTRACT TResult Update(SProcessContext* pContext);
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
   MO_ABSTRACT TResult Startup();
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
