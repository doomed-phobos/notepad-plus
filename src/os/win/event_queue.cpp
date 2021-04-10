#include "os/event_queue.h"

#include <windows.h>

namespace os
{
   void EventQueue::getEvents(Event& ev, bool wait)
   {
      MSG msg;
      BOOL res;

      while(m_events.empty()) {
         if(ev.type != Event::None_Type)
            wait = false;

         if(wait)
            res = ::GetMessage(&msg, nullptr, 0, 0);
         else
            res = ::PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE);


         if(res) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
         }else if(!wait)
            break;
      }

      if(m_events.empty()) {
         ev.type = Event::None_Type;
      }else {
         ev = m_events.front();
         m_events.pop();
      }
   }

   void EventQueue::queueEvent(const Event& ev)
   {
      m_events.push(ev);
   }

   EventQueue* EventQueue::GetInstance()
   {
      static EventQueue instance;

      return &instance; 
   }
} // namespace os