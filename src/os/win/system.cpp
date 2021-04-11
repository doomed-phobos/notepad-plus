#include "os/system.h"

#include "os/native_dialogs.h"
#include "os/event_queue.h"
#include "window.h"
#include "keys.h"

#include <stdexcept>
#include <CommCtrl.h>

namespace os
{
   System::System()
   {
      m_nativeDialogs = new NativeDialogs;

      INITCOMMONCONTROLSEX icex;
      icex.dwSize = sizeof(INITCOMMONCONTROLSEX);
      icex.dwICC = ICC_TAB_CLASSES;
      
      if(!InitCommonControlsEx(&icex))
         throw std::runtime_error("InitCommonControlsEx failed!");
   }

   System::~System()
   {
      delete m_nativeDialogs;
   }

   Window* System::createWindow(int width, int height)
   {
      Window* win(new WinWindow(width, height));
      if(!m_defaultWindow)
         m_defaultWindow = win;

      return win;
   }

   Surface* createSurface(int width, int height)
   {
      SkiaSurface* surface = new SkiaSurface;
      surface->create(width, height);

      return surface;
   }

   Surface* loadSurface(const char* filename)
   {
      return SkiaSurface::MakeFromFilename(filename);
   }

   EventQueue* System::eventQueue()
   {
      return EventQueue::GetInstance();
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
      //TODO: Verificar si esto no causa algun tipo de daño
      static System instance;

      return &instance;
   }
} // namespace os
