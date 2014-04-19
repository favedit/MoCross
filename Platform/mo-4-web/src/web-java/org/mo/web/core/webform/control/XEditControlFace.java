package org.mo.web.core.webform.control;

//============================================================
// <T>编辑控件接口对象的XML节点基类。</T>
//============================================================
public interface XEditControlFace
      extends
         XControlFace,
         XEditDescriptorFace,
         XEditValueFace
{
   // 名称定义
   String NAME = "EditControl";

   // 显示方式的名称定义
   String PTY_LABEL_TYPE = "label_type";

   // 标签位置的名称定义
   String PTY_LABEL_POSITION = "label_position";

   // 标签宽度的名称定义
   String PTY_LABEL_WIDTH = "label_width";

   // 标签高度的名称定义
   String PTY_LABEL_HEIGHT = "label_height";

   // 编辑宽度的名称定义
   String PTY_EDIT_WIDTH = "edit_width";

   // 编辑高度的名称定义
   String PTY_EDIT_HEIGHT = "edit_height";

   // 搜索方式的名称定义
   String PTY_SEARCH_TYPE = "search_type";

   // 数据类型的名称定义
   String PTY_DATA_TYPE = "data_type";

   // 编辑颜色的名称定义
   String PTY_EDIT_COLOR = "edit_color";

   // 编辑可的名称定义
   String PTY_TYPE_ABLE = "type_able";

   //============================================================
   // <T>获得显示方式的内容。</T>
   //
   // @return 显示方式
   //============================================================
   String getLabelType();

   //============================================================
   // <T>设置显示方式的内容。</T>
   //
   // @param value 显示方式
   //============================================================
   void setLabelType(String value);

   //============================================================
   // <T>获得标签位置的内容。</T>
   //
   // @return 标签位置
   //============================================================
   String getLabelPosition();

   //============================================================
   // <T>设置标签位置的内容。</T>
   //
   // @param value 标签位置
   //============================================================
   void setLabelPosition(String value);

   //============================================================
   // <T>获得标签宽度的内容。</T>
   //
   // @return 标签宽度
   //============================================================
   String getLabelWidth();

   //============================================================
   // <T>设置标签宽度的内容。</T>
   //
   // @param value 标签宽度
   //============================================================
   void setLabelWidth(String value);

   //============================================================
   // <T>获得标签高度的内容。</T>
   //
   // @return 标签高度
   //============================================================
   String getLabelHeight();

   //============================================================
   // <T>设置标签高度的内容。</T>
   //
   // @param value 标签高度
   //============================================================
   void setLabelHeight(String value);

   //============================================================
   // <T>获得编辑宽度的内容。</T>
   //
   // @return 编辑宽度
   //============================================================
   String getEditWidth();

   //============================================================
   // <T>设置编辑宽度的内容。</T>
   //
   // @param value 编辑宽度
   //============================================================
   void setEditWidth(String value);

   //============================================================
   // <T>获得编辑高度的内容。</T>
   //
   // @return 编辑高度
   //============================================================
   String getEditHeight();

   //============================================================
   // <T>设置编辑高度的内容。</T>
   //
   // @param value 编辑高度
   //============================================================
   void setEditHeight(String value);

   //============================================================
   // <T>获得搜索方式的内容。</T>
   //
   // @return 搜索方式
   //============================================================
   String getSearchType();

   //============================================================
   // <T>设置搜索方式的内容。</T>
   //
   // @param value 搜索方式
   //============================================================
   void setSearchType(String value);

   //============================================================
   // <T>获得数据类型的内容。</T>
   //
   // @return 数据类型
   //============================================================
   String getDataType();

   //============================================================
   // <T>设置数据类型的内容。</T>
   //
   // @param value 数据类型
   //============================================================
   void setDataType(String value);

   //============================================================
   // <T>获得编辑颜色的内容。</T>
   //
   // @return 编辑颜色
   //============================================================
   String getEditColor();

   //============================================================
   // <T>设置编辑颜色的内容。</T>
   //
   // @param value 编辑颜色
   //============================================================
   void setEditColor(String value);

   //============================================================
   // <T>获得编辑可的内容。</T>
   //
   // @return 编辑可
   //============================================================
   String getTypeAble();

   //============================================================
   // <T>设置编辑可的内容。</T>
   //
   // @param value 编辑可
   //============================================================
   void setTypeAble(String value);
}
