#ifndef __MO_FR_CONTENT_H__
#define __MO_FR_CONTENT_H__
//************************************************************

#ifndef __MO_FR_COMMON_H__
#include "MoFrCommon.h"
#endif // __MO_FR_COMMON_H__

#ifndef __MO_FR_LOADER_H__
#include "MoFrLoader.h"
#endif // __MO_FR_LOADER_H__

MO_NAMESPACE_BEGIN

class FContent;
class FContentLoader;
class FContentConsole;

//============================================================
// <T>���ݡ�</T>
//============================================================
class MO_FR_DECLARE FContent : public FInstance
{
   MO_CLASS_DECLARE_INHERITS(FContent, FInstance);
protected:
   TString _typeName;
   TString _name;
   TTimeSpan _timeoutSpan;
   TBool _statusReady;
   TTimeTick _updateTick;
public:
   FContent();
   MO_ABSTRACT ~FContent();
public:
   //------------------------------------------------------------
   // <T>����������ơ�</T>
   MO_INLINE TCharC* TypeName(){
      return _typeName;
   }
   //------------------------------------------------------------
   // <T>�����������ơ�</T>
   MO_INLINE void SetTypeName(TCharC* pTypeName){
      _typeName = pTypeName;
   }
   //------------------------------------------------------------
   // <T>������ơ�</T>
   MO_INLINE TCharC* Name(){
      return _name;
   }
   //------------------------------------------------------------
   // <T>�������ơ�</T>
   MO_INLINE void SetName(TCharC* pName){
      _name = pName;
   }
   //------------------------------------------------------------
   // <T>��ó�ʱʱ����</T>
   MO_INLINE TTimeSpan TimeoutSpan(){
      return _timeoutSpan;
   }
   //------------------------------------------------------------
   // <T>���ó�ʱʱ����</T>
   MO_INLINE void SetTimeoutSpan(TTimeSpan timeoutSpan){
      _timeoutSpan = timeoutSpan;
   }
   //------------------------------------------------------------
   // <T>��ø���ʱ�̡�</T>
   MO_INLINE TTimeTick UpdateTick(){
      return _updateTick;
   }
   //------------------------------------------------------------
   // <T>���ø���ʱ�̡�</T>
   MO_INLINE void SetUpdateTick(TTimeTick updateTick){
      _updateTick = updateTick;
   }
public:
   MO_ABSTRACT TBool TestReady();
   MO_ABSTRACT TBool TestValid();
public:
   MO_ABSTRACT TResult Unserialize(IDataInput* pInput);
   MO_ABSTRACT TResult Complete();
public:
   MO_ABSTRACT TResult Process();
};
//------------------------------------------------------------
typedef MO_FR_DECLARE GPtr<FContent>  GContentPtr;
typedef MO_FR_DECLARE GPtrs<FContent> GContentPtrs;

//============================================================
// <T>���ݼ�������</T>
//============================================================
class MO_FR_DECLARE FContentLoader : public FLoader
{
   MO_CLASS_DECLARE_INHERITS(FContentLoader, FLoader);
protected:
   FContentConsole* _pConsole;
   TString _assetName;
   GContentPtr _content;
public:
   FContentLoader();
   MO_ABSTRACT ~FContentLoader();
public:
   //------------------------------------------------------------
   // <T>��ÿ���̨��</T>
   MO_INLINE FContentConsole* Console(){
      return _pConsole;
   }
   //------------------------------------------------------------
   // <T>���ÿ���̨��</T>
   MO_INLINE void SetConsole(FContentConsole* pConsole){
      _pConsole = pConsole;
   }
   //------------------------------------------------------------
   // <T>�����Դ���ơ�</T>
   MO_INLINE TCharC* AssetName(){
      return _assetName;
   }
   //------------------------------------------------------------
   // <T>������Դ���ơ�</T>
   MO_INLINE void SetAssetName(TCharC* pAssetName){
      _assetName = pAssetName;
   }
   //------------------------------------------------------------
   // <T>������ݡ�</T>
   MO_INLINE FContent* Content(){
      return _content;
   }
   //------------------------------------------------------------
   // <T>�������ݡ�</T>
   MO_INLINE void SetContent(FContent* pContent){
      _content = pContent;
   }
public:
   MO_OVERRIDE TResult Process();
};

//============================================================
// <T>���ݿ���̨��</T>
//============================================================
class MO_FR_DECLARE FContentConsole : public FConsole
{
   MO_CLASS_DECLARE_INHERITS(FContentConsole, FConsole);
protected:
   GClassInstanceFactoryPtr _pipelineFactory;
public:
   FContentConsole();
   MO_ABSTRACT ~FContentConsole();
public:
   //------------------------------------------------------------
   // <T>��ùܵ�������</T>
   MO_INLINE FClassInstanceFactory* PipelineFactory(){
      return _pipelineFactory;
   }
public:
   MO_ABSTRACT TResult PushLoader(FContentLoader* pLoader);
};

//============================================================
// <T>���ݹ�������</T>
//============================================================
class MO_FR_DECLARE RContentManager : public RSingleton<FContentConsole>{
};

MO_NAMESPACE_END

//************************************************************
#endif // __MO_FR_CONTENT_H__
