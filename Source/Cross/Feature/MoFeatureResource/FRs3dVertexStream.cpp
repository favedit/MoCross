#include "MoFrContent3dModel.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FRs3dVertexStream, FInstance);

//============================================================
// <T>������Դ3D���㻺�塣</T>
//============================================================
FRs3dVertexStream::FRs3dVertexStream(){
   MO_CLEAR(_pBuffer);
   _formatCd = EContent3dVertexFormat_Float4;
   _stride = 0;
   _offset = 0;
}

//============================================================
// <T>������Դ3D���㻺�塣</T>
//============================================================
FRs3dVertexStream::~FRs3dVertexStream(){
}

//============================================================
// <T>���������ﷴ���л���Ϣ����</T>
//
// @param pInput ������
// @return ������
//============================================================
TResult FRs3dVertexStream::Unserialize(IDataInput* pInput){
   MO_CHECK(pInput, return ENull);
   // ��ȡ����
   _code.Unserialize(pInput);
   _formatCd = (EContent3dVertexFormat)pInput->ReadUint8();
   _stride = pInput->ReadUint8();
   _offset = pInput->ReadUint8();
   return ESuccess;
}

MO_NAMESPACE_END
