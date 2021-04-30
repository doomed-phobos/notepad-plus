#ifndef _OS_WINDOW_H
#define _OS_WINDOW_H
#include "utils/signal.h"
#include "gfx/size.h"
#include "mouse_cursor.h"
#include "scoped_handle.h"
#include "style.h"

namespace os
{
   class Surface;

   class Window
   {
   public:
      typedef void* NativeHandle;

      struct Styles {
         static const Style None;
         static const Style Default;
         static const Style WithCaption;
         static const Style WithSystemMenu;
         static const Style Minimizable;
         static const Style Maximizable;
         static const Style Resizable;
         static const Style InitiallyMinimized;
         static const Style InitiallyMaximized;
      };

      virtual ~Window() {}

      virtual void setTitle(const char title[]) = 0;
      virtual void setVisible(bool visible) = 0;
      virtual void setMouseCursor(MouseCursor cursor) = 0;

      virtual void invalidate() = 0;
      virtual void captureMouse() = 0;
      virtual void releaseMouse() = 0;

      virtual Surface* surface() = 0;
      virtual NativeHandle handle() = 0;
      virtual gfx::SizeI clientSize() const = 0;

      utils::Signal<void, Surface*> OnPaint;
   };

   typedef ScopedHandle<Window> WindowHandle;
} // namespace os

#endif