#include "MoFgRender.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FRenderParameter, FRenderObject);

//============================================================
// <T>������Ⱦ��������</T>
//============================================================
FRenderParameter::FRenderParameter(){
   _code = -1;
   _shaderCd = ERenderShader_Unknown;
   _formatCd = ERenderParameterFormat_Unknown;
   _statusUsed = EFalse;
   _slot = -1;
   _size = 0;
   MO_CLEAR(_pShader);
}

//============================================================
// <T>������Ⱦ��������</T>
//============================================================
FRenderParameter::~FRenderParameter(){
}

//============================================================
// <T>����������ݡ�</T>
//
// @param pData ����
// @param capacity ����
// @return ������
//============================================================
TResult FRenderParameter::Get(TAny* pData, TInt capacity){
   MO_FATAL_UNSUPPORT();
   return EUnsupport;
}

//============================================================
// <T>�����������ݡ�</T>
//
// @param pData ����
// @param length ����
// @return ������
//============================================================
TResult FRenderParameter::Set(TAny* pData, TInt length){
   MO_CHECK(_buffer, return ENull);
   _buffer->Set(_slot, pData, length);
   return EUnsupport;
}

//============================================================
// <T>����3ά���������������ݡ�</T>
//
// @parma matrix ����
// @parma count ����
// @parma transpose �Ƿ�ת��
// @return ������
//============================================================
TResult FRenderParameter::SetFloat3(TFloat x, TFloat y, TFloat z){
   // ��������
   TFloat data[3];
   data[0] = x;
   data[1] = y;
   data[2] = z;
   // �ύ����
   TResult resultCd = Set(data, sizeof(TFloat) * 3);
   return resultCd;
}

//============================================================
// <T>����4ά���������������ݡ�</T>
//
// @parma matrix ����
// @parma count ����
// @parma transpose �Ƿ�ת��
// @return ������
//============================================================
TResult FRenderParameter::SetFloat4(TFloat x, TFloat y, TFloat z, TFloat w){
   // ��������
   TFloat data[4];
   data[0] = x;
   data[1] = y;
   data[2] = z;
   data[3] = w;
   // �ύ����
   TResult resultCd = Set(data, sizeof(TFloat) * 4);
   return resultCd;
}

//============================================================
// <T>����3x3������������ݡ�</T>
//
// @parma matrix ����
// @parma count ����
// @parma transpose �Ƿ�ת��
// @return ������
//============================================================
TResult FRenderParameter::SetMatrix3x3(const SFloatMatrix3d* pMatrix, TInt count, TBool transpose){
   MO_CHECK(pMatrix, return ENull);
   MO_CHECK(count > 0, return EFailure);
   MO_CHECK(count <= MO_EG_CONST_MATRIX_MAX, return EFailure);
   // ��������
   TFloat data[9 * MO_EG_CONST_MATRIX_MAX];
   TFloat* pWriter = data;
   for(TInt n = 0; n < count; n++){
      const SFloatMatrix3d& matrix = pMatrix[n];
      if(transpose){
         *pWriter++ = matrix.data[0][0];
         *pWriter++ = matrix.data[1][0];
         *pWriter++ = matrix.data[2][0];
         *pWriter++ = matrix.data[0][1];
         *pWriter++ = matrix.data[1][1];
         *pWriter++ = matrix.data[2][1];
         *pWriter++ = matrix.data[0][2];
         *pWriter++ = matrix.data[1][2];
         *pWriter++ = matrix.data[2][2];
      }else{
         *pWriter++ = matrix.data[0][0];
         *pWriter++ = matrix.data[0][1];
         *pWriter++ = matrix.data[0][2];
         *pWriter++ = matrix.data[1][0];
         *pWriter++ = matrix.data[1][1];
         *pWriter++ = matrix.data[1][2];
         *pWriter++ = matrix.data[2][0];
         *pWriter++ = matrix.data[2][1];
         *pWriter++ = matrix.data[2][2];
      }
   }
   // �ύ����
   TResult resultCd = Set(data, sizeof(TFloat) * 9 * count);
   return resultCd;
}

//============================================================
// <T>����4x3������������ݡ�</T>
//
// @parma matrix ����
// @parma count ����
// @parma transpose �Ƿ�ת��
// @return ������
//============================================================
TResult FRenderParameter::SetMatrix4x3(const SFloatMatrix3d* pMatrix, TInt count, TBool transpose){
   MO_CHECK(pMatrix, return ENull);
   MO_CHECK(count > 0, return EFailure);
   MO_CHECK(count <= MO_EG_CONST_MATRIX_MAX, return EFailure);
   // ��������
   TFloat data[12 * MO_EG_CONST_MATRIX_MAX];
   TFloat* pWriter = data;
   for(TInt n = 0; n < count; n++){
      const SFloatMatrix3d& matrix = pMatrix[n];
      if(transpose){
         *pWriter++ = matrix.data[0][0];
         *pWriter++ = matrix.data[1][0];
         *pWriter++ = matrix.data[2][0];
         *pWriter++ = matrix.data[3][0];
         *pWriter++ = matrix.data[0][1];
         *pWriter++ = matrix.data[1][1];
         *pWriter++ = matrix.data[2][1];
         *pWriter++ = matrix.data[3][1];
         *pWriter++ = matrix.data[0][2];
         *pWriter++ = matrix.data[1][2];
         *pWriter++ = matrix.data[2][2];
         *pWriter++ = matrix.data[3][2];
      }else{
         *pWriter++ = matrix.data[0][0];
         *pWriter++ = matrix.data[0][1];
         *pWriter++ = matrix.data[0][2];
         *pWriter++ = matrix.data[0][3];
         *pWriter++ = matrix.data[1][0];
         *pWriter++ = matrix.data[1][1];
         *pWriter++ = matrix.data[1][2];
         *pWriter++ = matrix.data[1][3];
         *pWriter++ = matrix.data[2][0];
         *pWriter++ = matrix.data[2][1];
         *pWriter++ = matrix.data[2][2];
         *pWriter++ = matrix.data[2][3];
      }
   }
   // �ύ����
   TResult resultCd = Set(data, sizeof(TFloat) * 12 * count);
   return resultCd;
}

//============================================================
// <T>����4x4������������ݡ�</T>
//
// @parma matrix ����
// @parma count ����
// @parma transpose �Ƿ�ת��
// @return ������
//============================================================
TResult FRenderParameter::SetMatrix4x4(const SFloatMatrix3d* pMatrix, TInt count, TBool transpose){
   MO_CHECK(pMatrix, return ENull);
   MO_CHECK(count > 0, return EFailure);
   MO_CHECK(count <= MO_EG_CONST_MATRIX_MAX, return EFailure);
   // ��������
   TFloat data[16 * MO_EG_CONST_MATRIX_MAX];
   TFloat* pWriter = data;
   for(TInt n = 0; n < count; n++){
      const SFloatMatrix3d& matrix = pMatrix[n];
      if(transpose){
         *pWriter++ = matrix.data[0][0];
         *pWriter++ = matrix.data[1][0];
         *pWriter++ = matrix.data[2][0];
         *pWriter++ = matrix.data[3][0];
         *pWriter++ = matrix.data[0][1];
         *pWriter++ = matrix.data[1][1];
         *pWriter++ = matrix.data[2][1];
         *pWriter++ = matrix.data[3][1];
         *pWriter++ = matrix.data[0][2];
         *pWriter++ = matrix.data[1][2];
         *pWriter++ = matrix.data[2][2];
         *pWriter++ = matrix.data[3][2];
         *pWriter++ = matrix.data[0][3];
         *pWriter++ = matrix.data[1][3];
         *pWriter++ = matrix.data[2][3];
         *pWriter++ = matrix.data[3][3];
      }else{
         *pWriter++ = matrix.data[0][0];
         *pWriter++ = matrix.data[0][1];
         *pWriter++ = matrix.data[0][2];
         *pWriter++ = matrix.data[0][3];
         *pWriter++ = matrix.data[1][0];
         *pWriter++ = matrix.data[1][1];
         *pWriter++ = matrix.data[1][2];
         *pWriter++ = matrix.data[1][3];
         *pWriter++ = matrix.data[2][0];
         *pWriter++ = matrix.data[2][1];
         *pWriter++ = matrix.data[2][2];
         *pWriter++ = matrix.data[2][3];
         *pWriter++ = matrix.data[3][0];
         *pWriter++ = matrix.data[3][1];
         *pWriter++ = matrix.data[3][2];
         *pWriter++ = matrix.data[3][3];
      }
   }
   // �ύ����
   TResult resultCd = Set(data, sizeof(TFloat) * 16 * count);
   return resultCd;
}

//============================================================
// <T>�������á�</T>
//
// @param pConfig ���ýڵ�
// @return ������
//============================================================
TResult FRenderParameter::LoadConfig(FXmlNode* pConfig){
   MO_CHECK(pConfig, return ENull);
   // ��������
   _name = pConfig->Get("name");
   // ���ù���
   _linker = pConfig->Get("linker");
   // ���ø�ʽ
   TCharC* pShader = pConfig->Get("shader", NULL);
   if(pShader != NULL){
      _shaderCd = RRenderShader::Parse(pShader);
   }
   // ���ø�ʽ
   TCharC* pFormat = pConfig->Get("format", NULL);
   if(pFormat != NULL){
      _formatCd = RRenderParameterFormat::Parse(pFormat);
   }
   return ESuccess;
}

MO_NAMESPACE_END
