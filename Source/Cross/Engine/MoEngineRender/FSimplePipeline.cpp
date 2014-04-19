#include "MoErPipeline.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FSimplePipeline, FPipeline);

//============================================================
// <T>�������Ⱦ�ܵ���</T>
//============================================================
FSimplePipeline::FSimplePipeline(){
   _name = "simple";
}

//============================================================
// <T>��������Ⱦ�ܵ���</T>
//============================================================
FSimplePipeline::~FSimplePipeline(){
}

//============================================================
// <T>���ô���</T>
//
// @return ������
//============================================================
TResult FSimplePipeline::OnSetup(){
   TResult result = FPipeline::OnSetup();
   // ������ɫ��Ⱦ����
   FSimpleColorPass* pPass = FSimpleColorPass::InstanceCreate();
   pPass->SetPipeline(this);
   pPass->Setup();
   _pPasses->Push(pPass);
   return result;
}

MO_NAMESPACE_END
