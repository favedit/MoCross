#include "MoPd11Render.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FPd11RenderLayout, FRenderLayout);

//============================================================
// <T>������Ⱦ����Ϣ��</T>
//============================================================
FPd11RenderLayout::FPd11RenderLayout(){
   _count = 0;
   MO_CLEAR(_piInputLayout);
}

//============================================================
// <T>������Ⱦ����Ϣ��</T>
//============================================================
FPd11RenderLayout::~FPd11RenderLayout(){
   MO_RELEASE(_piInputLayout);
}

//============================================================
// <T>���ô���</T>
//
// @return ������
//============================================================
TResult FPd11RenderLayout::OnSetup(){
   MO_CHECK(_pRenderable, return ENull);
   TInt index = 0;
   GRenderShaderAttributeDictionary::TIterator iterator = _pProgram->Attributes().IteratorC();
   while(iterator.Next()){
      FRenderProgramAttribute* pAttribute = *iterator;
      // ���ʹ����
      if(!pAttribute->IsStatusUsed()){
         continue;
      }
      // �����Ⱦ����
      TCharC* pLinker = pAttribute->Linker();
      FRenderableAttribute* pRenderableAttribute = _pRenderable->AttributeFind(pLinker);
      MO_CHECK(pRenderableAttribute->CheckValid(), continue);
      //............................................................
      // ���û�����Ϣ
      if(pRenderableAttribute != NULL){
         FPd11RenderVertexBuffer* pVertexBuffer = pRenderableAttribute->VertexBuffer()->Convert<FPd11RenderVertexBuffer>();
         _piBuffer[index] = pVertexBuffer->NativeBuffer();
         _strides[index] = pVertexBuffer->Stride();
         _offsets[index] = pRenderableAttribute->Offset();
      }else{
         _piBuffer[index] = NULL;
         _strides[index] = 0;
         _offsets[index] = 0;
      }
      index++;
   }
   _count = index;
   return ESuccess;
}

MO_NAMESPACE_END
