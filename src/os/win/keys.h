#ifndef _OS_WIN_KEYS_H
#define _OS_WIN_KEYS_H
#include "os/keys.h"

#include <cassert>
#include <cmath>
#include <windows.h>

namespace os
{
   bool win_is_key_pressed(KeyCode keycode);
   int keycode_to_win32vk(KeyCode keycode);
   KeyCode win32vk_to_keycode(int vk);
   KeyModifiers get_modifiers_from_win32_message();
   
   // Basado en el codigo de LAF (laf/os/win/keys.h)
   class VkToUnicode
   {
   public:
      VkToUnicode() : m_size(0) {
         m_ok = (GetKeyboardState(&m_keystate[0]) ? true: false);
      }

      void toUnicode(int vk, int scancode) {
         m_size =
         ToUnicode(vk, scancode, m_keystate, m_buffer,
                     sizeof(m_buffer)/sizeof(m_buffer[0]), 0);

         if(m_size == 0 ||
           (m_size == 1 && m_buffer[0] == 0 &&
            m_keystate[VK_CONTROL] | m_keystate[VK_LCONTROL] | m_keystate[VK_RCONTROL])) {
            m_keystate[VK_SHIFT] = m_keystate[VK_LSHIFT] = m_keystate[VK_RSHIFT] = 0;
            m_keystate[VK_CONTROL] = m_keystate[VK_LCONTROL] = m_keystate[VK_RCONTROL] = 0;
            m_size =
            ToUnicode(vk, scancode, m_keystate, m_buffer,
                     sizeof(m_buffer)/sizeof(m_buffer[0]), 0);
         }
      }

      operator bool() { return m_ok; }
      int size() const { return std::abs(m_size); }
      LPCWSTR begin() const { return m_buffer; }
      LPCWSTR end() const { return m_buffer+size(); }

      int operator[](const int i) {
         assert(i >= 0 && i < size());
         return m_buffer[i];
      }

      bool isDeadKey() const {
         return m_size == -1;
      }
   private:
      bool m_ok;
      BYTE m_keystate[256];
      WCHAR m_buffer[8];
      int m_size;
   };
} // namespace os

#endif