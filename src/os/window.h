#ifndef _OS_WINDOW_H
#define _OS_WINDOW_H

namespace os
{
   class Window
   {
   public:
      typedef void* NativeHandle;

      void setVisible(bool visible);

      NativeHandle handle();
   };
} // namespace os

#endif