#include "MoFgRender.h"

MO_NAMESPACE_BEGIN

//MO_CLASS_IMPLEMENT_INHERITS(FRenderTextures, FInstance);
//
////============================================================
//// <T>������Ⱦ�����ϡ�</T>
////============================================================
//FRenderTextures::FRenderTextures(){
//   _pTextures = MO_CREATE(FRenderTextureCollection);
//}
//
////============================================================
//// <T>������Ⱦ�����ϡ�</T>
////============================================================
//FRenderTextures::~FRenderTextures(){
//   MO_DELETE(_pTextures);
//}
//
////============================================================
//// <T>�������������</T>
////
//// @return ��������
////============================================================
//TInt FRenderTextures::Count(){
//   return _pTextures->Count();
//}
//
////============================================================
//// <T>���ָ������λ�õ�����</T>
////
//// @param index ����λ��
//// @return ����
////============================================================
//FRenderTexture* FRenderTextures::Get(TInt index){
//   return _pTextures->Get(index);
//}
//
////============================================================
//// <T>����һ������</T>
////
//// @param pTexture ����
////============================================================
//void FRenderTextures::Push(FRenderTexture* pTexture){
//   _pTextures->Push(pTexture);
//}
//
////============================================================
//// <T>���ݲ�ֵ�����Ͳ�����Ⱦ����</T>
////
//// @param samplerCd ��ֵ������
//// @return ��Ⱦ����
////============================================================
//FRenderTexture* FRenderTextures::FindTexture(ERenderSampler samplerCd){
//   TInt count = _pTextures->Count();
//   for(TInt n = 0; n < count; n++){
//      FRenderTexture* pTexture = _pTextures->Get(n);
//      if(pTexture->SamplerCd() == samplerCd){
//         return pTexture;
//      }
//   }
//   return NULL;
//}
//
////============================================================
//// <T>���ݲ�ֵ�����ͻ����Ⱦ����</T>
////
//// @param samplerCd ��ֵ������
//// @return ��Ⱦ����
////============================================================
//FRenderTexture* FRenderTextures::GetTexture(ERenderSampler samplerCd){
//   FRenderTexture* pTexture = FindTexture(samplerCd);
//   MO_CHECK(pTexture, return NULL);
//   return pTexture;
//}

MO_NAMESPACE_END
