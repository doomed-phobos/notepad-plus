#ifndef _OS_WIN_KEYS_H
#define _OS_WIN_KEYS_H
#include "os/keys.h"

namespace os
{
   bool win_is_key_pressed(KeyCode keycode);
   int keycode_to_win32vk(KeyCode keycode);
   KeyCode win32vk_to_keycode(int vk);
} // namespace os

#endif