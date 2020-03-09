#define WIN32_LEAN_AND_MEAN
#define VC_EXTRALEAN
#include <assert.h>
#include <tchar.h>
#include <windows.h>

#include "shared.h"

BOOL CALLBACK FlashAppWindowsCallback(HWND hwnd, LPARAM lParam) {
  TCHAR name[64];

  UINT sz = sizeof(name) / sizeof(TCHAR);
  GetWindowText(hwnd, name, 64);
  if (_tcscmp(name, MAIN_WINDOW_TITLE) == 0) {
    PostMessage(hwnd, WM_KEYPRESS_INTERCEPTED, 0, 0);
  }
  return TRUE;
}

LRESULT __declspec(dllexport)
    HookProc(int nCode, WPARAM wParam, LPARAM lParam) {
  if (nCode == HC_ACTION) {
    assert(wParam == WM_KEYDOWN || wParam == WM_KEYUP ||
           wParam == WM_SYSKEYDOWN || wParam == WM_SYSKEYUP);

    DWORD vkCode = ((KBDLLHOOKSTRUCT *)lParam)->vkCode;
    if (vkCode == VK_LWIN || vkCode == VK_RWIN) {
      EnumWindows(FlashAppWindowsCallback, 0);
      return 1;
    }
  }

  return CallNextHookEx(NULL, nCode, wParam, lParam);
}