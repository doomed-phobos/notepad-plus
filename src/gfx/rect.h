#ifndef _GFX_RECT_H
#define _GFX_RECT_H

namespace gfx
{
   template<typename T>
   class PointT;

   template<typename T>
   class SizeT;
   
   template<typename T>
   class RectT
   {
   public:
      T x, y;
      T width, height;

      RectT() : x(0), y(0) ,
                width(0), height(0) {}
      RectT(const T& x, const T& y, const T& width, const T& height) : x(x), y(y),
                                                                       width(width), height(height) {}
      RectT(const PointT<T>& pt, const SizeT<T>& sz) : x(pt.x), y(pt.y),
                                                       width(sz.width), height(sz.height) {}
      RectT(PointT<T> leftTop, PointT<T> rightBottom) {
         T temp;
         
         if(leftTop.x > rightBottom.x) {
            temp = leftTop.x;
            leftTop.x = rightBottom.x;
            rightBottom.x = temp;
         }

         if(leftTop.y > rightBottom.y) {
            temp = leftTop.y;
            leftTop.y = rightBottom.y;
            rightBottom.y = temp;
         }

         x = leftTop.x;
         y = leftTop.y;
         width = rightBottom.x - leftTop.x;
         height = rightBottom.y - leftTop.y;
      }

      template<typename U>
      explicit RectT(const RectT<U>& rc) : x(static_cast<T>(rc.x)), y(static_cast<T>(rc.y)),
                                           width(static_cast<T>(rc.width)), height(static_cast<T>(rc.height)) {}

      bool isEmpty() const {
         return width < 0 || height < 0;
      }

      bool contains(const PointT<T>& pt) const {
         return pt.x >= x && pt.x < x+width &&
                pt.y >= y && pt.y < y+height;
      }

      RectT& setOrigin(const PointT<T>& pt) {
         x = pt.x;
         y = pt.y;
         return *this;
      }

      RectT& offset(const T& dx, const T& dy) {
         x += dx;
         y += dy;
         return *this;
      }

      RectT& offset(const PointT<T>& delta) {
         x += delta.x;
         y += delta.y;
         return *this;
      }
   };

   typedef RectT<int> RectI;
   typedef RectT<float> RectF;
} // namespace gfx

#endif