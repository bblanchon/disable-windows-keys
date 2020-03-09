#ifndef _MAINWINDOW_H
#define _MAINWINDOW_H

#define WIN32_LEAN_AND_MEAN
#define VC_EXTRALEAN
#include <windows.h>

void RegisterMainWindowClass(HINSTANCE hInstance);
HWND CreateMainWindow(HINSTANCE hInstance);

#endif