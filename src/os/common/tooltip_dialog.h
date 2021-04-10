#ifndef _OS_COMMON_NATIVE_DIALOGS
#define _OS_COMMON_NATIVE_DIALOGS
#include "os/native_dialogs.h"

namespace os
{
   class CommonToolTipDialog : public ToolTipDialog
   {
   public:
      virtual void setText(const std::string& text) override {
         m_text = text;
      }
   protected:
      std::string m_text;
   };
} // namespace os

#endif