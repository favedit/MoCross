using MS.Common.System;
using System;
using System.Net.Sockets;

namespace MS.Common.Net.Sockets
{
   //============================================================
   // <T>网络链接。</T>
   //
   // @class
   //============================================================
   public class FSocket : IDisposable
   {
      // 日志输出接口
      private static ILogger _logger = RLogger.Find(typeof(FSocket));

      protected Socket _socket;

      protected string _host;

      protected int _port;

      protected FSocketInput _input;

      protected FSocketOutput _output;

      //============================================================
      // <T>构造网络链接的实例对象。</T>
      //
      // @return 实例对象
      //============================================================
      public FSocket() {
      }

      //============================================================
      // <T>构造网络链接的实例对象。</T>
      //
      // @param host 主机地址
      // @param port 端口号
      // @return 实例对象
      //============================================================
      public FSocket(Socket socket) {
         _socket = socket;
      }

      //============================================================
      // <T>获得当前链接是否已经链接上。</T>
      //
      // @return 是否已经链接
      //============================================================
      public bool Connected {
         get { return (null != _socket) ? _socket.Connected : false; }
      }

      //============================================================
      // <T>获得连接套接字。</T>
      //============================================================
      public Socket NativeSocket {
         get { return _socket; }
      }

      //============================================================
      // <T>获得或设置主机地址。</T>
      //============================================================
      public string Host {
         get { return _host; }
         set { _host = value; }
      }

      //============================================================
      // <T>获得或设置端口。</T>
      //============================================================
      public int Port {
         get { return _port; }
         set { _port = value; }
      }

      //============================================================
      // <T>获得输入流数据。</T>
      //============================================================
      public FSocketInput Input {
         get {
            if (null == _input) {
               _input = new FSocketInput(this);
            }
            return _input;
         }
      }

      //============================================================
      // <T>获得输出流数据。</T>
      //============================================================
      public FSocketOutput Output {
         get {
            if (null == _output) {
               _output = new FSocketOutput(this);
            }
            return _output;
         }
      }

      //============================================================
      // <T>获得当前链接是否已经链接上。</T>
      //
      // @return 是否已经链接
      //============================================================
      public bool Blocking {
         get { return _socket.Blocking; }
         set { _socket.Blocking = value; }
      }

      //============================================================
      // <T>断开连接。</T>
      //============================================================
      public void Disconnect() {
         try {
            _socket.Close();
         }catch(Exception e){
            _logger.Error(this, "Disconnect", e);
         }
      }

      //============================================================
      // <T>释放对象。</T>
      //============================================================
      public void Dispose() {
         Disconnect();
      }
   }
}
