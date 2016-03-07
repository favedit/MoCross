#include "MoFrContent3dModel.h"

MO_NAMESPACE_BEGIN;

//============================================================
// <T>������Դ��������</T>
//============================================================
FRs3dStream::FRs3dStream() {
   _pData = MO_CREATE(FByteStream);
}

//============================================================
// <T>������Դ��������</T>
//============================================================
FRs3dStream::~FRs3dStream() {
   MO_DELETE(_pData);
}

//============================================================
// <T>���л��ڲ����ݵ��������</T>
//
// @param pOutput �����
// @return ������
//============================================================
TResult FRs3dStream::Serialize(IDataOutput * pOutput){
   // �������
   pOutput->WriteString(_code);
   pOutput->WriteUint8((TUint8)_elementDataCd);
   pOutput->WriteUint8((TUint8)_elementCount);
   pOutput->WriteBool(EFalse);
   pOutput->WriteUint8((TUint8)_dataStride);
   pOutput->WriteUint32((TUint32)_dataCount);
   // �������
   pOutput->Write(_pData->MemoryC(), _pData->Length());
   return ESuccess;
}

MO_NAMESPACE_END;
