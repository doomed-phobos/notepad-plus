#ifndef _OS_EVENT_H
#define _OS_EVENT_H
#include "keys.h"
#include "gfx/point.h"
#include "utils/paths.h"

namespace os
{
   class Window;

   struct Event
   {
      enum Type {
         None_Type,
         Close_Type,
         Resize_Type,
         DropFiles_Type,
         Focus_Type,
         MouseUp_Type,
         MouseDown_Type,
         MouseDoubleClick_Type,
         MouseMove_Type,
         MouseEnter_Type,
         MouseLeave_Type,
         MouseWheel_Type,
         KeyDown_Type,
         KeyUp_Type
      };

      enum MouseButton {
         None_MouseButton,
         Left_MouseButton,
         Middle_MouseButton,
         Right_MouseButton
      };

      Event() : type(None_Type),
                window(nullptr),
                mouseButton(None_MouseButton),
                wheelDelta(0.0),
                keyModifiers(kKeyUninitializedModifier),
                keyCode(kKeyNil),
                deadKey(false),
                unicodeChr(0) {}


      Type type;
      Window* window;
      utils::paths files;
      MouseButton mouseButton;
      gfx::PointI mousePosition;
      double wheelDelta;
      KeyModifiers keyModifiers;
      KeyCode keyCode;
      bool deadKey;
      wchar_t unicodeChr;
      bool isFocus;
   };
} // namespace os

#endif