#ifndef _OS_NATIVE_DIALOGS_H
#define _OS_NATIVE_DIALOGS_H
#include <string>

namespace os
{
   class Window;

   class ToolTipDialog
   {
   public:
      virtual void setText(const std::string& text) = 0;
      virtual bool show(Window* parent) = 0;
      virtual void dispose() = 0;
   };

   class NativeDialogs
   {
   public:
      ToolTipDialog* createToolTip();
   };
} // namespace os

#endif