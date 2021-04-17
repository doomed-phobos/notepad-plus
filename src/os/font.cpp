#include "font.h"

#include <utility>

#define DefaultFontSize 12.f

namespace os
{
   Font::Font(TypefaceHandle typeface, float size, float scaleX, float skewX) :
      m_typeface(std::move(typeface)),
      m_size(size),
      m_scaleX(scaleX),
      m_skewX(skewX),
      m_edging(SubpixelAntiAlias_Edging) {}
   
   Font::Font(TypefaceHandle typeface, float size) :
      Font(std::move(typeface), size, 1.f, 0.f) {}
   
   Font::Font(TypefaceHandle typeface) :
      Font(std::move(typeface), DefaultFontSize, 1.f, 0.f) {}

   void Font::setEdging(Edging edging)
   {
      m_edging = edging;
   }
   
   Typeface* Font::typeface() const
   {
      return m_typeface.get();
   }
   
   Font::Edging Font::edging() const
   {
      return m_edging;
   }

   float Font::size() const
   {
      return m_size;
   }

   float Font::scaleX() const
   {
      return m_scaleX;
   }

   float Font::skewX() const
   {
      return m_skewX;
   }
} // namespace os