#ifndef _GFX_PAINT_H
#define _GFX_PAINT_H
#include "color.h"

namespace gfx
{
   class Paint
   {
   public:
      Paint() :
         m_color(colors::NoneColor),
         m_antialias(false),
         m_strokeWidth(1.f),
         m_style(Fill_Style)
      {}

      Paint(color_t color) :
         Paint()
      {m_color = color;}

      enum Style {
         Fill_Style,
         Stroke_Style,
         StrokeAndFill_Style
      };

      color_t getColor() const {return m_color;}
      Style getStyle() const {return m_style;}
      float getStrokeWidth() const {return m_strokeWidth;}
      bool isAntialias() const {return m_antialias;}

      void setColor(const color_t c) {m_color = c;}
      void setStyle(const Style style) {m_style = style;}
      void setStrokeWidth(const float width) {m_strokeWidth = width;}
      void setAntialias(const bool aa) {m_antialias = aa;}
   private:
      color_t m_color;
      Style m_style;
      float m_strokeWidth;
      bool m_antialias;
   };
} // namespace gfx

#endif