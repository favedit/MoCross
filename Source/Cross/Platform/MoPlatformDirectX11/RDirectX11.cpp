#include "MoPd11Core.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>ת�����ģʽ���͡�</T>
//
// @param fillCd ���ģʽ
// @return ������
//============================================================
D3D11_FILL_MODE RDirectX11::ConvertFillMode(ERenderFillMode fillCd){
   switch(fillCd){
      case ERenderFillMode_Line:
         return D3D11_FILL_WIREFRAME;
      case ERenderFillMode_Fill:
         return D3D11_FILL_SOLID;
   }
   MO_STATIC_FATAL("Convert fill mode failure. (fill=%d)", fillCd);
   return D3D11_FILL_SOLID;
}

//============================================================
// <T>ת���޳�ģʽ���͡�</T>
//
// @param cullCd �޳�ģʽ
// @return ������
//============================================================
D3D11_CULL_MODE RDirectX11::ConvertCullMode(ERenderCullMode cullCd){
   switch(cullCd){
      case ERenderCullMode_Front:
         return D3D11_CULL_FRONT;
      case ERenderCullMode_Back:
         return D3D11_CULL_BACK;
      case ERenderCullMode_Both:
         return D3D11_CULL_NONE;
   }
   MO_STATIC_FATAL("Convert cull mode failure. (cull=%d)", cullCd);
   return D3D11_CULL_NONE;
}

//============================================================
// <T>ת������������͡�</T>
//
// @param strideCd �������
// @return ������
//============================================================
DXGI_FORMAT RDirectX11::ConvertIndexStride(ERenderIndexStride strideCd){
   switch(strideCd){
      case ERenderIndexStride_Uint16:
         return DXGI_FORMAT_R16_UINT;
      case ERenderIndexStride_Uint32:
         return DXGI_FORMAT_R32_UINT;
   }
   MO_STATIC_FATAL("Convert index stride failure. (stride=%d)", strideCd);
   return DXGI_FORMAT_UNKNOWN;
}

MO_NAMESPACE_END
