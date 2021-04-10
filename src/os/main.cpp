#include "os.h"

#include <iostream>

class A
{
public:
   A() {
      utils::Slot_mem<A, void, int> a(this, &A::foo);

      a(12);
   }

   void foo(int a) {
      printf("FOO: %d\n", a);
   }
};

int main()
{
   /*
   os::System* sys(os::System::GetInstance());
   std::unique_ptr<os::Window> win(sys->createWindow(800, 400));

   win->setTitle("notepad+");
   win->setVisible(true);

   os::EventQueue* queue = sys->eventQueue();

   bool is_run = true;
   while(is_run) {
      os::Event ev;
      queue->getEvents(ev, true);

      switch(ev.type) {
      case os::Event::MouseDown_Type:
         break;
      case os::Event::Close_Type:
         is_run = false;
         break;
      }
   }*/

   A a;
   
   return 0;
}