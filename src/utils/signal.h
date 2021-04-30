#ifndef _UTILS_SIGNAL_H
#define _UTILS_SIGNAL_H
#include "slot.h"

#include <vector>

namespace utils
{
   template<typename R, typename... Args>
   class Signal_base
   {
   public:
      typedef Slot<R, Args...> slot_t;
      typedef std::vector<slot_t*> list_t;

      Signal_base() {}
      ~Signal_base() {
         disconnectAll();
      }

      slot_t* connect(R(*function)(Args...)) {
         return addSlot(new Slot_fun<R, Args...>(function));
      }

      template<class T>
      slot_t* connect(T* t, R(T::*function)(Args...)) {
         return addSlot(new Slot_mem<T, R, Args...>(t, function));
      }

      void disconnectAll() {
         for(typename list_t::iterator it = m_slots.begin();
             it != m_slots.end(); it++)
             delete *it;

         m_slots.clear();
      }
   private:
      slot_t* addSlot(slot_t* slot) {
         m_slots.push_back(slot);
         return slot;
      }
   protected:
      list_t m_slots;
   };

   template<typename R, typename... Args>
   class Signal : public Signal_base<R, Args...>
   {
   public:
      R operator()(Args&&... args) {
         R result = R();

         for(typename Signal_base<R, Args...>::list_t::iterator it = m_slots.begin();
             it != m_slots.end(); it++) {
            slot_t* slot = *it;
            result = (*slot)(std::forward<Args>(args)...);
         }

         return result;
      }
   };

   template<typename... Args>
   class Signal<void, Args...> : public Signal_base<void, Args...>
   {
   public:
      void operator()(Args&&... args) {
         for(typename Signal_base<void, Args...>::list_t::iterator it = m_slots.begin();
             it != m_slots.end(); it++) {
            slot_t* slot = *it;
            (*slot)(std::forward<Args>(args)...);
         }
      }
   };
} // namespace utils

#endif