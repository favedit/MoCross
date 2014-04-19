﻿using MO.Common.Lang;
using MO.Common.IO;

namespace MO.Common.Geom
{
   //============================================================
   // <T>整数二维点。</T>
   //============================================================
   public class SIntPoint2 : SPoint2<int>
   {
      //============================================================
      // <T>构造二维点。</T>
      //
      // @param x X坐标
      // @param y Y坐标
      //============================================================
      public SIntPoint2(int x = 0, int y = 0)
         : base(x, y) {
      }

      //============================================================
      // <T>判断是否为空。</T>
      //
      // @return 是否为空
      //============================================================
      public bool IsEmpty() {
         return (X == 0) && (Y == 0);
      }

      //============================================================
      // <T>加法运算。</T>
      //
      // @param point 二维点
      //============================================================
      public void Add(SIntPoint2 point) {
         X += point.X;
         Y += point.Y;
      }

      //============================================================
      // <T>加法运算。</T>
      //
      // @param point 二维点
      // @param scale 缩放
      //============================================================
      public void Add(SIntPoint2 point, float scale) {
         X += (int)(point.X * scale);
         Y += (int)(point.Y * scale);
      }

      //============================================================
      // <T>解析字符串。</T>
      //
      // @param value 字符串
      //============================================================
      public bool Parse(string value) {
         if(value != null) {
            string[] items = value.Split(',');
            if(items.Length == 2) {
               X = RInt.Parse(items[0]);
               Y = RInt.Parse(items[1]);
               return true;
            }
         }
         return false;
      }

      //============================================================
      // <T>序列化内容到输出流。</T>
      //
      // @param output 输出流
      //============================================================
      public void Serialize(IOutput output) {
         output.WriteInt32(X);
         output.WriteInt32(Y);
      }

      //============================================================
      // <T>序列化内容到输出流。</T>
      //
      // @param output 输出流
      //============================================================
      public void Serialize16(IOutput output) {
         output.WriteInt16((short)X);
         output.WriteInt16((short)Y);
      }

      //============================================================
      // <T>重置内容。</T>
      //============================================================
      public void Reset() {
         X = 0;
         Y = 0;
      }
   }
}
