#include "os.h"

#include <iostream>

os::System* sys = os::System::GetInstance();

void paint(os::Surface* surface)
{
   surface->clear(gfx::rgba(86, 157, 229));

   surface->drawRect(gfx::RectI(gfx::PointI(0, 0), gfx::PointI(surface->width(), 20)),
      gfx::Paint(gfx::rgba(245, 246, 247)));
   
   surface->drawRect(gfx::RectI(gfx::PointI(1, 21), gfx::PointI(surface->width()-1, surface->height()-1)),
      gfx::Paint(gfx::rgba(255, 255, 255)));
   
   surface->drawRect(gfx::RectI(gfx::PointI(surface->width()-16, 21), gfx::PointI(surface->width()-1, surface->height()-1)),
      gfx::Paint(gfx::rgba(240, 240, 240)));

   os::Font font(sys->fontManager()->makeDefault(), 24);
   
   gfx::Paint p;
   p.setColor(gfx::rgba(0, 0, 0));
   p.setAntialias(true);
   p.setStyle(gfx::Paint::Stroke_Style);
   surface->drawText("AAAAA", gfx::PointI(10, 50), p, font);
}

int main()
{
   os::WindowHandle win(sys->createWindow(800, 400));

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
      case os::Event::Close_Type:
         is_run = false;
         break;
      }
   }
   
   return 0;
}