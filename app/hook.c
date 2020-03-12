// Disable Windows Keys
// https://bblanchon.github.io/disable-windows-keys
// Copyright (C) 2020  Benoit Blanchon

#include "shared.h"
#include "stdafx.h"

BOOL CALLBACK FlashAppWindowsCallback(HWND hwnd, LPARAM lParam) {
  UNREFERENCED_PARAMETER(lParam);

  TCHAR szClassName[64];
  GetClassName(hwnd, szClassName, ARRAYSIZE(szClassName));

  if (_tcscmp(szClassName, MAIN_WINDOW_CLASS) == 0) {
    PostMessage(hwnd, WM_KEYPRESS_INTERCEPTED, 0, 0);
  }
  return TRUE;
}

LRESULT CALLBACK HookProc(int nCode, WPARAM wParam, LPARAM lParam) {
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