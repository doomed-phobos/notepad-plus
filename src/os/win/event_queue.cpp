#include "os/event_queue.h"

#include <iostream>
#include <windows.h>

namespace os
{
   void processEvent()
   {
      MSG msg;

      while(PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
         TranslateMessage(&msg);
         DispatchMessage(&msg);
      } 
   }

   void EventQueue::getEvents(Event& ev, bool wait)
   {
      if(m_events.empty()) {
         processEvent();

         if(wait) {
            while(m_events.empty()) {
               Sleep(10);
               processEvent();
            }
         }
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