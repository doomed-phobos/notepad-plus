#include "string.h"

#include <vector>
#include <windows.h>

namespace utils
{
   std::string to_utf8(const std::wstring& wstr)
   {
      int required_size = ::WideCharToMultiByte(
         CP_UTF8,
         0,
         wstr.c_str(), (int)wstr.size(),
         nullptr, 0,
         NULL, NULL);

      if(required_size == 0) return std::string();

      std::vector<char> buf(++required_size);

      ::WideCharToMultiByte(
         CP_UTF8,
         0,
         wstr.c_str(), (int)wstr.size(),
         &buf[0], (int)buf.size(),
         NULL, NULL);

      return std::string(&buf[0]);
   }

   std::wstring from_utf8(const std::string& str)
   {
      int required_size =
         ::MultiByteToWideChar(CP_UTF8, 0,
            str.c_str(), (int)str.size(),
            nullptr, 0);

      if(required_size == 0) return std::wstring();

      std::vector<wchar_t> buf(++required_size);

      ::MultiByteToWideChar(CP_UTF8, 0,
         str.c_str(), (int)str.size(),
         &buf[0], required_size);

      return std::wstring(&buf[0]);
   }
} // namespace utils