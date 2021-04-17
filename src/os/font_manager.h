#ifndef _OS_FONT_MANAGER_H
#define _OS_FONT_MANAGER_H
#include "typeface.h"

#include <string>

namespace os
{
   class FontStyle;

   class FontManager
   {
   public:
      virtual ~FontManager() {}

      virtual int countFamilies() const = 0;
      virtual std::string getFamilyName(int index) const = 0;

      virtual TypefaceHandle makeFromFilename(const char* filename) = 0;
      virtual TypefaceHandle makeFromFamilyName(const char* name, FontStyle fontStyle) = 0;
      virtual TypefaceHandle makeDefault() = 0;
   };
} // namespace os

#endif