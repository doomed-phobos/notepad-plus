#ifndef _OS_EVENT_H
#define _OS_EVENT_H
#include "keys.h"
#include "gfx/point.h"

namespace os
{
   class Window;

   struct Event
   {
      enum Type {
         None_Type,
         Close_Type,
         MouseUp_Type,
         MouseDown_Type,
         MouseMove_Type,
         MouseEnter_Type,
         MouseLeave_Type
      };

      enum MouseButton {
         None_MouseButton,
         Left_MouseButton,
         Middle_MouseButton,
         Right_MouseButton
      };

      Event() : type(None_Type),
                mouseButton(None_MouseButton),
                keyModifiers(kKeyUninitializedModifier) {}

      Type type;
      MouseButton mouseButton;
      Window* window;
      KeyModifiers keyModifiers;
      gfx::PointI mousePosition;
   };
} // namespace os

#endif