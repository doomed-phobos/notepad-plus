#ifndef _OS_SKIA_SKIA_FONT_MANAGER_H
#define _OS_SKIA_SKIA_FONT_MANAGER_H
#include "os/font_manager.h"

#include "os/font.h"
#include "os/font_style.h"

#include "SkFontMgr.h"

namespace os
{
   class SkiaFontManager : public FontManager
   {
   public:
      SkiaFontManager();

      virtual int countFamilies() const override;
      virtual std::string getFamilyName(int index) const override;

      virtual TypefaceHandle makeDefault() override;
      virtual TypefaceHandle makeFromFamilyName(const char family[], FontStyle fontStyle) override;
      virtual TypefaceHandle makeFromFilename(const char filename[]) override;
   private:
      sk_sp<SkFontMgr> m_manager;
   };
} // namespace os

#endif