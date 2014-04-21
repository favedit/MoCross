#ifndef __MO_FP_TAIL_H__
#define __MO_FP_TAIL_H__
//************************************************************

#ifndef __MO_FP_COMMON_H__
#include "MoFpCommon.h"
#endif // __MO_FP_COMMON_H__

MO_NAMESPACE_BEGIN

//============================================================
// <T>������Ϣ��</T>
//============================================================
struct MO_FP_DECLARE STailInfo{
public:
   // ����
   SFloatPoint3 location;
   // �ߴ�
   SFloatSize3 size;
   // ��ת
   SFloatVector3 rotation;
   // ������ɫ
   SFloatColor4 groundColor;
   // ��������
   SFloatCoord coord;
public:
   //------------------------------------------------------------
   // <T>���������Ϣ��</T>
   STailInfo(){
   }
};
//------------------------------------------------------------
typedef MO_FP_DECLARE TFixVector<STailInfo, 64> TFsTailInfoVector;

//============================================================
// <T>���ٿ�������</T>
//============================================================
class MO_FP_DECLARE FTailController : public FObject{
protected:
   TInt _limit;
   TInt _interval;
   TFsTailInfoVector _infos;
   TTimeTick _lastTick;
public:
   FTailController();
   MO_ABSTRACT ~FTailController();
public:
   //------------------------------------------------------------
   // <T>��ü���������</T>
   MO_INLINE TInt Limit(){
      return _limit;
   }
   //------------------------------------------------------------
   // <T>���ü���������</T>
   MO_INLINE void SetLimit(TInt limit){
      _limit = limit;
   }
   //------------------------------------------------------------
   // <T>��ú�������</T>
   MO_INLINE TInt Interval(){
      return _interval;
   }
   //------------------------------------------------------------
   // <T>���ü���������</T>
   MO_INLINE void SetInterval(TInt interval){
      _interval = interval;
   }
   //------------------------------------------------------------
   // <T>������Ϣ���ϡ�</T>
   MO_INLINE TFsTailInfoVector& Infos(){
      return _infos;
   }
public:
   TResult Push(STailInfo& info);
   TResult Reset();
};

MO_NAMESPACE_END

//************************************************************
#endif // __MO_FP_TAIL_H__
