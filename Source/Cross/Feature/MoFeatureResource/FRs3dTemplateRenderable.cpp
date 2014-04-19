#include "MoFrContent3dModel.h"
#include "MoFrContent3dTemplate.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FRs3dTemplateRenderable, FInstance);

//============================================================
// <T>������Դ3Dģ����Ⱦ����</T>
//============================================================
FRs3dTemplateRenderable::FRs3dTemplateRenderable(){
   _geometryIndex = 0;
}

//============================================================
// <T>������Դ3Dģ����Ⱦ����</T>
//============================================================
FRs3dTemplateRenderable::~FRs3dTemplateRenderable(){
}

//============================================================
// <T>���������ﷴ���л���Ϣ����</T>
//
// @param pInput ������
// @return ������
//============================================================
TResult FRs3dTemplateRenderable::Unserialize(IDataInput* pInput){
   MO_CHECK(pInput, return ENull);
   // ��ȡ��������
   _modelName.UnserializeAutomatic(pInput);
   _geometryIndex = pInput->ReadInt16();
   _materialName.UnserializeAutomatic(pInput);
   // ��������
   _optionInstanced = pInput->ReadBool();
   _instanceCount = pInput->ReadUint8();
   _optionDynamic = pInput->ReadBool();
   _optionMerge = pInput->ReadBool();
   _optionBoneScale = pInput->ReadBool();
   _optionSelect = pInput->ReadBool();
   _optionVisible = pInput->ReadBool();
   _optionGround = pInput->ReadBool();
   // ��ȡ����
   _matrix.Unserialize(pInput);
   return ESuccess;
}

MO_NAMESPACE_END
