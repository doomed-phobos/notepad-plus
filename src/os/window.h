#ifndef _OS_WINDOW_H
#define _OS_WINDOW_H
#include <string>

namespace os
{
   class Window
   {
   public:
      typedef void* NativeHandle;

      virtual void setTitle(const std::string& title) = 0;
      virtual void setVisible(bool visible) = 0;

      virtual void captureMouse() = 0;
      virtual void releaseMouse() = 0;

      virtual NativeHandle handle() = 0;
   };
} // namespace os

#endif