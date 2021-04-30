#ifndef _OS_STYLE_H
#define _OS_STYLE_H

namespace os
{
   class Style
   {
   public:
      explicit Style(long value);

      long value() const;

      Style operator|(const Style& style) const;
   private:
      long m_value;
   };
} // namespace os

#endif