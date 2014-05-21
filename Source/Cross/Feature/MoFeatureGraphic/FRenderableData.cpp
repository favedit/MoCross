#include "MoFgBase.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FRenderableData, FInstance);

//============================================================
// <T>������Ⱦ�������ԡ�</T>
//============================================================
FRenderableData::FRenderableData(){
   _vertexCount = 0;
   MO_CLEAR(_pIndexBuffer);
}

//============================================================
// <T>������Ⱦ�������ԡ�</T>
//============================================================
FRenderableData::~FRenderableData(){
}

//============================================================
// <T>����ָ����������ԡ�</T>
//
// @param pCode ����
// @return ����
//============================================================
FRenderableAttribute* FRenderableData::AttributeFind(TCharC* pCode){
   MO_CHECK(pCode, return NULL);
   TInt count = _attributes.Count();
   for(TInt n = 0; n < count; n++){
      FRenderableAttribute* pRenderableAttribute = _attributes.Get(n);
      if(pRenderableAttribute->IsCode(pCode)){
         return pRenderableAttribute;
      }
   }
   return NULL;
}

//============================================================
// <T>���ָ����������ԡ�</T>
//
// @param pCode ����
// @return ����
//============================================================
FRenderableAttribute* FRenderableData::AttributeGet(TCharC* pCode){
   MO_CHECK(pCode, return NULL);
   FRenderableAttribute* pRenderableAttribute = AttributeFind(pCode);
   if(pRenderableAttribute == NULL){
      MO_FATAL("Can't find renderable attribute. (code=%s)", pCode);
   }
   return pRenderableAttribute;
}

//============================================================
// <T>����һ�����ԡ�</T>
//
// @param pAttribute ����
// @return ������
//============================================================
TResult FRenderableData::AttributePush(FRenderableAttribute* pAttribute){
   MO_CHECK(pAttribute, return ENull);
   // �����Ƿ����
   TCharC* pCode = pAttribute->Code();
   FRenderableAttribute* pFind = AttributeFind(pCode);
   if(pFind != NULL){
      MO_FATAL("Attribute is already exists. (code=%s)", pCode);
      return EDuplicate;
   }
   // �������
   _attributes.Push(pAttribute);
   return ESuccess;
}

//============================================================
// <T>�Ƴ�һ�����ԡ�</T>
//
// @param pAttribute ����
// @return ������
//============================================================
TResult FRenderableData::AttributeRemove(FRenderableAttribute* pAttribute){
   MO_CHECK(pAttribute, return ENull);
   // �����Ƿ����
   if(!_attributes.Contains(pAttribute)){
      MO_FATAL("Attribute is not exists. (code=%s)", pAttribute->Code());
      return ENotExists;
   }
   // �������
   _attributes.Push(pAttribute);
   return ESuccess;
}

//============================================================
// <T>����ָ�����ݡ�</T>
//
// @param pData ����
// @return ������
//============================================================
TResult FRenderableData::Assign(FRenderableData* pData){
   MO_CHECK(pData, return ENull);
   // ��������
   _vertexCount = pData->VertexCount();
   // �������Լ���
   _attributes.Clear();
   GRenderableAttributePtrs::TIterator iterator = pData->Attributes().Iterator();
   while(iterator.Next()){
      _attributes.Push(*iterator);
   }
   // ��������
   _pIndexBuffer = pData->IndexBuffer();
   return ESuccess;
}

MO_NAMESPACE_END
