#ifndef _OS_TYPEFACE_H
#define _OS_TYPEFACE_H
#include "scoped_handle.h"

namespace os
{
   class FontStyle;

   class Typeface
   {
   public:
      virtual ~Typeface() {}

      virtual FontStyle fontStyle() const = 0;
      virtual const char* getFamilyName() const = 0;
   };

   typedef ScopedHandle<Typeface> TypefaceHandle;
} // namespace os

#endif