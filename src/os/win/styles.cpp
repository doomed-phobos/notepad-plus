#include "os/window.h"

#include <windows.h>

namespace os
{
   const Style Window::Styles::None                = Style(WS_POPUP);
   const Style Window::Styles::WithCaption         = Style(WS_CAPTION);
   const Style Window::Styles::WithSystemMenu      = Style(WS_SYSMENU);
   const Style Window::Styles::Minimizable         = Style(WS_MINIMIZEBOX);
   const Style Window::Styles::Maximizable         = Style(WS_MAXIMIZEBOX);
   const Style Window::Styles::Resizable           = Style(WS_SIZEBOX);
   const Style Window::Styles::InitiallyMinimized  = Style(WS_MINIMIZE);
   const Style Window::Styles::InitiallyMaximized  = Style(WS_MAXIMIZE);
   const Style Window::Styles::Default = 
      Window::Styles::WithCaption |
      Window::Styles::WithSystemMenu |
      Window::Styles::Minimizable |
      Window::Styles::Maximizable |
      Window::Styles::Resizable;
} // namespace os