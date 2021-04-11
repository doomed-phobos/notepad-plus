#ifndef _OS_SYSTEM_H
#define _OS_SYSTEM_H
#include "keys.h"

namespace os
{
   class Window;
   class EventQueue;
   class NativeDialogs;
   class Surface;

   class System
   {
   public:
      ~System();

      bool isKeyPressed(KeyCode keycode);

      Window* defaultWindow();
      Window* createWindow(int width, int height);
      Surface* createSurface(int width, int height);
      Surface* loadSurface(const char* filename);

      EventQueue* eventQueue();
      NativeDialogs* nativeDialogs();

      static System* GetInstance();
   private:
      System();

      NativeDialogs* m_nativeDialogs;
      Window* m_defaultWindow;
   };
} // namespace os

#endif