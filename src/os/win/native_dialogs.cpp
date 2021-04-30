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
      Win32ToolTipDialog() :
         m_hToolTip(nullptr),
         m_shown(false) ,
         m_info{0} {}

      ~Win32ToolTipDialog() {
         this->destroy();
      }

      virtual void show(Window* parent) override {
         if(!m_shown) {
            m_shown = true;

            this->create(parent);

            SendMessage(m_hToolTip, TTM_ADDTOOL, 0, (LPARAM)&m_info);
            SendMessage(m_hToolTip, TTM_TRACKACTIVATE, TRUE, (LPARAM)&m_info);
         }
      }

      virtual void hide() override {
         if(m_shown) {
            m_shown = false;

            this->destroy();
         }
      }

      virtual bool isVisible() override {
         return m_shown;
      }

      virtual void setText(const char text[]) override {
         m_text = utils::from_utf8(text);
         m_info.lpszText = &m_text[0];
      }
   private:
      void create(Window* parent) {
         if(!m_hToolTip) {
            HWND hParent = reinterpret_cast<HWND>(parent->handle());
         
            m_hToolTip = CreateWindowEx(WS_EX_TOPMOST,
               TOOLTIPS_CLASS,
               NULL,
               WS_POPUP | TTS_NOPREFIX | TTS_ALWAYSTIP,
               CW_USEDEFAULT, CW_USEDEFAULT,
               CW_USEDEFAULT, CW_USEDEFAULT,
               hParent,
               NULL,
               NULL,
               NULL);

            SetWindowPos(m_hToolTip, HWND_TOPMOST, 0, 0, 0, 0,
               SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);

            m_info.cbSize = sizeof(TOOLINFO);
            m_info.uFlags = TTF_SUBCLASS;
            m_info.hwnd = hParent;
            m_info.lpszText = &m_text[0];

            GetClientRect(hParent, &m_info.rect);
         }
      }

      void destroy() {
         if(m_hToolTip) {
            DestroyWindow(m_hToolTip);
            m_hToolTip = nullptr;
         }
      }

      HWND m_hToolTip;
      TOOLINFO m_info;
      bool m_shown;
      std::wstring m_text;
   };

   ToolTipDialogHandle NativeDialogs::createToolTip()
   {
      return new Win32ToolTipDialog();
   }
} // namespace os