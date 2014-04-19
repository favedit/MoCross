package org.mo.web.core.webform.control;

import org.mo.com.xml.IXmlObject;

//============================================================
// <T>复选框接口对象的XML节点基类。</T>
//============================================================
public interface XDescCheckFace
      extends IXmlObject
{
   // 名称定义
   String NAME = "MDescCheck";

   // 真值的名称定义
   String PTY_EDIT_TRUE = "edit_true";

   // 假值的名称定义
   String PTY_EDIT_FALSE = "edit_false";

   //============================================================
   // <T>获得真值的内容。</T>
   //
   // @return 真值
   //============================================================
   String getEditTrue();

   //============================================================
   // <T>设置真值的内容。</T>
   //
   // @param value 真值
   //============================================================
   void setEditTrue(String value);

   //============================================================
   // <T>获得假值的内容。</T>
   //
   // @return 假值
   //============================================================
   String getEditFalse();

   //============================================================
   // <T>设置假值的内容。</T>
   //
   // @param value 假值
   //============================================================
   void setEditFalse(String value);
}