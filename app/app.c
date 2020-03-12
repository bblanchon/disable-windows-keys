// Disable Windows Keys
// https://bblanchon.github.io/disable-windows-keys
// Copyright (C) 2020  Benoit Blanchon

#include "mainwindow.h"
#include "resource.h"
#include "stdafx.h"

LPCTSTR hookDllName = TEXT("disable-windows-keys-hook.dll");
LPCSTR hookProcName = "HookProc";

void ShowError(HINSTANCE hInstance, LPCTSTR message) {
  TCHAR title[64];
  LoadString(hInstance, IDS_TITLE, title, ARRAYSIZE(title));

  MessageBox(NULL, message, title, MB_OK | MB_ICONWARNING);
}

void ShowErrorF(HINSTANCE hInstance, LPCTSTR format, ...) {
  va_list args;
  va_start(args, format);

  TCHAR message[128];
  _vsntprintf_s(message, ARRAYSIZE(message), _TRUNCATE, format, args);
  ShowError(hInstance, message);

  va_end(args);
}

int WINAPI _tWinMain(__in HINSTANCE hInstance, __in_opt HINSTANCE hPrevInstance,
                     __in LPTSTR lpCmdLine, __in int nShowCmd) {

  UNREFERENCED_PARAMETER(hPrevInstance);

  LANGID langid = (LANGID)_tcstoul(lpCmdLine, NULL, 16);
  SetThreadUILanguage(langid);

  HMODULE hdll = LoadLibrary(hookDllName);
  if (hdll == NULL) {
    ShowErrorF(hInstance, TEXT("Failed to load \"%s\""), hookDllName);
    return 1;
  }

  HOOKPROC hookProc = (HOOKPROC)GetProcAddress(hdll, hookProcName);
  if (hookProc == NULL) {
    ShowError(hInstance, TEXT("Loaded DLL is incompatible"));
    return 1;
  }

  HHOOK hook = SetWindowsHookEx(WH_KEYBOARD_LL, hookProc, hdll, 0);
  if (hookProc == NULL) {
    ShowErrorF(hInstance, TEXT("Failed to install hook (code=%u)"),
               GetLastError());
    return 1;
  }

  RegisterMainWindowClass(hInstance);
  HWND hwnd = CreateMainWindow(hInstance);
  ShowWindow(hwnd, nShowCmd);
  UpdateWindow(hwnd);

  MSG msg;
  while (GetMessage(&msg, NULL, 0, 0)) {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }

  UnhookWindowsHookEx(hook);

  return 0;
}
