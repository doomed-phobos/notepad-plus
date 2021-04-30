#include "skia_typeface.h"

namespace os
{
   SkiaTypeface::SkiaTypeface(sk_sp<SkTypeface>&& skTypeface) :
      m_skTypeface(std::move(skTypeface))
   {}

   FontStyle SkiaTypeface::fontStyle() const
   {
      return details::from_skia(m_skTypeface->fontStyle());
   }

   const char* SkiaTypeface::getFamilyName() const
   {
      SkString skFamilyName;
      m_skTypeface->getFamilyName(&skFamilyName);

      return skFamilyName.c_str();
   }
} // namespace os