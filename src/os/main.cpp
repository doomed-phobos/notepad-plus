#include "os.h"

#include <iostream>
//TODO: Crear fuentes y surface::drawText
void paint(os::Surface* surface)
{
   surface->clear(gfx::rgba(86, 157, 229));
}

int main()
{
   os::System* sys(os::System::GetInstance());
   std::unique_ptr<os::Window> win(sys->createWindow(800, 400));
   win->OnPaint.connect(paint);

   win->setTitle("notepad+");
   win->setMouseCursor(os::Arrow_MouseCursor);
   win->setVisible(true);

   os::EventQueue* queue = sys->eventQueue();

   bool is_run = true;
   while(is_run) {
      os::Event ev;
      queue->getEvents(ev, true);

      switch(ev.type) {
      case os::Event::KeyDown_Type:
         std::wcout << (wchar_t)ev.unicodeChr;
         break;
      case os::Event::Close_Type:
         is_run = false;
         break;
      }
   }
   
   return 0;
}