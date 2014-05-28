#include "MoPoRender.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FPoRenderLayout, FRenderLayout);

//============================================================
// <T>������Ⱦ����Ϣ��</T>
//============================================================
FPoRenderLayout::FPoRenderLayout(){
   _count = 0;
}

//============================================================
// <T>������Ⱦ����Ϣ��</T>
//============================================================
FPoRenderLayout::~FPoRenderLayout(){
}

//============================================================
// <T>���ô���</T>
//
// @return ������
//============================================================
TResult FPoRenderLayout::OnSetup(){
   MO_CHECK(_pRenderable, return ENull);
   TInt index = 0;
   GRenderShaderAttributePtrs& attributes = _pProgram->Attributes();
   TInt count = attributes.Count();
   for(TInt n = 0; n < count; n++){
      FRenderProgramAttribute* pAttribute = _pProgram->Attributes().Get(n);
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
         FPoRenderVertexBuffer* pVertexBuffer = pRenderableAttribute->GraphicsObject<FPoRenderVertexBuffer>();
         _pBuffers[index] = pVertexBuffer;
         _slots[index] = pAttribute->Slot();
         _offsets[index] = pRenderableAttribute->Offset();
         _formats[index] = pAttribute->FormatCd();
         index++;
      }
   }
   _count = index;
   return ESuccess;
}

MO_NAMESPACE_END
