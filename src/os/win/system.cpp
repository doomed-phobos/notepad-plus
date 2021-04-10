#include "os/system.h"

#include "os/native_dialogs.h"
#include "keys.h"

namespace os
{
   System::System()
   {
      m_nativeDialogs = new NativeDialogs;
   }

   System::~System()
   {
      delete m_nativeDialogs;
   }

   NativeDialogs* System::nativeDialogs()
   {
      return m_nativeDialogs;
   }

   bool System::isKeyPressed(KeyCode keycode)
   {
      return win_is_key_pressed(keycode);
   }

   System* System::GetInstance()
   {
      static System instance;
      return &instance;
   }
} // namespace os
