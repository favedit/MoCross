﻿namespace MO.Common.Geom
{
   //============================================================
   // <T>二维点。</T>
   //============================================================
   public class SPoint2<T>
   {
      // 横坐标
      public T X;

      // 纵坐标
      public T Y;

      //============================================================
      // <T>构造二维点。</T>
      //============================================================
      public SPoint2() {
      }

      //============================================================
      // <T>构造二维点。</T>
      //
      // @param x X坐标
      // @param y Y坐标
      //============================================================
      public SPoint2(T x, T y) {
         X = x;
         Y = y;
      }

      //============================================================
      // <T>接收二维点对象。</T>
      //
      // @param point 二维点对象
      //============================================================
      public void Assign(SPoint2<T> point) {
         if(point != null) {
            X = point.X;
            Y = point.Y;
         }
      }

      //============================================================
      // <T>设置二维点。</T>
      //
      // @param x X坐标
      // @param y Y坐标
      //============================================================
      public void Set(T x, T y) {
         X = x;
         Y = y;
      }

      //============================================================
      // <T>格式化成字符串。</T>
      //
      // @return 字符串
      //============================================================
      public override string ToString() {
         return X + "," + Y;
      }
   }
}