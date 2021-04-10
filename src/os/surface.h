#ifndef _OS_SURFACE_H
#define _OS_SURFACE_H
#include "gfx/point.h"

namespace os
{
   class Surface
   {
   public:
      enum BlendMode {
         DstOver_BlendMode,
         SrcOver_BlendMode,
         Xor_BlendMode
      };

      virtual ~Surface() {}

      /*virtual int width() const = 0;
      virtual int height() const = 0;

      virtual void clear(gfx::color_t c) = 0;

      virtual void drawLine(const float x0, const float y0,
                            const float x1, const float y1, const gfx::Paint& paint) = 0;
      void drawLine(const gfx::PointF& pt0, const gfx::PointF& pt1,
                    const gfx::Paint& paint) {
         drawLine(pt0.x, pt0.y, pt1.x, pt1.y, paint);
      }
      void drawLine(const gfx::PointI& pt0, const gfx::PointI& pt1,
                    const gfx::Paint& paint) {
         drawLine((float)pt0.x, (float)pt0.y,
                  (float)pt1.x, (float)pt1.y, paint);
      }

      virtual void drawCircle(const float cx, const float cy, const float radius,
                              const gfx::Paint& paint) = 0;
      void drawCircle(const gfx::PointF& center, const float radius,
                      const gfx::Paint& paint) {
         drawCircle(center.x, center.y, radius, paint);
      }

      virtual void drawRect(const gfx::RectF& rc, const gfx::Paint& paint) = 0;
      virtual void drawSurface(const Surface* src, int dstX, int dstY) = 0;
   
      virtual void setBlendMode(BlendMode mode) = 0;*/
   };
} // namespace os

#endif