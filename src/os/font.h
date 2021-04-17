#ifndef _OS_FONT_H
#define _OS_FONT_H
#include "typeface.h"
#include "font_style.h"

namespace os
{
   class Font
   {
   public:
      enum Edging {
         Alias_Edging,
         AntiAlias_Edging,
         SubpixelAntiAlias_Edging
      };

      Font(TypefaceHandle typeface);
      Font(TypefaceHandle typeface, float size);
      Font(TypefaceHandle typeface, float size, float scaleX, float skewX);

      void setEdging(Edging edging);

      Typeface* typeface() const;
      Edging edging() const;
      float size() const;
      float scaleX() const;
      float skewX() const;
   private:
      TypefaceHandle m_typeface;
      Edging m_edging;
      float m_size;
      float m_scaleX;
      float m_skewX;
   };
} // namespace os

#endif