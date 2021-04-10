#ifndef _OS_SYSTEM_H
#define _OS_SYSTEM_H
#include "keys.h"

#include <memory>

namespace os
{
   class Window;
   class EventQueue;
   class NativeDialogs;

   class System
   {
   public:
      ~System();

      bool isKeyPressed(KeyCode keycode);

      std::unique_ptr<Window> createWindow(int width, int height);

      EventQueue* eventQueue();
      NativeDialogs* nativeDialogs();

      static System* GetInstance();
   private:
      System();

      NativeDialogs* m_nativeDialogs;
   };
} // namespace os

#endif