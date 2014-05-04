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

//============================================================
// <T>�����������͡�</T>
//
// @param componentType ������
// @param mask �ڱ�����
// @return ������
//============================================================
ERenderShaderAttributeFormat RDirectX11::ParseAttrbuteFormat(D3D_REGISTER_COMPONENT_TYPE componentType, TInt mask){
   // �ж�λ��
   TInt count = 0;
   if(mask & 0x01){
      count++;
   }
   if(mask & 0x02){
      count++;
   }
   if(mask & 0x04){
      count++;
   }
   if(mask & 0x08){
      count++;
   }
   // ��������
   switch(componentType){
      case D3D_REGISTER_COMPONENT_UINT32:
         break;
      case D3D_REGISTER_COMPONENT_SINT32:
         break;
      case D3D_REGISTER_COMPONENT_FLOAT32:{
         if(count == 1){
            return ERenderShaderAttributeFormat_Float1;
         }else if(count == 2){
            return ERenderShaderAttributeFormat_Float2;
         }else if(count == 3){
            return ERenderShaderAttributeFormat_Float3;
         }else if(count == 4){
            return ERenderShaderAttributeFormat_Float4;
         }
      }
   }
   MO_STATIC_FATAL("Parse attribtue format failure. (component_type=%d)", componentType);
   return ERenderShaderAttributeFormat_Unknown;
}

//============================================================
// <T>ת�����Ը�ʽ��</T>
//
// @param formatCd ��ʽ
// @return ���Ը�ʽ
//============================================================
DXGI_FORMAT RDirectX11::ConvertAttrbuteFormat(ERenderShaderAttributeFormat formatCd){
   switch(formatCd){
      case ERenderShaderAttributeFormat_Float1:
         return DXGI_FORMAT_R32_FLOAT;
      case ERenderShaderAttributeFormat_Float2:
         return DXGI_FORMAT_R32G32_FLOAT;
      case ERenderShaderAttributeFormat_Float3:
         return DXGI_FORMAT_R32G32B32_FLOAT;
      case ERenderShaderAttributeFormat_Float4:
         return DXGI_FORMAT_R32G32B32A32_FLOAT;
      case ERenderShaderAttributeFormat_Byte4:
         return DXGI_FORMAT_R8G8B8A8_UINT;
      case ERenderShaderAttributeFormat_Byte4Normal:
         return DXGI_FORMAT_R8G8B8A8_SNORM;
   }
   MO_STATIC_FATAL("Convert attribute format failure. (format=%d)", formatCd);
   return DXGI_FORMAT_UNKNOWN;
}

MO_NAMESPACE_END
