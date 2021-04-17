#include "skia_font_manager.h"

#include "skia_typeface.h"

namespace os
{
   SkiaFontManager::SkiaFontManager() :
      m_manager(SkFontMgr::RefDefault()) {}

   int SkiaFontManager::countFamilies() const
   {
      return m_manager->countFamilies();
   }

   std::string SkiaFontManager::getFamilyName(int index) const
   {
      SkString familyName;
      m_manager->getFamilyName(index, &familyName);

      return familyName.c_str();
   }

   TypefaceHandle SkiaFontManager::makeDefault()
   {
      return SkiaTypeface::MakeFromDefault();
   }

   TypefaceHandle SkiaFontManager::makeFromFamilyName(const char* family, FontStyle fontStyle)
   {
      return SkiaTypeface::MakeFromFamilyName(family, fontStyle);
   }

   TypefaceHandle SkiaFontManager::makeFromFilename(const char* filename)
   {
      return SkiaTypeface::MakeFromFilename(filename);
   }
} // namespace os