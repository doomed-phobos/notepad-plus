#ifndef _UTILS_SLOT_H
#define _UTILS_SLOT_H
#include <utility>

namespace utils
{
   template<typename R, typename... Args>
   class Slot
   {
   public:
      virtual ~Slot() {}
      virtual R operator()(Args&&... args) = 0;
   };

   template<typename R, typename... Args>
   class Slot_fun : public Slot<R, Args...>
   {
   public:
      Slot_fun(R(*function)(Args...)) : m_function(function) {}

      virtual R operator()(Args&&... args) override {
         if(m_function)
            return m_function(std::forward<Args>(args)...);
      }
   private:
      R(*m_function)(Args...);
   };

   template<typename... Args>
   class Slot_fun<void, Args...> : public Slot<void, Args...>
   {
   public:
      Slot_fun(void(*function)(Args...)) : m_function(function) {}

      virtual void operator()(Args&&... args) override {
         if(m_function)
            m_function(std::forward<Args>(args)...);
      }
   private:
      void(*m_function)(Args...);      
   };

   template<class T, typename R, typename... Args>
   class Slot_mem : public Slot<R, Args...>
   {
   public:
      Slot_mem(T* t, R(T::*function)(Args...)) : m_t(t),
                                                 m_function(function) {}

      virtual R operator()(Args&&... args) override {
         if(m_function)
            return (m_t->*m_function)(std::forward<Args>(args)...);
      }
   private:
      T* m_t;
      R(T::*m_function)(Args...);
   };

   template<class T, typename... Args>
   class Slot_mem<T, void, Args...> : public Slot<void, Args...>
   {
   public:
      Slot_mem(T* t, void(T::*function)(Args...)) : m_t(t),
                                                 m_function(function) {}

      virtual void operator()(Args&&... args) override {
         if(m_function)
            (m_t->*m_function)(std::forward<Args>(args)...);
      }
   private:
      T* m_t;
      void(T::*m_function)(Args...);
   };
} // namespace utils

#endif