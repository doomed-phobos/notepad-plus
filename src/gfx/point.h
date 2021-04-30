#ifndef _GFX_POINT_H
#define _GFX_POINT_H

namespace gfx
{
   template<typename T>
   class SizeT;
   
   template<typename T>
   class PointT
   {
   public:
      T x, y;

      PointT() : x(0), y(0) {}
      PointT(const T& x, const T& y) : x(x), y(y) {}
      
      template<typename U>
      PointT(const PointT<U>& pt) : x(static_cast<T>(pt.x)), y(static_cast<T>(pt.y)) {}
      
      template<typename U>
      explicit PointT(const SizeT<U>& sz) : x(static_cast<T>(sz.width)),
                                            y(static_cast<T>(sz.height)) {}

      PointT operator/(const T& value) const {
         return PointT(x / value, y / value);
      }

      PointT operator-() const {
         return PointT(-x, -y);
      }
   };

   typedef PointT<int> PointI;
   typedef PointT<float> PointF;
} // namespace gfx

#endif