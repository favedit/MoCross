#include "MoFgBitmap.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FImage, FInstance);

//============================================================
// <T>����ͼ�Ρ�</T>
//============================================================
FImage::FImage(){
   _formatCd = EImageFormat_A8R8G8B8;
}

//============================================================
// <T>����ͼ�Ρ�</T>
//============================================================
FImage::~FImage(){
}

MO_NAMESPACE_END
