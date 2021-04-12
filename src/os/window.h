#ifndef _OS_WINDOW_H
#define _OS_WINDOW_H
#include "utils/signal.h"
#include "mouse_cursor.h"

#include <string>

namespace os
{
   class Surface;

   class Window
   {
   public:
      typedef void* NativeHandle;

      virtual void setTitle(const std::string& title) = 0;
      virtual void setVisible(bool visible) = 0;
      virtual void setMouseCursor(MouseCursor cursor) = 0;

      virtual void invalidate() = 0;
      virtual void captureMouse() = 0;
      virtual void releaseMouse() = 0;

      virtual NativeHandle handle() = 0;

      utils::Signal<void, Surface*> OnPaint;
   };
} // namespace os

#endif