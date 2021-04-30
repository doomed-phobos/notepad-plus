#ifndef _GFX_SIZE_H
#define _GFX_SIZE_H

namespace gfx
{
   template<typename T>
   class SizeT
   {
   public:
      T width, height;

      SizeT() : width(0), height(0) {}
      SizeT(const T& width, const T& height) : width(width), height(height) {}

      SizeT operator/(const T& value) const {
         return SizeT(width/value, height/2);
      }
   };

   typedef SizeT<int> SizeI;
   typedef SizeT<float> SizeF;
} // namespace gfx

#endif