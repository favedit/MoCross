#include "MoE2Display.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>����ͼƬ����</T>
//============================================================
FPicture::FPicture(){
   //_objectCd |= EComponent_Renderable;
   _typeCd = EDisplayType_Picture;
   _pMaterial = MO_CREATE(FMaterial);
   //_pMaterial->SetEffectCd(ERenderEffect_2dTexture);
   MO_CLEAR(_pResource);
}

//============================================================
// <T>����ͼƬ����</T>
//============================================================
FPicture::~FPicture(){
   MO_DELETE(_pMaterial);
}

//============================================================
// <T>����λͼ��</T>
//
// @param pResource ��Դ
// @return ������
//============================================================
TResult FPicture::SetResource(FPictureResource* pResource){
   MO_CHECK(pResource, return ENull);
   SIntSize2& size = pResource->Size();
   _pResource = pResource;
   //_pMaterial->SetOptionDepth(EFalse);
   //_pMaterial->SetOptionAlpha(ETrue);
   //_pMaterial->TextureSet(pResource->Bitmap()->RenderTexture());
   //// ���δ���ù��ߴ磬��ʹ��Ĭ�ϳߴ�
   //if(_size.IsEmpty()){
   //   _size.Set((TFloat)size.width, (TFloat)size.height);
   //}
   return ESuccess;
}

MO_NAMESPACE_END
