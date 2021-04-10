#ifndef _OS_NATIVE_DIALOGS_H
#define _OS_NATIVE_DIALOGS_H
#include <string>
#include <memory>

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
      std::unique_ptr<ToolTipDialog> createToolTip();
   };
} // namespace os

#endif