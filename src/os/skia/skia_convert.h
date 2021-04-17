#ifndef _OS_SKIA_SKIA_CONVERT_H
#define _OS_SKIA_SKIA_CONVERT_H
#include "gfx/paint.h"
#include "gfx/rect.h"
#include "os/font_style.h"

#include "SkPaint.h"
#include "SkRect.h"
#include "SkFontStyle.h"

#include <algorithm>

namespace os::details
{
   inline SkColor to_skia(const gfx::color_t c)
   {
      return SkColorSetARGB(gfx::getA(c), gfx::getR(c), gfx::getG(c), gfx::getB(c));
   }

   inline void to_skia(SkPaint& skPaint, const gfx::Paint& paint)
   {
      static_assert(gfx::Paint::Fill_Style == SkPaint::kFill_Style &&
                    gfx::Paint::Stroke_Style == SkPaint::kStroke_Style &&
                    gfx::Paint::StrokeAndFill_Style == SkPaint::kStrokeAndFill_Style,
                    "Los estilos de gfx::Paint no coinciden con los de SkPaint");
      
      skPaint.setStyle((SkPaint::Style)paint.getStyle());
      skPaint.setColor(to_skia(paint.getColor()));
      skPaint.setStrokeWidth(paint.getStrokeWidth());
      skPaint.setAntiAlias(paint.isAntialias());
   }

   inline SkRect to_skia(const gfx::RectF& rc)
   {
      return SkRect::MakeXYWH(rc.x, rc.y, rc.width, rc.height);
   }

   inline SkRect to_skia_stroke(const gfx::RectF& rc)
   {
      return SkRect::MakeXYWH(rc.x, rc.y,
                              std::max(0.f, rc.width),
                              std::max(0.f, rc.height));
   }

   inline SkFontStyle to_skia(const FontStyle& style)
   {
      return SkFontStyle((int)style.weight(),
         (int)style.width(),
         (SkFontStyle::Slant)style.slant());
   }

   inline FontStyle from_skia(const SkFontStyle& skStyle)
   {
      return FontStyle((FontStyle::Weight)skStyle.weight(),
         (FontStyle::Width)skStyle.width(),
         (FontStyle::Slant)skStyle.slant());
   }
} // namespace os::details

#endif