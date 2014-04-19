#ifndef __MO_EG_PROCESSOR_H__
#define __MO_EG_PROCESSOR_H__
//************************************************************

#ifndef __MO_EG_COMMON_H__
#include "MoEgCommon.h"
#endif // __MO_EG_COMMON_H__

#ifndef __MO_EG_CORE_H__
#include "MoEgCore.h"
#endif // __MO_EG_CORE_H__

MO_NAMESPACE_BEGIN

//============================================================
// <T>�첽����ӿڡ�</T>
//============================================================
class MO_EG_DECLARE IProcessor{
public:
   //------------------------------------------------------------
   // <T>�����첽����ӿڡ�</T>
   MO_ABSTRACT ~IProcessor(){
   }
public:
   MO_VIRTUAL TResult AnsyProcess() = 0;
};
//------------------------------------------------------------
typedef MO_EG_DECLARE FLooper<IProcessor*> FProcessorLooper;

//============================================================
// <T>�첽�����̡߳�</T>
//============================================================
class MO_EG_DECLARE FProcessorThread : public FThread{
protected:
   TInt _interval;
   TThreadLocker _locker;
   TInt _looperLimit;
   FProcessorLooper* _pLooper;
public:
   FProcessorThread();
   MO_ABSTRACT ~FProcessorThread();
public:
   //------------------------------------------------------------
   // <T>���ѭ�����ơ�</T>
   MO_INLINE TInt LooperLimit(){
      return _looperLimit;
   }
   //------------------------------------------------------------
   // <T>����ѭ�����ơ�</T>
   MO_INLINE void SetLooperLimit(TInt looperLimit){
      _looperLimit = looperLimit;
   }
   //------------------------------------------------------------
   // <T>���ģ�ͼ��ϡ�</T>
   MO_INLINE FProcessorLooper* Looper(){
      return _pLooper;
   }
public:
   TResult Register(IProcessor* pProcessor);
   TResult Unregister(IProcessor* pProcessor);
public:
   MO_OVERRIDE TResult Process();
public:
   TResult Clear();
};

//============================================================
// <T>�첽��������</T>
//============================================================
class MO_EG_DECLARE FProcessor : public FInstance
{
   MO_CLASS_DECLARE_INHERITS(FProcessor, FInstance);
protected:
   FProcessorThread* _pThread;
public:
   FProcessor();
   MO_ABSTRACT ~FProcessor();
public:
   //------------------------------------------------------------
   // <T>����̡߳�</T>
   MO_INLINE FProcessorThread* Thread(){
      return _pThread;
   }
public:
   TResult Register(IProcessor* pProcessor);
   TResult Unregister(IProcessor* pProcessor);
public:
   TResult Startup();
   TResult Shutdown();
public:
   TResult Clear();
};
//------------------------------------------------------------
typedef MO_EG_DECLARE FObjects<FProcessor*> FProcessorCollection;

//============================================================
// <T>�첽�������̨��</T>
//============================================================
class MO_EG_DECLARE FProcessorConsole : public FConsole{
protected:
   FProcessorCollection* _pProcessores;
public:
   FProcessorConsole();
   MO_ABSTRACT ~FProcessorConsole();
public:
   //------------------------------------------------------------
   // <T>��ô��������ϡ�</T>
   MO_INLINE FProcessorCollection* Processores(){
      return _pProcessores;
   }
public:
   TResult Register(FProcessor* pProcessor);
   TResult Unregister(FProcessor* pProcessor);
public:
   TResult Startup();
   TResult Shutdown();
};

//============================================================
// <T>�첽�����������</T>
//============================================================
class MO_EG_DECLARE RProcessorManager : public RSingleton<FProcessorConsole>{
};

MO_NAMESPACE_END

//************************************************************
#endif // __MO_EG_PROCESSOR_H__
