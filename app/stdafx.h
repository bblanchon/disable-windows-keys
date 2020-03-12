// Disable Windows Keys
// https://bblanchon.github.io/disable-windows-keys
// Copyright (C) 2020  Benoit Blanchon

#pragma once

// Target Windows 7 or above
#define WINVER 0x0602
#define _WIN32_WINNT 0x0602

#define WIN32_LEAN_AND_MEAN
#define VC_EXTRALEAN

#include <assert.h>
#include <tchar.h>
#include <windows.h>
