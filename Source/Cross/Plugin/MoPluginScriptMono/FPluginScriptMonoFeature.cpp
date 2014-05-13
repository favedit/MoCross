#include "MoPluginScriptMono.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FPluginScriptMonoFeature, FFeature);

//============================================================
// <T>����ƽ̨DirectX11���ܡ�</T>
//============================================================
FPluginScriptMonoFeature::FPluginScriptMonoFeature(){
   _name = "DirectX 11";
}

//============================================================
// <T>����ƽ̨DirectX11���ܡ�</T>
//============================================================
FPluginScriptMonoFeature::~FPluginScriptMonoFeature(){
}

//============================================================
// <T>���������</T>
//
// @return ������
//============================================================
TResult FPluginScriptMonoFeature::Construct(){
   TResult resultCd = FFeature::Construct();
   return resultCd;
}

//============================================================
// <T>��������</T>
//
// @return ������
//============================================================
TResult FPluginScriptMonoFeature::Startup(){
   TResult resultCd = FFeature::Startup();
   return resultCd;
}

//============================================================
// <T>������</T>
//
// @return ������
//============================================================
TResult FPluginScriptMonoFeature::Suspend(){
   TResult resultCd = FFeature::Suspend();
   return resultCd;
}

//============================================================
// <T>��������</T>
//
// @return ������
//============================================================
TResult FPluginScriptMonoFeature::Resume(){
   TResult resultCd = FFeature::Resume();
   return resultCd;
}

//============================================================
// <T>ֹͣ����</T>
//
// @return ������
//============================================================
TResult FPluginScriptMonoFeature::Shutdown(){
   TResult resultCd = FFeature::Shutdown();
   return resultCd;
}

//============================================================
// <T>�ͷ������</T>
//
// @return ������
//============================================================
TResult FPluginScriptMonoFeature::Dispose(){
   TResult resultCd = FFeature::Dispose();
   return resultCd;
}

MO_NAMESPACE_END
