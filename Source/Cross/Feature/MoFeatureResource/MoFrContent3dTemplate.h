#ifndef __MO_FR_CONTENT3D_TEMPLATE_H__
#define __MO_FR_CONTENT3D_TEMPLATE_H__
//************************************************************

#ifndef __MO_FR_COMMON_H__
#include "MoFrCommon.h"
#endif // __MO_FR_COMMON_H__

#ifndef __MO_FR_CONTENT3D_BASE_H__
#include "MoFrContent3dBase.h"
#endif // __MO_FR_CONTENT3D_BASE_H__

MO_NAMESPACE_BEGIN

//============================================================
class FRs3dModelVector;

//============================================================
// <T>��Դ3Dģ����Ⱦ����</T>
//============================================================
class MO_FR_DECLARE FRs3dTemplateRenderable : public FInstance
{
   MO_CLASS_DECLARE_INHERITS(FRs3dTemplateRenderable, FInstance);
protected:
   // ģ������
   TFsName _modelName;
   // ��������
   TInt _geometryIndex;
   // ��������
   TFsName _materialName;
   // ʵ������
   TBool _optionInstanced;
   // ʵ�����
   TInt _instanceCount;
   // ��̬����
   TBool _optionDynamic;
   // �ں�����
   TBool _optionMerge;
   // ������������
   TBool _optionBoneScale;
   // ѡ������
   TBool _optionSelect;
   // �ɼ�����
   TBool _optionVisible;
   // ��������
   TBool _optionGround;
   // �任����
   SFloatMatrix3d _matrix;
public:
   FRs3dTemplateRenderable();
   MO_ABSTRACT ~FRs3dTemplateRenderable();
public:
   //------------------------------------------------------------
   // <T>���ģ����Դ��š�</T>
   MO_INLINE TCharC* ModelName(){
      return _modelName;
   }
   //------------------------------------------------------------
   // <T>��ü�����������</T>
   MO_INLINE TInt GeometryIndex(){
      return _geometryIndex;
   }
   //------------------------------------------------------------
   // <T>��ò�����Դ��š�</T>
   MO_INLINE TCharC* MaterialName(){
      return _materialName;
   }
   //------------------------------------------------------------
   // <T>���ʵ�����á�</T>
   MO_INLINE TBool OptionInstanced(){
      return _optionInstanced;
   }
   //------------------------------------------------------------
   // <T>���ʵ�������</T>
   MO_INLINE TBool InstanceCount(){
      return _instanceCount;
   }
   //------------------------------------------------------------
   // <T>��ö�̬���á�</T>
   MO_INLINE TBool OptionDynamic(){
      return _optionDynamic;
   }
   //------------------------------------------------------------
   // <T>����ں����á�</T>
   MO_INLINE TBool OptionMerge(){
      return _optionMerge;
   }
   //------------------------------------------------------------
   // <T>��ù����������á�</T>
   MO_INLINE TBool OptionBoneScale(){
      return _optionBoneScale;
   }
   //------------------------------------------------------------
   // <T>���ѡ�����á�</T>
   MO_INLINE TBool OptionSelect(){
      return _optionSelect;
   }
   //------------------------------------------------------------
   // <T>��ÿɼ����á�</T>
   MO_INLINE TBool OptionVisible(){
      return _optionVisible;
   }
   //------------------------------------------------------------
   // <T>��õ������á�</T>
   MO_INLINE TBool OptionGround(){
      return _optionGround;
   }
   //------------------------------------------------------------
   // <T>��ñ任����</T>
   MO_INLINE SFloatMatrix3d& Matrix(){
      return _matrix;
   }
public:
   MO_ABSTRACT TResult Unserialize(IDataInput* pInput);
};
//------------------------------------------------------------
typedef MO_FR_DECLARE FVector<FRs3dTemplateRenderable*> FRs3dTemplateRenderableCollection;

//============================================================
// <T>��Դ3Dģ�塣</T>
//============================================================
class MO_FR_DECLARE FRs3dTemplate : public FResource3d{
protected:
   FRs3dModelCollection* _pModels;
   FRs3dTemplateRenderableCollection* _pRenderables;
public:
   FRs3dTemplate();
   MO_ABSTRACT ~FRs3dTemplate();
public:
   //------------------------------------------------------------
   // <T>���ģ�ͼ��ϡ�</T>
   MO_INLINE FRs3dModelCollection* Models(){
      return _pModels;
   }
   //------------------------------------------------------------
   // <T>�����Ⱦ���ϡ�</T>
   MO_INLINE FRs3dTemplateRenderableCollection* Renderables(){
      return _pRenderables;
   }
public:
   MO_ABSTRACT TResult Unserialize(IDataInput* pInput);
   void RenderableClear();
};
//------------------------------------------------------------
typedef MO_FR_DECLARE FSet<TResourceId, FRs3dTemplate*> FRs3dTemplateSet;
typedef MO_FR_DECLARE FDictionary<FRs3dTemplate*> FRs3dTemplateDictionary;

//============================================================
// <T>��Դ3Dģ���������</T>
//============================================================
class MO_FR_DECLARE FRs3dTemplateConsole : public FConsole{
protected:
   FRs3dTemplateDictionary* _pTemplates;
public:
   FRs3dTemplateConsole();
   MO_ABSTRACT ~FRs3dTemplateConsole();
public:
   //------------------------------------------------------------
   // <T>���ģ�ͼ��ϡ�</T>
   MO_INLINE FRs3dTemplateDictionary* Templates(){
      return _pTemplates;
   }
public:
   MO_ABSTRACT FRs3dTemplate* Load(TCharC* pName);
public:
   FRs3dTemplate* Find(TCharC* pName);
public:
   void Clear();
};

MO_NAMESPACE_END

//************************************************************
#endif // __MO_FR_CONTENT3D_TEMPLATE_H__
