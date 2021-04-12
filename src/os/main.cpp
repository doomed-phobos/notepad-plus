#include "os.h"

#include <iostream>
//TODO: Crear fuentes y surface::drawText

static bool isFocus = false;

struct Theme
{
   gfx::color_t background = gfx::colors::None;
   gfx::color_t menu       = gfx::colors::None;
   gfx::color_t page       = gfx::colors::None;

   static Theme Focus() {
      Theme theme;
      theme.background = gfx::colors::Red;
      theme.menu = gfx::rgba(240, 240, 240);
      //theme.page = gfx::rgba(255, 255, 255);

      return theme;
   }

   static Theme NoFocus() {
      Theme theme;
      theme.background = gfx::colors::Blue;
      theme.menu = gfx::rgba(240, 240, 240);
      //theme.page = gfx::rgba(255, 255, 255);

      return theme;
   }
};

void paint(os::Surface* surface)
{
   Theme theme;
   if(isFocus)
      theme = Theme::Focus();
   else
      theme = Theme::NoFocus();

   surface->clear(theme.background);

   surface->drawRect(gfx::RectF(gfx::PointF(0, 0), gfx::PointT(surface->width(), 20)),
      gfx::Paint(theme.menu));
   
   surface->drawRect(gfx::RectF(gfx::PointF(1, 21), gfx::PointF(surface->width()-1, surface->height()-1)),
      gfx::Paint(theme.page));
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
      case os::Event::Close_Type:
         is_run = false;
         break;
      case os::Event::Focus_Type:
         isFocus = ev.isFocus;
         win->invalidate();
         break;
      }
   }
   
   return 0;
}