#include "style.h"

namespace os
{
   Style::Style(long value) :
      m_value(value)
   {}

   long Style::value() const
   {
      return m_value;
   }

   Style Style::operator|(const Style& style) const
   {
      return Style(m_value | style.m_value);
   }
} // namespace os