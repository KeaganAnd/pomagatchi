#include "platform.h"

#if defined(__APPLE__)
#import <Cocoa/Cocoa.h>
#import <QuartzCore/QuartzCore.h> // Needed for kCGDesktopWindowLevel
#include <raylib.h>

void Platform_SetDesktopMode(void) {
  void *handle = GetWindowHandle();
  if (!handle)
    return;

  NSWindow *window = (__bridge NSWindow *)handle;

  // Set window at desktop level (behind everything)
  [window setLevel:(NSInteger)kCGDesktopWindowLevel];

  // Make it visible on all spaces and stationary
  [window setCollectionBehavior:NSWindowCollectionBehaviorCanJoinAllSpaces |
                                NSWindowCollectionBehaviorStationary];

  // Optional: ignore mouse clicks
  // [window setIgnoresMouseEvents:YES];
}
#else
void Platform_SetDesktopMode(void) {}
#endif
