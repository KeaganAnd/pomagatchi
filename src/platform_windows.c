#include "platform.h"
#include <raylib.h>

#if defined(_WIN32)

#include <windows.h>

void Platform_SetDesktopMode(void)
{
    HWND hwnd = (HWND)GetWindowHandle();
    if (!hwnd) return;

    // Remove from taskbar
    LONG exStyle = GetWindowLong(hwnd, GWL_EXSTYLE);
    exStyle |= WS_EX_TOOLWINDOW;
    exStyle &= ~WS_EX_APPWINDOW;
    SetWindowLong(hwnd, GWL_EXSTYLE, exStyle);

    // Send to bottom
    SetWindowPos(hwnd,
                 HWND_BOTTOM,
                 0, 0, 0, 0,
                 SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
}

#else
void Platform_SetDesktopMode(void) {}
#endif
