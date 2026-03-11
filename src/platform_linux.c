#include "platform.h"
#include <raylib.h>

#if defined(__linux__)

#include <X11/Xlib.h>
#include <X11/Xatom.h>

void Platform_SetDesktopMode(void)
{
    Display *display = (Display *)GetWindowHandle();
    if (!display) return;

    Window window = GetWindowHandle(); // raylib returns X11 Window on Linux

    Atom wmType = XInternAtom(display, "_NET_WM_WINDOW_TYPE", False);
    Atom desktopType = XInternAtom(display, "_NET_WM_WINDOW_TYPE_DESKTOP", False);

    XChangeProperty(display,
                    window,
                    wmType,
                    XA_ATOM,
                    32,
                    PropModeReplace,
                    (unsigned char *)&desktopType,
                    1);

    XFlush(display);
}

#else
void Platform_SetDesktopMode(void) {}
#endif
