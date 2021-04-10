#include "keys.h"

#include <windows.h>

namespace os
{
   KeyCode win32vk_to_keycode(int vk)
   {
      static KeyCode keymap[256] = {
         kKeyNil,
         kKeyNil,
         kKeyNil,
         kKeyNil,
         kKeyNil,
         kKeyNil,
         kKeyNil,
         kKeyNil,
         kKeyBackspace,
         kKeyTab,
         kKeyNil,
         kKeyNil,
         kKeyNil,
         kKeyEnter,
         kKeyNil,
         kKeyNil,
         kKeyLShift,
         kKeyLControl,
         kKeyAlt,
         kKeyPause,
         kKeyCapsLock,
         kKeyKana,
         kKeyNil,
         kKeyNil,
         kKeyNil,
         kKeyKanji,
         kKeyNil,
         kKeyEsc,
         kKeyConvert,
         kKeyNoconvert,
         kKeyNil,
         kKeyNil,
         kKeySpace,
         kKeyPageUp,
         kKeyPageDown,
         kKeyEnd,
         kKeyHome,
         kKeyLeft,
         kKeyUp,
         kKeyRight,
         kKeyDown,
         kKeyNil,
         kKeyNil,
         kKeyNil,
         kKeyPrtscr,
         kKeyInsert,
         kKeyDel,
         kKeyNil,
         kKey0,
         kKey1,
         kKey2,
         kKey3,
         kKey4,
         kKey5,
         kKey6,
         kKey7,
         kKey8,
         kKey9,
         kKeyNil,
         kKeyNil,
         kKeyNil,
         kKeyNil,
         kKeyNil,
         kKeyNil,
         kKeyNil,
         kKeyA,
         kKeyB,
         kKeyC,
         kKeyD,
         kKeyE,
         kKeyF,
         kKeyG,
         kKeyH,
         kKeyI,
         kKeyJ,
         kKeyK,
         kKeyL,
         kKeyM,
         kKeyN,
         kKeyO,
         kKeyP,
         kKeyQ,
         kKeyR,
         kKeyS,
         kKeyT,
         kKeyU,
         kKeyV,
         kKeyW,
         kKeyX,
         kKeyY,
         kKeyZ,
         kKeyLWin,
         kKeyRWin,
         kKeyMenu,
         kKeyNil,
         kKeyNil,
         kKey0Pad,
         kKey1Pad,
         kKey2Pad,
         kKey3Pad,
         kKey4Pad,
         kKey5Pad,
         kKey6Pad,
         kKey7Pad,
         kKey8Pad,
         kKey9Pad,
         kKeyAsterisk,
         kKeyPlusPad,
         kKeyNil,
         kKeyMinusPad,
         kKeyNil,
         kKeySlashPad,
         kKeyF1,
         kKeyF2,
         kKeyF3,
         kKeyF4,
         kKeyF5,
         kKeyF6,
         kKeyF7,
         kKeyF8,
         kKeyF9,
         kKeyF10,
         kKeyF11,
         kKeyF12,
         kKeyNil,
         kKeyNil,
         kKeyNil,
         kKeyNil,
         kKeyNil,
         kKeyNil,
         kKeyNil,
         kKeyNil,
         kKeyNil,
         kKeyNil,
         kKeyNil,
         kKeyNil,
         kKeyNil,
         kKeyNil,
         kKeyNil,
         kKeyNil,
         kKeyNil,
         kKeyNil,
         kKeyNil,
         kKeyNil,
         kKeyNumLock,
         kKeyScrLock,
         kKeyNil,
         kKeyNil,
         kKeyNil,
         kKeyNil,
         kKeyNil,
         kKeyNil,
         kKeyNil,
         kKeyNil,
         kKeyNil,
         kKeyNil,
         kKeyNil,
         kKeyNil,
         kKeyNil,
         kKeyNil,
         kKeyLShift,
         kKeyRShift,
         kKeyLControl,
         kKeyRControl,
         kKeyAlt,
         kKeyAltGr,
         kKeyNil,
         kKeyNil,
         kKeyNil,
         kKeyNil,
         kKeyNil,
         kKeyNil,
         kKeyNil,
         kKeyNil,
         kKeyNil,
         kKeyNil,
         kKeyNil,
         kKeyNil,
         kKeyNil,
         kKeyNil,
         kKeyNil,
         kKeyNil,
         kKeyNil,
         kKeyNil,
         kKeyNil,
         kKeyNil,
         kKeyUnknown,
         kKeyEquals,
         kKeyComma,
         kKeyMinus,
         kKeyStop,
         kKeySlash,
         kKeyTilde,
         kKeyNil,
         kKeyNil,
         kKeyNil,
         kKeyNil,
         kKeyNil,
         kKeyNil,
         kKeyNil,
         kKeyNil,
         kKeyNil,
         kKeyNil,
         kKeyNil,
         kKeyNil,
         kKeyNil,
         kKeyNil,
         kKeyNil,
         kKeyNil,
         kKeyNil,
         kKeyNil,
         kKeyNil,
         kKeyNil,
         kKeyNil,
         kKeyNil,
         kKeyNil,
         kKeyNil,
         kKeyNil,
         kKeyNil,
         kKeyOpenbrace,
         kKeyBackslash,
         kKeyClosebrace,
         kKeyQuote,
         kKeyNil,
         kKeyNil,
         kKeyNil,
         kKeyBackslash2,
         kKeyNil,
         kKeyNil,
         kKeyNil,
         kKeyNil,
         kKeyNil,
         kKeyNil,
         kKeyNil,
         kKeyNil,
         kKeyNil,
         kKeyNil,
         kKeyNil,
         kKeyNil,
         kKeyNil,
         kKeyNil,
         kKeyNil,
         kKeyNil,
         kKeyNil,
         kKeyNil,
         kKeyNil,
         kKeyNil,
         kKeyNil,
         kKeyNil,
         kKeyNil,
         kKeyNil,
         kKeyNil,
         kKeyNil,
         kKeyNil,
         kKeyNil,
         kKeyNil,
      };

      if(vk < 0 || vk > 255)
         vk = 0;

      return keymap[vk];
   }

   int keycode_to_win32vk(KeyCode keycode)
   {
      static int init = false;
      static int keymap[kTotalKeyCodes];

      if(!init) {
         init = true;
         for(int i = 0; i < kTotalKeyCodes; i++)
            keymap[i] = 0;
         for(int vk = 0; vk < 256; vk++) {
            KeyCode kc = win32vk_to_keycode(vk);
            if(kc != kKeyNil)
               keymap[kc] = vk; 
         }
      }

      if(keycode < kKeyNil || keycode > kTotalKeyCodes)
         keycode = kKeyNil;

      return keymap[keycode];
   }

   bool win_is_key_pressed(KeyCode keycode)
   {
      int vk = keycode_to_win32vk(keycode);

      if(vk)
         return (GetAsyncKeyState(vk) & 0x8000 ? true : false);
      else
         return false;
   }

   bool win32vk_is_pressed(int vk)
   {
      return GetKeyState(vk) & 0x8000 ? true : false;
   }

   KeyModifiers get_modifiers_from_win32_message()
   {
      int modifiers = kKeyNoneModifier;
      if(win32vk_is_pressed(VK_LSHIFT) ||
         win32vk_is_pressed(VK_RSHIFT))
         modifiers |= kKeyShiftModifier;
      if(win32vk_is_pressed(VK_LCONTROL) ||
         win32vk_is_pressed(VK_RCONTROL))
         modifiers |= kKeyCtrlModifier;
      if(win32vk_is_pressed(VK_LMENU) ||
         win32vk_is_pressed(VK_RMENU))
         modifiers |= kKeyAltModifier;
      if(win32vk_is_pressed(VK_SPACE))
         modifiers |= kKeySpaceModifier;
      if(win32vk_is_pressed(VK_LWIN) ||
         win32vk_is_pressed(VK_RWIN))
         modifiers |= kKeyWinModifier;
      return (KeyModifiers)modifiers;
   }
} // namespace os
