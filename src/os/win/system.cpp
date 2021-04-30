#include "os/system.h"

#include "os/native_dialogs.h"
#include "os/event_queue.h"
#include "os/skia/skia_surface.h"
#include "os/skia/skia_font_manager.h"
#include "window.h"
#include "keys.h"

#include <stdexcept>
#include <CommCtrl.h>

namespace os
{
   System::System() :
      m_nativeDialogs(new NativeDialogs),
      m_fontManager(new SkiaFontManager),
      m_defaultWindow(nullptr)
   {
      INITCOMMONCONTROLSEX icex;
      icex.dwSize = sizeof(INITCOMMONCONTROLSEX);
      icex.dwICC = ICC_TAB_CLASSES;
      
      if(!InitCommonControlsEx(&icex))
         throw std::runtime_error("InitCommonControlsEx failed!");
   }

   System::~System()
   {
   }

   Window* System::defaultWindow()
   {
      return m_defaultWindow;
   }

   WindowHandle System::createWindow(int width, int height, const Style& style)
   {
      Window* win(new WinWindow(width, height, style));
      if(!m_defaultWindow)
         m_defaultWindow = win;

      return win;
   }

   ScopedHandle<Surface> System::createSurface(int width, int height)
   {
      SkiaSurface* surface = new SkiaSurface;
      surface->create(width, height);

      return surface;
   }

   ScopedHandle<Surface> System::loadSurface(const char filename[])
   {
      return SkiaSurface::MakeFromFilename(filename);
   }

   EventQueue* System::eventQueue()
   {
      return EventQueue::GetInstance();
   }

   NativeDialogs* System::nativeDialogs()
   {
      return m_nativeDialogs.get();
   }

   FontManager* System::fontManager()
   {
      return m_fontManager.get();
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
