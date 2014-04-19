//============================================================
// <T>ϵͳ����ö�ٶ��塣</T>
//
// @version 1.0.1
// @auto ����������Ĵ��룬�����޸������ֶ��޸ı���ĵط��޸ġ�
//============================================================
#include "MoCrConstant.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>�����ַ�����������Э��ö���ࡣ</T>
//
// @param pValue �ַ���
// @return ö����
//============================================================
ENetProtocol REnumNetProtocol::Parse(TCharC* pValue){
   // �ж��Ƿ���Ҫ����
   if(RInt::IsInteger(pValue)){
      return (ENetProtocol)RInt::Parse(pValue);
   }
   // ���ö��ֵ
   TFsText text = pValue;
   // �ж��Ƿ�λ��
   if(text.Equals("Unknown")){
      return ENetProtocol_Unknown;
   }
   // �ж��Ƿ�����
   if(text.Equals("Data")){
      return ENetProtocol_Data;
   }
   // �ж��Ƿ���Ϣ
   if(text.Equals("Message")){
      return ENetProtocol_Message;
   }
   // �ж��Ƿ�·��
   if(text.Equals("Router")){
      return ENetProtocol_Router;
   }
   // �ж��Ƿ���
   if(text.Equals("Transfer")){
      return ENetProtocol_Transfer;
   }
   // �ж��Ƿ����ݰ�
   if(text.Equals("Package")){
      return ENetProtocol_Package;
   }
   MO_STATIC_FATAL("Unknown enum value. (enum=ENetProtocol, value=%s)", pValue);
   return (ENetProtocol)0;
}

//============================================================
// <T>���ݴ����������Э��ö���ࡣ</T>
//
// @param pCode ����
// @return ö����
//============================================================
ENetProtocol REnumNetProtocol::ParseCode(TCharC* pCode){
   TFsText text = pCode;
   MO_STATIC_FATAL("Unknown enum value. (enum=ENetProtocol, code=%s)", pCode);
   return (ENetProtocol)0;
}

//============================================================
// <T>���������Э��ö�����ô��롣</T>
//
// @param value ö����
// @return ����
//============================================================
TCharC* REnumNetProtocol::ToCode(ENetProtocol value){
   return "Unknown";
}

//============================================================
// <T>���������Э��ö�������ַ�����</T>
//
// @param value ö����
// @return �ַ���
//============================================================
TCharC* REnumNetProtocol::ToString(ENetProtocol value){
   // ���λ��
   if(ENetProtocol_Unknown == value){
      return "Unknown";
   }
   // �������
   if(ENetProtocol_Data == value){
      return "Data";
   }
   // �����Ϣ
   if(ENetProtocol_Message == value){
      return "Message";
   }
   // ���·��
   if(ENetProtocol_Router == value){
      return "Router";
   }
   // ��ô���
   if(ENetProtocol_Transfer == value){
      return "Transfer";
   }
   // ������ݰ�
   if(ENetProtocol_Package == value){
      return "Package";
   }
   return "Unknown";
}

//============================================================
// <T>�������������</T>
//
// @return ��ʽ���ַ���
//============================================================
TSize TNetSignSet::Capacity(){
   return sizeof(TUint32);
}

//============================================================
// <T>���ܶԷ��������ݡ�</T>
//
// @param set ���϶���
//============================================================
void TNetSignSet::Assign(TNetSignSet& set){
   _value = set.Get();
}

//============================================================
// <T>���ܶԷ��������ݡ�</T>
//
// @param set ���϶���
//============================================================
void TNetSignSet::Parse(TCharC* pValue){
   _value = 0;
   TFsStringToken token(pValue, ',');
   TInt count = token.Count();
   for(TInt n = 0; n < count; n ++){
      TFsCode code = token.Get(n);
      if(code.Equals("Unknown")){
         SetBit(ENetSign_Unknown);
         continue;
      }
      if(code.Equals("Valid")){
         SetBit(ENetSign_Valid);
         continue;
      }
      if(code.Equals("Client")){
         SetBit(ENetSign_Client);
         continue;
      }
      if(code.Equals("Debug")){
         SetBit(ENetSign_Debug);
         continue;
      }
      if(code.Equals("Analysis")){
         SetBit(ENetSign_Analysis);
         continue;
      }
      if(code.Equals("Track")){
         SetBit(ENetSign_Track);
         continue;
      }
   }
}

//============================================================
// <T>���ܶԷ��������ݡ�</T>
//
// @param set ���϶���
//============================================================
void TNetSignSet::ParseValue(TCharC* pValue){
   _value = 0;
   TFsStringToken token(pValue, ',');
   TInt count = token.Count();
   for(TInt n = 0; n < count; n ++){
      TFsCode code = token.Get(n);
      if(code.Equals("0")){
         SetBit(ENetSign_Unknown);
         continue;
      }
      if(code.Equals("1")){
         SetBit(ENetSign_Valid);
         continue;
      }
      if(code.Equals("2")){
         SetBit(ENetSign_Client);
         continue;
      }
      if(code.Equals("3")){
         SetBit(ENetSign_Debug);
         continue;
      }
      if(code.Equals("4")){
         SetBit(ENetSign_Analysis);
         continue;
      }
      if(code.Equals("5")){
         SetBit(ENetSign_Track);
         continue;
      }
   }
}

//============================================================
// <T>��ø�ʽ���ַ�����</T>
//
// @param pValue �ַ���
// @param capacity ���ݳ���
// @return ��ʽ���ַ���
//============================================================
TChar* TNetSignSet::ToString(TChar* pValue, TSize capacity){
   TStringRefer text(pValue, capacity);
   text.Append(GetBit(ENetSign_Unknown) ? "" : "_");
   text.Append(GetBit(ENetSign_Valid) ? "" : "_");
   text.Append(GetBit(ENetSign_Client) ? "" : "_");
   text.Append(GetBit(ENetSign_Debug) ? "" : "_");
   text.Append(GetBit(ENetSign_Analysis) ? "" : "_");
   text.Append(GetBit(ENetSign_Track) ? "" : "_");
   return pValue;
}

//============================================================
// <T>��ø�ʽ���ַ�����</T>
//
// @return ��ʽ���ַ���
//============================================================
TFsText TNetSignSet::ToString(){
   TFsText text;
   ToString(text.Memory(), text.Size());
   return text;
}

//============================================================
// <T>�����ַ�������������־ö���ࡣ</T>
//
// @param pValue �ַ���
// @return ö����
//============================================================
ENetSign REnumNetSign::Parse(TCharC* pValue){
   // �ж��Ƿ���Ҫ����
   if(RInt::IsInteger(pValue)){
      return (ENetSign)RInt::Parse(pValue);
   }
   // ���ö��ֵ
   TFsText text = pValue;
   // �ж��Ƿ�δ֪
   if(text.Equals("Unknown")){
      return ENetSign_Unknown;
   }
   // �ж��Ƿ���Ч
   if(text.Equals("Valid")){
      return ENetSign_Valid;
   }
   // �ж��Ƿ�ͻ�
   if(text.Equals("Client")){
      return ENetSign_Client;
   }
   // �ж��Ƿ����
   if(text.Equals("Debug")){
      return ENetSign_Debug;
   }
   // �ж��Ƿ����
   if(text.Equals("Analysis")){
      return ENetSign_Analysis;
   }
   // �ж��Ƿ����
   if(text.Equals("Track")){
      return ENetSign_Track;
   }
   MO_STATIC_FATAL("Unknown enum value. (enum=ENetSign, value=%s)", pValue);
   return (ENetSign)0;
}

//============================================================
// <T>���ݴ������������־ö���ࡣ</T>
//
// @param pCode ����
// @return ö����
//============================================================
ENetSign REnumNetSign::ParseCode(TCharC* pCode){
   TFsText text = pCode;
   MO_STATIC_FATAL("Unknown enum value. (enum=ENetSign, code=%s)", pCode);
   return (ENetSign)0;
}

//============================================================
// <T>�����������־ö�����ô��롣</T>
//
// @param value ö����
// @return ����
//============================================================
TCharC* REnumNetSign::ToCode(ENetSign value){
   return "Unknown";
}

//============================================================
// <T>�����������־ö�������ַ�����</T>
//
// @param value ö����
// @return �ַ���
//============================================================
TCharC* REnumNetSign::ToString(ENetSign value){
   // ���δ֪
   if(ENetSign_Unknown == value){
      return "Unknown";
   }
   // �����Ч
   if(ENetSign_Valid == value){
      return "Valid";
   }
   // ��ÿͻ�
   if(ENetSign_Client == value){
      return "Client";
   }
   // ��õ���
   if(ENetSign_Debug == value){
      return "Debug";
   }
   // ��÷���
   if(ENetSign_Analysis == value){
      return "Analysis";
   }
   // ��ø���
   if(ENetSign_Track == value){
      return "Track";
   }
   return "Unknown";
}

//============================================================
// <T>�����ַ��������Ϣ����ö���ࡣ</T>
//
// @param pValue �ַ���
// @return ö����
//============================================================
ENetMessage REnumNetMessage::Parse(TCharC* pValue){
   // �ж��Ƿ���Ҫ����
   if(RInt::IsInteger(pValue)){
      return (ENetMessage)RInt::Parse(pValue);
   }
   // ���ö��ֵ
   TFsText text = pValue;
   // �ж��Ƿ�δ֪
   if(text.Equals("Unknown")){
      return ENetMessage_Unknown;
   }
   // �ж��Ƿ�����
   if(text.Equals("Request")){
      return ENetMessage_Request;
   }
   // �ж��Ƿ�Ӧ��
   if(text.Equals("Response")){
      return ENetMessage_Response;
   }
   // �ж��Ƿ�֪ͨ
   if(text.Equals("Notify")){
      return ENetMessage_Notify;
   }
   MO_STATIC_FATAL("Unknown enum value. (enum=ENetMessage, value=%s)", pValue);
   return (ENetMessage)0;
}

//============================================================
// <T>���ݴ�������Ϣ����ö���ࡣ</T>
//
// @param pCode ����
// @return ö����
//============================================================
ENetMessage REnumNetMessage::ParseCode(TCharC* pCode){
   TFsText text = pCode;
   MO_STATIC_FATAL("Unknown enum value. (enum=ENetMessage, code=%s)", pCode);
   return (ENetMessage)0;
}

//============================================================
// <T>������Ϣ����ö�����ô��롣</T>
//
// @param value ö����
// @return ����
//============================================================
TCharC* REnumNetMessage::ToCode(ENetMessage value){
   return "Unknown";
}

//============================================================
// <T>������Ϣ����ö�������ַ�����</T>
//
// @param value ö����
// @return �ַ���
//============================================================
TCharC* REnumNetMessage::ToString(ENetMessage value){
   // ���δ֪
   if(ENetMessage_Unknown == value){
      return "Unknown";
   }
   // �������
   if(ENetMessage_Request == value){
      return "Request";
   }
   // ���Ӧ��
   if(ENetMessage_Response == value){
      return "Response";
   }
   // ���֪ͨ
   if(ENetMessage_Notify == value){
      return "Notify";
   }
   return "Unknown";
}

//============================================================
// <T>�������������</T>
//
// @return ��ʽ���ַ���
//============================================================
TSize TNetMessageSignSet::Capacity(){
   return sizeof(TUint32);
}

//============================================================
// <T>���ܶԷ��������ݡ�</T>
//
// @param set ���϶���
//============================================================
void TNetMessageSignSet::Assign(TNetMessageSignSet& set){
   _value = set.Get();
}

//============================================================
// <T>���ܶԷ��������ݡ�</T>
//
// @param set ���϶���
//============================================================
void TNetMessageSignSet::Parse(TCharC* pValue){
   _value = 0;
   TFsStringToken token(pValue, ',');
   TInt count = token.Count();
   for(TInt n = 0; n < count; n ++){
      TFsCode code = token.Get(n);
      if(code.Equals("Unknown")){
         SetBit(ENetMessageSign_Unknown);
         continue;
      }
      if(code.Equals("Tcp")){
         SetBit(ENetMessageSign_Tcp);
         continue;
      }
      if(code.Equals("Udp")){
         SetBit(ENetMessageSign_Udp);
         continue;
      }
      if(code.Equals("Thread")){
         SetBit(ENetMessageSign_Thread);
         continue;
      }
   }
}

//============================================================
// <T>���ܶԷ��������ݡ�</T>
//
// @param set ���϶���
//============================================================
void TNetMessageSignSet::ParseValue(TCharC* pValue){
   _value = 0;
   TFsStringToken token(pValue, ',');
   TInt count = token.Count();
   for(TInt n = 0; n < count; n ++){
      TFsCode code = token.Get(n);
      if(code.Equals("0")){
         SetBit(ENetMessageSign_Unknown);
         continue;
      }
      if(code.Equals("1")){
         SetBit(ENetMessageSign_Tcp);
         continue;
      }
      if(code.Equals("2")){
         SetBit(ENetMessageSign_Udp);
         continue;
      }
      if(code.Equals("3")){
         SetBit(ENetMessageSign_Thread);
         continue;
      }
   }
}

//============================================================
// <T>��ø�ʽ���ַ�����</T>
//
// @param pValue �ַ���
// @param capacity ���ݳ���
// @return ��ʽ���ַ���
//============================================================
TChar* TNetMessageSignSet::ToString(TChar* pValue, TSize capacity){
   TStringRefer text(pValue, capacity);
   text.Append(GetBit(ENetMessageSign_Unknown) ? "" : "_");
   text.Append(GetBit(ENetMessageSign_Tcp) ? "" : "_");
   text.Append(GetBit(ENetMessageSign_Udp) ? "" : "_");
   text.Append(GetBit(ENetMessageSign_Thread) ? "" : "_");
   return pValue;
}

//============================================================
// <T>��ø�ʽ���ַ�����</T>
//
// @return ��ʽ���ַ���
//============================================================
TFsText TNetMessageSignSet::ToString(){
   TFsText text;
   ToString(text.Memory(), text.Size());
   return text;
}

//============================================================
// <T>�����ַ��������Ϣ��־ö���ࡣ</T>
//
// @param pValue �ַ���
// @return ö����
//============================================================
ENetMessageSign REnumNetMessageSign::Parse(TCharC* pValue){
   // �ж��Ƿ���Ҫ����
   if(RInt::IsInteger(pValue)){
      return (ENetMessageSign)RInt::Parse(pValue);
   }
   // ���ö��ֵ
   TFsText text = pValue;
   // �ж��Ƿ�δ֪
   if(text.Equals("Unknown")){
      return ENetMessageSign_Unknown;
   }
   // �ж��Ƿ�TCP֧��
   if(text.Equals("Tcp")){
      return ENetMessageSign_Tcp;
   }
   // �ж��Ƿ�UDP֧��
   if(text.Equals("Udp")){
      return ENetMessageSign_Udp;
   }
   // �ж��Ƿ��߳�֧��
   if(text.Equals("Thread")){
      return ENetMessageSign_Thread;
   }
   MO_STATIC_FATAL("Unknown enum value. (enum=ENetMessageSign, value=%s)", pValue);
   return (ENetMessageSign)0;
}

//============================================================
// <T>���ݴ�������Ϣ��־ö���ࡣ</T>
//
// @param pCode ����
// @return ö����
//============================================================
ENetMessageSign REnumNetMessageSign::ParseCode(TCharC* pCode){
   TFsText text = pCode;
   MO_STATIC_FATAL("Unknown enum value. (enum=ENetMessageSign, code=%s)", pCode);
   return (ENetMessageSign)0;
}

//============================================================
// <T>������Ϣ��־ö�����ô��롣</T>
//
// @param value ö����
// @return ����
//============================================================
TCharC* REnumNetMessageSign::ToCode(ENetMessageSign value){
   return "Unknown";
}

//============================================================
// <T>������Ϣ��־ö�������ַ�����</T>
//
// @param value ö����
// @return �ַ���
//============================================================
TCharC* REnumNetMessageSign::ToString(ENetMessageSign value){
   // ���δ֪
   if(ENetMessageSign_Unknown == value){
      return "Unknown";
   }
   // ���TCP֧��
   if(ENetMessageSign_Tcp == value){
      return "Tcp";
   }
   // ���UDP֧��
   if(ENetMessageSign_Udp == value){
      return "Udp";
   }
   // ����߳�֧��
   if(ENetMessageSign_Thread == value){
      return "Thread";
   }
   return "Unknown";
}

//============================================================
// <T>�����ַ������������Ϣ��������ö���ࡣ</T>
//
// @param pValue �ַ���
// @return ö����
//============================================================
ENetMessageService REnumNetMessageService::Parse(TCharC* pValue){
   // �ж��Ƿ���Ҫ����
   if(RInt::IsInteger(pValue)){
      return (ENetMessageService)RInt::Parse(pValue);
   }
   // ���ö��ֵ
   TFsText text = pValue;
   // �ж��Ƿ��߼�
   if(text.Equals("Logic")){
      return ENetMessageService_Logic;
   }
   // �ж��Ƿ��¼
   if(text.Equals("Login")){
      return ENetMessageService_Login;
   }
   // �ж��Ƿ�ˢ��
   if(text.Equals("Refresh")){
      return ENetMessageService_Refresh;
   }
   MO_STATIC_FATAL("Unknown enum value. (enum=ENetMessageService, value=%s)", pValue);
   return (ENetMessageService)0;
}

//============================================================
// <T>���ݴ�����������Ϣ��������ö���ࡣ</T>
//
// @param pCode ����
// @return ö����
//============================================================
ENetMessageService REnumNetMessageService::ParseCode(TCharC* pCode){
   TFsText text = pCode;
   MO_STATIC_FATAL("Unknown enum value. (enum=ENetMessageService, code=%s)", pCode);
   return (ENetMessageService)0;
}

//============================================================
// <T>����������Ϣ��������ö�����ô��롣</T>
//
// @param value ö����
// @return ����
//============================================================
TCharC* REnumNetMessageService::ToCode(ENetMessageService value){
   return "Unknown";
}

//============================================================
// <T>����������Ϣ��������ö�������ַ�����</T>
//
// @param value ö����
// @return �ַ���
//============================================================
TCharC* REnumNetMessageService::ToString(ENetMessageService value){
   // ����߼�
   if(ENetMessageService_Logic == value){
      return "Logic";
   }
   // ��õ�¼
   if(ENetMessageService_Login == value){
      return "Login";
   }
   // ���ˢ��
   if(ENetMessageService_Refresh == value){
      return "Refresh";
   }
   return "Unknown";
}

//============================================================
// <T>�����ַ�����������ն�ö���ࡣ</T>
//
// @param pValue �ַ���
// @return ö����
//============================================================
ENetTerminal REnumNetTerminal::Parse(TCharC* pValue){
   // �ж��Ƿ���Ҫ����
   if(RInt::IsInteger(pValue)){
      return (ENetTerminal)RInt::Parse(pValue);
   }
   // ���ö��ֵ
   TFsText text = pValue;
   // �ж��Ƿ�δ֪
   if(text.Equals("Unknown")){
      return ENetTerminal_Unknown;
   }
   // �ж��Ƿ�ͻ���
   if(text.Equals("Client")){
      return ENetTerminal_Client;
   }
   // �ж��Ƿ����������
   if(text.Equals("ServerTransfer")){
      return ENetTerminal_ServerTransfer;
   }
   // �ж��Ƿ�ȫ�ִ���
   if(text.Equals("GlobalTransfer")){
      return ENetTerminal_GlobalTransfer;
   }
   // �ж��Ƿ�ȫ�ִ���
   if(text.Equals("GlobalProxy")){
      return ENetTerminal_GlobalProxy;
   }
   // �ж��Ƿ�ȫ������
   if(text.Equals("GlobalDomain")){
      return ENetTerminal_GlobalDomain;
   }
   // �ж��Ƿ�ȫ�ֵ�½
   if(text.Equals("GlobalLogin")){
      return ENetTerminal_GlobalLogin;
   }
   // �ж��Ƿ�ȫ������
   if(text.Equals("GlobalGate")){
      return ENetTerminal_GlobalGate;
   }
   // �ж��Ƿ�ȫ�ִ洢
   if(text.Equals("GlobalStorage")){
      return ENetTerminal_GlobalStorage;
   }
   // �ж��Ƿ���Ϸ����
   if(text.Equals("GameProxy")){
      return ENetTerminal_GameProxy;
   }
   // �ж��Ƿ���Ϸ����
   if(text.Equals("GameDomain")){
      return ENetTerminal_GameDomain;
   }
   // �ж��Ƿ���Ϸ����
   if(text.Equals("GameGate")){
      return ENetTerminal_GameGate;
   }
   // �ж��Ƿ���Ϸ��¼
   if(text.Equals("GameLogin")){
      return ENetTerminal_GameLogin;
   }
   // �ж��Ƿ���Ϸ����
   if(text.Equals("GameScene")){
      return ENetTerminal_GameScene;
   }
   // �ж��Ƿ���Ϸս��
   if(text.Equals("GameBattle")){
      return ENetTerminal_GameBattle;
   }
   // �ж��Ƿ���Ϸ�洢
   if(text.Equals("GameStorage")){
      return ENetTerminal_GameStorage;
   }
   // �ж��Ƿ���Ϸ����
   if(text.Equals("GameChat")){
      return ENetTerminal_GameChat;
   }
   // �ж��Ƿ���Ϸ��־
   if(text.Equals("GameLogger")){
      return ENetTerminal_GameLogger;
   }
   // �ж��Ƿ������Խӷ�����
   if(text.Equals("GameWebInterface")){
      return ENetTerminal_GameWebInterface;
   }
   MO_STATIC_FATAL("Unknown enum value. (enum=ENetTerminal, value=%s)", pValue);
   return (ENetTerminal)0;
}

//============================================================
// <T>���ݴ����������ն�ö���ࡣ</T>
//
// @param pCode ����
// @return ö����
//============================================================
ENetTerminal REnumNetTerminal::ParseCode(TCharC* pCode){
   TFsText text = pCode;
   // �ж��Ƿ�δ֪
   if(text.Equals("UNK")){
      return ENetTerminal_Unknown;
   }
   // �ж��Ƿ�ͻ���
   if(text.Equals("CLT")){
      return ENetTerminal_Client;
   }
   // �ж��Ƿ����������
   if(text.Equals("STS")){
      return ENetTerminal_ServerTransfer;
   }
   // �ж��Ƿ�ȫ�ִ���
   if(text.Equals("ATS")){
      return ENetTerminal_GlobalTransfer;
   }
   // �ж��Ƿ�ȫ�ִ���
   if(text.Equals("APX")){
      return ENetTerminal_GlobalProxy;
   }
   // �ж��Ƿ�ȫ������
   if(text.Equals("ADM")){
      return ENetTerminal_GlobalDomain;
   }
   // �ж��Ƿ�ȫ�ֵ�½
   if(text.Equals("ALG")){
      return ENetTerminal_GlobalLogin;
   }
   // �ж��Ƿ�ȫ������
   if(text.Equals("AGT")){
      return ENetTerminal_GlobalGate;
   }
   // �ж��Ƿ�ȫ�ִ洢
   if(text.Equals("ASR")){
      return ENetTerminal_GlobalStorage;
   }
   // �ж��Ƿ���Ϸ����
   if(text.Equals("GPX")){
      return ENetTerminal_GameProxy;
   }
   // �ж��Ƿ���Ϸ����
   if(text.Equals("GDM")){
      return ENetTerminal_GameDomain;
   }
   // �ж��Ƿ���Ϸ����
   if(text.Equals("GGT")){
      return ENetTerminal_GameGate;
   }
   // �ж��Ƿ���Ϸ��¼
   if(text.Equals("GLG")){
      return ENetTerminal_GameLogin;
   }
   // �ж��Ƿ���Ϸ����
   if(text.Equals("GSC")){
      return ENetTerminal_GameScene;
   }
   // �ж��Ƿ���Ϸս��
   if(text.Equals("GBT")){
      return ENetTerminal_GameBattle;
   }
   // �ж��Ƿ���Ϸ�洢
   if(text.Equals("GSR")){
      return ENetTerminal_GameStorage;
   }
   // �ж��Ƿ���Ϸ����
   if(text.Equals("GCT")){
      return ENetTerminal_GameChat;
   }
   // �ж��Ƿ���Ϸ��־
   if(text.Equals("GLO")){
      return ENetTerminal_GameLogger;
   }
   // �ж��Ƿ������Խӷ�����
   if(text.Equals("GWI")){
      return ENetTerminal_GameWebInterface;
   }
   MO_STATIC_FATAL("Unknown enum value. (enum=ENetTerminal, code=%s)", pCode);
   return (ENetTerminal)0;
}

//============================================================
// <T>���������ն�ö�����ô��롣</T>
//
// @param value ö����
// @return ����
//============================================================
TCharC* REnumNetTerminal::ToCode(ENetTerminal value){
   // ���δ֪
   if(ENetTerminal_Unknown == value){
      return "UNK";
   }
   // ��ÿͻ���
   if(ENetTerminal_Client == value){
      return "CLT";
   }
   // ��÷���������
   if(ENetTerminal_ServerTransfer == value){
      return "STS";
   }
   // ���ȫ�ִ���
   if(ENetTerminal_GlobalTransfer == value){
      return "ATS";
   }
   // ���ȫ�ִ���
   if(ENetTerminal_GlobalProxy == value){
      return "APX";
   }
   // ���ȫ������
   if(ENetTerminal_GlobalDomain == value){
      return "ADM";
   }
   // ���ȫ�ֵ�½
   if(ENetTerminal_GlobalLogin == value){
      return "ALG";
   }
   // ���ȫ������
   if(ENetTerminal_GlobalGate == value){
      return "AGT";
   }
   // ���ȫ�ִ洢
   if(ENetTerminal_GlobalStorage == value){
      return "ASR";
   }
   // �����Ϸ����
   if(ENetTerminal_GameProxy == value){
      return "GPX";
   }
   // �����Ϸ����
   if(ENetTerminal_GameDomain == value){
      return "GDM";
   }
   // �����Ϸ����
   if(ENetTerminal_GameGate == value){
      return "GGT";
   }
   // �����Ϸ��¼
   if(ENetTerminal_GameLogin == value){
      return "GLG";
   }
   // �����Ϸ����
   if(ENetTerminal_GameScene == value){
      return "GSC";
   }
   // �����Ϸս��
   if(ENetTerminal_GameBattle == value){
      return "GBT";
   }
   // �����Ϸ�洢
   if(ENetTerminal_GameStorage == value){
      return "GSR";
   }
   // �����Ϸ����
   if(ENetTerminal_GameChat == value){
      return "GCT";
   }
   // �����Ϸ��־
   if(ENetTerminal_GameLogger == value){
      return "GLO";
   }
   // ��������Խӷ�����
   if(ENetTerminal_GameWebInterface == value){
      return "GWI";
   }
   return "Unknown";
}

//============================================================
// <T>���������ն�ö�������ַ�����</T>
//
// @param value ö����
// @return �ַ���
//============================================================
TCharC* REnumNetTerminal::ToString(ENetTerminal value){
   // ���δ֪
   if(ENetTerminal_Unknown == value){
      return "Unknown";
   }
   // ��ÿͻ���
   if(ENetTerminal_Client == value){
      return "Client";
   }
   // ��÷���������
   if(ENetTerminal_ServerTransfer == value){
      return "ServerTransfer";
   }
   // ���ȫ�ִ���
   if(ENetTerminal_GlobalTransfer == value){
      return "GlobalTransfer";
   }
   // ���ȫ�ִ���
   if(ENetTerminal_GlobalProxy == value){
      return "GlobalProxy";
   }
   // ���ȫ������
   if(ENetTerminal_GlobalDomain == value){
      return "GlobalDomain";
   }
   // ���ȫ�ֵ�½
   if(ENetTerminal_GlobalLogin == value){
      return "GlobalLogin";
   }
   // ���ȫ������
   if(ENetTerminal_GlobalGate == value){
      return "GlobalGate";
   }
   // ���ȫ�ִ洢
   if(ENetTerminal_GlobalStorage == value){
      return "GlobalStorage";
   }
   // �����Ϸ����
   if(ENetTerminal_GameProxy == value){
      return "GameProxy";
   }
   // �����Ϸ����
   if(ENetTerminal_GameDomain == value){
      return "GameDomain";
   }
   // �����Ϸ����
   if(ENetTerminal_GameGate == value){
      return "GameGate";
   }
   // �����Ϸ��¼
   if(ENetTerminal_GameLogin == value){
      return "GameLogin";
   }
   // �����Ϸ����
   if(ENetTerminal_GameScene == value){
      return "GameScene";
   }
   // �����Ϸս��
   if(ENetTerminal_GameBattle == value){
      return "GameBattle";
   }
   // �����Ϸ�洢
   if(ENetTerminal_GameStorage == value){
      return "GameStorage";
   }
   // �����Ϸ����
   if(ENetTerminal_GameChat == value){
      return "GameChat";
   }
   // �����Ϸ��־
   if(ENetTerminal_GameLogger == value){
      return "GameLogger";
   }
   // ��������Խӷ�����
   if(ENetTerminal_GameWebInterface == value){
      return "GameWebInterface";
   }
   return "Unknown";
}

//============================================================
// <T>�������������</T>
//
// @return ��ʽ���ַ���
//============================================================
TSize TNetRouterFlagSet::Capacity(){
   return sizeof(TUint32);
}

//============================================================
// <T>���ܶԷ��������ݡ�</T>
//
// @param set ���϶���
//============================================================
void TNetRouterFlagSet::Assign(TNetRouterFlagSet& set){
   _value = set.Get();
}

//============================================================
// <T>���ܶԷ��������ݡ�</T>
//
// @param set ���϶���
//============================================================
void TNetRouterFlagSet::Parse(TCharC* pValue){
   _value = 0;
   TFsStringToken token(pValue, ',');
   TInt count = token.Count();
   for(TInt n = 0; n < count; n ++){
      TFsCode code = token.Get(n);
      if(code.Equals("Valid")){
         SetBit(ENetRouterFlag_Valid);
         continue;
      }
      if(code.Equals("Disconnect")){
         SetBit(ENetRouterFlag_Disconnect);
         continue;
      }
   }
}

//============================================================
// <T>���ܶԷ��������ݡ�</T>
//
// @param set ���϶���
//============================================================
void TNetRouterFlagSet::ParseValue(TCharC* pValue){
   _value = 0;
   TFsStringToken token(pValue, ',');
   TInt count = token.Count();
   for(TInt n = 0; n < count; n ++){
      TFsCode code = token.Get(n);
      if(code.Equals("0")){
         SetBit(ENetRouterFlag_Valid);
         continue;
      }
      if(code.Equals("1")){
         SetBit(ENetRouterFlag_Disconnect);
         continue;
      }
   }
}

//============================================================
// <T>��ø�ʽ���ַ�����</T>
//
// @param pValue �ַ���
// @param capacity ���ݳ���
// @return ��ʽ���ַ���
//============================================================
TChar* TNetRouterFlagSet::ToString(TChar* pValue, TSize capacity){
   TStringRefer text(pValue, capacity);
   text.Append(GetBit(ENetRouterFlag_Valid) ? "" : "_");
   text.Append(GetBit(ENetRouterFlag_Disconnect) ? "" : "_");
   return pValue;
}

//============================================================
// <T>��ø�ʽ���ַ�����</T>
//
// @return ��ʽ���ַ���
//============================================================
TFsText TNetRouterFlagSet::ToString(){
   TFsText text;
   ToString(text.Memory(), text.Size());
   return text;
}

//============================================================
// <T>�����ַ������·�ɱ�־ö���ࡣ</T>
//
// @param pValue �ַ���
// @return ö����
//============================================================
ENetRouterFlag REnumNetRouterFlag::Parse(TCharC* pValue){
   // �ж��Ƿ���Ҫ����
   if(RInt::IsInteger(pValue)){
      return (ENetRouterFlag)RInt::Parse(pValue);
   }
   // ���ö��ֵ
   TFsText text = pValue;
   // �ж��Ƿ���Ч
   if(text.Equals("Valid")){
      return ENetRouterFlag_Valid;
   }
   // �ж��Ƿ�Ͽ�����
   if(text.Equals("Disconnect")){
      return ENetRouterFlag_Disconnect;
   }
   MO_STATIC_FATAL("Unknown enum value. (enum=ENetRouterFlag, value=%s)", pValue);
   return (ENetRouterFlag)0;
}

//============================================================
// <T>���ݴ�����·�ɱ�־ö���ࡣ</T>
//
// @param pCode ����
// @return ö����
//============================================================
ENetRouterFlag REnumNetRouterFlag::ParseCode(TCharC* pCode){
   TFsText text = pCode;
   MO_STATIC_FATAL("Unknown enum value. (enum=ENetRouterFlag, code=%s)", pCode);
   return (ENetRouterFlag)0;
}

//============================================================
// <T>����·�ɱ�־ö�����ô��롣</T>
//
// @param value ö����
// @return ����
//============================================================
TCharC* REnumNetRouterFlag::ToCode(ENetRouterFlag value){
   return "Unknown";
}

//============================================================
// <T>����·�ɱ�־ö�������ַ�����</T>
//
// @param value ö����
// @return �ַ���
//============================================================
TCharC* REnumNetRouterFlag::ToString(ENetRouterFlag value){
   // �����Ч
   if(ENetRouterFlag_Valid == value){
      return "Valid";
   }
   // ��öϿ�����
   if(ENetRouterFlag_Disconnect == value){
      return "Disconnect";
   }
   return "Unknown";
}

//============================================================
// <T>�����ַ�������ռ�ģʽö���ࡣ</T>
//
// @param pValue �ַ���
// @return ö����
//============================================================
ECrAllocMode REnumCrAllocMode::Parse(TCharC* pValue){
   // �ж��Ƿ���Ҫ����
   if(RInt::IsInteger(pValue)){
      return (ECrAllocMode)RInt::Parse(pValue);
   }
   // ���ö��ֵ
   TFsText text = pValue;
   // �ж��Ƿ�̬����
   if(text.Equals("Create")){
      return ECrAllocMode_Create;
   }
   // �ж��Ƿ�̬����
   if(text.Equals("Link")){
      return ECrAllocMode_Link;
   }
   MO_STATIC_FATAL("Unknown enum value. (enum=ECrAllocMode, value=%s)", pValue);
   return (ECrAllocMode)0;
}

//============================================================
// <T>���ݴ������ռ�ģʽö���ࡣ</T>
//
// @param pCode ����
// @return ö����
//============================================================
ECrAllocMode REnumCrAllocMode::ParseCode(TCharC* pCode){
   TFsText text = pCode;
   MO_STATIC_FATAL("Unknown enum value. (enum=ECrAllocMode, code=%s)", pCode);
   return (ECrAllocMode)0;
}

//============================================================
// <T>�����ռ�ģʽö�����ô��롣</T>
//
// @param value ö����
// @return ����
//============================================================
TCharC* REnumCrAllocMode::ToCode(ECrAllocMode value){
   return "Unknown";
}

//============================================================
// <T>�����ռ�ģʽö�������ַ�����</T>
//
// @param value ö����
// @return �ַ���
//============================================================
TCharC* REnumCrAllocMode::ToString(ECrAllocMode value){
   // ��ö�̬����
   if(ECrAllocMode_Create == value){
      return "Create";
   }
   // ��þ�̬����
   if(ECrAllocMode_Link == value){
      return "Link";
   }
   return "Unknown";
}

//============================================================
// <T>�����ַ�����ö���״̬ö���ࡣ</T>
//
// @param pValue �ַ���
// @return ö����
//============================================================
EGmObjectStatus REnumGmObjectStatus::Parse(TCharC* pValue){
   // �ж��Ƿ���Ҫ����
   if(RInt::IsInteger(pValue)){
      return (EGmObjectStatus)RInt::Parse(pValue);
   }
   // ���ö��ֵ
   TFsText text = pValue;
   // �ж��Ƿ�δ֪
   if(text.Equals("Unknown")){
      return EGmObjectStatus_Unknown;
   }
   // �ж��Ƿ���Ч
   if(text.Equals("Valid")){
      return EGmObjectStatus_Valid;
   }
   // �ж��Ƿ񼤻�
   if(text.Equals("Active")){
      return EGmObjectStatus_Active;
   }
   // �ж��Ƿ񶳽�
   if(text.Equals("Frozen")){
      return EGmObjectStatus_Frozen;
   }
   MO_STATIC_FATAL("Unknown enum value. (enum=EGmObjectStatus, value=%s)", pValue);
   return (EGmObjectStatus)0;
}

//============================================================
// <T>���ݴ����ö���״̬ö���ࡣ</T>
//
// @param pCode ����
// @return ö����
//============================================================
EGmObjectStatus REnumGmObjectStatus::ParseCode(TCharC* pCode){
   TFsText text = pCode;
   MO_STATIC_FATAL("Unknown enum value. (enum=EGmObjectStatus, code=%s)", pCode);
   return (EGmObjectStatus)0;
}

//============================================================
// <T>���ݶ���״̬ö�����ô��롣</T>
//
// @param value ö����
// @return ����
//============================================================
TCharC* REnumGmObjectStatus::ToCode(EGmObjectStatus value){
   return "Unknown";
}

//============================================================
// <T>���ݶ���״̬ö�������ַ�����</T>
//
// @param value ö����
// @return �ַ���
//============================================================
TCharC* REnumGmObjectStatus::ToString(EGmObjectStatus value){
   // ���δ֪
   if(EGmObjectStatus_Unknown == value){
      return "Unknown";
   }
   // �����Ч
   if(EGmObjectStatus_Valid == value){
      return "Valid";
   }
   // ��ü���
   if(EGmObjectStatus_Active == value){
      return "Active";
   }
   // ��ö���
   if(EGmObjectStatus_Frozen == value){
      return "Frozen";
   }
   return "Unknown";
}

//============================================================
// <T>�����ַ�����ø��ĸ���ö���ࡣ</T>
//
// @param pValue �ַ���
// @return ö����
//============================================================
EGmObjectChange REnumGmObjectChange::Parse(TCharC* pValue){
   // �ж��Ƿ���Ҫ����
   if(RInt::IsInteger(pValue)){
      return (EGmObjectChange)RInt::Parse(pValue);
   }
   // ���ö��ֵ
   TFsText text = pValue;
   // �ж��Ƿ�δ֪
   if(text.Equals("Unknown")){
      return EGmObjectChange_Unknown;
   }
   // �ж��Ƿ�δ����
   if(text.Equals("Unchanged")){
      return EGmObjectChange_Unchanged;
   }
   // �ж��Ƿ񴴽�
   if(text.Equals("Create")){
      return EGmObjectChange_Create;
   }
   // �ж��Ƿ�ɾ��
   if(text.Equals("Delete")){
      return EGmObjectChange_Delete;
   }
   // �ж��Ƿ����
   if(text.Equals("Change")){
      return EGmObjectChange_Change;
   }
   // �ж��Ƿ���
   if(text.Equals("Receive")){
      return EGmObjectChange_Receive;
   }
   MO_STATIC_FATAL("Unknown enum value. (enum=EGmObjectChange, value=%s)", pValue);
   return (EGmObjectChange)0;
}

//============================================================
// <T>���ݴ����ø��ĸ���ö���ࡣ</T>
//
// @param pCode ����
// @return ö����
//============================================================
EGmObjectChange REnumGmObjectChange::ParseCode(TCharC* pCode){
   TFsText text = pCode;
   MO_STATIC_FATAL("Unknown enum value. (enum=EGmObjectChange, code=%s)", pCode);
   return (EGmObjectChange)0;
}

//============================================================
// <T>���ݸ��ĸ���ö�����ô��롣</T>
//
// @param value ö����
// @return ����
//============================================================
TCharC* REnumGmObjectChange::ToCode(EGmObjectChange value){
   return "Unknown";
}

//============================================================
// <T>���ݸ��ĸ���ö�������ַ�����</T>
//
// @param value ö����
// @return �ַ���
//============================================================
TCharC* REnumGmObjectChange::ToString(EGmObjectChange value){
   // ���δ֪
   if(EGmObjectChange_Unknown == value){
      return "Unknown";
   }
   // ���δ����
   if(EGmObjectChange_Unchanged == value){
      return "Unchanged";
   }
   // ��ô���
   if(EGmObjectChange_Create == value){
      return "Create";
   }
   // ���ɾ��
   if(EGmObjectChange_Delete == value){
      return "Delete";
   }
   // ��ø���
   if(EGmObjectChange_Change == value){
      return "Change";
   }
   // ��û��
   if(EGmObjectChange_Receive == value){
      return "Receive";
   }
   return "Unknown";
}

//============================================================
// <T>�������������</T>
//
// @return ��ʽ���ַ���
//============================================================
TSize TGmObjectFlagSet::Capacity(){
   return sizeof(TUint32);
}

//============================================================
// <T>���ܶԷ��������ݡ�</T>
//
// @param set ���϶���
//============================================================
void TGmObjectFlagSet::Assign(TGmObjectFlagSet& set){
   _value = set.Get();
}

//============================================================
// <T>���ܶԷ��������ݡ�</T>
//
// @param set ���϶���
//============================================================
void TGmObjectFlagSet::Parse(TCharC* pValue){
   _value = 0;
   TFsStringToken token(pValue, ',');
   TInt count = token.Count();
   for(TInt n = 0; n < count; n ++){
      TFsCode code = token.Get(n);
      if(code.Equals("Create")){
         SetBit(EGmObjectFlag_Create);
         continue;
      }
      if(code.Equals("Valid")){
         SetBit(EGmObjectFlag_Valid);
         continue;
      }
      if(code.Equals("Lock")){
         SetBit(EGmObjectFlag_Lock);
         continue;
      }
   }
}

//============================================================
// <T>���ܶԷ��������ݡ�</T>
//
// @param set ���϶���
//============================================================
void TGmObjectFlagSet::ParseValue(TCharC* pValue){
   _value = 0;
   TFsStringToken token(pValue, ',');
   TInt count = token.Count();
   for(TInt n = 0; n < count; n ++){
      TFsCode code = token.Get(n);
      if(code.Equals("0")){
         SetBit(EGmObjectFlag_Create);
         continue;
      }
      if(code.Equals("1")){
         SetBit(EGmObjectFlag_Valid);
         continue;
      }
      if(code.Equals("2")){
         SetBit(EGmObjectFlag_Lock);
         continue;
      }
   }
}

//============================================================
// <T>��ø�ʽ���ַ�����</T>
//
// @param pValue �ַ���
// @param capacity ���ݳ���
// @return ��ʽ���ַ���
//============================================================
TChar* TGmObjectFlagSet::ToString(TChar* pValue, TSize capacity){
   TStringRefer text(pValue, capacity);
   text.Append(GetBit(EGmObjectFlag_Create) ? "C" : "_");
   text.Append(GetBit(EGmObjectFlag_Valid) ? "V" : "_");
   text.Append(GetBit(EGmObjectFlag_Lock) ? "L" : "_");
   return pValue;
}

//============================================================
// <T>��ø�ʽ���ַ�����</T>
//
// @return ��ʽ���ַ���
//============================================================
TFsText TGmObjectFlagSet::ToString(){
   TFsText text;
   ToString(text.Memory(), text.Size());
   return text;
}

//============================================================
// <T>�����ַ�����ö����־ö���ࡣ</T>
//
// @param pValue �ַ���
// @return ö����
//============================================================
EGmObjectFlag REnumGmObjectFlag::Parse(TCharC* pValue){
   // �ж��Ƿ���Ҫ����
   if(RInt::IsInteger(pValue)){
      return (EGmObjectFlag)RInt::Parse(pValue);
   }
   // ���ö��ֵ
   TFsText text = pValue;
   // �ж��Ƿ񴴽�
   if(text.Equals("Create")){
      return EGmObjectFlag_Create;
   }
   // �ж��Ƿ���Ч
   if(text.Equals("Valid")){
      return EGmObjectFlag_Valid;
   }
   // �ж��Ƿ�����
   if(text.Equals("Lock")){
      return EGmObjectFlag_Lock;
   }
   MO_STATIC_FATAL("Unknown enum value. (enum=EGmObjectFlag, value=%s)", pValue);
   return (EGmObjectFlag)0;
}

//============================================================
// <T>���ݴ����ö����־ö���ࡣ</T>
//
// @param pCode ����
// @return ö����
//============================================================
EGmObjectFlag REnumGmObjectFlag::ParseCode(TCharC* pCode){
   TFsText text = pCode;
   MO_STATIC_FATAL("Unknown enum value. (enum=EGmObjectFlag, code=%s)", pCode);
   return (EGmObjectFlag)0;
}

//============================================================
// <T>���ݶ����־ö�����ô��롣</T>
//
// @param value ö����
// @return ����
//============================================================
TCharC* REnumGmObjectFlag::ToCode(EGmObjectFlag value){
   return "Unknown";
}

//============================================================
// <T>���ݶ����־ö�������ַ�����</T>
//
// @param value ö����
// @return �ַ���
//============================================================
TCharC* REnumGmObjectFlag::ToString(EGmObjectFlag value){
   // ��ô���
   if(EGmObjectFlag_Create == value){
      return "Create";
   }
   // �����Ч
   if(EGmObjectFlag_Valid == value){
      return "Valid";
   }
   // �������
   if(EGmObjectFlag_Lock == value){
      return "Lock";
   }
   return "Unknown";
}

MO_NAMESPACE_END
