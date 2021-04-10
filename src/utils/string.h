#ifndef _UTILS_STRING_H
#define _UTILS_STRING_H
#include <string>

namespace utils
{
   std::string to_utf8(const std::wstring& wstr);
   std::wstring from_utf8(const std::string& str);
} // namespace utils

#endif