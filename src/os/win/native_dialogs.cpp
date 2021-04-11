#include "os/native_dialogs.h"

#include "os/window.h"
#include "utils/string.h"

#include <windows.h>
#include <commctrl.h>

//TODO: Cambiar esto a un archivo de manifest
#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

namespace os
{
   class Win32ToolTipDialog : public ToolTipDialog
   {
   public:
      Win32ToolTipDialog() : m_hToolTip(nullptr) ,
                             m_shown(false) {}
      ~Win32ToolTipDialog() {this->close();}

      virtual bool show(Window* parent) override {
         if(!m_hToolTip) {
            HWND hParent = reinterpret_cast<HWND>(parent->handle());
            HINSTANCE hInst = GetModuleHandle(nullptr);

            m_hToolTip = CreateWindowEx(WS_EX_TOPMOST, TOOLTIPS_CLASS, NULL, 
                                          WS_POPUP | TTS_NOPREFIX | TTS_ALWAYSTIP, 
                                          CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, 
                                          hParent, NULL, hInst, NULL);

            SetWindowPos(m_hToolTip, HWND_TOPMOST, 0, 0, 0, 0, 
                  SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);

            std::wstring text = utils::from_utf8(m_text);
            TOOLINFO ti = {0};
            ti.cbSize = sizeof(TOOLINFO);
            ti.uFlags = TTF_SUBCLASS;
            ti.hwnd = hParent;
            ti.hinst = hInst;
            ti.lpszText = &text[0];
            
            GetClientRect (hParent, &ti.rect);

            if(!SendMessage(m_hToolTip, TTM_ADDTOOL, 0, (LPARAM)&ti))
               return false;

            if(!SendMessage(m_hToolTip, TTM_TRACKACTIVATE, TRUE, (LPARAM)&ti))
               return false;
            
            m_shown = true;

            return true;
         }

         if(m_shown)
            return true;

         return false;
      }

      virtual void close() override {
         if(m_hToolTip) {
            DestroyWindow(m_hToolTip);
            m_hToolTip = nullptr;
            m_shown = false;
         }
      }

      virtual bool isVisible() override {
         return m_hToolTip != nullptr;
      }

      virtual void setText(const std::string& text) override {
         m_text = text;
      }
   private:
      HWND m_hToolTip;
      bool m_shown;
      std::string m_text;
   };

   ToolTipDialog* NativeDialogs::createToolTip()
   {
      return new Win32ToolTipDialog();
   }
} // namespace os