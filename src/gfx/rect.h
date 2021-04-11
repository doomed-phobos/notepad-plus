#ifndef _GFX_RECT_H
#define _GFX_RECT_H

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

      bool isEmpty() const {
         return width < 0 || height < 0;
      }
   };

   typedef RectT<int> RectI;
   typedef RectT<float> RectF;
} // namespace gfx

#endif