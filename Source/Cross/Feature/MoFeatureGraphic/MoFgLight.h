#ifndef __MO_FG_LIGHT_H__
#define __MO_FG_LIGHT_H__
//************************************************************

#ifndef __MO_FG_COMMON_H__
#include "MoFgCommon.h"
#endif // __MO_FG_COMMON_H__

#ifndef __MO_FG_CAMERA_H__
#include "MoFgCamera.h"
#endif // __MO_FG_CAMERA_H__

#ifndef __MO_FG_MATERIAL_H__
#include "MoFgMaterial.h"
#endif // __MO_FG_MATERIAL_H__

MO_NAMESPACE_BEGIN

//============================================================
class FLight;

//============================================================
// <T>��Դ��Ӱ��Ϣ��</T>
//============================================================
struct MO_FG_DECLARE SLightShadow{
public:
   // ����
   TFloat _base;
   // ����
   TFloat _rate;
   // �㼶
   TFloat _level;
   // ��Χ
   TFloat _range;
public:
   //------------------------------------------------------------
   // <T>�����Դ��Ӱ��Ϣ��</T>
   SLightShadow(){
      _base = 0.00000005f;
      _rate = 0.5f;
      _level = 0.000004f;
      _range = 0.0f;
   }
public:
   //------------------------------------------------------------
   // <T>���������з����л���Ϣ��</T>
   void Unserialize(IDataInput* pInput){
      _base = pInput->ReadFloat();
      _rate = pInput->ReadFloat();
      _level = pInput->ReadFloat();
      _range = pInput->ReadFloat();
   }
};

//============================================================
// <T>��Դ��</T>
//============================================================
class MO_FG_DECLARE FLight : public FInstance
{
   MO_CLASS_DECLARE_INHERITS(FLight, FInstance);
protected:
   // ���ĵ�
   SFloatPoint3 _center;
   // ����
   //TInt _typeCd;
   // ���ø���
   //TBool _optionTrack;
   // ��Ӱ��Ϣ1
   //SLightShadow _shadow1;
   // ��Ӱ��Ϣ2
   //SLightShadow _shadow2;
   // ��Ӱ��Ϣ3
   //SLightShadow _shadow3;
   // ��Ӱ������С
   //TFloat shadowAmbientMin;
   // ��Ӱ�������
   //TFloat shadowAmbientMax;
   // ��Ӱ�������
   //TFloat shadowAmbientThick;
   // ��Ӱ������Χ
   //TFloat shadowAmbientRange;
   // ��Ӱ�ں�1����
   //TFloat shadowMerge1Base;
   // ��Ӱ�ں�1����
   //TFloat shadowMerge1Rate;
   // ��Ӱ�ں�2����
   //TFloat shadowMerge2Base;
   // ��Ӱ�ں�2����
   //TFloat shadowMerge2Rate;
   // ������Ϣ
   // TFloat material:FGeLightMaterial = new FGeLightMaterial(); 
public:
   FLight();
   MO_ABSTRACT ~FLight();
public:
   //------------------------------------------------------------
   // <T>������ĵ㡣</T>
   MO_INLINE SFloatPoint3& Center(){
      return _center;
   }
};
//------------------------------------------------------------
typedef MO_FG_DECLARE FObjects<FLight*> FLightCollection;
typedef MO_FG_DECLARE FList<FLight*> FLightList;

//============================================================
// <T>�����Դ��</T>
//============================================================
class MO_FG_DECLARE FDirectionalLight : public FLight
{
   MO_CLASS_DECLARE_INHERITS(FDirectionalLight, FLight);
protected:
   GPtr<FCamera> _camera;
   GPtr<FViewport> _viewport;
   SFloatVector3 _direction;
   GPtr<FMaterial> _material;
public:
   FDirectionalLight();
   MO_ABSTRACT ~FDirectionalLight();
public:
   //------------------------------------------------------------
   // <T>��������</T>
   MO_INLINE FCamera* Camera(){
      return _camera;
   }
   //------------------------------------------------------------
   // <T>���������</T>
   MO_INLINE void SetCamera(FCamera* pCamera){
      _camera = pCamera;
   }
   //------------------------------------------------------------
   // <T>����ӽǡ�</T>
   MO_INLINE FViewport* Viewport(){
      return _viewport;
   }
   //------------------------------------------------------------
   // <T>�����ӽǡ�</T>
   MO_INLINE void SetViewport(FViewport* pViewport){
      _viewport = pViewport;
   }
   //------------------------------------------------------------
   // <T>��÷����Դ��</T>
   MO_INLINE SFloatVector3& Direction(){
      return _direction;
   }
   //------------------------------------------------------------
   // <T>��ò��ʡ�</T>
   MO_INLINE FMaterial* Material(){
      return _material;
   }
   //------------------------------------------------------------
   // <T>���ò��ʡ�</T>
   MO_INLINE void SetMaterial(FMaterial* pMaterial){
      _material = pMaterial;
   }
};

//============================================================
// <T>���Դ��</T>
//============================================================
class MO_FG_DECLARE FPointLight : public FLight
{
   MO_CLASS_DECLARE_INHERITS(FPointLight, FLight);
public:
   FPointLight();
   MO_ABSTRACT ~FPointLight();
};

//============================================================
// <T>�۽���Դ��</T>
//============================================================
class MO_FG_DECLARE FSpotLight : public FLight
{
   MO_CLASS_DECLARE_INHERITS(FSpotLight, FLight);
public:
   FSpotLight();
   MO_ABSTRACT ~FSpotLight();
};

MO_NAMESPACE_END

//************************************************************
#endif // __MO_FG_LIGHT_H__
