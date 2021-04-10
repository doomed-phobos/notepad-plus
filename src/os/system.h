#ifndef _OS_SYSTEM_H
#define _OS_SYSTEM_H
#include "keys.h"

namespace os
{
   class Window;
   class NativeDialogs;

   class System
   {
   public:
      ~System();

      bool isKeyPressed(KeyCode keycode);

      NativeDialogs* nativeDialogs();

      static System* GetInstance();
   private:
      System();

      NativeDialogs* m_nativeDialogs;
   };
} // namespace os

#endif