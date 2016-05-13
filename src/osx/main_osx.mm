#import <AppKit/AppKit.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_syswm.h>
#include <SDL2/SDL_opengl.h>

#include "platform.h"

bool initWindow(SDL_Window *window)
{
  //transparency starts here
  SDL_SysWMinfo info;
  SDL_VERSION(&info.version);
  if (!SDL_GetWindowWMInfo(window, &info))
  {
    return false;
  }

  NSWindow *ccWindow = info.info.cocoa.window ;
  // always on top
  [ccWindow setLevel:NSFloatingWindowLevel];

  // position and size of window
  const auto &size = [NSScreen mainScreen].frame.size;
  SDL_SetWindowSize(window, size.width, GameHeight);
  SDL_SetWindowPosition(window, 0, size.height - GameHeight);

  [ccWindow setStyleMask:NSBorderlessWindowMask];
  [ccWindow setBackingType:NSBackingStoreBuffered];
  [ccWindow setHasShadow:NO];
  [ccWindow setAlphaValue:1.0f];
  [ccWindow setOpaque:NO];
  [ccWindow setBackgroundColor:[NSColor clearColor]];

  return true;
}

bool initRenderer(SDL_Renderer *renderer)
{
  NSOpenGLContext *nscontext;
  nscontext = (NSOpenGLContext*)SDL_GL_GetCurrentContext();

  GLint aValue = 0;
  [nscontext setValues:&aValue forParameter:NSOpenGLCPSurfaceOpacity];
  
  return true;
}