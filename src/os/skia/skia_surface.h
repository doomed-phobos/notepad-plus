#ifndef _OS_SKIA_SKIA_SURFACE_H
#define _OS_SKIA_SKIA_SURFACE_H
#include "os/surface.h"

#include "SkBitmap.h"
#include "SkCanvas.h"

namespace os
{
   class SkiaSurface : public Surface
   {
   public:
      SkiaSurface();

      virtual void clear(gfx::color_t c) override;
      virtual void create(int width, int height) override;
      
      void draw() {

      }

      virtual void drawLine(const float x0, const float y0,
                            const float x1, const float y1, const gfx::Paint& paint) override;
      void drawCircle(const float cx, const float cy, const float radius,
                              const gfx::Paint& paint) override;
      virtual void drawRect(const gfx::RectF& rc, const gfx::Paint& paint) override;
      virtual void drawText(const char* text, const gfx::PointI& position, const gfx::Paint& paint,
                            const Font& font, TextAlign align = Left_TextAlign) override;
      virtual void drawSurface(const Surface* src, int dstX, int dstY) override;

      virtual void setBlendMode(BlendMode mode) override;

      static Surface* MakeFromFilename(const char* filename);
      void swapBitmap(SkBitmap& other);

      SkBitmap& bitmap();
      virtual int width() const override;
      virtual int height() const override;
   private:
      void rebuild();

      SkBitmap m_bitmap;
      SkCanvas* m_canvas;
      SkPaint m_paint;
   };
} // namespace os

#endif