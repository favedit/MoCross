﻿namespace MO.Common.Collection
{
   //============================================================
   // <T>名称和内容的成对接口。</T>
   //============================================================
   public interface IPair<N, V>
   {
      //============================================================
      // <T>获得总数。</T>
      //
      // @return 总数
      //============================================================
      int Count { get; }

      //============================================================
      // <T>获得位置。</T>
      //
      // @return 位置
      //============================================================
      int Position { get; }

      //============================================================
      // <T>获得名称。</T>
      //
      // @return 名称
      //============================================================
      N Name { get; }

      //============================================================
      // <T>获得内容。</T>
      //
      // @return 内容
      //============================================================
      V Value { get; }

      //============================================================
      // <T>判断是否为第一个内容。</T>
      //
      // @return 是否标志
      //============================================================
      bool IsFirst();

      //============================================================
      // <T>判断是否为最后一个内容。</T>
      //
      // @return 是否标志
      //============================================================
      bool IsLast();
   }
}
