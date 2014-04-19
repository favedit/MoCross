#include "MoFgRender.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FRenderTarget, FRenderInstance);

//============================================================
// <T>������ȾĿ�ꡣ</T>
//============================================================
FRenderTarget::FRenderTarget(){
   _optionDepth = EFalse;
   _optionStencil = EFalse;
   _size.Set(1024, 1024);
   _usageCd = ERenderUsage_ReadWrite;
   _textureCd = ERenderTexture_Unknown;
   _formatCd = ERenderTextureFormat_Unknown;
   _backgroundColor.Set(0.0f, 0.0f, 0.0f, 0.0f);
   _pTextures = MO_CREATE(FRenderTextureCollection);
}

//============================================================
// <T>������ȾĿ�ꡣ</T>
//============================================================
FRenderTarget::~FRenderTarget(){
   MO_DELETE(_pTextures);
}

//============================================================
// <T>���ô���</T>
//
// @return ������
//============================================================
TResult FRenderTarget::OnSetup(){
   return ESuccess;
}

//============================================================
// <T>���ô���</T>
//
// @return ������
//============================================================
TResult FRenderTarget::Setup(){
   TResult result = EContinue;
   if(!_statusSetup){
      result = OnSetup();
      if(result){
         MO_WARN("Setup result is not success. (result=%d)", result);
      }
      _statusSetup = ETrue;
   }
   return result;
}

MO_NAMESPACE_END
