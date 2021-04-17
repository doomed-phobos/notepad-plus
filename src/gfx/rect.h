#ifndef _GFX_RECT_H
#define _GFX_RECT_H
template<typename T>
class PointT;

namespace gfx
{
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
   };

   typedef RectT<int> RectI;
   typedef RectT<float> RectF;
} // namespace gfx

#endif