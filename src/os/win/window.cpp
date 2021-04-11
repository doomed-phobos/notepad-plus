#include "window.h"

#include "utils/string.h"
#include "keys.h"

#include <cassert>
#include <stdexcept>
#include <CommCtrl.h>
#include <windowsx.h>

#define SIGN(value) value < 0 ? -value : value

namespace os
{
   class WinWindow::WindowClass
   {
   public:
      static void Register() {
         WNDCLASSEX wcex = {0};
         HINSTANCE hInstance = GetHModule();

         if(GetClassInfoEx(hInstance, str_WndClass, &wcex)) return;

         wcex.cbSize = sizeof(WNDCLASSEX);
         wcex.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
         wcex.hInstance = hInstance;
         wcex.lpfnWndProc = &GlobalWindowProc;
         wcex.lpszClassName = str_WndClass;
         wcex.style = CS_DBLCLKS;
      
         if(!RegisterClassEx(&wcex))
            throw std::runtime_error("Error al registar clase");
      }

      static HINSTANCE GetHModule() {
         return GetModuleHandle(nullptr);
      }

      static constexpr const wchar_t* str_WndClass = L"Window";
   };

   WinWindow::WinWindow(int width, int height) :
      m_hwnd(nullptr),
      m_hcursor(nullptr),
      m_mouseHover(false),
      m_surface(new SkiaSurface)
   {
      WindowClass::Register();

      m_hwnd = CreateWindowEx(
         WS_EX_APPWINDOW | WS_EX_ACCEPTFILES,
         WindowClass::str_WndClass,
         L"",
         WS_OVERLAPPEDWINDOW,
         CW_USEDEFAULT, CW_USEDEFAULT,
         width, height,
         nullptr,
         nullptr,
         WindowClass::GetHModule(),
         this
      );

      if(!m_hwnd)
         throw std::runtime_error("Error al crear ventana");

      SetWindowLongPtr(m_hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));
   }

   WinWindow::~WinWindow()
   {
      if(m_hwnd)
         DestroyWindow(m_hwnd);
   }

   void WinWindow::setTitle(const std::string& str)
   {
      SetWindowText(m_hwnd, utils::from_utf8(str).c_str());
   }

   void WinWindow::setVisible(bool visible)
   {
      if(visible) {
         ShowWindow(m_hwnd, SW_SHOWNORMAL);
         UpdateWindow(m_hwnd);
      }else {
         ShowWindow(m_hwnd, SW_HIDE);
      }
   }

   void WinWindow::setMouseCursor(MouseCursor cursor)
   {
      switch(cursor) {
      case No_MouseCursor:         /*No hacer nada*/ break;
      case Arrow_MouseCursor:      m_hcursor = LoadCursor(NULL, IDC_ARROW);     break;
      case IBeam_MouseCursor:      m_hcursor = LoadCursor(NULL, IDC_IBEAM);     break;
      case Wait_MouseCursor:       m_hcursor = LoadCursor(NULL, IDC_WAIT);      break;
      case Cross_MouseCursor:      m_hcursor = LoadCursor(NULL, IDC_CROSS);     break;
      case SizeNWSE_MouseCursor:   m_hcursor = LoadCursor(NULL, IDC_SIZENWSE);  break;
      case SizeNESW_MouseCursor:   m_hcursor = LoadCursor(NULL, IDC_SIZENESW);  break;
      case SizeWE_MouseCursor:     m_hcursor = LoadCursor(NULL, IDC_SIZEWE);    break;
      case SizeNS_MouseCursor:     m_hcursor = LoadCursor(NULL, IDC_SIZENS);    break;
      case SizeAll_MouseCursor:    m_hcursor = LoadCursor(NULL, IDC_SIZEALL);   break;
      case Help_MouseCursor:       m_hcursor = LoadCursor(NULL, IDC_HELP);      break;
      case Hand_MouseCursor:       m_hcursor = LoadCursor(NULL, IDC_HAND);      break;
      case Forbidden_MouseCursor:  m_hcursor = LoadCursor(NULL, IDC_NO);        break;
      }

      SetCursor(m_hcursor);
   }

   void WinWindow::captureMouse()
   {
      if(GetCapture() != m_hwnd)
         SetCapture(m_hwnd);
   }

   void WinWindow::releaseMouse()
   {
      if(GetCapture() == m_hwnd)
         ReleaseCapture();
   }

   Window::NativeHandle WinWindow::handle()
   {
      return reinterpret_cast<NativeHandle>(m_hwnd);
   }

   LRESULT CALLBACK WinWindow::GlobalWindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
   {
      WinWindow* win = nullptr;
      if(msg == WM_NCCREATE) {
         win = reinterpret_cast<WinWindow*>(reinterpret_cast<LPCREATESTRUCT>(lParam)->lpCreateParams);

         if(win && win->m_hwnd == nullptr)
            win->m_hwnd = hWnd;
      }else {
         win = reinterpret_cast<WinWindow*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
      }

      if(win) {
         assert(win->m_hwnd == hWnd);
         return win->wndProc(msg, wParam, lParam);
      }

      return DefWindowProc(hWnd, msg, wParam, lParam);
   }

   LRESULT WinWindow::wndProc(UINT msg, WPARAM wParam, LPARAM lParam)
   {
      switch(msg) {
      case WM_SETCURSOR:
         if(LOWORD(lParam) == HTCLIENT) {
            SetCursor(m_hcursor);
            return TRUE;
         }
         break;
      case WM_CLOSE: {
         Event ev;
         ev.type = Event::Close_Type;

         queueEvent(ev);
         return 0;
      }
         break;
      case WM_LBUTTONDBLCLK:
      case WM_MBUTTONDBLCLK:
      //case WM_XBUTTONDBLCLK:
      case WM_RBUTTONDBLCLK: {
         Event ev;
         mouseEvent(ev, lParam);
         ev.type = Event::MouseDoubleClick_Type;
         ev.mouseButton = (msg == WM_LBUTTONDBLCLK ? Event::Left_MouseButton    :
                           msg == WM_MBUTTONDBLCLK ? Event::Middle_MouseButton  :
                           msg == WM_RBUTTONDBLCLK ? Event::Right_MouseButton   :
                           Event::None_MouseButton);

         queueEvent(ev);
      }
         break;
      case WM_LBUTTONDOWN:
      case WM_MBUTTONDOWN:
      // WM_XBUTTONDOWN
      case WM_RBUTTONDOWN: {
         Event ev;
         mouseEvent(ev, lParam);
         ev.type = Event::MouseDown_Type;
         ev.mouseButton = (msg == WM_LBUTTONDOWN ? Event::Left_MouseButton    :
                           msg == WM_MBUTTONDOWN ? Event::Middle_MouseButton  :
                           msg == WM_RBUTTONDOWN ? Event::Right_MouseButton   :
                           Event::None_MouseButton);

         queueEvent(ev);
      }
         break;
      case WM_LBUTTONUP:
      case WM_MBUTTONUP:
      case WM_RBUTTONUP: {
         Event ev;
         mouseEvent(ev, lParam);
         ev.type = Event::MouseUp_Type;
         ev.mouseButton = (msg == WM_LBUTTONUP ? Event::Left_MouseButton   :
                           msg == WM_MBUTTONUP ? Event::Middle_MouseButton :
                           msg == WM_RBUTTONUP ? Event::Right_MouseButton  :
                           Event::None_MouseButton);

         queueEvent(ev);
      }
         break;
      case WM_MOUSEMOVE: {
         Event ev;
         mouseEvent(ev, lParam);

         if(!m_mouseHover) {
            m_mouseHover = true;
            ev.type = Event::MouseEnter_Type;

            queueEvent(ev);

            TRACKMOUSEEVENT tme;
            tme.cbSize = sizeof(TRACKMOUSEEVENT);
            tme.dwFlags = TME_LEAVE;
            tme.hwndTrack = m_hwnd;
            _TrackMouseEvent(&tme);
         }

         ev.type = Event::MouseMove_Type;
         queueEvent(ev);
      }
         break;
      case WM_NCMOUSEMOVE:
      case WM_MOUSELEAVE: {
         if(m_mouseHover) {
            m_mouseHover = false;

            Event ev;
            ev.type = Event::MouseLeave_Type;
            ev.keyModifiers = get_modifiers_from_win32_message();
            queueEvent(ev);
         }
      }
         break;
      case WM_MOUSEWHEEL: {
         POINT pos = {GET_X_LPARAM(lParam),
                      GET_Y_LPARAM(lParam)};
         ScreenToClient(m_hwnd, &pos);

         Event ev;
         ev.type = Event::MouseWheel_Type;
         ev.keyModifiers = get_modifiers_from_win32_message();
         ev.mousePosition = gfx::PointF((float)pos.x, (float)pos.y);

         int delta = GET_WHEEL_DELTA_WPARAM(wParam);
         if(std::abs(delta) >= WHEEL_DELTA)
            delta /= WHEEL_DELTA;
         else
            delta = SIGN(delta);

         ev.wheelDelta = delta;
         queueEvent(ev);
      }
         break;
      case WM_PAINT: {
         PAINTSTRUCT ps;
         HDC hDC = BeginPaint(m_hwnd, &ps);
         
         OnPaint(m_surface.get());

         const SkBitmap& bmp = m_surface->bitmap();
         BITMAPINFO bmi = {0};
         bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
         bmi.bmiHeader.biBitCount = 32;
         bmi.bmiHeader.biWidth = bmp.width();
         bmi.bmiHeader.biHeight = -bmp.height();
         bmi.bmiHeader.biPlanes = 1;
         bmi.bmiHeader.biCompression = BI_RGB;

         assert(bmp.width() * bmp.bytesPerPixel() == bmp.rowBytes());
         
         StretchDIBits(hDC, 0, 0, bmp.width(), bmp.height(),
                       0, 0, bmp.width(), bmp.height(),
                       bmp.getPixels(), &bmi, DIB_RGB_COLORS, SRCCOPY);

         EndPaint(m_hwnd, &ps);
      }
         break;
      case WM_SIZE: {
         int width = LOWORD(lParam);
         int height = HIWORD(lParam);

         Event ev;
         ev.type = Event::Resize_Type;
         queueEvent(ev);

         m_surface->create(width, height);

         InvalidateRect(m_hwnd, NULL, FALSE);

         return 0;
      }
         break;
      case WM_SYSKEYDOWN:
      case WM_KEYDOWN: {
         int vk = wParam;
         int scancode = (lParam >> 16) & 0xff;
         bool sendMsg = true;
         KeyCode keycode = win32vk_to_keycode(vk);

         if(keycode >= kKeyFirstModifierKeyCode &&
            lParam & (1 << 30)) return 0;

         Event ev;
         ev.type = Event::KeyDown_Type;
         ev.keyModifiers = get_modifiers_from_win32_message();
         ev.keyCode = keycode;

         VkToUnicode tu;
         if(tu) {
            tu.toUnicode(vk, scancode);
            if(tu.isDeadKey()) {
               ev.deadKey = true;
               ev.unicodeChr = tu[0];
            }else if(tu.size() > 0) {
               sendMsg = false;
               for(int chr : tu) {
                  ev.unicodeChr = chr;
                  queueEvent(ev);
               }
            }
         }

         if(sendMsg)
            queueEvent(ev);

         return 0;
      }
         break;
      case WM_SYSKEYUP:
      case WM_KEYUP: {
         Event ev;
         ev.type = Event::KeyUp_Type;
         ev.keyModifiers = get_modifiers_from_win32_message();
         ev.keyCode = win32vk_to_keycode(wParam);
         ev.unicodeChr = 0;
         queueEvent(ev);

         return 0;
      }
         break;
      case WM_DROPFILES: {
      }
         break;
      }

      return DefWindowProc(m_hwnd, msg, wParam, lParam);
   }

   void WinWindow::queueEvent(Event& ev)
   {
      ev.window = this;
      EventQueue::GetInstance()->queueEvent(ev);
   }

   void WinWindow::mouseEvent(Event& ev, LPARAM lParam)
   {
      ev.keyModifiers = get_modifiers_from_win32_message();
      ev.mousePosition = gfx::PointI(GET_X_LPARAM(lParam),
                                     GET_Y_LPARAM(lParam));
   }
} // namespace os