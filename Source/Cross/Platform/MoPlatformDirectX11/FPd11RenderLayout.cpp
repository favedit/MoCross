#include "MoPd11Render.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FPd11RenderLayout, FRenderLayout);

//============================================================
// <T>������Ⱦ����Ϣ��</T>
//============================================================
FPd11RenderLayout::FPd11RenderLayout(){
   _count = 0;
   MO_CLEAR(_piInputLayout);
   RTypes<ID3D11Buffer*>::Clear(_piBuffer, MO_RENDER_ATTRIBUTE_MAXCNT);
   RTypes<UINT>::Clear(_strides, MO_RENDER_ATTRIBUTE_MAXCNT);
   RTypes<UINT>::Clear(_offsets, MO_RENDER_ATTRIBUTE_MAXCNT);
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
         FPd11RenderVertexBuffer* pVertexBuffer = pRenderableAttribute->GraphicsObject<FPd11RenderVertexBuffer>();
         _piBuffer[n] = pVertexBuffer->NativeBuffer();
         _strides[n] = pVertexBuffer->Stride();
         _offsets[n] = pRenderableAttribute->Offset();
      }else{
         _piBuffer[n] = NULL;
         _strides[n] = 0;
         _offsets[n] = 0;
      }
   }
   _count = count;
   return ESuccess;
}

MO_NAMESPACE_END
