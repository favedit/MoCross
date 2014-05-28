#include "MoFgRender.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FRenderStatistics, FStatistics);

//============================================================
// <T>������Ⱦͳ������</T>
//============================================================
FRenderStatistics::FRenderStatistics(){
   Reset();
}

//============================================================
// <T>������Ⱦͳ������</T>
//============================================================
FRenderStatistics::~FRenderStatistics(){
}

//============================================================
// <T>����������������</T>
//============================================================
void FRenderStatistics::UpdateOptionFillCount(){
   _optionFillCount++;
}

//============================================================
// <T>����������ȴ�����</T>
//============================================================
void FRenderStatistics::UpdateOptionDeepCount(){
   _optionDeepCount++;
}

//============================================================
// <T>�������ü��ô�����</T>
//============================================================
void FRenderStatistics::UpdateOptionCullCount(){
   _optionCullCount++;
}

//============================================================
// <T>���������ںϴ�����</T>
//============================================================
void FRenderStatistics::UpdateOptionBlendCount(){
   _optionBlendCount++;
}

//============================================================
// <T>���³��������</T>
//============================================================
void FRenderStatistics::UpdateProgramCount(){
   _programCount++;
}

//============================================================
// <T>���³�����������</T>
//
// @param constLength ��������
//============================================================
void FRenderStatistics::UpdateProgramCount(TInt constLength){
   _programConstLength += constLength;
   _programConstCount++;
}

//============================================================
// <T>���»��ƴ�����</T>
//
// @param faceCount ������
//============================================================
void FRenderStatistics::UpdateDraw(TInt faceCount){
   _drawFaceCount += faceCount;
   _drawCount++;
}

//============================================================
// <T>���¶��㻺�������</T>
//============================================================
void FRenderStatistics::UpdateVertexBufferCount(){
   _vertexBufferCount++;
}

//============================================================
// <T>����ȡ����������</T>
//============================================================
void FRenderStatistics::UpdateSamplerCount(){
   _samplerCount++;
}

//============================================================
// <T>���ô���</T>
//
// @return ������
//============================================================
TResult FRenderStatistics::Reset(){
   TResult result = FStatistics::Reset();
   _optionFillCount = 0;
   _optionDeepCount = 0;
   _optionCullCount = 0;
   _optionBlendCount = 0;
   _programCount = 0;
   _programConstLength = 0;
   _programConstCount = 0;
   _vertexBufferCount = 0;
   _samplerCount = 0;
   _drawFaceCount = 0;
   _drawCount = 0;
   return result;
}

//============================================================
// <T>��ø�����Ϣ��</T>
//
// @return ������
//============================================================
TResult FRenderStatistics::Dump(MString* pDump){
   pDump->AppendFormat("Render statistics info: draw_face_count=%d, draw_count=%d\n", _drawFaceCount, _drawCount);
   pDump->AppendFormat("   status: program=%d, fill=%d, deep=%d, cull=%d, blend=%d\n", _programCount, _optionFillCount, _optionDeepCount, _optionCullCount, _optionBlendCount);
   pDump->AppendFormat("   const : const_length=%d, const_length=%d\n", _programConstLength, _programConstCount);
   pDump->AppendFormat("   object: vertex_count=%d, sampler_count=%d", _vertexBufferCount, _samplerCount);
   return ESuccess;
}

MO_NAMESPACE_END
