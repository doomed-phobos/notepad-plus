#ifndef _UTILS_STRING_H
#define _UTILS_STRING_H
#include <string>

namespace utils
{
   std::string format_to_string(const char* format, ...);

   std::string to_utf8(const std::wstring& wstr);
   std::wstring from_utf8(const std::string& str);
} // namespace utils

#endif