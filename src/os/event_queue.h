#ifndef _OS_EVENT_QUEUE_H
#define _OS_EVENT_QUEUE_H
#include "event.h"

#include <queue>

namespace os
{
   class EventQueue
   {
   public:
      void getEvents(Event& ev, bool wait);
      void queueEvent(const Event& ev);

      static EventQueue* GetInstance();
   private:
      EventQueue() = default;

      std::queue<Event> m_events;
   };
} // namespace os

#endif