#include "mainwindow.h"
#include "resource.h"
#include "shared.h"
#include "stdafx.h"

#define FLASH_TIMER_ID 1
#define TEXT_COLOR RGB(255, 255, 255)
#define BACKGROUND_COLOR RGB(0, 121, 216)
#define PADDING_TOP 20
#define PADDING_BOTTOM 20
#define PADDING_RIGHT 30
#define PADDING_LEFT 30
#define MAIN_WINDOW_STYLE                                                      \
  (WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX)

static HFONT hFont;
static HPEN hPen;

static void DrawExplanationText(HDC hdc, RECT *rect, UINT format) {
  HINSTANCE hInstance = GetModuleHandle(NULL);

  TCHAR szExplanation[128];
  size_t nExplanation = LoadString(hInstance, IDS_EXPLANATION, szExplanation,
                                   ARRAYSIZE(szExplanation));

  SetTextColor(hdc, TEXT_COLOR);
  SetBkMode(hdc, TRANSPARENT);
  SelectObject(hdc, hFont);
  DrawText(hdc, szExplanation, nExplanation, rect, format);
}

static void OnPaint(HWND hwnd) {
  PAINTSTRUCT ps;
  HDC hdc = BeginPaint(hwnd, &ps);

  RECT rect;
  GetClientRect(hwnd, &rect);

  rect.top += PADDING_TOP;
  rect.left = PADDING_LEFT;
  rect.bottom -= PADDING_BOTTOM;
  rect.right -= PADDING_RIGHT;
  DrawExplanationText(hdc, &rect, DT_TOP | DT_LEFT | DT_NOCLIP);

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
  wcex.hbrBackground = CreateSolidBrush(BACKGROUND_COLOR);
  wcex.lpszMenuName = 0;
  wcex.lpszClassName = MAIN_WINDOW_CLASS;
  wcex.hIconSm = 0;
  RegisterClassEx(&wcex);

  hFont = CreateFont(32, 0, 0, 0, FW_LIGHT, FALSE, FALSE, FALSE,
                     DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
                     PROOF_QUALITY, FF_SWISS, TEXT("Segoe UI Light"));
}
void MeasureSize(SIZE *sz) {
  RECT rect = {0, 0, 450, 200};

  HDC hdc = GetDC(NULL);
  DrawExplanationText(hdc, &rect, DT_CALCRECT | DT_TOP | DT_LEFT);
  ReleaseDC(NULL, hdc);

  AdjustWindowRect(&rect, MAIN_WINDOW_STYLE, FALSE);

  sz->cx = rect.right - rect.left + PADDING_LEFT + PADDING_RIGHT;
  sz->cy = rect.bottom - rect.top + PADDING_TOP + PADDING_BOTTOM;
}

HWND CreateMainWindow(HINSTANCE hInstance) {
  TCHAR szTitle[32];
  size_t nTitle =
      LoadString(hInstance, IDS_TITLE, szTitle, ARRAYSIZE(szTitle) - 1);
  szTitle[nTitle] = 0;

  SIZE sz;
  MeasureSize(&sz);

  return CreateWindow(MAIN_WINDOW_CLASS, szTitle, MAIN_WINDOW_STYLE,
                      CW_USEDEFAULT, 0, sz.cx, sz.cy, NULL, NULL, hInstance,
                      NULL);
}