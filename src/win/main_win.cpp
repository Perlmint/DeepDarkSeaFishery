#include <windows.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_syswm.h>

bool initWindow(SDL_Window *window)
{
  //transparency starts here
  SDL_SysWMinfo info;
  SDL_VERSION(&info.version);
  if (SDL_GetWindowWMInfo(window, &info))
  {
    HWND hwnd = info.info.win.window;
    SetWindowLong(hwnd, GWL_EXSTYLE, GetWindowLong(hwnd, GWL_EXSTYLE) |WS_EX_LAYERED);
    SetLayeredWindowAttributes(hwnd, RGB(0,0,0), (255 * 70)/100, LWA_COLORKEY);
  }

  return true;
}
