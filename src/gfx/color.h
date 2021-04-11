#ifndef _GFX_COLOR_H
#define _GFX_COLOR_H
#include <cstdint>

namespace gfx
{
   typedef uint32_t color_t;
   typedef uint8_t color_channel_t;

   enum ColorShift {
      R_ColorShift = 0,
      G_ColorShift = 8,
      B_ColorShift = 16,
      A_ColorShift = 24
   };

   constexpr inline color_t rgba(color_channel_t r,
                                 color_channel_t g,
                                 color_channel_t b,
                                 color_channel_t a = 255)
   {
      return color_t((r << R_ColorShift) |
                     (g << G_ColorShift) |
                     (b << B_ColorShift) |
                     (a << A_ColorShift));
   }

   constexpr inline color_channel_t getR(color_t c) {return (c >> R_ColorShift) & 0xff;}
   constexpr inline color_channel_t getG(color_t c) {return (c >> G_ColorShift) & 0xff;}
   constexpr inline color_channel_t getB(color_t c) {return (c >> B_ColorShift) & 0xff;}
   constexpr inline color_channel_t getA(color_t c) {return (c >> A_ColorShift) & 0xff;}

   namespace colors
   {
      constexpr inline color_t NoneColor  =  color_t(0);
      constexpr inline color_t WhiteColor =  rgba(255, 255, 255);
      constexpr inline color_t RedColor   =  rgba(255, 0, 0);
      constexpr inline color_t GreenColor =  rgba(0, 255, 0);
      constexpr inline color_t BlueColor  =  rgba(0, 0, 255);
   } // namespace colors
} // namespace gfx

#endif