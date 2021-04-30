#ifndef _OS_SKIA_SKIA_TYPEFACE_H
#define _OS_SKIA_SKIA_TYPEFACE_H
#include "os/typeface.h"
#include "os/font_style.h"
#include "skia_convert.h"

#include "SkTypeface.h"

namespace os
{
   class SkiaTypeface : public Typeface
   {
   public:
      virtual FontStyle fontStyle() const override;
      virtual const char* getFamilyName() const override;

      static SkiaTypeface* MakeFromDefault() {
         return new SkiaTypeface(SkTypeface::MakeDefault());
      }

      static SkiaTypeface* MakeFromFamilyName(const char family[], FontStyle style) {
         return new SkiaTypeface(SkTypeface::MakeFromName(family, details::to_skia(style)));
      }

      static SkiaTypeface* MakeFromFilename(const char filename[]) {
         return new SkiaTypeface(SkTypeface::MakeFromFile(filename));
      }

      sk_sp<SkTypeface> skTypeface() {return m_skTypeface;}
   private:
      SkiaTypeface(sk_sp<SkTypeface>&& skTypeface);

      sk_sp<SkTypeface> m_skTypeface;
   };
} // namespace os

#endif