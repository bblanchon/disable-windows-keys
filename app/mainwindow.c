#include "mainwindow.h"
#include "resource.h"
#include "shared.h"
#include "stdafx.h"

#define FLASH_TIMER_ID 1

static HFONT hFont;

static void OnPaint(HWND hwnd) {
  PAINTSTRUCT ps;
  HDC hdc = BeginPaint(hwnd, &ps);

  RECT rect;
  GetClientRect(hwnd, &rect);

  SelectObject(hdc, hFont);

  HINSTANCE hInstance = GetModuleHandle(NULL);

  TCHAR szExplanation[128];
  size_t nExplanation = LoadString(hInstance, IDS_EXPLANATION, szExplanation,
                                   ARRAYSIZE(szExplanation));

  rect.top = 20;
  rect.left = 40;
  DrawText(hdc, szExplanation, nExplanation, &rect, DT_TOP | DT_LEFT);

  EndPaint(hwnd, &ps);
}

static void OnTimer(HWND hwnd, UINT_PTR uTimerID) {
  KillTimer(hwnd, uTimerID);

  FLASHWINFO flashinfo = {sizeof(FLASHWINFO)};
  flashinfo.hwnd = hwnd;
  flashinfo.dwFlags = FLASHW_STOP;
  flashinfo.uCount = 0;
  FlashWindowEx(&flashinfo);
}

static void OnKeypressIntercepted(HWND hwnd) {
  FLASHWINFO flashinfo = {sizeof(FLASHWINFO)};
  flashinfo.hwnd = hwnd;
  flashinfo.dwFlags = FLASHW_ALL;
  flashinfo.uCount = 1;
  flashinfo.dwTimeout = 1;
  FlashWindowEx(&flashinfo);
  SetTimer(hwnd, FLASH_TIMER_ID, 1000, NULL);
}

static LRESULT CALLBACK WindowProc(HWND hwnd, UINT message, WPARAM wParam,
                                   LPARAM lParam) {

  switch (message) {
  case WM_KEYPRESS_INTERCEPTED:
    OnKeypressIntercepted(hwnd);
    break;

  case WM_TIMER:
    OnTimer(hwnd, wParam);
    break;

  case WM_PAINT:
    OnPaint(hwnd);
    break;

  case WM_DESTROY:
    PostQuitMessage(0);
    break;

  default:
    return DefWindowProcW(hwnd, message, wParam, lParam);
  }
  return 0;
}

void RegisterMainWindowClass(HINSTANCE hInstance) {
  WNDCLASSEX wcex = {sizeof(WNDCLASSEX)};
  wcex.style = CS_HREDRAW | CS_VREDRAW;
  wcex.lpfnWndProc = WindowProc;
  wcex.cbClsExtra = 0;
  wcex.cbWndExtra = 0;
  wcex.hInstance = hInstance;
  wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPICON));
  wcex.hCursor = 0;
  wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
  wcex.lpszMenuName = 0;
  wcex.lpszClassName = MAIN_WINDOW_CLASS;
  wcex.hIconSm = 0;
  RegisterClassEx(&wcex);

  hFont =
      CreateFont(30, 0, 0, 0, 0, TRUE, 0, 0, 0, 0, 0, 0, 0, TEXT("Segoe UI"));
}

HWND CreateMainWindow(HINSTANCE hInstance) {
  TCHAR szTitle[32];
  size_t nTitle =
      LoadString(hInstance, IDS_TITLE, szTitle, ARRAYSIZE(szTitle) - 1);
  szTitle[nTitle] = 0;

  return CreateWindow(MAIN_WINDOW_CLASS, szTitle,
                      (WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU |
                       WS_MINIMIZEBOX | WS_MAXIMIZEBOX),
                      CW_USEDEFAULT, 0, 450, 150, NULL, NULL, hInstance, NULL);
}