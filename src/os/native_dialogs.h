#ifndef _OS_NATIVE_DIALOGS_H
#define _OS_NATIVE_DIALOGS_H
#include "scoped_handle.h"

namespace os
{
   class Window;

   class ToolTipDialog
   {
   public:
      virtual ~ToolTipDialog() {}

      virtual void show(Window* parent) = 0;
      virtual void hide() = 0;
      
      virtual bool isVisible() = 0;

      virtual void setText(const char text[]) = 0;
   };

   typedef ScopedHandle<ToolTipDialog> ToolTipDialogHandle;

   class NativeDialogs
   {
   public:
      ToolTipDialogHandle createToolTip();
   };
} // namespace os

#endif