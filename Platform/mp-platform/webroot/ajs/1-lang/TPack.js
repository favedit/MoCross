﻿//==========================================================
// <T>含有定义值的打包字符串。</T>
// <P>定义值描述：${名称}</P>
//
// @tool
// @history 091110 MAOCY 创建
//==========================================================
function TPack(){
   var o = this;
   //..........................................................
   // @attribute
   o.count      = 0;
   o.names      = null;
   o.values     = null;
   //..........................................................
   // @method
   o.get        = TPack_get;
   o.set        = TPack_set;
   o.pack       = TPack_pack;
   o.unpack     = TPack_unpack;
   return o;
}
//==========================================================
function TPack_get(n){
}
//==========================================================
function TPack_set(n, v){
   var o = this;
}
//==========================================================
function TPack_pack(){
   var o = this;
}
//==========================================================
function TPack_unpack(s){
   var o = this;
}