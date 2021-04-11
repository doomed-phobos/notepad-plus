#ifndef _OS_NATIVE_DIALOGS_H
#define _OS_NATIVE_DIALOGS_H
#include <string>

namespace os
{
   class Window;

   class ToolTipDialog
   {
   public:
      virtual ~ToolTipDialog() {}

      virtual bool show(Window* parent) = 0;
      virtual void close() = 0;
      
      virtual bool isVisible() = 0;

      virtual void setText(const std::string& text) = 0;
   };

   class NativeDialogs
   {
   public:
      ToolTipDialog* createToolTip();
   };
} // namespace os

#endif