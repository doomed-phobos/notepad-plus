#ifndef _OS_SYSTEM_H
#define _OS_SYSTEM_H
#include "keys.h"
#include "scoped_handle.h"

namespace os
{
   class Window;
   class EventQueue;
   class NativeDialogs;
   class Surface;
   class FontManager;

   class System
   {
   public:
      ~System();

      bool isKeyPressed(KeyCode keycode);

      Window* defaultWindow();
      ScopedHandle<Window> createWindow(int width, int height);
      ScopedHandle<Surface> createSurface(int width, int height);
      ScopedHandle<Surface> loadSurface(const char* filename);

      EventQueue* eventQueue();
      FontManager* fontManager();
      NativeDialogs* nativeDialogs();

      static System* GetInstance();
   private:
      System();

      ScopedHandle<NativeDialogs> m_nativeDialogs;
      ScopedHandle<FontManager> m_fontManager;
      Window* m_defaultWindow;
   };
} // namespace os

#endif