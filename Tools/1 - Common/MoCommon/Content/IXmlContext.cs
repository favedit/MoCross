namespace MO.Common.Content
{
   //============================================================
   // <T>文档环境接口。</T>
   //============================================================
   public interface IXmlObjectContext
   {
      //============================================================
      // <T>获得对象文档。</T>
      //
      // @return 对象文档
      //============================================================
      IXmlObjectDocument Document { get; }

      //============================================================
      // <T>获得顶层对象。</T>
      //
      // @return 顶层对象
      //============================================================
      IXmlObject Top { get; }

      //============================================================
      // <T>获得父对象。</T>
      //
      // @return 父对象
      //============================================================
      IXmlObject Parent { get; }

      //============================================================
      // <T>获得设置。</T>
      //
      // @return 设置
      //============================================================
      FXmlNode Config { get; }
   }
}
