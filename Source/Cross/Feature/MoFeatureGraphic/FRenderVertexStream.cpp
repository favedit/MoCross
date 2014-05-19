#include "MoFgRender.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FRenderVertexStream, FInstance);

//============================================================
// <T>������Ⱦ���㻺�塣</T>
//============================================================
FRenderVertexStream::FRenderVertexStream(){
   _formatCd = ERenderAttributeFormat_Unknown;
   _offset = 0;
   MO_CLEAR(_pVertexBuffer);
}

//============================================================
// <T>������Ⱦ���㻺�塣</T>
//============================================================
FRenderVertexStream::~FRenderVertexStream(){
}

//============================================================
// <T>��ö����ȡ�</T>
//
// @return ���
//============================================================
TInt FRenderVertexStream::Stride(){
   TInt stride = 0;
   if(_pVertexBuffer != NULL){
      stride = _pVertexBuffer->Stride();
   }
   return stride;
}

MO_NAMESPACE_END
