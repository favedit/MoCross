#ifndef __MO_EG_ENGINE_H__
#define __MO_EG_ENGINE_H__
//************************************************************

#ifndef __MO_EG_PLATFORM_H__
#include "MoEgPlatform.h"
#endif // __MO_EG_PLATFORM_H__

MO_NAMESPACE_BEGIN

//============================================================
// <T>����ͳ������</T>
//============================================================
class MO_EG_DECLARE FEngineStatistics : public FStatistics
{
   MO_CLASS_DECLARE_INHERITS(FEngineStatistics, FStatistics);
protected:
   GPtr<FStatistics> _frameStatistics;
   GPtr<FStatistics> _frameProcessBeforeStatistics;
   GPtr<FStatistics> _frameDrawStatistics;
   GPtr<FStatistics> _frameProcessAfterStatistics;
public:
   FEngineStatistics();
   MO_ABSTRACT ~FEngineStatistics();
public:
   //------------------------------------------------------------
   // <T>���֡ͳ�ơ�</T>
   MO_INLINE FStatistics* FrameStatistics(){
      return _frameStatistics;
   }
   //------------------------------------------------------------
   // <T>���֡��ʼ����ͳ�ơ�</T>
   MO_INLINE FStatistics* FrameProcessBeforeStatistics(){
      return _frameProcessBeforeStatistics;
   }
   //------------------------------------------------------------
   // <T>���֡ͳ�ơ�</T>
   MO_INLINE FStatistics* FrameDrawStatistics(){
      return _frameDrawStatistics;
   }
   //------------------------------------------------------------
   // <T>���֡��������ͳ�ơ�</T>
   MO_INLINE FStatistics* FrameProcessAfterStatistics(){
      return _frameProcessAfterStatistics;
   }
public:
   TResult Setup();
};

//============================================================
// <T>�������̨��</T>
//============================================================
class MO_EG_DECLARE FEngineConsole : public FConsole{
protected:
   GPtr<FStageEffect> _stageEffect;
   GPtr<FRenderRectangle> _renderRectangle;
   FRenderRegion* _pRegion;
   // ֡�����������
   TFrameListeners _listenersFrameEnter;
   // ֡�߼���������
   TFrameListeners _listenersFrameLogic;
   // ֡�뿪��������
   TFrameListeners _listenersFrameLeave;
   // ͳ����Ϣ
   GPtr<FEngineStatistics> _statistics;
public:
   FEngineConsole();
   MO_ABSTRACT ~FEngineConsole();
public:
   //------------------------------------------------------------
   // <T>���֡����������ϡ�</T>
   MO_INLINE TFrameListeners& ListenersFrameEnter(){
      return _listenersFrameEnter;
   }
   //------------------------------------------------------------
   // <T>���֡�߼��������ϡ�</T>
   MO_INLINE TFrameListeners& ListenersFrameLogic(){
      return _listenersFrameLogic;
   }
   //------------------------------------------------------------
   // <T>���֡����������ϡ�</T>
   MO_INLINE TFrameListeners& ListenersFrameLeave(){
      return _listenersFrameLeave;
   }
   //------------------------------------------------------------
   // <T>���ͳ����Ϣ��</T>
   MO_INLINE FEngineStatistics* Statistics(){
      return _statistics;
   }
public:
   MO_ABSTRACT void Setup();
public:
   MO_ABSTRACT TResult OnResize(SResizeEvent* pEvent);
public:
   MO_ABSTRACT TResult ProcessLayer(FDisplayLayer* pLayer);
   MO_ABSTRACT TResult ProcessFrame(FStageFrame* pFrame);
   MO_ABSTRACT TResult Process();
};

//============================================================
// <T>�����������</T>
//============================================================
class MO_EG_DECLARE REngineManager : public RSingleton<FEngineConsole>{
};

MO_NAMESPACE_END
      
//************************************************************
#endif // __MO_EG_ENGINE_H__
