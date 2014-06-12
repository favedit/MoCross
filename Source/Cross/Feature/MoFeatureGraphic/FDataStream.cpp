#include "MoFgStream.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>������������</T>
//============================================================
FDataStream::FDataStream(){
}

//============================================================
// <T>������������</T>
//============================================================
FDataStream::~FDataStream(){
}

//============================================================
// <T>���ֽ�����д��2���ֽڡ�</T>
//
// @param value1 �ֽ�1
// @param value2 �ֽ�2
//============================================================
void FDataStream::WriteByte2(TByte value1, TByte value2){
   TByte values[2];
   values[0] = value1;
   values[1] = value2;
   Write(values, sizeof(values));
}

//============================================================
// <T>���ֽ�����д��3���ֽڡ�</T>
//
// @param value1 �ֽ�1
// @param value2 �ֽ�2
// @param value3 �ֽ�3
//============================================================
void FDataStream::WriteByte3(TByte value1, TByte value2, TByte value3){
   TByte values[3];
   values[0] = value1;
   values[1] = value2;
   values[2] = value3;
   Write(values, sizeof(values));
}

//============================================================
// <T>���ֽ�����д��4���ֽڡ�</T>
//
// @param value1 �ֽ�1
// @param value2 �ֽ�2
// @param value3 �ֽ�3
// @param value4 �ֽ�4
//============================================================
void FDataStream::WriteByte4(TByte value1, TByte value2, TByte value3, TByte value4){
   TByte values[4];
   values[0] = value1;
   values[1] = value2;
   values[2] = value3;
   values[3] = value4;
   Write(values, sizeof(values));
}

//============================================================
// <T>���ֽ�����д��2��32λ��������</T>
//
// @param value1 ������1
// @param value2 ������2
//============================================================
void FDataStream::WriteFloat2(TFloat value1, TFloat value2){
   TFloat values[2];
   values[0] = value1;
   values[1] = value2;
   Write(values, sizeof(values));
}

//============================================================
// <T>���ֽ�����д��3��32λ��������</T>
//
// @param value1 ������1
// @param value2 ������2
// @param value3 ������3
//============================================================
void FDataStream::WriteFloat3(TFloat value1, TFloat value2, TFloat value3){
   TFloat values[3];
   values[0] = value1;
   values[1] = value2;
   values[2] = value3;
   Write(values, sizeof(values));
}

//============================================================
// <T>���ֽ�����д��4��32λ��������</T>
//
// @param value1 ������1
// @param value2 ������2
// @param value3 ������3
// @param value4 ������4
//============================================================
void FDataStream::WriteFloat4(TFloat value1, TFloat value2, TFloat value3, TFloat value4){
   TFloat values[4];
   values[0] = value1;
   values[1] = value2;
   values[2] = value3;
   values[3] = value4;
   Write(values, sizeof(values));
}

MO_NAMESPACE_END
