#include "MoFrContent3dModel.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FRs3dGeometry, FInstance);

//============================================================
// <T>������Դ3D�����塣</T>
//============================================================
FRs3dGeometry::FRs3dGeometry(){
   _optionInstanced = EFalse;
   _instanceCount = 0;
   _vertexBuffer = MO_CREATE(FRs3dVertexBuffer);
   _indexBuffer = MO_CREATE(FRs3dIndexBuffer);
   _pBoneIds = MO_CREATE(FBoneIds);
   _pTrack = MO_CREATE(FRs3dTrack);
}

//============================================================
// <T>������Դ3D�����塣</T>
//============================================================
FRs3dGeometry::~FRs3dGeometry(){
   MO_DELETE(_pBoneIds);
   MO_DELETE(_pTrack);
}

//============================================================
// <T>���������ﷴ���л���Ϣ����</T>
//
// @param pInput ������
// @return ������
//============================================================
TResult FRs3dGeometry::Unserialize(IDataInput* pInput){
   MO_CHECK(pInput, return ENull);
   // ��ȡ����
   _optionInstanced = pInput->ReadBool();
   _instanceCount = pInput->ReadUint8();
   _matrix.Unserialize(pInput);
   _outline.Unserialize(pInput);
   _materialName.UnserializeAutomatic(pInput);
   // ��ȡ���㻺��
   _vertexBuffer->Unserialize(pInput);
   // ��ȡ��������
   _indexBuffer->Unserialize(pInput);
   // ��ȡ��ͷ����
   TInt boneCount = pInput->ReadInt8();
   for(TInt n = 0; n < boneCount; n++){
      _pBoneIds->Push(pInput->ReadUint8());
   }
   // ��ȡ����
   _pTrack->Unserialize(pInput);
   MO_DEBUG(TC("Unserialize geometry success. (vertex=%d, index=%d, bone=%d, frame=%d)"),
         _vertexBuffer->Count(), _indexBuffer->Count(), boneCount, _pTrack->Frames().Count());
   return ESuccess;
}

MO_NAMESPACE_END
