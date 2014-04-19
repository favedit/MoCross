#ifndef __MO_EG_CONTENT3D_SCENE_H__
#define __MO_EG_CONTENT3D_SCENE_H__
//************************************************************

#ifndef __MO_FR_COMMON_H__
#include "MoFrCommon.h"
#endif // __MO_FR_COMMON_H__

#ifndef __MO_FR_CONTENT3D_BASE_H__
#include "MoFrContent3dBase.h"
#endif // __MO_FR_CONTENT3D_BASE_H__

MO_NAMESPACE_BEGIN

//============================================================

//============================================================
// <T>�����������̡�</T>
//============================================================
class MO_FR_DECLARE FRs3dScenePass : public FInstance
{
   MO_CLASS_DECLARE_INHERITS(FRs3dScenePass, FInstance);
protected:
   // ����
   TString _name;
   // ��ȾĿ��ߴ�
   SIntSize2 _renderTargetSize;
public:
   FRs3dScenePass();
   MO_ABSTRACT ~FRs3dScenePass();
public:
   MO_ABSTRACT TResult Unserialize(IDataInput* pInput);
};
//------------------------------------------------------------
typedef MO_FR_DECLARE GPtrs<FRs3dScenePass> GRs3dScenePassPtrs;

//============================================================
// <T>����������Դ��</T>
//============================================================
class MO_FR_DECLARE FRs3dSceneTechnique : public FInstance
{
   MO_CLASS_DECLARE_INHERITS(FRs3dSceneTechnique, FInstance);
protected:
   // ����
   TString _name;
   // ���̼���
   GRs3dScenePassPtrs _passes;
public:
   FRs3dSceneTechnique();
   MO_ABSTRACT ~FRs3dSceneTechnique();
public:
   MO_ABSTRACT TResult Unserialize(IDataInput* pInput);
};

//============================================================
// <T>�����ӽ���Դ��</T>
//============================================================
class MO_FR_DECLARE FRs3dSceneViewport : public FInstance
{
   MO_CLASS_DECLARE_INHERITS(FRs3dSceneViewport, FInstance);
protected:
   // �н�
   TFloat _angle;
   // ��ƽ��
   TFloat _near;
   // Զƽ��
   TFloat _far;
public:
   FRs3dSceneViewport();
   MO_ABSTRACT ~FRs3dSceneViewport();
public:
   //------------------------------------------------------------
   // <T>��üнǡ�</T>
   MO_INLINE TFloat Angle(){
      return _angle;
   }
   //------------------------------------------------------------
   // <T>��ý�ƽ�档</T>
   MO_INLINE TFloat Near(){
      return _near;
   }
   //------------------------------------------------------------
   // <T>���Զƽ�档</T>
   MO_INLINE TFloat Far(){
      return _far;
   }
public:
   MO_ABSTRACT TResult Unserialize(IDataInput* pInput);
};

//============================================================
// <T>���������Դ��</T>
//============================================================
class MO_FR_DECLARE FRs3dSceneCamera : public FInstance
{
   MO_CLASS_DECLARE_INHERITS(FRs3dSceneCamera, FInstance);
protected:
   // ��������
   TFsName _typeName;
   // ����ǰ����
   TFloat _centerFront;
   // ���ĺ����
   TFloat _centerBack;
   // λ��
   SFloatPoint3 _position;
   // ����
   SFloatVector3 _direction;
   // ����ƽ��
   TFloat _focalNear;
   // Զ��ƽ��
   TFloat _focalFar;
   // �ӽ�
   GPtr<FRs3dSceneViewport> _viewport;
public:
   FRs3dSceneCamera();
   MO_ABSTRACT ~FRs3dSceneCamera();
public:
   //------------------------------------------------------------
   // <T>����������ơ�</T>
   MO_INLINE TCharC* TypeName(){
      return _typeName;
   }
   //------------------------------------------------------------
   // <T>���λ�á�</T>
   MO_INLINE SFloatPoint3& Position(){
      return _position;
   }
   //------------------------------------------------------------
   // <T>��÷���</T>
   MO_INLINE SFloatVector3& Direction(){
      return _direction;
   }
   //------------------------------------------------------------
   // <T>��ý���ƽ�档</T>
   MO_INLINE TFloat FocalNear(){
      return _focalNear;
   }
   //------------------------------------------------------------
   // <T>���Զ��ƽ�档</T>
   MO_INLINE TFloat FocalFar(){
      return _focalFar;
   }
   //------------------------------------------------------------
   // <T>����ӽǡ�</T>
   MO_INLINE FRs3dSceneViewport* Viewport(){
      return _viewport;
   }
public:
   MO_ABSTRACT TResult Unserialize(IDataInput* pInput);
};

//============================================================
// <T>����������Դ��</T>
//============================================================
class MO_FR_DECLARE FRs3dSceneMaterial : public FInstance
{
   MO_CLASS_DECLARE_INHERITS(FRs3dSceneMaterial, FInstance);
protected:
   // ����
   TString _name;
   // ��������
   TString _label;
   // ��������
   TString _typeName;
   // ������Ϣ
   SMaterialInfo _info;
   // ʱ����
   TInt _interval;
   // ��ת�Ƕ�
   SFloatVector3 _rotation;
   // �������
   //public var themeCode:String;
   // �߶�����
   SFloatColor4 _height;
   // �������
   TFloat _surfaceRate;
   // ���淴��
   TFloat _surfaceReflect;
   // ��������
   TFloat _surfaceBright;
   // �������ȼ���
   TFloat _surfaceBrightLevel;
   // ����ֲ�
   TFloat _surfaceCoarse;
   // ����ֲڼ���
   TFloat _surfaceCoarseLevel;
   // �����ں�
   TFloat _surfaceMerge;
   // ����ǿ��
   TFloat _surfacePower;
   //// ��Ӱ����
   //public var shadowMaterial:SFloatColor4 = new SFloatColor4(1.0, 1.0, 1.0, 1.0);
   //// ��Ӱ������
   //public var shadowMaterialInv:SFloatColor4 = new SFloatColor4(1.0, 1.0, 1.0, 1.0);
   ////............................................................
   //// ���⿪��
   //public var bloomEnable:Boolean;
   //// ��������
   //public var bloom:SFloatColor4 = new SFloatColor4(1.0, 1.0, 0.0, 0.0);
   //// ��⿪��
   //public var glossinessEnable:Boolean;
   //// �������
   //public var glossiness:SFloatColor4 = new SFloatColor4(1.0, 0.0, 0.0, 0.0);
   //// �ֲ�����
   //public var layer:SFloatColor4 = new SFloatColor4(0, 0, 0, 0);
   //// �ɼ���
   //public var visible:SFloatColor4 = new SFloatColor4(1.0, 1.0, 1.0, 1.0);
   //// ��Ӱ1
   //public var shadow1:SFloatColor4 = new SFloatColor4(1.0, 1.0, 1.0, 1.0);
   //// ��Ӱ2
   //public var shadow2:SFloatColor4 = new SFloatColor4(1.0, 1.0, 1.0, 1.0);
   //// ��Ӱ3
   //public var shadow3:SFloatColor4 = new SFloatColor4(1.0, 1.0, 1.0, 1.0);
   //// ��Ӱ����
   //public var shadowCoord:SFloatColor4 = new SFloatColor4(1.0, 1.0, 1.0, 1.0);
   //// ���Ա�־
   //public var identityFlag:String;
   //// ������
   //public var identityCode:String;
public:
   FRs3dSceneMaterial();
   MO_ABSTRACT ~FRs3dSceneMaterial();
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
   // <T>��ò�����Ϣ��</T>
   MO_INLINE SMaterialInfo& Info(){
      return _info;
   }
public:
   //------------------------------------------------------------
   // <T>���ò��ʸ߶���Ϣ��</T>
   void SetHeightDepth(TFloat value){
      _height.red = value;
      _height.green = value / 5.0f; // EGeEffect.HeightStep;
      _height.blue = 1.0f / 5.0f; // EGeEffect.HeightStep; // (�ƶ�����)
      _height.alpha = value * 2.0f; // (���ƫ��)
   }
public:
   MO_ABSTRACT TResult Unserialize(IDataInput* pInput);
};
//------------------------------------------------------------
typedef MO_FR_DECLARE GPtrs<FRs3dSceneMaterial> GRs3dSceneMaterialPtrs;

//============================================================
// <T>������Դ��Դ��</T>
//============================================================
class MO_FR_DECLARE FRs3dSceneLight : public FInstance
{
   MO_CLASS_DECLARE_INHERITS(FRs3dSceneLight, FInstance);
protected:
   // ����
   TFsName _typeName;
   // ���ø���
   TBool _optionTrack;
   // ��Ӱ1
   SShadowInfo _shadow1;
   // ��Ӱ2
   SShadowInfo _shadow2;
   // ��Ӱ3
   SShadowInfo _shadow3;
   // ��Ӱ������С
   TFloat _shadowAmbientMin;
   // ��Ӱ�������
   TFloat _shadowAmbientMax;
   // ��Ӱ�������
   TFloat _shadowAmbientThick;
   // ��Ӱ������Χ
   TFloat _shadowAmbientRange;
   // ��Ӱ�ں�1����
   TFloat _shadowMerge1Base;
   // ��Ӱ�ں�1����
   TFloat _shadowMerge1Rate;
   // ��Ӱ�ں�2����
   TFloat _shadowMerge2Base;
   // ��Ӱ�ں�2����
   TFloat _shadowMerge2Rate;
   // ��������
   GPtr<FRs3dSceneMaterial> _material;
   // �������
   GPtr<FRs3dSceneCamera> _camera;
public:
   FRs3dSceneLight();
   MO_ABSTRACT ~FRs3dSceneLight();
public:
   //------------------------------------------------------------
   // <T>��ó������ʡ�</T>
   MO_INLINE FRs3dSceneMaterial* Material(){
      return _material;
   }
   //------------------------------------------------------------
   // <T>��ó��������</T>
   MO_INLINE FRs3dSceneCamera* Camera(){
      return _camera;
   }
public:
   MO_ABSTRACT TResult Unserialize(IDataInput* pInput);
};

//============================================================
// <T>����������Դ��</T>
//============================================================
class MO_FR_DECLARE FRs3dSceneRegion : public FInstance
{
   MO_CLASS_DECLARE_INHERITS(FRs3dSceneRegion, FInstance);
protected:
   // ��ɫ
   SFloatColor4 _color;
   // ��ɫ����
   SFloatColor4 _colorLevel;
   // ����Ϣ
   SFogInfo _fog;
   // �߽���Ϣ
   SEdgeInfo _edge;
   // ƽ����Ϣ
   SFaceInfo _face;
   // ���
   GPtr<FRs3dSceneCamera> _camera;
   // ��Դ
   GPtr<FRs3dSceneLight> _light;
public:
   FRs3dSceneRegion();
   MO_ABSTRACT ~FRs3dSceneRegion();
public:
   //------------------------------------------------------------
   // <T>�����ɫ��</T>
   MO_INLINE SFloatColor4& Color(){
      return _color;
   }
   //------------------------------------------------------------
   // <T>��������</T>
   MO_INLINE FRs3dSceneCamera* Camera(){
      return _camera;
   }
   //------------------------------------------------------------
   // <T>��ù�Դ��</T>
   MO_INLINE FRs3dSceneLight* Light(){
      return _light;
   }
public:
   MO_ABSTRACT TResult Unserialize(IDataInput* pInput);
};

//============================================================
// <T>��Դ����������</T>
//============================================================
class MO_FR_DECLARE FRs3dSceneMovie : public FInstance
{
   MO_CLASS_DECLARE_INHERITS(FRs3dSceneMovie, FInstance);
protected:
   // ��������
   TString _typeName;
   // ʱ����
   TInt _interval;
   // ��ת�Ƕ�
   SFloatVector3 _rotation;
public:
   FRs3dSceneMovie();
   MO_ABSTRACT ~FRs3dSceneMovie();
public:
   //------------------------------------------------------------
   // <T>����������ơ�</T>
   MO_INLINE TCharC* TypeName(){
      return _typeName;
   }
   //------------------------------------------------------------
   // <T>��ü����</T>
   MO_INLINE TInt Interval(){
      return _interval;
   }
   //------------------------------------------------------------
   // <T>�����ת��</T>
   MO_INLINE SFloatVector3& Rotation(){
      return _rotation;
   }
public:
   MO_ABSTRACT TResult Unserialize(IDataInput* pInput);
};
//------------------------------------------------------------
typedef MO_FR_DECLARE GPtrs<FRs3dSceneMovie> GRs3dSceneMoviePtrs;

//============================================================
// <T>������Ⱦ��Դ��</T>
//============================================================
class MO_FR_DECLARE FRs3dSceneRenderable : public FInstance
{
   MO_CLASS_DECLARE_INHERITS(FRs3dSceneRenderable, FInstance);
protected:
   // ��������
   TFsName _name;
public:
   FRs3dSceneRenderable();
   MO_ABSTRACT ~FRs3dSceneRenderable();
public:
   //------------------------------------------------------------
   // <T>����������ơ�</T>
   MO_INLINE TCharC* Name(){
      return _name;
   }
public:
   MO_ABSTRACT TResult Unserialize(IDataInput* pInput);
};
//------------------------------------------------------------
typedef MO_FR_DECLARE GPtrs<FRs3dSceneRenderable> GRs3dSceneRenderablePtrs;

//============================================================
// <T>��Դ������Ϣ��</T>
//============================================================
class MO_FR_DECLARE FRs3dSceneDisplay : public FInstance
{
   MO_CLASS_DECLARE_INHERITS(FRs3dSceneDisplay, FInstance);
protected:
   // ��Դ
   TFsName _source;
   // �ϲ������־
   TBool _optionMergeVertex;
   // �ϲ����ʱ�־
   TBool _optionMergeMaterial;
   // ����
   SFloatMatrix3d _matrix;
   // ��������
   GRs3dSceneMoviePtrs _movies;
   // ���ʼ���
   GRs3dSceneMaterialPtrs _materials;
   // ��Ⱦ����
   GRs3dSceneRenderablePtrs _renderables;
public:
   FRs3dSceneDisplay();
   MO_ABSTRACT ~FRs3dSceneDisplay();
public:
   //------------------------------------------------------------
   // <T>�����Դ��</T>
   MO_INLINE TCharC* Source(){
      return _source;
   }
   //------------------------------------------------------------
   // <T>��úϲ������־��</T>
   MO_INLINE TBool OptionMergeVertex(){
      return _optionMergeVertex;
   }
   //------------------------------------------------------------
   // <T>��úϲ����ʱ�־��</T>
   MO_INLINE TBool OptionMergeMaterial(){
      return _optionMergeMaterial;
   }
   //------------------------------------------------------------
   // <T>��þ���</T>
   MO_INLINE SFloatMatrix3d& Matrix(){
      return _matrix;
   }
   //------------------------------------------------------------
   // <T>��ö������ϡ�</T>
   MO_INLINE GRs3dSceneMoviePtrs& Movies(){
      return _movies;
   }
   //------------------------------------------------------------
   // <T>��ò��ʼ��ϡ�</T>
   MO_INLINE GRs3dSceneMaterialPtrs& Materials(){
      return _materials;
   }
   //------------------------------------------------------------
   // <T>�����Ⱦ���ϡ�</T>
   MO_INLINE GRs3dSceneRenderablePtrs& Renderables(){
      return _renderables;
   }
public:
   MO_ABSTRACT TResult Unserialize(IDataInput* pInput);
};
//------------------------------------------------------------
typedef MO_FR_DECLARE GPtrs<FRs3dSceneDisplay> GRs3dSceneDisplayPtrs;

//============================================================
// <T>���������Դ��</T>
//============================================================
class MO_FR_DECLARE FRs3dSceneSky : public FInstance
{
   MO_CLASS_DECLARE_INHERITS(FRs3dSceneSky, FInstance);
protected:
   // ����
   TString _name;
   // ��������
   TString _typeName;
   // ��ʾ����
   GRs3dSceneDisplayPtrs _displays;
public:
   FRs3dSceneSky();
   MO_ABSTRACT ~FRs3dSceneSky();
public:
   //------------------------------------------------------------
   // <T>������ơ�</T>
   MO_INLINE TCharC* Name(){
      return _name;
   }
   //------------------------------------------------------------
   // <T>����������ơ�</T>
   MO_INLINE TCharC* TypeName(){
      return _typeName;
   }
   //------------------------------------------------------------
   // <T>�����ʾ���ϡ�</T>
   MO_INLINE GRs3dSceneDisplayPtrs& Displays(){
      return _displays;
   }
public:
   MO_ABSTRACT TResult Unserialize(IDataInput* pInput);
};

//============================================================
// <T>��Դ������Ϣ��</T>
//============================================================
class MO_FR_DECLARE FRs3dSceneMap : public FInstance
{
   MO_CLASS_DECLARE_INHERITS(FRs3dSceneMap, FInstance);
protected:
   // ����
   TString _name;
   // ��������
   TString _typeName;
   // ��ʾ����
   GRs3dSceneDisplayPtrs _displays;
public:
   FRs3dSceneMap();
   MO_ABSTRACT ~FRs3dSceneMap();
public:
   //------------------------------------------------------------
   // <T>������ơ�</T>
   MO_INLINE TCharC* Name(){
      return _name;
   }
   //------------------------------------------------------------
   // <T>����������ơ�</T>
   MO_INLINE TCharC* TypeName(){
      return _typeName;
   }
   //------------------------------------------------------------
   // <T>�����ʾ���ϡ�</T>
   MO_INLINE GRs3dSceneDisplayPtrs& Displays(){
      return _displays;
   }
public:
   MO_ABSTRACT TResult Unserialize(IDataInput* pInput);
};

//============================================================
// <T>�����ռ���Դ��</T>
//============================================================
class MO_FR_DECLARE FRs3dSceneSpace : public FInstance
{
   MO_CLASS_DECLARE_INHERITS(FRs3dSceneSpace, FInstance);
protected:
   // ����
   TString _name;
   // ��������
   TString _typeName;
   // ��ʾ����
   GRs3dSceneDisplayPtrs _displays;
public:
   FRs3dSceneSpace();
   MO_ABSTRACT ~FRs3dSceneSpace();
public:
   //------------------------------------------------------------
   // <T>������ơ�</T>
   MO_INLINE TCharC* Name(){
      return _name;
   }
   //------------------------------------------------------------
   // <T>����������ơ�</T>
   MO_INLINE TCharC* TypeName(){
      return _typeName;
   }
   //------------------------------------------------------------
   // <T>�����ʾ���ϡ�</T>
   MO_INLINE GRs3dSceneDisplayPtrs& Displays(){
      return _displays;
   }
public:
   MO_ABSTRACT TResult Unserialize(IDataInput* pInput);
};

//============================================================
// <T>��Դ������Ϣ��</T>
//============================================================
class MO_FR_DECLARE FRs3dScene : public FResource3d
{
   MO_CLASS_DECLARE_INHERITS(FRs3dScene, FResource3d);
protected:
   // �������
   TFsName _themeCode;
   // ����
   // TFsName theme:FGeRsTheme;
   // ����
   GPtr<FRs3dSceneTechnique> _technique;
   // ����
   GPtr<FRs3dSceneRegion> _region;
   // ���
   GPtr<FRs3dSceneSky> _sky;
   // ��ͼ
   GPtr<FRs3dSceneMap> _map;
   // �ռ�
   GPtr<FRs3dSceneSpace> _space;
public:
   FRs3dScene();
   MO_ABSTRACT ~FRs3dScene();
public:
   //------------------------------------------------------------
   // <T>��ü�����</T>
   MO_INLINE FRs3dSceneTechnique* Technique(){
      return _technique;
   }
   //------------------------------------------------------------
   // <T>�������</T>
   MO_INLINE FRs3dSceneRegion* Region(){
      return _region;
   }
   //------------------------------------------------------------
   // <T>�����ա�</T>
   MO_INLINE FRs3dSceneSky* Sky(){
      return _sky;
   }
   //------------------------------------------------------------
   // <T>��õ�ͼ��</T>
   MO_INLINE FRs3dSceneMap* Map(){
      return _map;
   }
   //------------------------------------------------------------
   // <T>��ÿռ䡣</T>
   MO_INLINE FRs3dSceneSpace* Space(){
      return _space;
   }
public:
   //MO_ABSTRACT TBool TestReady();
   //MO_ABSTRACT TBool TestValid();
public:
   MO_ABSTRACT TResult Unserialize(IDataInput* pInput);
//public:
//   MO_ABSTRACT TResult OnOpen();
//   MO_ABSTRACT TResult OnClose();
//public:
//   TResult Open();
//   TResult Close();
};
//------------------------------------------------------------
typedef MO_FR_DECLARE GPtrDictionary<FRs3dScene> GRs3dScenePtrDictionary;

//============================================================
// <T>��Դ��������̨��</T>
//============================================================
class MO_FR_DECLARE FRs3dSceneConsole : public FObject{
protected:
   GRs3dScenePtrDictionary _scenes;
public:
   FRs3dSceneConsole();
   MO_ABSTRACT ~FRs3dSceneConsole();
public:
   //------------------------------------------------------------
   // <T>��ó������ϡ�</T>
   MO_INLINE GRs3dScenePtrDictionary& Scenes(){
      return _scenes;
   }
public:
   MO_ABSTRACT FRs3dScene* Load(TCharC* pName);
public:
   FRs3dScene* Find(TCharC* pName);
   FRs3dScene* Open(TCharC* pName);
public:
   void Clear();
};

MO_NAMESPACE_END

//************************************************************
#endif // __MO_EG_CONTENT3D_SCENE_H__
