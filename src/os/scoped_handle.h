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
      ScopedHandle() : m_ptr(nullptr), m_refCounter(nullptr) {}
      ScopedHandle(T* ptr) : m_ptr(ptr),
                             m_refCounter(new RefCounter) {}
      
      ScopedHandle(const ScopedHandle& that) {
         m_ptr = that.m_ptr;
         m_refCounter = that.m_refCounter;
         ref();
      }

      ScopedHandle(ScopedHandle&& that) {
         m_ptr = that.release();
         m_refCounter = std::exchange(that.m_refCounter, nullptr);
      }

      ~ScopedHandle() {unref();}

      T* release() {
         return std::exchange(m_ptr, nullptr);
      }

      void reset(T* ptr = nullptr) {
         if(m_ptr != ptr)
            ScopedHandle(ptr).swap(*this);
      }

      void swap(ScopedHandle& that) {
         std::swap(m_ptr, that.m_ptr);
         std::swap(m_refCounter, that.m_refCounter);
      }

      int use_count() const {
         return m_refCounter ? m_refCounter->get() : 0;
      }
      
      T* get() const {return m_ptr;}
      T* operator->() const {return m_ptr;}
      operator bool() const {return m_ptr != nullptr;}

      ScopedHandle& operator=(const ScopedHandle& that) {
         if(m_ptr != that.m_ptr)
            ScopedHandle(that).swap(*this);

         return *this;
      }

      ScopedHandle& operator=(ScopedHandle&& that) {
         if(m_ptr != that.m_ptr)
            ScopedHandle(std::move(that)).swap(*this);

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
         mutable std::atomic_int32_t m_refCount;
      };

      void ref() {
         if(m_refCounter)
            m_refCounter->add();
      }

      void unref() {
         if(m_refCounter && m_refCounter->sub() == 1) {
            delete m_ptr;
            delete m_refCounter;

            m_ptr = nullptr;
            m_refCounter = nullptr;
         }
      }

      RefCounter* m_refCounter;
      T* m_ptr;
   };
} // namespace os

#endif