#include "mainwindow.h"
#include <windows.h>

LPCTSTR hookDllName = TEXT("disable-windows-keys-hook.dll");

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                     LPSTR lpCmdLine, int nCmdShow) {
  RegisterMainWindowClass(hInstance);
  HWND hwnd = CreateMainWindow(hInstance);
  ShowWindow(hwnd, nCmdShow);
  UpdateWindow(hwnd);

  HMODULE hdll = LoadLibrary(hookDllName);
  HOOKPROC hookProc = (HOOKPROC)GetProcAddress(hdll, "HookProc");
  int err = GetLastError();
  HHOOK hook = SetWindowsHookExW(WH_KEYBOARD_LL, hookProc, hdll, 0);

  MSG msg;
  while (GetMessage(&msg, NULL, 0, 0)) {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }

  UnhookWindowsHookEx(hook);

  return 0;
}
