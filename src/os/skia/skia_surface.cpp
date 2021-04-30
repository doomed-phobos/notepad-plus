#include "skia_surface.h"

#include "skia_convert.h"
#include "skia_typeface.h"
#include "os/font.h"

#include "SkCodec.h"
#include "SkStream.h"
#include "SkFont.h"
#include "SkTextUtils.h"

#include <stdexcept>

namespace os
{
   SkiaSurface::SkiaSurface() :
      m_canvas(nullptr)
   {}

   SkiaSurface::~SkiaSurface()
   {
      delete m_canvas;
   }

   void SkiaSurface::create(int width, int height)
   {
      if(!m_bitmap.tryAllocPixels(SkImageInfo::MakeN32(width, height, kOpaque_SkAlphaType)))
         throw std::runtime_error("Error al intentar alojar pixeles!");

      m_bitmap.eraseColor(SK_ColorTRANSPARENT);
      rebuild();
   }

   int SkiaSurface::width() const
   {
      return m_bitmap.width();
   }

   int SkiaSurface::height() const
   {
      return m_bitmap.height();
   }

   void SkiaSurface::clear(gfx::color_t c)
   {
      m_canvas->clear(details::to_skia(c));
   }

   void SkiaSurface::putPixel(gfx::color_t c, int x, int y)
   {
      m_paint.setColor(details::to_skia(c));
      m_canvas->drawPoint(SkIntToScalar(x), SkIntToScalar(y), m_paint);
   }

   void SkiaSurface::drawCircle(const float cx, const float cy, const float radius,
                              const gfx::Paint& paint)
   {
      details::to_skia(m_paint, paint);
      m_canvas->drawCircle(cx, cy, radius, m_paint);
   }

   void SkiaSurface::drawLine(const float x0, const float y0,
                            const float x1, const float y1, const gfx::Paint& paint)
   {
      details::to_skia(m_paint, paint);
      m_canvas->drawLine(x0, y0, x1, y1, m_paint);
   }

   void SkiaSurface::drawRect(const gfx::RectF& rc, const gfx::Paint& paint)
   {
      if(rc.isEmpty()) return;

      details::to_skia(m_paint, paint);

      if(paint.getStyle() == gfx::Paint::Stroke_Style)
         m_canvas->drawRect(details::to_skia_stroke(rc), m_paint);
      else
         m_canvas->drawRect(details::to_skia(rc), m_paint);
   }

   void SkiaSurface::drawText(const char text[], const gfx::PointF& position, const gfx::Paint& paint,
                              const Font& font, TextAlign align)
   {
      Typeface* typeface = font.typeface();
      sk_sp<SkTypeface> skTypeface(typeface ? reinterpret_cast<SkiaTypeface*>(typeface)->skTypeface() :
         SkTypeface::MakeDefault());

      SkFont skFont(skTypeface, font.size(), font.scaleX(), font.skewX());
      skFont.setEdging((SkFont::Edging)font.edging());

      details::to_skia(m_paint, paint);

      SkTextUtils::DrawString(
         m_canvas,
         text,
         position.x, position.y,
         skFont,
         m_paint,
         (SkTextUtils::Align)align
      );
   }

   void SkiaSurface::drawSurface(const Surface* src, int dstX, int dstY)
   {
      SkRect srcRect = SkRect::MakeXYWH(0.f, 0.f, SkIntToScalar(width()), SkIntToScalar(height()));
      SkRect dstRect = SkRect::MakeXYWH(SkIntToScalar(dstX), SkIntToScalar(dstY),
                                        SkIntToScalar(width()), SkIntToScalar(height()));

      SkPaint p;
      p.setBlendMode(SkBlendMode::kSrc);

      m_canvas->drawBitmapRect(
         ((SkiaSurface*)src)->bitmap(), srcRect, dstRect, &p
      );
   }

   void SkiaSurface::setBlendMode(BlendMode mode)
   {
      switch(mode) {
      case DstOver_BlendMode: m_paint.setBlendMode(SkBlendMode::kDstOver); break;
      case SrcOver_BlendMode: m_paint.setBlendMode(SkBlendMode::kSrcOver); break;
      case Xor_BlendMode:     m_paint.setBlendMode(SkBlendMode::kXor);     break;
      }
   }

   Surface* SkiaSurface::MakeFromFilename(const char* filename)
   {
      FILE* file = fopen(filename, "rb");

      std::unique_ptr<SkCodec> codec = SkCodec::MakeFromStream(std::unique_ptr<SkFILEStream>(new SkFILEStream(filename)));
      if(!codec) return nullptr;

      SkImageInfo info = codec->getInfo()
         .makeColorType(kN32_SkColorType)
         .makeAlphaType(kPremul_SkAlphaType);
      
      SkBitmap bmp;
      if(!bmp.tryAllocPixels(info)) return nullptr;
      bmp.eraseColor(SK_ColorTRANSPARENT);

      const SkCodec::Result result = codec->getPixels(info, bmp.getPixels(), bmp.rowBytes());
      if(result != SkCodec::Result::kSuccess) return nullptr;

      SkiaSurface* surface = new SkiaSurface;
      surface->swapBitmap(bmp);
      return surface;
   }

   void SkiaSurface::swapBitmap(SkBitmap& other)
   {
      m_bitmap.swap(other);
      rebuild();
   }

   SkBitmap& SkiaSurface::bitmap()
   {
      return m_bitmap;
   }

   void SkiaSurface::rebuild()
   {
      delete m_canvas;
      m_canvas = new SkCanvas(m_bitmap);
   }
} // namespace os