#include "string.h"

#include <cstdarg>
#include <vector>
#include <windows.h>

namespace utils
{
   std::string format_to_string(const char* format, ...)
   {
      va_list args;
      va_start(args, format);
      std::size_t required_size = vsnprintf(nullptr, 0, format, args);
      std::vector<char> buf(++required_size);

      vsnprintf(&buf[0], buf.size(), format, args);
      
      va_end(args);

      return std::string(&buf[0]);
   }

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