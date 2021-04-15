#ifndef _OS_SCOPED_HANDLE_H
#define _OS_SCOPED_HANDLE_H
#include <atomic>
#include <utility>

namespace os
{
   template<typename T>
   class ScopedHandle
   {
   public:
      ScopedHandle(T* ptr = nullptr) : m_ptr(ptr), m_refCount(new RefCounter) {}
      ScopedHandle(const ScopedHandle& that) {
         m_ptr = that.get();
         m_refCount = that.m_refCount;
         ref();
      }
      ScopedHandle(ScopedHandle&& that) : m_ptr(that.release()) {}

      ~ScopedHandle() {unref();}

      T* release() {
         return std::exchange(m_ptr, nullptr);
      }

      void reset(T* ptr = nullptr) {
         if(m_ptr != ptr) {
            m_ptr = ptr;
            unref();
         }
      }

      int use_count() const {
         return m_refCount->get();
      }
      
      T* get() const {return m_ptr;}
      T* operator->() const {return m_ptr;}

      ScopedHandle& operator=(const ScopedHandle& that) {
         if(m_ptr != that.m_ptr) {
            reset(that.m_ptr);
            m_refCount = that.m_refCount;
            ref();
         }

         return *this;
      }
   private:
      class RefCounter {
      public:
         RefCounter() : m_refCount(1) {}

         int add() const {
            return m_refCount.fetch_add(1, std::memory_order_relaxed);
         }

         int sub() const {
            return m_refCount.fetch_add(-1, std::memory_order_relaxed);
         }

         int get() const {
            return m_refCount.load(std::memory_order_acquire);
         }
      private:
         mutable std::atomic_int m_refCount;
      };

      void ref() {
         m_refCount->add();
      }

      void unref() {
         if(m_refCount->sub() == 1)
            safe_dispose();
      }

      inline void safe_dispose() {
         delete m_refCount;
         if(m_ptr)
            delete m_ptr;
      }

      RefCounter* m_refCount;
      T* m_ptr;
   };
} // namespace os

#endif