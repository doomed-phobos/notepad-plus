#include "os/native_dialogs.h"

#include "os/common/tooltip_dialog.h"
#include "os/window.h"

#include <windows.h>
#include <commctrl.h>

namespace os
{
   class Win32ToolTipDialog : public CommonToolTipDialog
   {
   public:
      virtual bool show(Window* parent) override {
         HWND hParent = reinterpret_cast<HWND>(parent->handle());
         m_hToolTip = CreateWindowEx(
            WS_EX_TOPMOST,
            TOOLTIPS_CLASS,
            NULL,
            WS_POPUP | TTS_NOPREFIX | TTS_ALWAYSTIP,
            CW_USEDEFAULT, CW_USEDEFAULT,
            CW_USEDEFAULT, CW_USEDEFAULT,
            hParent,
            NULL,
            GetModuleHandle(nullptr),
            NULL);

         SetWindowPos(m_hToolTip, HWND_TOPMOST, 0, 0, 0, 0,
            SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);

         TOOLINFO ti = {0};
         ti.cbSize = sizeof(TOOLINFO);
         ti.uFlags = TTF_SUBCLASS;
         ti.hwnd = hParent;
         ti.hinst = GetModuleHandle(nullptr);
         ti.lpszText = L"HOLA";

         ti.rect = {0, 0, 100, 100};

         SendMessage(m_hToolTip, TTM_ADDTOOL, 0, (LPARAM)&ti);

         return true;
      }

      virtual void dispose() override {
         delete this;
      }
   private:
      HWND m_hToolTip;
   };

   ToolTipDialog* NativeDialogs::createToolTip()
   {
      return new Win32ToolTipDialog();
   }
} // namespace os